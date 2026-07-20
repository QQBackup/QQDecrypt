---
title: login.db
order: 8
---

# login.db

`login.db` 存贮 QQ NT 客户端本地缓存的**已登录/快速登录账号列表**（uin、uid、昵称、头像、A1 登录票据、最近登录时间等）。

与 `nt_msg.db` 等库不同，它的密钥**无需 hook 获取**——密钥是硬编码在 QQ 客户端里的固定值。

## 密钥

`login.db` 的 SQLCipher 密钥是一个**硬编码在 QQ NT 客户端中的固定字符串**，对所有账号、所有设备都相同：

```
BD156D6710D54D8782F4
```

该字符串长度为 20 字节。

> [!TIP]
> 在 Windows 平台 hook `sqlite3_key_v2` 获取 `nt_msg.db` 密钥时，有概率会额外 hook 到这个长度为 20 的 key——它就是 `login.db` 的密钥，属于正常现象。参见 [NTQQ (Windows) 教程](/decrypt/extract/NTQQ%20(Windows))。

## 加密参数

`login.db` 的加密方式与 `nt_msg.db` 等库**完全一致**：同为 SQLCipher v4，同样在真正的 SQLCipher 数据流前有 1024 字节的文件头需要跳过，SQLCipher 参数也相同：

| 参数 | 值 |
| --- | --- |
| 文件头 | 1024 字节（同 `nt_msg.db`） |
| `cipher_page_size` | 4096 |
| `kdf_iter` | 4000 |
| `cipher_kdf_algorithm` | `PBKDF2_HMAC_SHA512`（随版本探测） |
| `cipher_hmac_algorithm` | `HMAC_SHA1` / `HMAC_SHA256`（随版本探测） |
| cipher | `aes-256-cbc` |

因此，解密流程与 [统一解密 NTQQ 数据库](/decrypt/decrypt_db) 完全相同，只需将密钥替换为上文的固定字符串 `BD156D6710D54D8782F4` 即可。

> [!NOTE]
> `kdf_iter`、HMAC 算法等与其它库共用同一套参数。唯一区别只是：`login.db` 的密钥是公开固定值，而 `nt_msg.db` 的密钥每个账号不同、需要 hook 获取。

## 表列表

| 表名 | 说明 | 文档 |
| --- | --- | --- |
| `login_table` | 已登录账号列表 | [login_table](./login_table) |
