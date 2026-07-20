---
title: 常用查询
order: 5
---

# c2c_msg_table 常用查询

以下查询以已解密的 `nt_msg_plain.db` 为例。字段名全部使用双引号，是因为数据库列名为数字；实际使用时请根据自己的数据库版本检查列是否存在。

## 查看表结构和索引

```sql
PRAGMA table_info(c2c_msg_table);

SELECT name, sql
FROM sqlite_master
WHERE type IN ('table', 'index')
  AND (tbl_name = 'c2c_msg_table' OR name LIKE '%40027%');
```

目标研究发现，多个索引以 `40027` 开头，因此按本地会话 ID 过滤通常比全表扫描更符合原表设计。

## 按私聊对象统计消息

```sql
SELECT
  "40030" AS peer_qq,
  COUNT(*) AS message_count,
  MIN("40050") AS first_time,
  MAX("40050") AS last_time
FROM c2c_msg_table
GROUP BY "40030"
ORDER BY last_time DESC;
```

如果数据库中存在 NULL 或异常时间值，建议先对 `40050` 做显式过滤；上例的 `MIN` 写法只用于展示字段组合，实际项目中可以直接使用 `MIN("40050")`。

## 区分收发方向

```sql
SELECT
  "40013" AS direction,
  CASE "40013"
    WHEN 0 THEN '收到'
    WHEN 1 THEN '自己发送'
    WHEN 2 THEN '自己发送（特殊）'
    WHEN 3 THEN '系统消息'
    ELSE '其他/迁移噪音'
  END AS direction_name,
  COUNT(*) AS message_count
FROM c2c_msg_table
GROUP BY "40013"
ORDER BY "40013";
```

对于普通消息，可以同时检查：

```sql
SELECT
  "40030" AS peer_qq,
  "40033" AS sender_qq,
  "40013" AS direction,
  COUNT(*) AS count
FROM c2c_msg_table
GROUP BY "40030", "40033", "40013";
```

通常 `40013=0` 时 `sender_qq` 等于 `peer_qq`；但系统消息、迁移数据和特殊消息不能套用这一简化规则。

## 按日期统计消息

```sql
SELECT
  datetime("40050", 'unixepoch', '+8 hours') AS sent_at_utc8,
  "40058" AS day_start,
  COUNT(*) AS message_count
FROM c2c_msg_table
WHERE "40050" > 0
GROUP BY "40058"
ORDER BY "40058";
```

`40050` 是消息发送时间，`40058` 是按 UTC+8 日期计算的日索引。展示给用户时，建议将 Unix 秒转换为明确的时区时间。

## 查找文本消息

文本正文位于 `40800` 的 Protobuf 中，不能直接用 SQLite 的 `LIKE` 对 BLOB 做可靠搜索。若只需要全文搜索，建议使用目标仓库的 `3.convert.py` 生成结构化导出库，再查询其 `messages.text` 字段。

```sql
SELECT id, msg_id, timestamp, direction, sender_qq, peer_qq, text
FROM messages
WHERE text MATCH :keyword
ORDER BY timestamp;
```

`messages` 是转换脚本生成的导出表，不是原始 `c2c_msg_table` 的内置表；没有执行转换脚本时，上述查询不会存在。

## 查找 Reaction

```sql
SELECT
  rowid,
  "40030" AS peer_qq,
  "40050" AS row_time,
  "40850" AS target_client_seq,
  "40851" AS reaction_time
FROM c2c_msg_table
WHERE "40011" = 9
ORDER BY "40851";
```

再使用[Reaction 与引用消息](./reactions-and-references)中的条件定位被回应消息。

## 保留原始字段

解析 `40800` 或 `40900` 时，即使某个字段暂时无法解释，也建议保留原始 BLOB、消息主键 `40001`、会话对象 `40030` 和时间 `40050`。研究结论可能随着 QQ 版本和新样本变化，保留原始数据才能重新验证。
