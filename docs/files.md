---
title: 文件下载
---

# 文件下载

<div class="file-list">
  <!-- 文件项开始 -->
  <div class="file-item">
    <div class="file-icon">
      <img src="/icons/javascript.svg" alt="JavaScript" />
    </div>
    <div class="file-name">
      <a href="/files/android_dump.js" download>android_dump.js</a>
    </div>
    <div class="file-date">
      2024/08/18 12:40
    </div>
  </div>
  
  <div class="file-item">
    <div class="file-icon">
      <img src="/icons/javascript.svg" alt="JavaScript" />
    </div>
    <div class="file-name">
      <a href="/files/android_get_backup_key.js" download>android_get_backup_key.js</a>
    </div>
    <div class="file-date">
      2024/08/18 12:40
    </div>
  </div>
  
  <div class="file-item">
    <div class="file-icon">
      <img src="/icons/python.svg" alt="Python" />
    </div>
    <div class="file-name">
      <a href="/files/android_get_backup_key.py" download>android_get_backup_key.py</a>
    </div>
    <div class="file-date">
      2024/08/18 12:40
    </div>
  </div>
  
  <div class="file-item">
    <div class="file-icon">
      <img src="/icons/python.svg" alt="Python" />
    </div>
    <div class="file-name">
      <a href="/files/android_get_key.py" download>android_get_key.py</a>
    </div>
    <div class="file-date">
      2024/08/18 12:40
    </div>
  </div>
  
  <div class="file-item">
    <div class="file-icon">
      <img src="/icons/python.svg" alt="Python" />
    </div>
    <div class="file-name">
      <a href="/files/android_hook_md5.py" download>android_hook_md5.py</a>
    </div>
    <div class="file-date">
      2024/08/18 12:40
    </div>
  </div>
  
  <div class="file-item">
    <div class="file-icon">
      <img src="/icons/javascript.svg" alt="JavaScript" />
    </div>
    <div class="file-name">
      <a href="/files/ios_get_key.js" download>ios_get_key.js</a>
    </div>
    <div class="file-date">
      2024/08/18 12:40
    </div>
  </div>
  
  <div class="file-item">
    <div class="file-icon">
      <img src="/icons/python.svg" alt="Python" />
    </div>
    <div class="file-name">
      <a href="/files/pcqq_DANGER_rekey.py" download>pcqq_DANGER_rekey.py</a>
    </div>
    <div class="file-date">
      2024/08/18 12:40
    </div>
  </div>
  
  <div class="file-item">
    <div class="file-icon">
      <img src="/icons/python.svg" alt="Python" />
    </div>
    <div class="file-name">
      <a href="/files/pcqq_dump.py" download>pcqq_dump.py</a>
    </div>
    <div class="file-date">
      2024/08/18 12:40
    </div>
  </div>
  
  <div class="file-item">
    <div class="file-icon">
      <img src="/icons/python.svg" alt="Python" />
    </div>
    <div class="file-name">
      <a href="/files/pcqq_get_key.py" download>pcqq_get_key.py</a>
    </div>
    <div class="file-date">
      2024/08/18 12:40
    </div>
  </div>
  
  <div class="file-item">
    <div class="file-icon">
      <img src="/icons/cplusplus.svg" alt="C++" />
    </div>
    <div class="file-name">
      <a href="/files/pcqq_rekey_to_none.cpp" download>pcqq_rekey_to_none.cpp</a>
    </div>
    <div class="file-date">
      2024/08/18 12:40
    </div>
  </div>
  <!-- 文件项结束 -->
</div>

<style>
.file-list {
  display: flex;
  flex-direction: column;
  gap: 1rem;
}

.file-item {
  background-color: #ffffff;
  border: 1px solid #e0e0e0;
  border-radius: 10px;
  padding: 1rem;
  display: flex;
  align-items: center;
  justify-content: space-between;
  opacity: 0;
  transform: translateY(20px);
  animation: fadeInUp 0.5s forwards;
  animation-delay: calc(0.1s * var(--i));
}

.file-item:nth-child(1) { --i: 1; }
.file-item:nth-child(2) { --i: 2; }
.file-item:nth-child(3) { --i: 3; }
.file-item:nth-child(4) { --i: 4; }
.file-item:nth-child(5) { --i: 5; }
.file-item:nth-child(6) { --i: 6; }
.file-item:nth-child(7) { --i: 7; }
.file-item:nth-child(8) { --i: 8; }
.file-item:nth-child(9) { --i: 9; }
.file-item:nth-child(10) { --i: 10; }

.file-icon img {
  width: 40px;
  height: 40px;
}

.file-name a {
  text-decoration: none;
  color: #333333;
  font-weight: bold;
  margin-left: 1rem;
}

.file-name a:hover {
  color: #007acc;
}

.file-date {
  color: #666666;
  font-size: 0.9rem;
}

@keyframes fadeInUp {
  to {
    opacity: 1;
    transform: translateY(0);
  }
}

/* 响应式调整 */
@media (max-width: 600px) {
  .file-item {
    flex-direction: column;
    align-items: flex-start;
  }
  
  .file-date {
    margin-top: 0.5rem;
  }
}
</style>
