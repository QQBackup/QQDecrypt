---
title: c2c_msg_table 字段总览
order: 2
---

# c2c_msg_table 字段总览

`c2c_msg_table` 是 `nt_msg.db` 中保存 QQ 私聊消息的核心数据表。现有的 [`nt_msg.db` 字段页](../db_file_analysis/nt_msg.db) 只保留基础说明；本章节以 [QQBackup/ntqq_msg_db_util](https://github.com/QQBackup/ntqq_msg_db_util) `master` 分支中的 [c2c_msg_table 字段研究](https://github.com/QQBackup/ntqq_msg_db_util/tree/master/db_docs/c2c_msg_table) 为准，集中整理字段关系和消息体结构。

> [!IMPORTANT]
> 下表中的行数、出现率和版本范围来自目标仓库研究使用的样本库（`nt_msg_plain.db`，约 131.8 万行）

## 阅读路线

建议按以下顺序阅读：

1. 先看本页的字段总览，理解消息 ID、会话对象、发送方向和时间字段之间的关系。
2. 再看[消息类型与属性标志](./message-types)，了解 `40011`、`40012`、`40013` 如何共同判断消息类别。
3. 需要解析消息内容时，阅读 [`40800` Protobuf 消息体](./message-body)。
4. 处理表情回应、引用和转发时，参考 [Reaction 与引用消息](./reactions-and-references)。
5. 最后使用[常用查询](./queries)将字段组合成可执行的 SQLite 查询。

## 字段置信度

目标研究使用以下标记：

| 标记 | 含义 |
| --- | --- |
| ✅ 高 | 有全量统计、字段交叉验证或 Protobuf 解码支持 |
| 🔍 中 | 有较强统计规律或局部样本验证，但仍存在推测 |
| ❓ 低 | 仅有样本现象，尚未确认具体协议语义 |
| ❌ 排除 | 已通过全量数据验证排除某种旧解释 |

## 一、消息标识与会话字段

| 字段 | SQLite 类型 | 结论 | 置信度 | 详细报告 |
| --- | --- | --- | --- | --- |
| `40001` | INTEGER | 消息全局唯一 ID，表主键；近似按时间递增，但不是标准 Snowflake ID | ✅ | [40001](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40001.md) |
| `40002` | INTEGER | 客户端生成的消息随机数，用于去重和 ACK 匹配；少量重复属于随机碰撞 | ✅ | [40002](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40002.md) |
| `40003` | INTEGER | 全局倒序序号，值越大越旧；大量会话为 `0`，不适合作为唯一 ID | ✅ | [40003](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40003.md) |
| `40005` | INTEGER | `clientSeq`，客户端 16 位消息序号，值域为 `0`–`65535`，会循环使用 | ✅ | [40005](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40005.md) |
| `40006` | INTEGER | `serverSeq`，服务端操作序号；旧数据中大量为 `0`，非零值与时间高度相关 | ✅ | [40006](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40006.md) |
| `40027` | INTEGER | 本地会话 ID；同一私聊对象的所有消息共享一个值，是客户端的会话分区键 | ✅ | [40027](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40027.md) |
| `40030` | INTEGER | 私聊会话对象 QQ 号；无论收发方向都表示对方，而不是当前账号 | ✅ | [40030](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40030.md) |
| `40020` | TEXT | 实际发送者的 NT UID；与 `40033` 严格一一对应 | ✅ | [40020](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40020.md) |
| `40021` | TEXT | 私聊对端 NT UID；始终对应 `40030`，不是“消息接收者”字段 | ✅ | [40021](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40021.md) |
| `40033` | INTEGER | 实际发送者 QQ 号；与 `40013` 联合判断收发方向 | ✅ | [40033](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40033.md) |

### 会话字段的关键关系

对一条普通私聊消息，可以按下面的方式理解：

| 问题 | 字段 | 解释 |
| --- | --- | --- |
| 这是哪个会话？ | `40027` / `40030` | `40027` 是本地整数会话 ID，`40030` 是对方 QQ 号；两者在样本中一一对应 |
| 谁实际发送？ | `40020` / `40033` | `40020` 是发送者 NT UID，`40033` 是发送者 QQ 号 |
| 消息是发出还是收到？ | `40013` | `0` 通常为收到，`1` 为自己发出，`2` 为自己发出的特殊类型 |
| 私聊另一侧是谁？ | `40021` | 始终是会话对端的 NT UID，发送和接收消息都不改变其角色 |

## 二、时间、协议与状态字段

| 字段 | SQLite 类型 | 结论 | 置信度 | 详细报告 |
| --- | --- | --- | --- | --- |
| `40008` | INTEGER | 预留字段；早期为 NULL，后期恒为 `0` | ❓ | — |
| `40009` | INTEGER | 批量转发标志；普通单发通常为 `0`，少量多目标转发为 `1` | 🔍 | [40009](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40009.md) |
| `40010` | INTEGER | 消息协议格式标志；绝大多数为 `1`，少数特殊值语义未确认 | ❓ | [40010](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40010.md) |
| `40040` | INTEGER | 疑似 NT 多端同步标志；`0` 更接近本机产生，`1` 可能为服务端同步 | ❓ | [40040](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40040.md) |
| `40041` | INTEGER | 几乎恒为 `2`，少量同步消息为 `0`，具体语义未确认 | ❓ | — |
| `40050` | INTEGER | 消息发送时间，Unix 秒级时间戳 | ✅ | — |
| `40052` | INTEGER | 样本中恒为 `0`，语义未知 | ❓ | — |
| `40058` | INTEGER | 消息日期索引，当日 00:00:00 的 Unix 时间戳，按 UTC+8 日期计算 | ✅ | — |
| `40060` | INTEGER | 疑似 NT 协议版本标志；`1` 为旧协议，`0` 为 NT 新协议 | ❓ | [40060](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40060.md) |
| `40093` | TEXT | 发送者昵称、备注名或外显名称 | ✅ | — |
| `40105` | INTEGER | 仅发出方向可能为 `1`，推测为已读/送达标志 | ❓ | [40105](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40105.md) |

## 三、消息体、Reaction 与引用字段

| 字段 | SQLite 类型 | 结论 | 置信度 | 详细报告 |
| --- | --- | --- | --- | --- |
| `40011` | INTEGER | 外层消息内容类型，决定 `40012` 的可取值空间 | ✅ | [40011](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40011.md) |
| `40012` | INTEGER | 消息属性标志；当 `40011=2` 时才是真正的 bitmask | ✅ | [40012](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40012.md) |
| `40013` | INTEGER | 消息发送方向：`0` 收到，`1/2` 发出，`3` 系统消息 | ✅ | [40013](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40013.md) |
| `40026` | INTEGER | 样本中恒为 `0`，语义未知 | ❓ | — |
| `40060` | INTEGER | 协议版本标志，需结合消息体中的 `49154` 解读 | ❓ | [40060](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40060.md) |
| `40062` | BLOB | 极少数固定值的扩展 Blob，语义未知 | ❓ | — |
| `40083` | INTEGER | 样本中恒为 `0` | ❓ | — |
| `40084` | INTEGER | 样本中恒为 `0` | ❓ | — |
| `40090` | TEXT | 样本中为空，可能用于引用摘要等扩展文本 | ❓ | — |
| `40600` | BLOB | 常见固定魔数或版本标记，少量记录可能包含 Protobuf 片段 | ❓ | — |
| `40601` | BLOB | 特殊系统推送消息的附加 Protobuf 数据 | ❓ | — |
| `40605` | BLOB | 极少量固定魔数，暂未发现可区分语义 | ❓ | — |
| `40800` | BLOB | 实际消息内容，Protobuf 编码；文本、图片、文件、通话、转发等均在此字段中 | ✅ | [40800](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40800.md) |
| `40801` | BLOB | 与 `40800` 同步出现的消息摘要，疑似供推送通知使用 | ❓ | — |
| `40850` | INTEGER | Reaction 所回应的原消息 `clientSeq`，对应原消息的 `40005` | ✅ | [40850](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40850.md) |
| `40851` | INTEGER | Reaction 行为自身的 Unix 秒级时间戳 | ✅ | [40851](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40851.md) |
| `40900` | BLOB | 被引用或被回应消息的嵌套 Protobuf 快照 | 🔍 | [40900](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40900.md) |

## 重要结论

- `40001` 是最可靠的消息主键；不要用 `40003`、`40005` 或 `40027` 单独替代它。
- `40027` 适合做会话分组，`40030` 适合展示私聊对象；在样本中两者严格一一对应。
- 判断消息方向时，应同时参考 `40013`、`40030` 和 `40033`，不要只根据发送者昵称判断。
- `40011` 决定外层消息类型，`40012` 只有在 `40011=2` 时才按位解析；其他类型下通常是固定的子状态值。
- `40800` 的顶层结构是重复的 `MsgContent`，一条消息可以包含多个段，因此不能假设一行只对应一个文本或一个媒体对象。
- `40900` 是引用上下文的快照，不应直接当作另一条独立的主表消息。

## 研究来源与更新策略

本页以目标仓库 `master` 分支的 [字段总览](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/summary.md) 和各字段报告为研究依据。样本统计或字段结论发生变化时，应优先对照目标仓库，再同步更新本项目页面。
