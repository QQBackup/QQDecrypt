---
title: Reaction 与引用消息
order: 4
---

# Reaction 与引用消息

Reaction、引用回复和转发消息会同时使用主表字段与嵌套 Protobuf。目标仓库的原始报告见 [`40850.md`](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40850.md)、[`40851.md`](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40851.md) 和 [`40900.md`](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/db_docs/c2c_msg_table/40900.md)。

## Reaction 消息

Reaction 通常表现为 `40011=9`。一条 Reaction 由下面两个字段描述其所回应的原消息：

| 字段 | 含义 |
| --- | --- |
| `40850` | 被回应原消息的 `clientSeq`，对应原消息的 `40005` |
| `40851` | Reaction 行为自身的发送时间，Unix 秒级时间戳 |

非 Reaction 消息中，这两个字段通常为 `0`。在目标样本中，两字段几乎总是同时出现。

### 定位被回应消息

可以先按同一会话和 `clientSeq` 查找候选消息：

```sql
SELECT
  rowid,
  "40001" AS msg_id,
  "40005" AS client_seq,
  "40013" AS direction,
  "40050" AS sent_at,
  "40800" AS body
FROM c2c_msg_table
WHERE "40030" = :peer_qq
  AND "40005" = :reaction_client_seq
  AND "40011" <> 9
ORDER BY "40050";
```

由于 `40005` 是 16 位循环序号，同一会话可能出现多个候选。应优先选择发送时间早于 Reaction 时间、且与上下文最接近的一条，而不能把 `40850` 当作全局唯一 ID。

## `40900`：引用消息快照

`40900` 是一段嵌套的 Protobuf 快照，用于在不重新查询主表的情况下展示被引用或被回应消息的上下文。

| 取值 | 含义 |
| --- | --- |
| NULL | 普通消息，没有引用上下文 |
| `a2 fc 13 00` | 字段存在但没有实际子消息的空占位符 |
| 其他变长 BLOB | 一个或多个被引用消息的部分字段快照 |

快照内部沿用主表的字段编号体系，可以看到 `40001`、`40011`、`40013`、`40020` 等字段；它不是一条可以直接当作主表行插入的独立记录。

## 解析时的注意事项

- Reaction 的原消息定位使用 `40030 + 40005`，必要时再结合时间筛选。
- `40900` 的内部消息可能只有部分字段，不能假设所有主表列都存在。
- `40800`、`40900` 都可能包含递归或重复结构，解析器应保留原始 BLOB 以便复核。
- 旧版合并转发和新版 NT 合并转发的结构不同，分别参考 `40011=8` 和 `40011=11` 的说明。
