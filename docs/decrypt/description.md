---
title: 说明(必看)
prev: false
order: 1
---


> [!WARNING] 警告
> 教程中可能对数据库进行不可逆操作，请注意备份数据库文件
>
>尽管已经经过实验验证可用，本仓库中给出的指引**可能**有**破坏聊天记录**或**导致封号**的风险，强烈建议在自行审查代码、评估>风险后使用。
>如果您确实要使用，**建议**进行以下操作，以减小风险：
>- 先将聊天记录使用其他更保险的方式**导出**，比如 PCQQ (Windows) 自带的“导出消息记录（`mht`格式）
>- 做好**备份**，比如 安卓端使用系统的备份功能、电脑端全盘备份
>- 将聊天记录使用官方的“**迁移聊天记录**”功能，转移到不常用设备或虚拟机后操作
>- 尽可能选择**不注入 QQ 进程**、**不对 QQ 安装包进行修改**的方式（如：不使用 QAuxiliary；不使用 Frida；不使用 gdb；使用安卓系统自带的备份功能，导出数据库后提取）
>
## 说明
本仓库**并非面向纯小白的教程**，而是在**假设您已经有一定逆向、动态调试等知识**的前提下提供的参考资料。尽管开发者可能会为了便捷提供详细教程或完整脚本，您也应当**有一定自行修改、调试的能力**。另外，请在提问前先**完整阅读** [qq-win-db-key](https://github.com/QQBackup/qq-win-db-key/issues) 与 [QQ-History-Backup](https://github.com/QQBackup/QQ-History-Backup/issues) 的**所有 issue**。如果您无论怎么改都跑不起来，请自由开 [issue](https://github.com/QQBackup/qq-win-db-key/issues)。（当然如果您感觉教程太烂了或者愿意补充，也可以直接开 PR，记得`@QQBackup`以通知维护者 merge）

**如果你不太懂怎么用**：强烈建议自行在B站、各个博客内寻找详细教程。

本项目仅供学习交流使用，严禁用于任何违反中国大陆法律法规、您所在地区法律法规、[QQ软件许可及服务协议](https://rule.tencent.com/rule/preview/46a15f24-e42c-4cb6-a308-2347139b1201)的行为，开发者不承担任何相关行为导致的直接或间接责任。

本项目不对生成内容的完整性、准确性作任何担保，生成的一切内容**不可用于法律取证**，您不应当将其用于学习与交流外的任何用途。

本项目基本遵循`LICENSE`里的开源协议，基本接近**标识项目地址**且**禁止商用**；部分文件同时以不同的协议发布，具体参见文件内对应的声明。

本教程中所需要的文件可在网站右上角“文件”栏目中找到，可能会滞后于原仓库[qq-win-db-key](https://github.com/QQBackup/qq-win-db-key)更新，若有需要可前往GitHub下载最新版本

## 解密流程

本栏目按处理阶段分为两个区：

1. [分平台提取](./extract/)：在 QQ 所在的平台上，只获取**原始数据库文件**和对应的 **key**，不在源设备上改写数据库。
2. [统一解密](./decode_db)：将原始数据库和 key 复制到 Windows，使用唯一指定的脚本导出未加密的原始 SQLite 数据库。

解密完成后，请参阅[读取数据库](../view/read_db)。

## 当前验证状态

| 平台教程 | 状态 | 已确认版本 | 确认时间 |
| --- | --- | --- | --- |
| NTQQ (Windows) | 已确认可用 | `9.9.32-51246` | `2026-07-19` |
| Android、iOS、Linux、macOS、PCQQ (Windows) | 尚未确认 | — | — |

如果你确认某个平台的教程依然可用，请打开 [PR](https://github.com/QQBackup/QQDecrypt/pulls) 或 [issue](https://github.com/QQBackup/QQDecrypt/issues) 通知维护者，并注明 QQ 版本、系统版本、架构，以及是否成功提取原始数据库和 key。

## 网站介绍

本站内容基于开源项目 [qq-win-db-key](https://github.com/QQBackup/qq-win-db-key) 构建，旨在提供跨平台 QQ 聊天数据库解密指南。特别感谢[原作者 Young-Lord](https://github.com/Young-Lord)等开发者的开拓性工作，未来计划逐步扩展数据库解析方案。

有任何问题和建议，欢迎提交 [issue](https://github.com/QQBackup/QQDecrypt/issues/new/choose)。

## 寻求合作者

欢迎一切能够实现相关数据解析算法、乐意适配其他平台的开发者参与本项目以及 [QQ-History-Backup](https://github.com/QQBackup/QQ-History-Backup/tree/dev) 的开发，直接提交 PR 或 issue 即可。文档的写作风格可以随意（但建议认真填写图片的替代文本和文件名），也可以只加入一个指向你的仓库或博客等内容的链接。

## 隐私政策

- 不收集或存储用户身份信息
- 禁用 Cookie 不影响网站功能
- 网站使用 Vercel 静态部署托管
