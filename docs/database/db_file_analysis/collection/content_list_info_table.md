---
title: content_list_info_table
order: 2
---

# content_list_info_table

聊天记录和笔记类收藏才存在此信息。

| 列名 | 类型 | 含义 | 注 |
| --- | --- | --- | --- |
| 180700 | str | sid | 与 180001 对应，可用于确定收藏消息 |
| 180720 | int | last updated time | 与 180011 对应，最后编辑时间 |
| 180708 | protobuf | favorite content | 收藏实际内容 |
