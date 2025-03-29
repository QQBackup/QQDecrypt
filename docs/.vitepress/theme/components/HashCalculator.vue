<template>
  <div class="vp-hash-box">
    <h3>计算 QQ_path_hash 和数据库密钥</h3>
    
    <div class="input-group">
      <label for="nt_uid">请输入 nt_uid:</label>
      <input 
        v-model="nt_uid" 
        id="nt_uid" 
        placeholder="例如：u_mIicAReWrdCB-kST6TXH7A" 
        @input="validatent_uid" 
        :class="{ invalid: nt_uidError }"
      />
      <span v-if="nt_uidError" class="error">{{ nt_uidError }}</span>
    </div>
    
    <div class="input-group">
      <label for="rand">请输入 rand:</label>
      <input 
        v-model="rand" 
        id="rand" 
        placeholder="例如：6tPaJ9GP" 
        @input="validateRand" 
        :class="{ invalid: randError }"
      />
      <span v-if="randError" class="error">{{ randError }}</span>
    </div>

    <div v-if="qqPathHash || key" class="results">
      <div v-if="qqPathHash" class="result">
        <p><strong>QQ_path_hash:</strong> {{ qqPathHash }}</p>
      </div>
      <div v-if="key" class="result">
        <p><strong>Key:</strong> {{ key }}</p>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue'
import md5 from 'crypto-js/md5'

const nt_uid = ref('')
const rand = ref('')
const nt_uidError = ref('')
const randError = ref('')
const qqPathHash = ref('')
const key = ref('')

function validatent_uid() {
  const nt_uidValue = nt_uid.value.trim()
  const nt_uidPattern = /^u_[A-Za-z0-9_-]{22}$/

  if (nt_uidValue === '') {
    nt_uidError.value = ''
    qqPathHash.value = ''
    key.value = ''
    return
  }

  if (!nt_uidPattern.test(nt_uidValue)) {
    nt_uidError.value = 'nt_uid 必须以 "u_" 开头，且总长度为24位，只包含英文、数字、下划线 (_) 和破折号 (-)。'
    qqPathHash.value = ''
    key.value = ''
  } else {
    nt_uidError.value = ''
    calculateQQPathHash()
    calculateKey()
  }
}

function validateRand() {
  const randValue = rand.value.trim()
  const randPattern = /^[A-Za-z0-9]{8}$/

  if (randValue === '') {
    randError.value = ''
    key.value = ''
    return
  }

  if (!randPattern.test(randValue)) {
    randError.value = 'rand 必须是8位纯英文和数字组成的值。'
    key.value = ''
  } else {
    randError.value = ''
    calculateKey()
  }
}

function calculateQQPathHash() {
  const uidHash = md5(nt_uid.value).toString()
  qqPathHash.value = md5(uidHash + 'nt_kernel').toString()
}

function calculateKey() {
  if (nt_uid.value && rand.value && !nt_uidError.value && !randError.value) {
    const uidHash = md5(nt_uid.value).toString()
    key.value = md5(uidHash + rand.value).toString()
  } else {
    key.value = ''
  }
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