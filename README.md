# QQDecrypt 文档库

QQ 聊天数据库解密与解析文档站，在线阅读地址：[qqbackup.github.io/QQDecrypt](https://qqbackup.github.io/QQDecrypt/)。

本仓库只负责文档站内容、图片和用于下载的示例脚本。脚本的开发与维护在 [qq-win-db-key](https://github.com/QQBackup/qq-win-db-key)；教程中需要的文件可能会滞后于代码库，请以代码库中的版本为准。

## 本地预览

```shell
npm install
npm run docs:dev
```

构建检查：

```shell
npm run docs:build
```

## 目录约定

- `docs/decrypt/`：解密入口和 Windows 统一解密流程。
- `docs/decrypt/extract/`：按平台获取原始数据库与 key 的教程。
- `docs/database/`：已解密数据库的读取、表结构和消息导出说明。
- `docs/research/`：研究笔记和机制分析，不作为稳定操作指南。
- `docs/about/`：项目说明、协议、贡献者和社区项目。
- `docs/public/`：站点图片和可下载脚本。

新增页面请放入对应目录，并设置 `title` 与 `order` frontmatter，方便自动生成侧边栏。

## 致谢

本文档站源于 [qq-win-db-key](https://github.com/QQBackup/qq-win-db-key)，感谢 [Young-Lord](https://github.com/Young-Lord) 等贡献者的开拓和维护。

