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
  background-color: var(--file-bg-color);
  border: 1px solid var(--file-border-color);
  border-radius: 10px;
  padding: 1rem;
  display: flex;
  align-items: center;
  justify-content: space-between;
  opacity: 1; /* 无动画 */
  transform: translateY(0); /* 无动画 */
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  transition: box-shadow 0.3s ease, transform 0.3s ease;
}

.file-item:hover {
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.15);
  transform: translateY(-2px);
}

/* 文件图标样式 */
.file-icon img {
  width: 40px;
  height: 40px;
  border-radius: 5px; /* 添加圆角 */
}

/* 文件名样式 */
.file-name a {
  text-decoration: none;
  color: var(--file-text-color);
  font-weight: bold;
  margin-left: 1rem;
  transition: color 0.3s ease, transform 0.3s ease;
}

.file-name a:hover {
  color: var(--file-hover-color);
  transform: scale(1.05); /* 放大效果 */
}

/* 文件日期样式 */
.file-date {
  color: var(--file-date-color);
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

/* 全局变量：浅色模式 */
:root {
  --file-bg-color: rgba(250, 250, 250, 1); /* 柔和白色背景 */
  --file-border-color: rgba(220, 220, 220, 1); /* 浅灰色边框 */
  --file-text-color: rgba(50, 50, 50, 1); /* 深灰色文字 */
  --file-hover-color: rgba(0, 91, 218, 1); /* 鲜艳蓝色悬停效果 */
  --file-date-color: rgba(100, 100, 100, 1); /* 中性灰色日期文字 */
}

/* 深色模式 */
.dark {
  --file-bg-color: rgba(32, 33, 39, 1); /* 深色背景 */
  --file-border-color: rgba(48, 48, 48, 1); /* 较深的灰色边框 */
  --file-text-color: rgba(220, 220, 220, 1); /* 浅灰白文字 */
  --file-hover-color: rgba(102, 153, 255, 1); /* 柔和蓝色悬停效果 */
  --file-date-color: rgba(161, 161, 161, 1); /* 浅灰色日期文字 */
}

.file-icon img {
  width: 40px;
  height: 40px;
  border-radius: 5px; 
  transition: filter 0.3s ease;
}

/* 深色模式下调整图标颜色 */
.dark .file-icon img {
  filter: invert(1) brightness(2);
}

</style>

