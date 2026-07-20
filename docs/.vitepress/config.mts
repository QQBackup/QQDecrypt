import { defineConfig } from 'vitepress';
import { generateSidebar } from 'vitepress-sidebar';

const buildDate = new Date(process.env.DOCS_LAST_UPDATED ?? Date.now());
const lastUpdated = Number.isNaN(buildDate.getTime())
  ? new Date().toISOString()
  : buildDate.toISOString();

const generatedSidebar = generateSidebar({
  documentRootPath: 'docs',
  useTitleFromFrontmatter:true,
  useFolderTitleFromIndexFile:true,
  frontmatterTitleFieldName:'title',
  excludeFilesByFrontmatterFieldName: 'hidesidebar',
  hyphenToSpace: true,
  sortMenusByFrontmatterOrder: true,
  useFolderLinkFromIndexFile: true
});

const sidebarItems = Array.isArray(generatedSidebar) ? generatedSidebar : [];
const decryptSidebar = sidebarItems.find((item) => item.text === '解密教程');
const decryptItems = decryptSidebar?.items ?? [];
const extractionSidebar = decryptItems.find((item) => item.text === '分平台提取');
const decodeSidebar = decryptItems.find((item) => item.text === '统一解密 NTQQ 数据库');
const descriptionSidebar = decryptItems.find((item) => item.text === '说明(必看)');
const viewSidebar = sidebarItems.find((item) => item.text === '数据库解析');
const researchSidebar = sidebarItems.find((item) => item.text === '研究笔记');
const aboutSidebar = sidebarItems.find((item) => item.text === '关于');
const viewItems = viewSidebar?.items ?? [];

export default defineConfig({
  base: '/QQDecrypt/',
  title: 'QQDecrypt',
  description: '解密QQ聊天数据库',
  lang: 'zh-CN',
  appearance: true,
  head: [
    ['link', { rel: 'icon', href: '/icons/favicon.ico' }],
  ],
  vite: {
    plugins: [],
  },
  sitemap: {
    hostname: 'https://qqbackup.github.io/QQDecrypt',
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
    lastUpdated: { text: '最后更新于' },
    sidebar: [
      ...(decryptSidebar
        ? [{
            ...decryptSidebar,
            text: '开始',
            link: undefined,
            items: [
              ...(descriptionSidebar
                ? [{ ...descriptionSidebar, text: '说明（必看）' }]
                : []),
            ],
          }]
        : []),
      ...(extractionSidebar
        ? [{
            ...extractionSidebar,
            text: '提取数据库密钥',
            link: '/decrypt/extract/',
            items: [
              ...(extractionSidebar.items ?? []),
            ],
          }]
        : []),
      ...(decodeSidebar
        ? [{ text: '解密数据库', link: decodeSidebar.link, items: [] }]
        : []),
      ...(viewSidebar
        ? [{ ...viewSidebar, text: '数据库内容解析', link: undefined, items: viewItems }]
        : []),
      ...(researchSidebar ? [researchSidebar] : []),
      ...(aboutSidebar
        ? [{
            ...aboutSidebar,
            link: undefined,
            items: [
              { text: '贡献者名单', link: '/about/contributors' },
              { text: '项目致谢', link: '/about/thanks' },
              { text: '使用协议', link: '/about/LICENSE' },
              { text: '社区项目', link: '/about/projects' },
              { text: '碎碎念', link: '/about/碎碎念' },
            ],
          }]
        : []),
    ],
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
    ],
    footer: {
      message: `最后更新时间：${lastUpdated}<br>CC BY-NC-SA 4.0 <a href="/about/LICENSE"> License</a>`,
      copyright: '<a href="/about/LICENSE">Copyright © 2026 </a>',
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
    ],
    outline: {
      level: [2, 3],
      label: '页面目录',
    },
  }
});
