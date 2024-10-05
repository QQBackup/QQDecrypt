## 致谢
该文档站内容源于[qq-win-db-key](https://github.com/QQBackup/qq-win-db-key)项目，是为了更加方便于查找有而将教程进行整合而生的，感谢[原作者Young-Lord](https://github.com/Young-Lord)等贡献者的付出
本项目用于导出并解密 PCQQ / QQ NT 等软件的聊天记录数据库。

仍在测试阶段

## 贡献须知

请确认项目在编辑后能够正常运行且显示正常。请善用以下命令：

```shell
npm run docs:dev
```

如有不明白的操作，请参阅[主题官方教程](https://vitepress.dev/zh/guide/getting-started)。
本项目使用了部分插件，具体可在config.mts中查看

本文档的主要文件储存在docx目录下。新增文件无需编辑目录，目录会自动生成。

```shell
├─ docs
│  ├─ .vitepress(VitePress 配置文件、开发服务器缓存、构建输出和可选主题自定义代码的位置)
│  │  ├─theme
|  |  └─ config.mts  
│  ├─Contributors（贡献者） 
│  ├─decrypt（解密相关文档）     
│  ├─thanks（致谢）
│  ├─public（媒体文件存放）                                          
│  │ ├─img（媒体文件存放）                                  
│  │ ├─icon                                                                                        
│  ├─ index.md
│  └─ introduce.md（了解项目）
└─ package.json
```