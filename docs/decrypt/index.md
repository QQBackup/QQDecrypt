---
title: 解密教程
prev: false
next: false
editLink: false
lastUpdated: false
---

# 解密教程

请先阅读[说明（必看）](./description)。本栏目按处理阶段分为两个区：

1. [分平台提取](./extract/)：在 QQ 所在的平台上，只获取**原始数据库文件**和对应的 **key**，不在源设备上改写数据库。
2. [统一解密](./decode_db)：将原始数据库和 key 复制到 Windows，使用唯一指定的脚本导出未加密的原始 SQLite 数据库。

解密完成后，请参阅[读取数据库](../view/read_db)。

## 当前验证状态

| 平台教程 | 状态 | 已确认版本 | 确认时间 |
| --- | --- | --- | --- |
| NTQQ (Windows) | 已确认可用 | `9.9.32-51246` | `2026-07-19` |
| Android、iOS、Linux、macOS、PCQQ (Windows) | 尚未确认 | — | — |

如果你确认某个平台的教程依然可用，请打开 [PR](https://github.com/QQBackup/QQDecrypt/pulls) 或 [issue](https://github.com/QQBackup/QQDecrypt/issues) 通知维护者，并注明 QQ 版本、系统版本、架构，以及是否成功提取原始数据库和 key。
