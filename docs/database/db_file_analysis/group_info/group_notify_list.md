---
title: group_notify_list
order: 1
---

# group_notify_list / doubt_group_notify_list

群通知。两张表结构相同，`group_notify_list` 含操作者信息（61006），`doubt_group_notify_list` 含操作人信息（61007）。

| 列名 | 类型 | 含义 | 说明 |
| --- | --- | --- | --- |
| 61001 | int | 消息时间戳 | 删除末三位并使用毫秒级时间戳 |
| 61002 | int | 状态 | 详见[下方](#61001-说明) |
| 61003 | int | 验证状态 | 1=过滤，0=正常，2=同意，3=拒绝，4=忽略 |
| 61004 | protobuf | 群组信息 | 群号与群昵称 |
| 61005 | protobuf | 被操作者 | nt_uid 与 QQ 昵称 |
| 61006 | protobuf | 操作者 | 仅 group_notify_list，nt_uid 与 QQ 昵称 |
| 61007 | protobuf | 操作人信息 | 仅 doubt_group_notify_list，nt_uid 与 QQ 昵称 |
| 61008 | int | 操作时间戳 | 秒级时间戳 |
| 61009 | | | |
| 61010 | str | 对方附加说明 | |
| 61011 | str | 系统附加说明 | 如风险提示 |

### 61001 说明

| 值 | 含义 |
| --- | --- |
| 1 | 申请加群 |
| 3 | 被设置为管理员 |
| 6 | 被移出群聊 |
| 11 | 被管理员拒绝加入 |
| 13 | 自主退出群聊 |
| 15 | 被取消管理员权限 |
