---
title: NTQQ 读取数据库
description: NTQQ 读取数据库说明
prev: false
order: 1
---

# NTQQ 读取数据库

阅读本文前，您应当已经通过其他方法，获取到了数据库的已解密文件。如果没有，请参考：[NTQQ 解密数据库](/decrypt/NTQQ%20解密数据库.md)。

以下以 `nt_msg.db` 代指已解密的数据库文件。

目前已知消息格式为`protobuf`，较为复杂，可使用 [CyberChef](https://gchq.github.io/CyberChef/#recipe=Protobuf_Decode('',false,false)Decode_text('UTF-8%20(65001)')) 工具进行自动解析，相关解析代码可以参考[提取QQ NT数据库 group_msg_table 中的纯文本](https://github.com/QQBackup/ntdb-plaintext-extracter)、[这份 Python 代码](https://github.com/QQBackup/QQ-History-Backup/issues/9#issuecomment-1929105881)与[这份 protobuf 定义](https://github.com/QQBackup/qq-win-db-key/issues/38#issuecomment-2294619828)，完整实现暂无，欢迎贡献。

## 社区项目

网站收集了互联网上其他有关解析 NTQQ 数据库的开源项目，具体可在[这里](/about/Projects)查看