---
title: 文件下载
sidebar: false
next: false 
prev: false
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
  
  <div class="file-item">
    <div class="file-icon">
      <img src="/icons/python.svg" alt="Python" />
    </div>
    <div class="file-name">
      <a href="/files/linux_qq_get_key.py" download>linux_qq_get_key.py</a>
    </div>
    <div class="file-date">
      2024/11/9 19:48
    </div>
  </div>  
  <!-- 文件项结束 -->
</div>

<style>
/* 文件列表容器 */
.file-list {
  display: flex;
  flex-direction: column;
  gap: 1rem;
}

/* 文件项样式 */
.file-item {
  background-color: var(--file-bg);
  border: 1px solid var(--file-border);
  border-radius: 10px;
  padding: 1rem;
  display: flex;
  align-items: center;
  justify-content: space-between;
  opacity: 1; /* 无动画 */
  transform: translateY(0); /* 无动画 */
}

/* 文件图标样式 */
.file-icon img {
  width: 40px;
  height: 40px;
}

/* 文件名样式 */
.file-name a {
  text-decoration: none;
  color: var(--file-text);
  font-weight: bold;
  margin-left: 1rem;
  transition: color 0.3s ease;
}

.file-name a:hover {
  color: var(--file-hover);
}

/* 文件日期样式 */
.file-date {
  color: var(--file-date-text);
  font-size: 0.9rem;
}

/* 小屏幕适配 */
@media (max-width: 600px) {
  .file-item {
    flex-direction: column;
    align-items: flex-start;
  }

  .file-date {
    margin-top: 0.5rem;
  }
}

/* 全局变量 */
:root {
  --file-bg: #f5f5f5; /* 清新中性的灰白色背景 */
  --file-border: #cccccc; /* 浅灰色边框 */
  --file-text: #2e2e2e; /* 深灰色文字 */
  --file-hover: #005bda; /* 清新的蓝色悬停效果 */
  --file-date-text: #444444; /* 中性灰色日期文字 */
}

/* 深色模式变量 */
.dark {
  --file-bg: #1e1e1e; /* 深色背景，更贴近黑色但不刺眼 */
  --file-border: #2e2e2e; /* 深灰色边框 */
  --file-text: #dcdcdc; /* 明亮的灰白色文字 */
  --file-hover: #6699ff; /* 柔和的蓝色悬停效果 */
  --file-date-text: #a1a1a1; /* 浅灰色日期文字 */
}
</style>

