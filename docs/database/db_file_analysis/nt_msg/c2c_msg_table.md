---
title: c2c_msg_table
order: 2
---

# c2c_msg_table

私聊消息表。本项目的字段研究已迁移至独立仓库：

> [QQBackup/ntqq_msg_db_util — c2c_msg_table 字段总览](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/summary.md)

## 常用外层字段速查

| 列名 | 类型 | 含义 | 说明 |
| --- | --- | --- | --- |
| `40001` | int | 消息唯一 ID | 表主键 |
| `40027` | int | 本地会话 ID | 适合按私聊会话分组 |
| `40030` | int | 私聊对象 QQ 号 | 无论收发方向都表示对方 |
| `40033` | int | 发送者 QQ 号 | 实际发送消息的账号 |
| `40050` | int | 消息时间 | Unix 秒级时间戳 |
| `40058` | int | 消息日期 | UTC+8 当日 00:00:00 的时间戳 |
| `40093` | str | 发送者昵称 | QQ 昵称或备注名 |
| `40800` | bytes | 消息内容 | Protobuf 格式，详见上游文档 |
