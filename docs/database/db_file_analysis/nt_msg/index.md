---
title: nt_msg.db
order: 1
---

# nt_msg.db

聊天消息数据库，包含私聊、群聊消息以及会话相关数据。

## 表列表

| 表名 | 说明 | 文档 |
| --- | --- | --- |
| `group_msg_table` | 群聊消息 | [group_msg_table](./group_msg_table)（详细研究见[上游仓库](https://github.com/QQBackup/nt_msg_db_util/blob/master/db_docs/group_msg_table/summary.md)） |
| `c2c_msg_table` | 私聊消息 | [c2c_msg_table](./c2c_msg_table)（详细研究见[上游仓库](https://github.com/QQBackup/nt_msg_db_util/blob/master/db_docs/c2c_msg_table/summary.md)） |
| `group_at_me_msg` | 被 @ 消息 | [group_at_me_msg](./group_at_me_msg) |
| `recent_contact_top_table` | 置顶聊天 | [recent_contact_top_table](./recent_contact_top_table) |
| `recent_contact_v3_table` | 聊天对象资料 | [recent_contact_v3_table](./recent_contact_v3_table) |

> [!TIP] 贡献资料
> - [KingsZNHONE](https://github.com/kingsznhone) 对百万行聊天数据库进行统计分析
> - [Yumeka](https://github.com/miniyu157) 整理出 c2c_msg_table 中 40800 列约 260 个 protobuf 字段，详见 [proto_maps.py](https://github.com/miniyu157/qq-dump/blob/main/chat_export/proto_maps.py)
>
> 感谢 [学习笔记 | QQNT 聊天记录导出](https://blog.reincarnatey.net/2024/0707-qqnt-history-export/) 与 [GroupChatAnnualReport](https://github.com/mobyw/GroupChatAnnualReport)
