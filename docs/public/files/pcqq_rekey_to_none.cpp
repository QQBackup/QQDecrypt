#include <iostream>
#include <cstdio>
#include <Windows.h>
#include <iomanip>
#include <vector>   
#include <string>   
#include <cstdlib>  
#include <tchar.h>  
#include <stdexcept> 

// SigScan code from https://github.com/aikar/SigScan , copyright belongs to original authors.
// Minor modifications for safety, clarity, and TCHAR compatibility.
DWORD_PTR SigScan(const char* szPattern, int offset = 0); 
bool InitializeSigScan(DWORD ProcessID, const TCHAR* szModule); 
void FinalizeSigScan();

#include <tlhelp32.h>

// --- Globals for SigScan ---
namespace SigScanInternal {
    bool bIsLocal = false;
    bool bInitialized = false;
    BYTE* moduleMemory = NULL;
    DWORD_PTR baseAddress = NULL;
    DWORD modSize = NULL;
}
// --- End Globals ---


// --- SigScan Struct ---
typedef struct checks {
    short start;
    short size;
    checks() : start(0), size(0) {}
    checks(short sstart, short ssize) : start(sstart), size(ssize) {}
} checks;
// --- End SigScan Struct ---

// --- SigScan Implementation ---
// (SigScan, InitializeSigScan, FinalizeSigScan implementations remain the same as the previous version)
// ... (Paste the SigScan, InitializeSigScan, FinalizeSigScan functions from the previous answer here) ...
// --- SigScan Implementation (Copied from previous answer) ---
// Accepts TCHAR* for Module name for Windows API compatibility
bool InitializeSigScan(DWORD ProcessID, const TCHAR* Module) {
    using namespace SigScanInternal;

    FinalizeSigScan(); // Clean up previous state if any

    MODULEENTRY32 uModule;
    SecureZeroMemory(&uModule, sizeof(MODULEENTRY32));
    uModule.dwSize = sizeof(MODULEENTRY32);

    // Use TH32CS_SNAPMODULE32 for potentially better compatibility if targeting 32-bit specifically
    HANDLE hModuleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
    if (hModuleSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: CreateToolhelp32Snapshot failed. Code: " << GetLastError() << std::endl;
        return false;
    }

    bool foundModule = false;
    // Use Module32First/Next which work with TCHAR versions of MODULEENTRY32 based on UNICODE define
    for (BOOL bModule = Module32First(hModuleSnapshot, &uModule); bModule; bModule = Module32Next(hModuleSnapshot, &uModule)) {
        // Use TCHAR-safe case-insensitive comparison
        if (!_tcsicmp(uModule.szModule, Module)) { // <-- FIX: Use _tcsicmp
            baseAddress = (DWORD_PTR)uModule.modBaseAddr; // Use DWORD_PTR
            modSize = uModule.modBaseSize;

            if (GetCurrentProcessId() == ProcessID) {
                bIsLocal = true;
                moduleMemory = (BYTE*)baseAddress; 
                bInitialized = true;
                foundModule = true;
            }
            else {
                bIsLocal = false;
                moduleMemory = new (std::nothrow) BYTE[modSize]; 
                if (!moduleMemory) {
                    std::cerr << "Error: Failed to allocate memory for module snapshot." << std::endl;
                    break; 
                }

                HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, ProcessID);
                if (hProcess) {
                    if (ReadProcessMemory(hProcess, (LPCVOID)baseAddress, moduleMemory, modSize, NULL)) {
                        bInitialized = true;
                        foundModule = true;
                    }
                    else {
                        std::cerr << "Error: ReadProcessMemory failed. Code: " << GetLastError() << std::endl;
                        delete[] moduleMemory;
                        moduleMemory = NULL;
                    }
                    CloseHandle(hProcess);
                }
                else {
                    std::cerr << "Error: OpenProcess failed. Code: " << GetLastError() << std::endl;
                    delete[] moduleMemory; 
                    moduleMemory = NULL;
                }
            }
            break; 
        }
    }

    CloseHandle(hModuleSnapshot);

    if (!foundModule && !bInitialized) {
        std::wcerr << L"Error: Module '" << Module << L"' not found or could not be read." << std::endl;
        return false;
    }
    return bInitialized;
}

void FinalizeSigScan() {
    using namespace SigScanInternal;
    if (moduleMemory) {
        if (!bIsLocal) {
            delete[] moduleMemory;
        }
        moduleMemory = NULL;
        bInitialized = false;
        baseAddress = NULL; 
        modSize = NULL; 
        bIsLocal = false;
    }
}
DWORD_PTR SigScan(const char* szPattern, int offset) {
    using namespace SigScanInternal;
    if (!bInitialized || !moduleMemory || !baseAddress || !szPattern) {
        std::cerr << "SigScan Error: Not initialized or invalid parameters." << std::endl;
        return NULL;
    }

    size_t patternLength = strlen(szPattern); 
    if (patternLength < 2) {
        std::cerr << "SigScan Error: Pattern too short." << std::endl;
        return NULL;
    }
    bool dereference = true;
    int ptrOffset = 0; 
    bool offsetFromStart = false;

    if (strncmp(szPattern, "##", 2) == 0) {
        dereference = false;
        szPattern += 2;
        patternLength -= 2;
        offsetFromStart = true; 
        ptrOffset = offset;     
    }
    else if (strncmp(szPattern, "@@", 2) == 0) {
        dereference = false;
        szPattern += 2;
        patternLength -= 2;
    }

    if (patternLength == 0 || patternLength % 2 != 0) {
        std::cerr << "SigScan Error: Pattern length invalid after prefix handling." << std::endl;
        return NULL;
    }

    size_t bufferSize = patternLength / 2; // Use size_t
    if (!offsetFromStart) {
        // Default: offset is from the end of the pattern bytes
        ptrOffset = bufferSize + offset;
    }


    // Use std::vector for automatic memory management and safety
    std::vector<unsigned char> buffer(bufferSize);
    std::vector<bool> mask(bufferSize); // true = wildcard, false = compare byte

    // Create the buffer and mask
    for (size_t i = 0; i < bufferSize; ++i) {
        char high = szPattern[i * 2];
        char low = szPattern[(i * 2) + 1];

        if (high == '?' && (low == '?' || low == '\0')) { // Handle single '?' or "??" as wildcard
            buffer[i] = 0x00; // Value doesn't matter
            mask[i] = true;   // Mark as wildcard
            if (low == '?') { /* already handled by loop increment */ }
            else { /* single '?' - technically malformed pattern but treat as wildcard */ }
        }
        else if (high == 'X' && low == 'X' && !offsetFromStart && (bufferSize - i >= 4)) {
            ptrOffset = i + offset; // User offset is relative to 'XX' start
            buffer[i] = 0x00; mask[i] = true; i++; // XX
            buffer[i] = 0x00; mask[i] = true; i++; // XX
            buffer[i] = 0x00; mask[i] = true; i++; // XX
            buffer[i] = 0x00; mask[i] = true;      // XX
        }
        else {
            // Convert hex chars to byte (allow lower case hex)
            unsigned char byteVal = 0;
            if (high >= '0' && high <= '9') byteVal = (high - '0') << 4;
            else if (high >= 'A' && high <= 'F') byteVal = (high - 'A' + 10) << 4;
            else if (high >= 'a' && high <= 'f') byteVal = (high - 'a' + 10) << 4;
            else { std::cerr << "SigScan Error: Invalid pattern character '" << high << "'" << std::endl; return NULL; }

            if (low >= '0' && low <= '9') byteVal |= (low - '0');
            else if (low >= 'A' && low <= 'F') byteVal |= (low - 'A' + 10);
            else if (low >= 'a' && low <= 'f') byteVal |= (low - 'a' + 10);
            else { std::cerr << "SigScan Error: Invalid pattern character '" << low << "'" << std::endl; return NULL; }

            buffer[i] = byteVal;
            mask[i] = false; // Not a wildcard
        }
    }


    // Iterate the Module memory
    DWORD matchCount = 0;
    DWORD_PTR lastAddress = NULL; // Use DWORD_PTR
    // Ensure pointer arithmetic stays within bounds
    if (modSize < bufferSize) return NULL; // Avoid underflow/wrap-around
    BYTE* endAddr = moduleMemory + modSize - bufferSize;

    for (BYTE* addr = moduleMemory; addr <= endAddr; ++addr) {
        bool found = true;
        for (size_t k = 0; k < bufferSize; ++k) {
            if (!mask[k] && buffer[k] != addr[k]) { // If not wildcard and bytes don't match
                found = false;
                break;
            }
        }

        if (found) {
            matchCount++;
            // Calculate the address based on the match location and offset logic
            BYTE* resultPtrLocation = addr + ptrOffset;

            // Ensure the calculated pointer location is within the module bounds
            // Check both start and end of potential read/address calculation
            size_t accessSize = (dereference ? sizeof(void*) : 1);
            if (resultPtrLocation < moduleMemory || (resultPtrLocation + accessSize) >(moduleMemory + modSize)) {
                std::cerr << "SigScan Warn: Calculated result pointer offset (0x" << std::hex << (DWORD_PTR)(resultPtrLocation - moduleMemory)
                    << ") is out of module bounds for match at module offset 0x" << (DWORD_PTR)(addr - moduleMemory)
                    << std::dec << ". Skipping this match." << std::endl;
                continue; // Skip this match as the result address would be invalid
            }

            if (dereference) {
                // Read the pointer from the target process memory
                lastAddress = *(DWORD_PTR*)resultPtrLocation; // Read DWORD_PTR
            }
            else {
                // Return the address itself relative to the actual module base
                lastAddress = baseAddress + (DWORD_PTR)(resultPtrLocation - moduleMemory);
            }
            // Optional: break on first match if desired
            // if (matchCount == 1) break;
        }
    }

    if (matchCount > 1) {
        std::cout << "SigScan Warn: Found " << matchCount << " matches for pattern. Returning last found address: 0x" << std::hex << lastAddress << std::dec << std::endl;
    }
    else if (matchCount == 0) {
        std::cerr << "SigScan Error: Pattern not found." << std::endl;
        return NULL;
    }
    // std::cout << "SigScan Success: Found address 0x" << std::hex << lastAddress << std::dec << std::endl; // Debug
    return lastAddress;
}
// --- SigScan End ---


// --- SQLite Function Pointer Types (Using void* for db handle) ---
typedef int(__cdecl* psqlite3_key)(void* db, const void* pKey, int nKey);
typedef int(__cdecl* psqlite3_open)(const char* filename, void** ppDb);
typedef int(__cdecl* psqlite3_exec)(void* db, const char* sql,
    int (*callback)(void*, int, char**, char**),
    void* cbArg,
    char** errmsg);
typedef int(__cdecl* psqlite3_rekey)(void* db, const void* pKey, int nKey);
typedef int(__cdecl* psqlite3_close)(void* db);
// typedef void (__cdecl *psqlite3_free)(void *ptr); // Needed to free errmsg
// --- End SQLite Types ---


// --- Callback for sqlite3_exec ---
static int callback(void* data, int argc, char** argv, char** azColName) {
    // Suppress unused parameter warning if data is not used
    (void)data;
    std::cout << "--- Row ---" << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << "-----------" << std::endl;
    return 0;
}
unsigned char hexCharToNibble(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    throw std::runtime_error("Invalid hexadecimal character");
}
bool parseHexString(const std::string& hexString, unsigned char* buffer, size_t bufferSize) {
    if (hexString.length() != bufferSize * 2) {
        std::cerr << "Error: Hex string must be exactly " << bufferSize * 2 << " characters long." << std::endl;
        return false;
    }

    try {
        for (size_t i = 0; i < bufferSize; ++i) {
            unsigned char highNibble = hexCharToNibble(hexString[i * 2]);
            unsigned char lowNibble = hexCharToNibble(hexString[i * 2 + 1]);
            buffer[i] = (highNibble << 4) | lowNibble;
        }
        return true;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error parsing hex string: " << e.what() << " in input '" << hexString << "'" << std::endl;
        return false;
    }
}
int main() {
    const TCHAR* targetDll = _T("KernelUtil.dll");
    const char* dbFilename = "Msg3.0.db";

    unsigned char pwdKey[16]; 
    std::string keyHexString;
    bool keyParsed = false;

    std::cout << "请输入你的key，长度应为32位:" << std::endl;
    std::cout << "(e.g., 11451419198101145141919810114514)" << std::endl;
    std::cout << ": ";
    std::cin >> keyHexString;
    if (!parseHexString(keyHexString, pwdKey, sizeof(pwdKey))) {
        std::cerr << "Invalid key format entered. Exiting." << std::endl;
        return 1; 
    }
    std::cout << "Key received successfully." << std::endl;


    std::cout << "\nLoading KernelUtil.dll..." << std::endl;
    HMODULE hModule = LoadLibrary(targetDll);
    if (hModule == NULL) {
        std::cerr << "Error loading " << targetDll << ". Code: " << GetLastError() << std::endl;
        return 1;
    }
    std::wcout << L"Module '" << targetDll << L"' loaded at address: 0x" << std::hex << (DWORD_PTR)hModule << std::dec << std::endl;


    std::cout << "Initializing SigScan for current process..." << std::endl;
    if (!InitializeSigScan(GetCurrentProcessId(), targetDll)) {
        std::cerr << "Failed to initialize SigScan." << std::endl;
        FreeLibrary(hModule);
        return 1;
    }

    std::cout << "Scanning for SQLite function signatures..." << std::endl;
    const char* sig_open = "##558BEC6A006A06FF750CFF7508E8????????85C0";
    const char* sig_key = "##558BEC566B751011837D1010740D68????????E8";
    const char* sig_exec = "##558BEC8B45088B40505DC3";
    const char* sig_rekey = "##558BEC837D1010740D68????????E8";
    const char* sig_close = "##558BEC8B45088B404C5DC3";

    psqlite3_open aopen = (psqlite3_open)(void*)SigScan(sig_open);
    psqlite3_key akey = (psqlite3_key)(void*)SigScan(sig_key);
    psqlite3_exec aexec = (psqlite3_exec)(void*)SigScan(sig_exec);
    psqlite3_rekey arekey = (psqlite3_rekey)(void*)SigScan(sig_rekey);
    psqlite3_close aclose = (psqlite3_close)(void*)SigScan(sig_close);

    if (!aopen || !akey || !aexec || !arekey || !aclose) {
        std::cerr << "Error: Failed to find one or more required function signatures." << std::endl;
        FinalizeSigScan();
        FreeLibrary(hModule);
        return 1;
    }

    std::cout << "Signatures found:" << std::hex << std::endl;
    std::cout << "  sqlite3_open:  0x" << (DWORD_PTR)aopen << std::endl;
    std::cout << std::dec;
    unsigned char emptyKey[16] = { 0 };

    void* pDB = NULL;
    int iRet = -1;
    char* pErrmsg = NULL;

    std::cout << "\nAttempting to open database: " << dbFilename << std::endl;
    iRet = aopen(dbFilename, &pDB);
    std::cout << "sqlite3_open returned: " << iRet << (pDB ? " (DB handle acquired)" : " (DB handle is NULL)") << std::endl;

    if (iRet == 0 && pDB != NULL) {
        std::cout << "Database opened successfully." << std::endl;

        std::cout << "Attempting to apply key..." << std::endl;
        iRet = akey(pDB, pwdKey, sizeof(pwdKey));
        std::cout << "sqlite3_key returned: " << iRet << std::endl;

        if (iRet == 0) {
            std::cout << "Key accepted. Executing query..." << std::endl;
            const char* selectSQL = "SELECT name, sql FROM sqlite_master WHERE type='table' ORDER BY name;";
            iRet = aexec(pDB, selectSQL, callback, NULL, &pErrmsg);
            std::cout << "sqlite3_exec returned: " << iRet << std::endl;

            if (iRet != 0 && pErrmsg) {
                std::cerr << "sqlite3_exec error: " << pErrmsg << std::endl;
                pErrmsg = NULL;
            }
            else if (pErrmsg) {
                pErrmsg = NULL;
            }
            std::cout << "Attempting to rekey database with empty key..." << std::endl;
            iRet = arekey(pDB, emptyKey, sizeof(emptyKey));
            std::cout << "sqlite3_rekey returned: " << iRet << std::endl;
            if (iRet == 0) {
                std::cout << "Database rekeyed successfully (password removed)." << std::endl;
            }
            else {
                std::cerr << "Warning: Failed to rekey database." << std::endl;
            }

        }
        else {
            std::cerr << "Error: Failed to apply key (Incorrect key?). Cannot query or rekey database." << std::endl;
        }
    }
    else {
        std::cerr << "Error: Failed to open database '" << dbFilename << "'." << std::endl;
        if (pErrmsg) {
            std::cerr << " Error details: " << pErrmsg << std::endl;
            pErrmsg = NULL;
        }
    }
    if (pDB != NULL) {
        std::cout << "Closing database..." << std::endl;
        iRet = aclose(pDB);
        std::cout << "sqlite3_close returned: " << iRet << std::endl;
    }

    std::cout << "Finalizing SigScan..." << std::endl;
    FinalizeSigScan();

    std::cout << "Freeing library..." << std::endl;
    FreeLibrary(hModule);

    std::cout << "Execution finished." << std::endl;
    return 0;
}