---
title: recent_contact_v3_table
order: 5
---

# recent_contact_v3_table

聊天对象资料信息。

| 列名 | 类型 | 含义 | 说明 |
| --- | --- | --- | --- |
| 40010 | int | chatType | 聊天类型 |
| 40021 | str | peeruid / nt_uid | |
| 40030 | int | uin | c2c 才有此值，group 此值均为 0 |
| 40051 | protobuf | lastMessage | 最后一条消息 |
| 40041 | int | sendStatus | 发送状态 |
| 40050 | int | lastTime | 最后一条消息的时间戳，单位：秒 |
| 40003 | str | msgSeq | |
| 40094 | str | source | 来源 |
| 40093 | str | sendNickName | |
| 40090 | str | sendMemberName | |
| 40095 | str | sendremarkName | 成员备注名称 |
| 40020 | str | nt_uid | |
| 40033 | int | uin | |
| 41110 | str | groupavatar | 群头像本地缓存路径 |
| 41135 | str | | 当通过群聊发起聊天时，显示对应群昵称 |
