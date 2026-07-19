---
title: 分平台提取
order: 2
---

# 分平台提取

本区只负责从 QQ 所在的平台取得两项输入：**原始数据库文件**和对应的 **key**。请不要在 Android、iOS、Linux 或 macOS 上直接改写、解密或转换数据库。

完成提取后，将数据库原文件和 key 一起复制到 Windows，再进入[统一解密](../decode_db)。统一解密的输出是未加密的原始 SQLite 数据库 `nt_msg_plain.db`。

## 平台教程

- [NTQQ (Windows)](./NTQQ%20(Windows))
- [NTQQ (Android)](./NTQQ%20(Android))
- [NTQQ (iOS)](./NTQQ%20(iOS))
- [NTQQ (Linux)](./NTQQ%20(Linux))
- [NTQQ (Linux)（GDB）](./NTQQ%20(Linux)%20(GDB))
- [NTQQ (macOS ARM)](./NTQQ%20(macOS%20ARM))
- [NTQQ (macOS ARM，无需关闭 SIP)](./NTQQ%20(macOS%20ARM%EF%BC%8C%E6%97%A0%E9%9C%80%E5%85%B3%E9%97%AD%20SIP))
- [NTQQ (macOS x86)](./NTQQ%20(macOS%20x86))
- [安卓版 QQ 及 TIM](./AndroidQQ)
- [iOS 版 QQ（旧架构）](./IOSQQ)
- [PCQQ (非 NT 架构)](./PCQQ%20(Windows))

如果你确认某个平台教程依然可用，请打开 [PR](https://github.com/QQBackup/QQDecrypt/pulls) 或 [issue](https://github.com/QQBackup/QQDecrypt/issues) 通知维护者，并注明 QQ 版本、系统版本、架构，以及是否成功提取原始数据库和 key。
