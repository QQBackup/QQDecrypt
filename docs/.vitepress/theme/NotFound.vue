<template>
  <div class="not-found-container">
    <img class="not-found-image" src="/icons/404.png" alt="404" />
    <h1 class="title">界面被猫猫吃掉啦</h1>
    <p class="description">这可能是由于内容被移到了别处</p>
    <a class="home-link" href="https://qqbackup.github.io/QQDecrypt">点我返回主页</a>
  </div>
</template>

<style scoped>
.not-found-container {
  text-align: center;
  padding: 2rem;
  min-height: 80vh;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
}

.not-found-image {
  width: 200px;
  margin-bottom: 1.5rem;
}

.title {
  font-size: 1.5rem;
  margin-bottom: 0.5rem;
}

.description {
  color: var(--vp-c-text-2);
  margin-bottom: 1.5rem;
}

.home-link {
  display: inline-block;
  color: var(--vp-c-brand);
  cursor: pointer;
  font-weight: 500;
  text-decoration: none;
  padding: 8px 16px;
  border-radius: 4px;
  background-color: var(--vp-c-brand-light);
  transition: all 0.2s;
}

.home-link:hover {
  background-color: var(--vp-c-brand);
  color: white;
  text-decoration: none;
}
</style>