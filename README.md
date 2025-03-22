## 致谢
该文档站内容源于[qq-win-db-key](https://github.com/QQBackup/qq-win-db-key)项目，是为了将互联网有关NTQQ数据库解密教程整合而生的，感谢[原作者Young-Lord](https://github.com/Young-Lord)等贡献者的付出

## 贡献须知

请确认项目在编辑后能够正常运行且显示正常。请善用以下命令：

```shell
pnpm run docs:dev
```

如有不明白的操作，请参阅[主题官方教程](https://vitepress.dev/zh/guide/getting-started)。
本项目使用了部分插件，具体可在config.mts中查看

本文档的主要文件储存在docs目录下。新增文件需指定`order`用于侧边栏排序

```plaintext
├─ docs
├─ .vitepress
│  ├─ theme
│  ├─ config.mts
├─ about(关于)
│  ├─ Contributors.md (贡献者)
│  ├─ thanks.md (致谢)
│  ├─ Projects.md (社区项目)
├─ decrypt (解密数据库相关文档)
├─ public (媒体文件存放)
├─ view (读取数据库相关文档)
├─ files.md (文件)
├─ index.md
└─ what-is-this.md (了解项目)
```

