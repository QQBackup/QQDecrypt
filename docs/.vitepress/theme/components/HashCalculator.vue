<template>
  <div class="hash-calculator">
    <h3>计算 QQ_path_hash 和数据库密钥</h3>
    
    <div class="input-group">
      <label for="uin">请输入 uin:</label>
      <input 
        v-model="uin" 
        id="uin" 
        placeholder="例如：u_mIicAReWrdCB-kST6TXH7A" 
        @input="validateUin" 
        :class="{ invalid: uinError }"
      />
      <span v-if="uinError" class="error">{{ uinError }}</span>
    </div>
    
    <div v-if="qqPathHash" class="result">
      <p><strong>QQ_path_hash:</strong> {{ qqPathHash }}</p>
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

    <div v-if="key" class="result">
      <p><strong>Key:</strong> {{ key }}</p>
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue'
import md5 from 'crypto-js/md5'

// 定义响应式变量
const uin = ref('')
const rand = ref('')

const uinError = ref('')
const randError = ref('')

const qqPathHash = ref('')
const key = ref('')

// 验证 UIN
function validateUin() {
  const uinValue = uin.value.trim()
  const uinPattern = /^u_[A-Za-z0-9_-]{22}$/

  if (!uinPattern.test(uinValue)) {
    uinError.value = 'UIN 必须以 "u_" 开头，且总长度为24位，只包含英文、数字、下划线 (_) 和破折号 (-)。'
    qqPathHash.value = ''
  } else {
    uinError.value = ''
    calculateQQPathHash()
  }
}

// 验证 Rand
function validateRand() {
  const randValue = rand.value.trim()
  const randPattern = /^[A-Za-z0-9]{8}$/

  if (!randPattern.test(randValue)) {
    randError.value = 'Rand 必须是8位纯英文和数字组成的值。'
    key.value = ''
  } else {
    randError.value = ''
    calculateKey()
  }
}

// 计算 QQ_path_hash
function calculateQQPathHash() {
  if (uin.value && !uinError.value) {
    const uidHash = md5(uin.value).toString()
    qqPathHash.value = md5(uidHash + 'nt_kernel').toString()
  } else {
    qqPathHash.value = ''
  }
}

// 计算 Key
function calculateKey() {
  if (uin.value && rand.value && !uinError.value && !randError.value) {
    const uidHash = md5(uin.value).toString()
    key.value = md5(uidHash + rand.value).toString()
  } else {
    key.value = ''
  }
}
</script>

<style scoped>
.hash-calculator {
  padding: 1em;
  border: 1px solid #ddd;
  border-radius: 8px;
  background-color: #f9f9f9;
}

.input-group {
  margin-bottom: 1em;
}

label {
  display: block;
  margin-bottom: 0.5em;
  font-weight: bold;
}

input {
  width: 100%;
  padding: 0.5em;
  border: 1px solid #ccc;
  border-radius: 4px;
}

input.invalid {
  border-color: red;
}

.error {
  color: red;
  font-size: 0.875em;
  margin-top: 0.25em;
  display: block;
}

.result {
  margin-top: 1em;
  padding: 1em;
  background-color: #eef;
  border-radius: 4px;
}

.result p {
  margin: 0.5em 0;
}
</style>
