---
title: profile_info_v6
order: 5
---

# profile_info_v6

QQ 用户信息。

| 列名 | 类型 | 含义 | 说明 |
| --- | --- | --- | --- |
| 1001 | str | QID | 设置了才有否则为 null |
| 1002 | int | uin | |
| 20002 | str | 用户昵称 | |
| 20009 | str | 用户备注 | |
| 20011 | str | 个性签名 | |
| 1000 | str | nt_uid | |
| 20004 | str | 头像链接 | s 后面需要带参数，如 s=640/100 |
| 21000 | protobuf | "尊贵身份标识符" | protobuf |
| 20072 | — | 是否为好友 | hex 值为 `c2e60900` 表示为好友 |
| 24105 | protobuf | 个性签名校验值 | |
