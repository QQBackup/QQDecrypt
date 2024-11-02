---
title: 致谢
---

**文档内容参考/引用了以下网站的内容，在此表达最诚挚的谢意（排名不分先后）：**
- 在原 qq-win-db-key 项目中引用的相关资料，此处不再全部列出
- 若有希望补充/想从致谢名单中移除的，可在 GitHub 开 issues 或通过 [issues@sbcnm.top](mailto:issues@sbcnm.top) 联系我修改

<div class="card-container">
  <div class="card">
    <a href="https://github.com/QQBackup/qq-win-db-key" target="_blank">
      <div class="card-image">
        <img src="/icons/logo.jpg" alt="">
      </div>
      <div class="card-content">
        <h3>qq-win-db-key</h3>
        <p>文档大部分参考教程皆来源于此。</p>
      </div>
    </a>
  </div>
  
  <div class="card">
    <a href="https://blog.reincarnatey.net/2024/0707-qqnt-history-export/" target="_blank">
      <div class="card-image">
        <img src="/thanks/失迹.png" alt="">
      </div>
      <div class="card-content">
        <h3>失迹の博客</h3>
        <p>为 nt_msg 表中列名信息提供了参考</p>
      </div>
    </a>
  </div>
 
  <div class="card">
    <a href="https://github.com/mobyw/GroupChatAnnualReport" target="_blank">
      <div class="card-image">
        <img src="/thanks/GroupChatAnnualReport.jpg" alt="">
      </div>
      <div class="card-content">
        <h3>GroupChatAnnualReport</h3>
        <p>为 nt_msg 表中列名信息提供了参考</p>
      </div>
    </a>
  </div>
  <div class="card">
    <a href="https://github.com/QQBackup/QQDecrypt" target="_blank">
      <div class="card-image">
        <img src="/thanks/github.png" alt="">
      </div>
      <div class="card-content">
        <h3>GitHub</h3>
        <p>为仓库源代码提供托管服务</p>
      </div>
    </a>
  </div>
  <div class="card">
    <a href="https://vitepress.dev/" target="_blank">
      <div class="card-image">
        <img src="/thanks/vitepress.svg" alt="">
      </div>
      <div class="card-content">
        <h3>VitePress</h3>
        <p>网站使用的静态生成框架</p>
      </div>
    </a>
  </div>
  <div class="card">
    <a href="https://vercel.com/" target="_blank">
      <div class="card-image">
        <img src="/thanks/vercel.png" alt="">
      </div>
      <div class="card-content">
        <h3>vercel</h3>
        <p>网站使用的静态网站自动化部署平台</p>
      </div>
    </a>
  </div>  
</div>

<style>
.card-container {
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
  padding: 1.5rem;
}

.card {
  background-color: #fff;
  border: 1px solid #e0e0e0;
  border-radius: 8px;
  width: 100%;
  max-width: 700px;
  display: flex;
  align-items: center;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  transition: transform 0.3s ease, box-shadow 0.3s ease;
  text-decoration: none;
  overflow: hidden;
  margin: 0 auto;
}

.card:hover {
  transform: scale(1.02);
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.15);
}

.card-image {
  width: 80px;
  height: 80px;
  overflow: hidden;
  border-radius: 50%;
  margin: 15px;
  flex-shrink: 0;
}

.card-image img {
  width: 100%;
  height: 100%;
  object-fit: cover;
  border-radius: 50%;
}

.card-content {
  padding: 10px;
  display: flex;
  flex-direction: column;
  justify-content: space-between;
  flex: 1;
}

.card-content h3 {
  font-size: 1.2rem;
  margin: 0;
  color: #333;
}

.card-content p {
  color: #666;
  font-size: 0.9rem;
  margin: 0;
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
  max-width: 100%;
  transition: white-space 0.3s ease;
}

.card:hover .card-content p {
  white-space: normal;
}
</style>
