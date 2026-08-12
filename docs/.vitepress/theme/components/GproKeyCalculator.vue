<template>
  <div class="vp-hash-box">
    <h3>计算 gpro 数据库密钥</h3>

    <div class="input-group">
      <label for="gpro_uin">请输入 QQ 号 (uin):</label>
      <input
        v-model="uin"
        id="gpro_uin"
        placeholder="例如：1707889225"
        @input="validateUin"
        :class="{ invalid: uinError }"
      />
      <span v-if="uinError" class="error">{{ uinError }}</span>
    </div>

    <div class="input-group">
      <label for="gpro_header">请输入头部盐值 (16 字节):</label>
      <input
        v-model="header"
        id="gpro_header"
        placeholder="例如：vgdBdzWwwrNNGORk"
        @input="validateHeader"
        :class="{ invalid: headerError }"
      />
      <span v-if="headerError" class="error">{{ headerError }}</span>
    </div>

    <div v-if="gproKey" class="results">
      <div class="result">
        <p><strong>gpro 密钥:</strong> {{ gproKey }}</p>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue'
import md5 from 'crypto-js/md5'
import sha1 from 'crypto-js/sha1'

const uin = ref('')
const header = ref('')
const uinError = ref('')
const headerError = ref('')
const gproKey = ref('')

function validateUin() {
  const val = uin.value.trim()
  if (val === '') {
    uinError.value = ''
    gproKey.value = ''
    return
  }
  if (!/^\d+$/.test(val)) {
    uinError.value = 'QQ 号必须为纯数字。'
    gproKey.value = ''
  } else {
    uinError.value = ''
    calculate()
  }
}

function validateHeader() {
  const val = header.value
  if (val === '') {
    headerError.value = ''
    gproKey.value = ''
    return
  }
  if (val.length !== 16) {
    headerError.value = '头部盐值必须为 16 个字符。'
    gproKey.value = ''
  } else {
    headerError.value = ''
    calculate()
  }
}

function calculate() {
  if (!uin.value.trim() || !header.value || uinError.value || headerError.value) {
    gproKey.value = ''
    return
  }
  const uinStr = uin.value.trim()
  const md5Uin = md5(uinStr).toString()
  const sha1Raw = sha1(uinStr)
  const md5Sha1 = md5(sha1Raw).toString()
  const userSeed = md5(md5Uin + md5Sha1).toString()
  const headerSeed = md5(header.value).toString()
  gproKey.value = md5(headerSeed + userSeed).toString()
}
</script>

<style scoped>
.vp-hash-box {
  max-width: 600px;
  margin: 2rem auto;
  padding: 2rem;
  border-radius: 12px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);

  --vp-hc-bg: var(--vp-c-bg);
  --vp-hc-text: var(--vp-c-text-1);
  --vp-hc-border: var(--vp-c-divider);
  --vp-hc-accent: var(--vp-c-brand);
  --input-border-light: #005f9e;

  background-color: var(--vp-hc-bg);
  color: var(--vp-hc-text);
  border: 1px solid var(--vp-hc-border);
}

.dark .vp-hash-box {
  --vp-hc-bg: var(--vp-c-bg-alt);
  --vp-hc-border: var(--vp-c-divider);
}

.vp-hash-box {
  & h3 {
    margin-bottom: 1.5rem;
    text-align: center;
    color: var(--vp-hc-text);
  }

  & .input-group {
    margin-bottom: 1.5rem;
  }

  & label {
    display: block;
    margin-bottom: 0.5rem;
    font-weight: 500;
    color: var(--vp-c-text-2);
  }

  & input {
    width: 100%;
    padding: 0.75rem;
    border: 2px solid var(--input-border-light);
    border-radius: 6px;
    background-color: var(--vp-c-bg-soft);
    color: var(--vp-hc-text);
    font-size: 1rem;
    transition: all 0.2s ease;

    &:focus {
      border-color: var(--vp-hc-accent);
      box-shadow: 0 0 0 3px var(--vp-c-brand-dimm);
    }

    &::placeholder {
      color: var(--vp-c-text-3);
    }

    &.invalid {
      border-color: red;
    }
  }

  & .error {
    display: block;
    margin-top: 0.5rem;
    color: red !important;
    font-size: 0.875rem;
  }

  .dark & input {
    border-color: var(--vp-c-divider);

    &.invalid {
      border-color: red;
    }
  }

  & .results {
    margin-top: 1.5rem;
    background-color: var(--vp-c-bg-soft);
    border-radius: 8px;
    padding: 1rem;
  }

  & .result {
    padding: 0.75rem;
    background-color: var(--vp-c-bg);
    border-radius: 6px;
    margin: 0.5rem 0;
    border: 1px solid var(--vp-c-divider);

    & strong {
      color: var(--vp-hc-accent);
    }
  }
}
</style>
