---
title: 致谢
sidebar: false
next: false 
prev: false
---

**网站的编写离不开以下网站或应用的支持，在此表达最诚挚的谢意（排名不分先后）：**
- 在原 qq-win-db-key 项目中引用的相关资料，此处不再全部列出
- 若有希望补充/想从致谢名单中移除的，可在 GitHub 开 issues 联系我修改

<div class="card-container">
  <a class="card" href="https://github.com/QQBackup/qq-win-db-key" target="_blank">
    <div class="card-image">
      <img src="/icons/logo.jpg" alt="">
    </div>
    <div class="card-content">
      <h3>qq-win-db-key</h3>
      <p>文档大部分参考教程皆来源于此。<br>基于CC BY-NC-SA 4.0协议转载</br></p>
    </div>
  </a>

  <a class="card" href="https://blog.reincarnatey.net/2024/0707-qqnt-history-export/" target="_blank">
    <div class="card-image">
      <img src="/thanks/失迹.png" alt="">
    </div>
    <div class="card-content">
      <h3>失迹の博客</h3>
      <p>为 nt_msg 表中列名信息提供了参考<br>基于CC BY-NC-SA 4.0协议转载</br></p>
    </div>
  </a>

  <a class="card" href="https://github.com/mobyw/GroupChatAnnualReport" target="_blank">
    <div class="card-image">
      <img src="/thanks/GroupChatAnnualReport.jpg" alt="">
    </div>
    <div class="card-content">
      <h3>GroupChatAnnualReport</h3>
      <p>为 nt_msg 表中列名信息提供了参考，为IDA教程提供补充,<br>基于MIT协议转载</br></p>
    </div>
  </a>

  <a class="card" href="https://github.com/QQBackup/QQDecrypt" target="_blank">
    <div class="card-image">
      <img src="/thanks/github.svg" alt="">
    </div>
    <div class="card-content">
      <h3>GitHub</h3>
      <p>为仓库源代码提供托管服务</p>
    </div>
  </a>

  <a class="card" href="https://vitepress.dev/" target="_blank">
    <div class="card-image">
      <img src="/thanks/vitepress.svg" alt="">
    </div>
    <div class="card-content">
      <h3>VitePress</h3>
      <p>网站使用的静态生成框架</p>
    </div>
  </a>

  <a class="card" href="https://vercel.com/" target="_blank">
    <div class="card-image">
      <img src="/thanks/vercel.png" alt="">
    </div>
    <div class="card-content">
      <h3>vercel</h3>
      <p>网站使用的静态网站自动化部署平台</p>
    </div>
  </a>

  <a class="card" href="https://vitepress.dev/" target="_blank">
    <div class="card-image">
      <img src="/thanks/vitepress.svg" alt="">
    </div>
    <div class="card-content">
      <h3>yiov的vitepress教程</h3>
      <p>为网站美化提供了参考</p>
    </div>
  </a>
  
</div>

<style>
.card-container {
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
  padding: 1.5rem;
}

.card {
  background-color: var(--card-bg);
  border: 1px solid var(--card-border);
  border-radius: 8px;
  width: 100%;
  max-width: 700px;
  display: flex;
  align-items: center;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.2);
  transition: transform 0.3s ease, box-shadow 0.3s ease, background-color 0.3s ease;
  text-decoration: none;
  overflow: hidden;
  margin: 0 auto;
  padding: 1rem;
}

.card:hover {
  transform: scale(1.02);
  box-shadow: 0 6px 10px rgba(0, 0, 0, 0.4);
  background-color: var(--card-hover-bg);
}

.card-image {
  width: 80px;
  height: 80px;
  overflow: hidden;
  border-radius: 50%;
  margin-right: 1rem;
  flex-shrink: 0;
}

.card-image img {
  width: 100%;
  height: 100%;
  object-fit: cover;
  border-radius: 50%;
}

.card-content {
  display: flex;
  flex-direction: column;
  justify-content: center;
  flex: 1;
}

.card-content h3 {
  font-size: 1.2rem;
  margin: 0;
  color: var(--card-text);
}

.card-content p {
  color: var(--card-text); 
  font-size: 0.9rem;
  margin: 0;
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: normal;
}

@media (max-width: 600px) {
  .card {
    flex-direction: column; 
    text-align: center;
  }

  .card-image {
    margin: 0 auto 1rem;
  }

  .card-content h3,
  .card-content p {
    text-align: center;
  }
}

/* 全局变量 */
:root {
  --card-border: rgba(200, 200, 200, 1); 
  --card-text: rgba(50, 50, 50, 1); 
}

/* 深色模式 */
.dark {
  --card-bg: rgba(32, 33, 39, 1); 
  --card-border: rgba(70, 70, 70, 1); 
  --card-text: rgba(200, 200, 200, 1); 
}
</style>



