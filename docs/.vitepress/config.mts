import { defineConfig } from 'vitepress';
import { generateSidebar } from 'vitepress-sidebar';

export default defineConfig({
  title: 'QQDecrypt',
  description: '解密QQ聊天数据库',
  lang: 'zh-CN',
  head: [
    ['link', { rel: 'icon', href: '/icons/favicon.ico' }],
  ],
  vite: {
    plugins: [],
  },
  sitemap: {
    hostname: 'https://docs.aaqwq.top',
  },
  markdown: {
    lineNumbers: true,
    config: (md) => {
    },
    image: {
      lazyLoading: true,
    },
  },
  themeConfig: {  
    appearance: true, 
    lastUpdated: { text: '最后更新于' },
    sidebar: generateSidebar({
      documentRootPath: 'docs',
      useTitleFromFrontmatter:true,
      useFolderTitleFromIndexFile:true, 
      frontmatterTitleFieldName:'title',      
      excludeFilesByFrontmatterFieldName: 'hidesidebar', 
      hyphenToSpace: true,
      sortMenusByFrontmatterOrder: true,
      useFolderLinkFromIndexFile: true
    }),
    nav: [
      { text: '主页', link: '/' },
      {
        text: '关于',
        items: [
          { text: '贡献者名单', link: '/about/contributors' },
          { text: '项目致谢', link: '/about/thanks' },
          { text: '使用协议', link: '/about/LICENSE' },
          { text: '社区项目', link: '/about/projects' }
        ]
      },
      { text: '文件', link: 'https://github.com/QQBackup/QQDecrypt/tree/main/docs/public/files' },
    ],
    footer: {
      message: ' CC BY-NC-SA 4.0 <a href="/about/LICENSE"> License</a>',
      copyright: '<a href="/about/碎碎念">Copyright © 2025 </a>',
    },
    editLink: {
      pattern: 'https://github.com/QQBackup/QQDecrypt/edit/main/docs/:path',
      text: '在 GitHub 上编辑此页',
    },
    docFooter: { 
      prev: '上一篇',
      next: '下一篇'
    },
    darkModeSwitchLabel: '亮/暗模式',
    lightModeSwitchTitle: '调整为亮色模式',
    darkModeSwitchTitle: '调整为暗色模式',
    sidebarMenuLabel: '菜单',
    returnToTopLabel: '回到顶部',
    socialLinks: [
      { icon: 'github', link: 'https://github.com/QQBackup/QQDecrypt' }, 
      { icon: 'telegram', link: 'https://t.me/+0mPSrIRky-hjNDAx' },   
    ],
    outline: {
      level: [2, 3],
      label: '页面目录',
    },
  }
});