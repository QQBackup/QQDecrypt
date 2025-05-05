---
title: files_in_chat.db
order: 6
---

# files_in_chat.db
接受的媒体文件信息
## files_in_chat_table

| 列名  | 含义              | 注                                               |
| ----- | ----------------- | ------------------------------------------------ |
| 45001 | clientSeq         | 接收的图片顺序，在本地数据库中递增               |
| 82300 | msgRandom         | 消息随机值，用于对消息去重                       |
| 40001 | msgid             | 消息ID                                           |
| 45403 | filepath          | 文件存贮路径                                     |
| 45404 | thumbpath         | 预览图缓存路径（多见于视频）                     |
| 40020 | nt_uid            | 发送者nt_uid                                     |
| 40021 | peeruid/senderuin | 来源群号/QQ号                                    |
| 40010 | chatType          | 聊天类型，具体[见此](/view/db文件分析/nt_msg.db) |
| 82301 | 未查明            |                                                  |
| 45002 | ElementType       |                                                  |
| 45003 | subElementType    |                                                  |
| 45402 | fileName          | 文件名                                           |
| 45405 | fileSize          | 文件大小(KB)                                     |
| 40050 | msgTime           | 发送时间                                         |
| 82302 | original          | 是否为原图，1为是，0为否                         |

* 这里面主要存贮的是有关下载文件、语音文件、视频文件的信息

  图片大部分`45403`值为空







