import os
import sys
import time
import argparse
import ctypes
import json
from ctypes import wintypes
import frida
import psutil
import requests
import win32process
import winreg

PROCESS_ALL_ACCESS = 0x1F0FFF
PROCESS_NAME = "QQ.exe"
OFFSET_URL = "https://qqbackup.github.io/QQDecrypt/files/QQ_Offset.json"

session = None
offset_data = {}
version = None

ReadProcessMemory = ctypes.windll.kernel32.ReadProcessMemory
ReadProcessMemory.argtypes = [
    wintypes.HANDLE, wintypes.LPCVOID, wintypes.LPVOID, ctypes.c_size_t,
    ctypes.POINTER(ctypes.c_size_t)
]
ReadProcessMemory.restype = wintypes.BOOL


def get_offset_data_from_url(url):
    try:
        response = requests.get(url, timeout=10)
        response.raise_for_status()
        return response.json()
    except requests.exceptions.RequestException as e:
        print(f"错误: 获取在线偏移量数据失败: {e}")
        sys.exit(1)
    except json.JSONDecodeError:
        print("错误: 无法解析从URL返回的JSON数据。")
        sys.exit(1)


def open_process(pid):
    return ctypes.windll.kernel32.OpenProcess(PROCESS_ALL_ACCESS, False, pid)


def get_module_base_address(process_handle, module_name):
    try:
        modules = win32process.EnumProcessModules(process_handle)
        for module in modules:
            module_path = win32process.GetModuleFileNameEx(process_handle, module)
            if module_name.lower() in os.path.basename(module_path).lower():
                return module
    except win32process.error as e:
        if e.winerror != 299:
            raise
    return None


def read_memory(process_handle, address, size):
    buffer = ctypes.create_string_buffer(size)
    bytesRead = ctypes.c_size_t(0)
    if ReadProcessMemory(process_handle, address, buffer, size, ctypes.byref(bytesRead)):
        return buffer.raw
    raise ctypes.WinError()


def is_qq_running():
    return any(PROCESS_NAME.lower() in p.name().lower() for p in psutil.process_iter(['name']))


def wait_for_qq_to_start():
    print("正在等待QQ启动...")
    while True:
        pids = {p.pid for p in psutil.process_iter(['pid', 'name']) if PROCESS_NAME.lower() in p.info['name'].lower()}
        ppids = {p.ppid() for p in psutil.process_iter(['name', 'ppid']) if PROCESS_NAME.lower() in p.info['name'].lower()}
        main_pids = pids.intersection(ppids)
        if main_pids:
            new_pid = main_pids.pop()
            print(f"检测到QQ主进程 (PID: {new_pid})。")
            time.sleep(3)
            return new_pid
        time.sleep(1)


def on_key_found(pid, key):
    print("\n" + "="*50)
    print(f"成功获取到密钥!")
    print(f"  - 密钥: {key}")
    print("="*50 + "\n")


def on_message(pid, message, data):
    if message.get('type') == 'send':
        payload = message.get('payload', {})
        if isinstance(payload, dict) and 'key' in payload:
            on_key_found(pid, payload['key'])
        else:
            print(f"[*] Script message: {payload}")
    elif message.get('type') == 'error':
        print(f"[!] Script error: {message.get('description')}")
        os._exit(1)


def get_qq_version():
    try:
        with winreg.OpenKey(winreg.HKEY_CURRENT_USER, r"Software\Tencent\QQNT", 0, winreg.KEY_READ) as key:
            return winreg.QueryValueEx(key, "Version")[0]
    except Exception:
        return None


def attach_to_qq(pid, script_content):
    global session
    print(f"正在尝试附加到 QQ.exe (PID: {pid})...")
    try:
        session = frida.attach(pid)
        script = session.create_script(script_content)
        script.on('message', lambda msg, data: on_message(pid, msg, data))
        script.load()
    except frida.ProcessNotFoundError:
        print(f"错误: 进程 {pid} 未找到，可能已关闭。")
        sys.exit(1)
    except Exception as e:
        print(f"附加到QQ时发生未知错误: {e}")
        sys.exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="从运行中的QQNT进程获取密钥。")
    parser.add_argument('--pid', type=int, help='直接指定一个已在运行的QQ进程PID以获取其密钥。')
    args = parser.parse_args()

    print(f"正在从 {OFFSET_URL} 获取偏移量数据...")
    offset_data = get_offset_data_from_url(OFFSET_URL)

    version = get_qq_version()
    print(f"当前QQ版本: {version}")

    if version not in offset_data:
        print("无法找到用户配置文件，请手动输入：")
        while True:
            user_input = input("请输入基址偏移（0x开头十六进制）：").strip()
            if user_input.lower().startswith("0x"):
                try:
                    key_offset = int(user_input, 16)
                    contributor = "未知"
                    timestamp = "未知"
                    break
                except ValueError:
                    print("输入格式错误，请输入有效的十六进制数字")
            else:
                print("请输入以0x开头的十六进制数字")
    else:
        version_data = offset_data[version]
        offsets = version_data["offsets"]
        contributor = version_data.get("contributor", "未知")
        timestamp = version_data.get("timestamp", "未知")
        print(f"版本 {version} 的基址由 {contributor} 贡献（提交时间：{timestamp}）")
        key_offset = int(offsets[0], 16)

    script_content = f"""
    (function () {{
        const baseAddr = Module.findBaseAddress("wrapper.node");
        if (!baseAddr) return;
        const hookAddr = baseAddr.add({key_offset});
        Interceptor.attach(hookAddr, {{
            onEnter: function (args) {{
                try {{
                    const key = Memory.readAnsiString(args[2], 16);
                    if (key && key.length > 0) {{
                        send({{ key: key.split('\\x00')[0] }}); 
                        Interceptor.detachAll();
                    }}
                }} catch (e) {{}}
            }}
        }});
    }})();
    """

    target_pid = None
    if args.pid:
        if not psutil.pid_exists(args.pid) or PROCESS_NAME.lower() not in psutil.Process(args.pid).name().lower():
            print(f"错误: 指定的PID {args.pid} 无效或不是QQ进程。")
            sys.exit(1)
        target_pid = args.pid
    else:
        if is_qq_running():
            print("检测到QQ正在运行，请退出QQ后重新运行...")
            while is_qq_running():
                time.sleep(1)
            print("正在等待附加进程。")
        target_pid = wait_for_qq_to_start()

    attach_to_qq(target_pid, script_content)
    print("\n已成功注入进程，查找密钥……")

    try:
        sys.stdin.read()
    except KeyboardInterrupt:
        print("\n用户终止操作。")
    finally:
        if session:
            session.detach()
