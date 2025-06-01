<template>
  <div class="qq-path-generator">
    <h2 class="generator-title">本地缓存图片路径计算</h2>
    <p class="generator-description">
预测 安卓QQ 本地缓存图片路径
    </p>
    <div class="input-wrapper">
      <input
        type="text"
        id="md5Input"
        v-model="md5Input"
        placeholder="请输入32位MD5值"
        @input="onMd5InputChange"
        :aria-invalid="!!errorMessage"
        aria-describedby="md5Error"
        class="md5-input-field"
      />
      <div v-if="errorMessage" id="md5Error" class="error-message-text">
        {{ errorMessage }}
      </div>
    </div>

    <div v-if="generatedPaths.length > 0 && !errorMessage" class="results-output">
      <h3 class="results-header">预测路径:</h3>
      <ul class="paths-list">
        <li v-for="pathItem in generatedPaths" :key="pathItem.folder" class="path-list-item">
          <strong class="folder-name">{{ pathItem.folder }}:</strong>
          <span class="path-string">{{ pathItem.path }}</span>
        </li>
      </ul>
    </div>
  </div>
</template>

<script setup>
import { ref, watch, nextTick } from 'vue';

// --- CRC64 Logic (Ported from Python to JavaScript using BigInt) ---
const _crc64_table_js = (() => {
  const table = new Array(256);
  for (let i = 0; i < 256; i++) {
    let bf = BigInt(i);
    for (let j = 0; j < 8; j++) {
      if ((bf & 1n) !== 0n) {
        bf = (bf >> 1n) ^ -7661587058870466123n;
      } else {
        bf >>= 1n;
      }
    }
    table[i] = bf;
  }
  return table;
})();

function crc64_js(s) {
  let v = -1n; // 0xFFFFFFFFFFFFFFFFn
  for (let i = 0; i < s.length; i++) {
    const charCode = BigInt(s.charCodeAt(i));
    const index = Number((charCode ^ v) & 0xFFn);
    v = _crc64_table_js[index] ^ (v >> 8n);
  }
  return v;
}

function get_img_path_from_md5_js(md5, folder) {
  const url = `${folder}:${md5}`;
  const crc_val = crc64_js(url);
  let filename_hex = crc_val.toString(16);
  let filename = 'Cache_' + filename_hex;
  const last_three = filename.length >= 3 ? filename.slice(-3) : filename;
  const rel_path = `./${folder}/${last_three}/${filename}`;
  return rel_path;
}

// --- Vue Component Logic ---
const md5Input = ref('');
const generatedPaths = ref([]);
const errorMessage = ref('');

const FOLDERS = ["chatraw", "chatimg", "chatthumb"];

// Handles live uppercasing and cursor position
function onMd5InputChange(event) {
  const inputElement = event.target;
  const originalValue = inputElement.value;
  const cursorPosition = inputElement.selectionStart;

  md5Input.value = originalValue.toUpperCase();

  nextTick(() => {
    // Vue updates the DOM in the next tick.
    // We need to ensure the element value has been updated by Vue before trying to set selection range.
    if (inputElement.value === md5Input.value) { // Check if DOM value matches reactive ref
        try {
            inputElement.setSelectionRange(cursorPosition, cursorPosition);
        } catch (e) {
            // In some edge cases (e.g. input type changing, or element becoming non-focusable briefly)
            // setSelectionRange might fail. Silently ignore.
            // console.warn("Could not set selection range:", e);
        }
    }
  });
}

watch(md5Input, async (currentValue) => {
  const md5 = currentValue.trim(); // Already uppercased by onMd5InputChange

  if (!md5) {
    generatedPaths.value = [];
    errorMessage.value = '';
    return;
  }

  const IS_HEX_ONLY = /^[0-9A-F]*$/.test(md5);
  const IS_CORRECT_LENGTH = md5.length === 32;

  if (!IS_HEX_ONLY) {
    errorMessage.value = '格式错误 (MD5包含无效字符)';
    generatedPaths.value = [];
  } else if (!IS_CORRECT_LENGTH) {
    errorMessage.value = '格式错误 (MD5长度应为32位)';
    generatedPaths.value = [];
  } else { // Is hex and is 32 chars long - i.e., a valid MD5 format
    errorMessage.value = '';
    
    // Minimal delay to allow UI to update (e.g., clear error message)
    // before potentially blocking (though crc64 is fast)
    await new Promise(resolve => setTimeout(resolve, 0)); 

    try {
      const paths = FOLDERS.map(folder => ({
        folder,
        path: get_img_path_from_md5_js(md5, folder)
      }));
      generatedPaths.value = paths;
    } catch (e) {
      console.error("Error generating paths:", e);
      errorMessage.value = "生成路径时发生内部错误。";
      generatedPaths.value = [];
    }
  }
});

</script>

<style scoped>
.qq-path-generator {
  padding: 1rem; /* p-4 */
  border: 1px solid var(--vp-c-divider); /* border */
  border-radius: 12px; /* rounded-lg */
  background-color: var(--vp-c-bg-soft, #f9f9f9);
  color: var(--vp-c-text-1, #333);
  font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen,
    Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;
  max-width: 600px;
  margin: 20px auto;
}

.qq-path-generator > * + * { /* Simulates space-y-4 for direct children */
  margin-top: 1rem;
}

.generator-title {
  font-size: 1.25rem; /* h3 example style */
  font-weight: 700; /* h3 example style */
  color: var(--vp-c-text-1); /* h3 example style */
  text-align: center; /* h3 example style */
  user-select: none; /* h3 example style */
  margin-bottom: 0.5rem; /* h3 example style */
  margin-top: 0; /* Reset default h2 margin */
}

.generator-description {
  text-align: center;
  font-size: 0.9em;
  color: var(--vp-c-text-2, #555);
  /* margin-bottom controlled by space-y on parent */
}

.input-wrapper {
  /* margin-top controlled by space-y on parent */
}

.input-wrapper > * + * { /* Simulates space-y-2 for direct children */
   margin-top: 0.5rem;
}

.md5-input-field {
  width: 100%;
  padding: 0.5rem 0.75rem; /* input example style */
  border: 2px solid var(--vp-c-divider); /* input example style */
  border-radius: 8px; /* input example style */
  font-family: monospace; /* input example style */
  font-size: 1rem; /* input example style */
  color: var(--vp-c-text-1); /* input example style */
  background-color: var(--vp-c-bg-soft); /* input example style */
  transition: border-color 0.3s ease, box-shadow 0.3s ease; /* input example style */
  box-sizing: border-box; /* input example style */
}

.md5-input-field:focus {
  outline: none; /* input focus example style */
  border-color: var(--vp-c-brand); /* input focus example style */
  /* Using rgba with --vp-rgb-brand for the shadow color to match VitePress theme */
  box-shadow: 0 0 8px 3px rgba(var(--vp-rgb-brand, 62, 175, 124), 0.2); /* input focus example style, adapted */
  background-color: var(--vp-c-bg); /* input focus example style */
}

.error-message-text {
  color: #e55353; /* text-red-500 example style */
  font-weight: 600; /* text-red-500 example style */
  font-size: 0.9rem; /* text-red-500 example style */
  user-select: none; /* text-red-500 example style */
  /* margin-top controlled by space-y on parent (.input-wrapper) */
  padding: 0.25rem 0.1rem; /* Small padding for better appearance */
}

.results-output {
  /* margin-top controlled by space-y on parent */
}

.results-header {
  font-size: 1.1rem; 
  font-weight: 600;
  color: var(--vp-c-text-2);
  margin-bottom: 0.75rem;
  margin-top: 0; /* If it's the first child of results-output */
}

.paths-list {
  list-style-type: none;
  padding: 0;
  margin: 0;
}

.paths-list > * + * { /* space-y for list items */
    margin-top: 0.5rem; 
}

.path-list-item {
  padding: 0.25rem 0;
  /* Styles for 'div > div' from example applied here indirectly */
}

.folder-name {
  color: var(--vp-c-brand); /* strong example style */
  user-select: text; /* strong example style */
  font-weight: bold;
  margin-right: 0.5em;
}

.path-string {
  font-family: monospace; /* 'div > div' example style */
  font-size: 1rem; /* 'div > div' example style, adjusted to 0.95rem for better fit */
  font-size: 0.95rem;
  color: var(--vp-c-text-1); /* 'div > div' example style */
  word-break: break-all; /* 'div > div' example style */
}

</style>