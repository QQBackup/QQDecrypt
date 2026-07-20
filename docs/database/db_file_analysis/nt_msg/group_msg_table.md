---
title: group_msg_table
order: 1
---

# group_msg_table

群聊消息表。部分列含义如下：

| 列名 | 类型 | MsgRecord | 说明 |
| --- | --- | --- | --- |
| 40001 | int | msgId | 消息 ID，具有唯一性 |
| 40002 | int | msgRandom | 消息随机值，用于对消息去重 |
| 40003 | int | msgSeq | 群聊消息 ID，在每个聊天中依次递增 |
| 40010 | int | chatType | 聊天类型，私聊为 1，群聊为 2，频道为 4，公众号为 103，企业客服为 102，临时会话为 100 |
| 40011 | int | msgType | 消息类型，详见[消息类型](#40011-消息类型) |
| 40012 | int | subMsgType | pb 消息类型，详见[子消息类型](#40012-子消息类型) |
| 40013 | int | sendType | 发送标志：本机发送=1，其他客户端发送=2，别人发的=0，转发=5，已退出/被封禁的消息中为当日整点时间戳 |
| 40020 | str | senderuid | nt_uid，对应 nt_uid_mapping_table |
| 40021 | str | peeruid | 会话 ID |
| 40027 | int | peeruin | 会话 ID |
| 40041 | int | sendStatus | 发送状态：2=成功，0=发送被阻止，1=尚未发送成功，3=消息被和谐 |
| 40050 | int | msgTime | 发送消息时的完整时间戳，UTC+8 |
| 40090 | str | sendMemberName | 发送者群名片，旧版格式为 `name(12345)` 或 `name<i@example.com>`，NT 中为群名片 |
| 40093 | str | sendNickName | 发送者昵称，旧版此字段为空，NT 中未设置群名片时才有 |
| 40800 | protobuf | 聊天消息 | 最为复杂，详见 [Protobuf 消息格式](#protobuf-消息格式) |
| 40900 | protobuf | 引用/转发缓存 | 值为 8 时存贮转发聊天缓存；值为 9 时存贮引用消息 |
| 40005 | int | clientSeq | 自己发的消息一定概率存在数值，正常情况为 0 |
| 40058 | int | 日期索引 | 当日 0 时整的时间戳，时区 GMT+0800 |
| 40006 | int | elem id? | 未确认 |
| 40100 | int | @ 状态 | 详见 [@ 状态](#40100-状态) |
| 40600 | protobuf | 状态标志 | 详见 [40600 值解读](#40600-值解读) |
| 40060 | int | 退群标志 | 已退出或已解散的群聊标志 |
| 40850 | int | 回复消息序号 | 该消息所回复的消息的序号 |
| 40801 | protobuf | | 未解析 |
| 40030 | int | 群号 | |
| 40033 | int | 发送者 QQ 号 | |
| 40062 | protobuf | 表态信息 | 存贮详细表态信息（表情和数量），数字与 [QQBOT 表情编号](https://bot.q.qq.com/wiki/develop/api-v2/openapi/emoji/model.html) 对应，protobuf 结构详见[下表](#_40062-值解读-贴表情) |
| 40083 | int | 表态表情数量总和 | |
| 40084 | int | 表态表情数量总和 | |

## 40062 值解读（贴表情）

仅群聊 `group_msg_table` 存在此列，记录该条消息被群成员「贴」的表情（表态）信息。整列为一段 protobuf，外层为可重复字段 `40062`，每个成员贴的每一种表情对应一个子结构，字段如下：

| Field Number | 类型 | 含义 | 说明 |
| --- | --- | --- | --- |
| 48301 | string | 表情 ID | 与 [QQBOT 表情编号](https://bot.q.qq.com/wiki/develop/api-v2/openapi/emoji/model.html) 对应；小黄脸系表情为数字编号，emoji 系表情为对应 Unicode 码点（超级表情不在此列表中） |
| 48302 | int | 表态标志 | 疑似标记该表情是否处于已表态状态 |
| 48303 | int | 表态数量 | 贴该表情的人数总和 |
| 48304 | bool | 是否本人所贴 | `true` 表示本账号也贴了该表情 |

> [!TIP]
> 表中的列 `40083`、`40084`（表态表情数量总和）与本列的 `48303` 数量相呼应，为便于统计而冗余存贮的整型值。

## 40011 消息类型

疑似用于区分消息类型：

| 值 | 类型 |
| --- | --- |
| 0 | 无消息（消息损坏？多见于已退出群聊且时间久远） |
| 1 | 消息空白（msgid 存在，应该是没加载出来） |
| 2 | 文本消息 |
| 3 | 群文件 |
| 5 | 系统（灰字）消息 |
| 6 | 语音消息 |
| 7 | 视频文件 |
| 8 | 合并转发消息 |
| 9 | 回复类型消息 |
| 10 | 红包 |
| 11 | 应用消息（如小程序） |
| 17 | 表情包 / 原创表情 |

## 40012 子消息类型

疑似用于区分 pb 消息类型：

| 值 | 类型 |
| --- | --- |
| 0 | 非常规 text 消息 |
| 1 | 普通文本消息 / 群文件其他类型消息 |
| 2 | 图片消息 / 群文件图片消息 |
| 3 | 群公告 |
| 4 | 撤回消息提醒 / 群文件视频消息 |
| 8 | 原创表情包 / 群文件音频消息 |
| 11 | 精华消息 |
| 12 | 拍一拍消息 |
| 16 | 群文件 docx 消息 |
| 32 | 平台文本消息 / 群文件 pptx 消息 |
| 33 | 回复类型消息 |
| 64 | 群文件 xlsx 消息 |
| 129 | 纯链接消息 |
| 161 | 存在链接 |
| 512 | 群文件 zip 消息 |
| 2048 | 群文件 exe 消息 |
| 4096 | 表情消息 |

## 40011 与 40012 组合

常见消息类型组合（由于优先级问题，部分消息不满足以下规则）：

| 40011, 40012 | 消息类型 |
| --- | --- |
| 0, 0 | 空消息 |
| 1, 0 | 已撤回消息 |
| 2, 1 | 普通文本类消息 |
| 2, 2 | 图片消息 |
| 2, 3 | 只带图片的纯文本消息 |
| 2, 16 | 纯表情消息 |
| 2, 17 | 带表情的纯文本消息 |
| 2, 19 | 带图片带表情的纯文本消息 |
| 2, 33 | 回复引用消息（不带表情） |
| 2, 35 | @ 消息 |
| 2, 49 | 回复引用消息（带表情） |
| 2, 65 | 机器人 Markdown 消息 |
| 2, 129 | 纯链接消息 |
| 2, 145 | 带表情链接消息 |
| 2, 577 | 机器人消息 |
| 2, 4096 | 收藏表情包 |
| 3, 1 | 群文件其他类型消息 |
| 3, 2 | 群文件图片（png, jpg）消息 |
| 3, 4 | 群文件视频消息 |
| 3, 8 | 群文件音频（mp3, flac）消息 |
| 3, 16 | 群文件 docx 消息 |
| 3, 32 | 群文件 pptx 消息 |
| 3, 64 | 群文件 xlsx 消息 |
| 3, 512 | 群文件 zip 消息 |
| 3, 2048 | 群文件 exe 消息 |
| 5, 4 | 撤回消息提醒 |
| 5, 12 | 拍一拍消息 |
| 6, 0 | amr 语音文件消息 |
| 7, 0 | 视频文件消息 |
| 8, 0 | 合并转发消息 |
| 9, 33 | 回复消息 |
| 9, 34 | 回复带图片消息（无 @） |
| 9, 35 | 回复带图片消息（有 @） |
| 9, 49 | 回复卡片引用消息 / 带表情回复 |
| 9, 51 | 带表情带图片带 @ |
| 9, 161 | 回复存在链接的消息 |
| 10, 0 | 红包 |
| 11, 0 | 应用消息（如小程序） |
| 11, 3 | 群公告 |
| 17, 8 | 表情包 / 原创表情 |

## 40100 @ 状态

| 值 | 含义 |
| --- | --- |
| 6 | 有人 @ 我 |
| 2 | 有人 @ 他人 |
| 0 | 不包含 @ |

## 40600 值解读

| 40600（hex） | 含义 |
| --- | --- |
| `14 00` | 回复消息；此时 40100=6 代表有人回复自己，=2 代表他人回复他人 |
| `c2e91304a8d114****`（不唯一） | 撤回消息 |

## Protobuf 消息格式

消息内容 Protobuf 的部分字段含义如下：

| Field Number | 类型 | 含义 | 说明 |
| --- | --- | --- | --- |
| 48000 | protobuf 或 protobuf array | 消息段 | 一条消息中可以有多个消息段，按内容顺序，类似于富文本；部分类型中可嵌套 |

### 消息段字段（48000）

| Field Number | 类型 | MsgRecord | 说明 | 所属 Element |
| --- | --- | --- | --- | --- |
| 40010 | int | chatType | | |
| 45001 | int | elementId | 元素 ID，具有唯一性 | |
| 45002 | int | elementType | 详见 [ElementType](#elementtype) | |
| 45003 | int | subElementType | 未确定 | |
| 45004 | str | msgid | +faceType | |
| 45101 | str | content | 文本消息 | text |
| 45102 | str | text | 语音转文字 | pttElement |
| 45402 | str | fileName | 文件名 | file、ptt |
| 45403 | str | filePath | 文件路径 | file、ptt |
| 45405 | int | fileSize | 文件大小 | fileElement、pttElement |
| 45406 | int | md5HexStr | 视频消息中对应 videoMD5 | fileElement |
| 45407 | bytes | file10MMD5 | | file、ptt 文件消息才存在 |
| 45408 | bytes | fileSha | | file 文件消息才存在 |
| 45409 | bytes | fileSha3 | | file 文件消息才存在 |
| 45410 | int | videotime | 视频时间 | videoElement、fileElement |
| 45411 | int | picWidth | 原图宽度 | |
| 45412 | int | picHeight | 原图高度 | |
| 45413 | int | thumbWidth | 预览封面宽度 | |
| 45414 | int | thumbHeight | 预览封面高度 | |
| 45415 | int | thumbSize | 预览封面大小 | videoElement |
| 45416 | int | picType | 图片类型，1000=静态图片，2000=GIF | picElement |
| 45418 | int | original | | |
| 45422 | str | thumbfilename | 预览封面路径（非官方） | videoElement |
| 45424 | string/bytes | originImageMd5 | | |
| 45503 | str | fileUuid | | |
| 45862 | bytes | thumbMD5 | 预览封面 MD5 | videoElement |
| 45906 | int | duration | 语音持续时间 | pttElement |
| 45923 | str | text | 语音转文字 | pttElement |
| 45925 | bytes | waveAmplitudes | 信号频率 | pttElement |
| 45954 | str | picThumbPath | 预览封面路径 | fileElement |
| 47401 | int | replaymsgid | 引用的消息 msgid | replyElement |
| 47402 | int | replayMsgSeq | 引用的消息 seq | replyElement |
| 47403 | int | replymsgTime | 引用的消息发送时间戳 | replyElement |
| 47404 | int | replymsgTime | 引用的消息发送时间戳 | replyElement |
| 47413 | str | 引用的消息 | 仅文本 | replyElement |
| 47421 | str | 引用方群昵称 | | replyElement |
| 47422 | int | sourceMsgIdInRecords | | replyElement |
| 47601 | int | faceindex | 表情 ID | faceElement |
| 47602 | str | facetext | 表情含义（外显文字） | |
| 47901 | str | bytesData | 卡片详细信息 | |
| 49155 | int | msgTime | 发送时间 | |
| 95654 | int | thumbSize | 预览封面大小 | fileElement |
| 47713 | str | 撤回消息后缀 | 适用于系统撤回消息 | 系统撤回消息 |
| 48602 | str | XML 消息内容 | 适用于 XML 消息 | XML 消息 |

### ElementType

| 值 | MsgRecord | 说明 |
| --- | --- | --- |
| 1 | textElement | 文本段 |
| 2 | picElement | 图片段 |
| 3 | fileElement | 文件消息 |
| 4 | pttElement | 语音消息 |
| 5 | videoElement | 视频消息 |
| 6 | faceElement | QQ 系统表情 |
| 7 | replyElement | 引用 |
| 8 | grayTipElement | 系统消息（灰字提示） |
| 9 | WalletElement | 红包消息 |
| 10 | arkElement | 卡片消息 |
| 11 | marketFaceElement | 商城表情 |
| 14 | markdownElement | markdown 消息 |
| 16 | — | XML 消息 |
| 17 | inlineKeyboardElement | markdown 按钮消息 |
| 21 | avRecordElement | 通话消息 |
| 26 | GrayTip_QQZone | 空间动态提示 |
| 27 | faceBubbleElement | 弹射表情包 |
| 28 | shareLocationElement | 位置共享 |
| 44 | QQBotChat | 机器人对话 |
