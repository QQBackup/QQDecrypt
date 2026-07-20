---
title: group_bulletin
order: 2
---

# group_bulletin

群公告（只有最新一条会被存贮）。

| 列名 | 类型 | 含义 | 说明 |
| --- | --- | --- | --- |
| 60001 | int | peerUid（群号） | |
| 64205 | protobuf | 群公告内容 | protobuf 格式 |

### 64205 Protobuf 结构

| Byte Range | Field Number | Type | 含义 |
| --- | --- | --- | --- |
| 0-1089 | 64205 | protobuf | |
| ├─ 0-8 | 60001 | varint | 群号 |
| ├─ 8-1084 | 64202 | protobuf | |
| │  ├─ 0-8 | 60001 | varint | 群号 |
| │  ├─ 8-36 | 64221 | string | 发布公告者 nt_uid |
| │  ├─ 40-76 | 64223 | string | fid |
| │  ├─ 80-88 | 64225 | varint | msgTime（消息发布时间） |
| │  ├─ 88-96 | 64226 | varint | ctime（公告发布时间） |
| │  └─ 4-17 | 64452 | string | 群公告内容 |
