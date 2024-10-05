---
title: 致谢
---

**文档内容参考/引用了以下网站的内容，在此表达最诚挚的谢意(排名不分先后)**
- 在原qq-win-db-key项目中引用的相关资料，此处不再全部列出
- 若有希望补充/想从致谢名单中移除的，可在GitHub开issues或通过[issues@sbcnm.top](mailto:issues@sbcnm.top)联系我修改

<div class="card-container">
  <!-- 卡片1 -->
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
  
  <!-- 卡片2 -->
  <div class="card">
    <a href="https://blog.reincarnatey.net/2024/0707-qqnt-history-export/" target="_blank">
      <div class="card-image">
        <img src="/thanks/blog.reincarnatey.net.jpeg" alt="">
      </div>
      <div class="card-content">
        <h3>失迹の博客</h3>
        <p>为nt_msg表中列名信息提供了参考</p>
      </div>
    </a>
  </div>

  <!-- 添加更多卡片 -->
</div>

<style>
.card-container {
  display: flex;
  gap: 2rem;
  padding: 2rem;
  flex-wrap: wrap; /* 使卡片在小屏幕上可以换行 */
}

.card {
  background-color: #fff;
  border: 1px solid #e0e0e0;
  border-radius: 10px;
  width: 550px; /* 增加卡片宽度 */
  overflow: hidden;
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
  transition: transform 0.3s ease, box-shadow 0.3s ease;
  text-decoration: none; /* 移除链接下划线 */
}

.card:hover {
  transform: translateY(-5px);
  box-shadow: 0 6px 12px rgba(0, 0, 0, 0.15);
}

.card-image img {
  width: 100%;
  height: 300px; /* 限制图片高度 */
  object-fit: cover; /* 保持图片比例并填充容器 */
}

.card-content {
  padding: 1rem;
}

.card-content h3 {
  font-size: 1.5rem; /* 增加标题字体大小 */
  margin-bottom: 0.5rem;
  color: #333; /* 使标题颜色更深 */
}

.card-content p {
  color: #666;
  font-size: 1rem; /* 增加描述字体大小 */
}
</style>
