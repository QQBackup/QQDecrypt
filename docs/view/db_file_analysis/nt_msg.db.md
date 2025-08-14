---
title: nt_msg.db
order: 1
---

# 字段含义

感谢项目[学习笔记 | QQNT 聊天记录导出](https://blog.reincarnatey.net/2024/0707-qqnt-history-export/)
与[GroupChatAnnualReport](https://github.com/mobyw/GroupChatAnnualReport)

## nt_msg.db
### `group_msg_table`
群聊数据 `group_msg_table` 表中的部分列含义如下：
|列名 | 类型 | MsgRecord | 说明|
|--- | --- | --- | --- |
|40001 | int | msgId | 消息ID，具有唯一性|
|40002 | int | msgRandom | 消息随机值，用于对消息去重|
|40003 | int | msgSeq | 群聊消息ID，在每个聊天中依次递增 |
|40010 | int | chatType | 聊天类型，私聊为1，群聊为2，频道为4，公众号为103，企业客服为102，临时会话为100 |
|40011 | int | msgType | 消息类型，详见[下表](#_40011部分值信息解读) |
|40012 | int | subMsgType | pb消息类型，详见[下表](#_40012部分值信息解读) |
|40013 | int | sendType | 发送标志，本机发送的消息为1，其他客户端发送的为2，别人发的消息为0 ，转发消息为5，在已退出或被封禁的消息中为当日整点时间戳 |
|40020 | str | senderuid | nt_uid, 对应  nt_uid_mapping_table|
|40021 | str | peeruid | 会话ID |
|40027 | int | peeruin | 会话ID |
|40041 | int | sendStatus | 发送状态，2为成功，0为发送被阻止（如不是对方好友），1为尚未发送成功（比如网络问题），3为消息被和谐 |
|40050 | int | msgTime | 发送消息时的完整时间戳，UTC+8：00 |
|40090 | str | sendMemberName | 发送者群名片，旧版 QQ  迁移数据中格式为 `name(12345)` 或 `name<i@example.com>`， QQNT 中为群名片 |
|40093 | str | sendNickName | 发送者昵称，旧版 QQ  此字段为空，QQNT 中未设置群名片时才有此字段 |
|40800 | <span style="color:blue;">protobuf</span> | 聊天消息，最为复杂 | 尚未解析完|
|40900 | <span style="color:blue;">protobuf</span> | 不同情况下存在不一样的数据（以列40011为区分） | 值为8时，列40900存贮转发聊天的缓存<br />值为9时，列40900存贮引用的消息|
|40005 | int | 只知道自己发的消息一定概率存在数值 | 正常情况为0|
|40058 | int | 当日 0 时整的时间戳格式 | 时区为 GMT+0800|
|40006 | int | elem id? | 不知道用处|
|40100 | int | @状态 | 详见[下表](#_40100值解读)|
|40600 | <span style="color:blue;">protobuf</span> | 状态标志？ | protobuf 格式，详见[说明](#_40600值解读)|
|40060 | int | 已退出或已解散的群聊标志 | |
|40850 | int | 回复消息序号 | 该消息所回复的消息的序号|
|40801 | <span style="color:blue;">protobuf</span> | 无法理解的protobuf | |
|40030 | int | 群号 | QQNT 保存的群号|
|40033 | int | 发送者 QQ 号 | QQNT 保存的发送者 QQ 号|
|40062 | <span style="color:blue;">protobuf</span> | 存贮详细表态信息（包括表态表情和表态数量） | 其数字与[QQBOT](https://bot.q.qq.com/wiki/develop/api-v2/openapi/emoji/model.html)中表情编号对应（超级表情不在此列表中）|
|40083 | int | 表态表情数量总和 | |
|40084 | int | 表态表情数量总和 | |

### `c2c_msg_table`
私聊数据 `c2c_msg_table` 表中的部分列含义如下：

| 列名    | 类型    | 含义        | 说明                      |
| ----- | ----- | --------- | ----------------------- |
| 40030 | int   | 私聊对象 QQ 号 | 对方 QQ 号（无论是对方还是自己发送的消息） |
| 40033 | int   | 发送者 QQ 号  | 发送者的 QQ 号               |
| 40050 | int   | 时间        | 时间戳（单位为秒）               |
| 40058 | int   | 日期        | 当日 0 时整的时间戳格式           |
| 40093 | str   | 消息发送者     | QQ 昵称或是备注名              |
| 40800 | bytes | 消息内容      | protobuf 格式             |

### `group_at_me_msg`
被@消息

| 列名  | 类型 | MsgRecord   | 含义                                          |
| ----- | ---- | ----------- | --------------------------------------------- |
| 40001 | int  | Msgid       | 消息ID                                        |
| 40027 | int  | peeruin     | 群号                                          |
| 40020 | str  | senderUid   | @我的成员的nt_uid                             |
| 40100 | int  | atTypeArray | @类型数组<br /> 有人 @ 我：6；@ 群里所有人：1 |
| 40050 | int  | timestamp   | 消息时间戳                                    |
| 40003 | int  | msgSeq      | 群聊消息ID，在每个群聊中依次递增              |

`recent_contact_top_table`

置顶聊天信息

| 列名  | 类型 | 含义                                |
| ----- | ---- | ----------------------------------- |
| 40010 | int  | 聊天类型                            |
| 41103 | int  | 置顶时间                            |
| 1000  | str  | 当置顶聊天为私聊时，此处显示uin     |
| 60001 | int  | 当置顶聊天为群聊时，此处显示peeruin |

### `recent_contact_v3_table`

聊天对象资料信息

| 列名  | 类型                                      | MsgRecord        | 含义                                 |
| ----- | ----------------------------------------- | ---------------- | ------------------------------------ |
| 40010 | int                                       | chatType         | [见上表](#group-msg-table)           |
| 40021 | str                                       | peeruin / nt_uid |                                      |
| 40030 | int                                       | uin              | c2c才有此值，group此值均为0          |
| 40051 | <span style="color:blue;">protobuf</span> | lastMessage      | protobuf，最后一条消息               |
| 40041 | int                                       | sendStatus       | [见上表](#group-msg-table)           |
| 40050 | int                                       | lastTime         | 最后一条消息的时间戳，单位：秒       |
| 40003 | str                                       | msgSeq           |                                      |
| 40094 | str                                       | source           | 来源                                 |
| 40093 | str                                       | sendNickName     |                                      |
| 40090 | str                                       | sendMemberName   |                                      |
| 40095 | str                                       | sendremarkName   | 成员备注名称                         |
| 40020 | str                                       | nt_uid           |                                      |
| 40033 | int                                       | uin              |                                      |
| 41110 | str                                       | groupavatar      | 群头像本地缓存路径                   |
| 41135 | str                                       |                  | 当通过群聊发起聊天时，显示对应群昵称 |

**注意：以下信息可能存在不准确性：所有值均为本人通过自己的聊天信息推断而来，可能存在未发现或错误分析，欢迎大佬指正**

#### 40011部分值信息解读
::: details 展开阅读

疑似用于区分消息类型

无消息（消息损坏？多见于已退出群聊且时间久远）：0

消息空白（msgid存在，应该是没加载出来）：1

text文本消息：2

群文件：3

我的聊天记录里没有4~大佬带带＞︿＜

系统（灰字）消息：5

语音消息：6

视频文件：7

合并转发消息：8

回复类型消息：9

红包：10

应用消息：11

:::

#### 40012部分值信息解读
::: details 展开阅读

疑似用于区分pb消息类型

非常规text消息：0

普通文本消息：1

群文件其他类型消息：1

图片消息：2

群文件图片消息：2

群公告：3

群文件视频消息：4

撤回消息提醒：4

群文件音频消息：8

原创表情包：8

射精消息：11

拍一拍消息：12

群文件docx消息：16

平台文本消息：32

群文件pptx消息：32

回复类型消息：33

群文件xlsx消息：64

存在链接：161

群文件zip消息：512

群文件exe消息：2048

表情消息：4096

:::

#### 40011与40012组合可判断消息类型
::: details 一些常见消息组合

由于优先级问题（特别是2类别的信息），部分消息不满足以下规则

空消息：0，0

已撤回消息：1，0

普通文本类消息：2，1

图片消息：2，2

只带图片的纯文本消息：2，3

纯表情消息：2，16

带表情的纯文本消息：2，17

带图片带表情的纯文本消息：2，19

纯链接消息：2，129

带表情链接消息：2，145

机器人消息：2，577

机器人Markdown消息：2，65

@消息：2，35

回复引用消息（不带表情）：2，33

回复引用消息（带表情）：2，49

收藏表情包：2，4096

群文件其他类型消息：3，1

群文件图片（png，jpg）消息：3，2

群文件视频消息：3，4

群文件音频（mp3，flac）消息：3，8

群文件docx消息：3，16

群文件pptx消息：3，32

群文件xlsx消息：3，64

群文件zip消息：3，512

群文件exe消息：3，2048

拍一拍消息：5，12

撤回消息提醒：5，4

amr语音文件消息：6，0

视频文件消息：7，0

合并转发消息：8，0

回复消息：9，33

回复带图片消息（无@）：9，34

回复带图片消息（有@）：9，35

回复带图片带@：9，35

回复卡片引用消息：9，49

带表情回复：9，49

带表情带图片带@：9，51

回复存在链接的消息：9，161

红包：10，0

应用消息（如小程序）：11，0

群公告：11，3

表情包：17，8

原创表情：17，8

:::

#### 40100值解读
值为6：有人@我；为2，有人@他人；为0，此条消息不包含@

#### 40600值解读

当40600（16进制）值为`14 00`时，为回复消息

此时：40100的值：

为6代表有人回复自己，为2代表他人回复他人

当40600（16进制）值为`c2e91304a8d114****`时（不唯一），为撤回消息

## Protobuf 消息格式

消息内容 protobuf 的部分字段含义如下：

| Field Number | 类型                        | 含义  | 说明                                  |
| ------------ | ------------------------- | --- | ----------------------------------- |
| 48000        | protobuf 或 protobuf array | 消息段 | 一条消息中可以有多个消息段，按内容顺序，类似于富文本；部分类型中可嵌套 |

消息段（48000）的部分字段含义如下：

| Field Number | 类型          | MsgRecord            | 说明                                                         | 所属Element                  |
| ------------ | ------------- | -------------------- | ------------------------------------------------------------ | ---------------------------- |
| 40010        | int           | chatType             |                                                              |                              |
| 45001        | int           | elementId            | 元素id，与msgid一样，具有唯一性                              |                              |
| 45002        | int           | elementType          |                                                              | [详见下表](#elementtype说明) |
| 45003        | int           | subElementType       | ？未确定                                                     |                              |
| 45004        | str           | msgid                | +faceType                                                    |                              |
| 45101        | str           | content              | 文本消息                                                     | text                         |
| 45102        | str           | text                 | 语音转文字                                                   | pttElement                   |
| 45402        | str           | fileName             | 文件名                                                       | file、ptt                    |
| 45403        | str           | filePath             | 文件路径                                                     | file 、ptt                   |
| 45405        | int           | fileSize             | 文件大小                                                     | fileElement 、pttElement     |
| 45406        | int           | md5HexStr            | 视频消息中对应videoMD5                                       | fileElement                  |
| 45407        | bytes         | file10MMD5           |                                                              | file、ptt 文件消息才存在     |
| 45408        | bytes         | fileSha              |                                                              | file文件消息才存在           |
| 45409        | bytes         | fileSha3             |                                                              | file 文件消息才存在          |
| 45410        | int           | videotime            | 视频时间                                                     | videoElement、fileElement    |
| 45411        | int           | thumbWidth           | 预览封面宽度                                                 | videoElement                 |
| 45412        | int           | thumbHeight          | 预览封面高度                                                 | videoElement                 |
| 45413        | int           | thumbWidth           | 预览封面宽度                                                 |                              |
| 45414        | int           | thumbHeight          | 预览封面高度                                                 |                              |
| 45415        | int           | thumbSize            | 预览封面大小                                                 | videoElement                 |
| 45416        | int           | picType              | 图片类型，1000为静态图片，2000为GIF                          | picElement                   |
| 45418        | int           | original             |                                                              |                              |
| 45422        | str           | thumbfilename        | （非官方）预览封面路径<br>位于半私有目录/Tencent/MobileQQ/shortvideo/thumbs/ | videoElement                 |
| 45424        | string\|bytes | originImageMd5       |                                                              |                              |
| 45503        | str           | fileUuid             |                                                              |                              |
| 45411        | int           | picWidth             | 原图宽度                                                     |                              |
| 45412        | int           | picHeight            | 原图宽度                                                     |                              |
| 45862        | bytes         | thumbMD5             | 预览封面MD5（对于45422文件）                                 | videoElement                 |
| 45906        | int           | duration             | 语音持续时间                                                 | pttElement                   |
| 45923        | str           | text                 | 语音转文字                                                   | pttElement                   |
| 45925        | bytes         | waveAmplitudes       | 信号频率                                                     | pttElement                   |
| 45954        | str           | picThumbPath         | 预览封面路径                                                 | fileElement                  |
| 47401        | int           | replaymsgid          | 引用的消息msgid                                              | replyElement                 |
| 47402        | int           | replayMsgSeq         | 引用的消息seq                                                | replyElement                 |
| 47403        | int           | replymsgTime         | 引用的消息发送时间戳                                         | replyElement                 |
| 47404        | int           | replymsgTime         | 引用的消息发送时间戳                                         | replyElement                 |
| 47413        | str           | 引用的消息           | 仅文本                                                       | replyElement                 |
| 47421        | str           | 引用方群昵称         |                                                              | replyElement                 |
| 47422        | int           | sourceMsgIdInRecords |                                                              | replyElement                 |
| 47601        | int           | faceindex            | 表情ID                                                       | faceElement                  |
| 47602        | str           | facetext             | 表情含义（外显文字）                                         |                              |
| 47901        | str           | bytesData            | 卡片详细信息                                                 |                              |
| 49155        | int           | msgTime              | 发送时间                                                     |                              |
| 95654        | int           | thumbSize            | 预览封面大小                                                 | fileElement                  |
| 47713        | str           | 撤回消息后缀         | 适用于系统撤回消息                                           | 系统撤回消息                 |
| 48602        | str           | XML 消息内容         | 适用于 XML 消息                                              | XML 消息                     |


### elementType说明
| 值   | MsgRecord             | 说明                 |
| ---- | --------------------- | -------------------- |
| 1    | textElement           | 文本段               |
| 2    | picElement            | 图片段               |
| 3    | fileElement           | 文件消息             |
| 4    | pttElement            | 语音消息             |
| 5    | videoElement          | 视频消息             |
| 6    | faceElement           | QQ系统表情           |
| 7    | replyElement          | 引用                 |
| 8    | grayTipElement        | 系统消息（灰字提示） |
| 9    | WalletElement         | 红包消息             |
| 10   | arkElement            | 卡片消息             |
| 11   | marketFaceElement     | 商城表情             |
| 14   | markdownElement       | markdown消息         |
| 16   | -                     | XML消息              |
| 17   | inlineKeyboardElement | markdown按钮消息     |
| 21   | avRecordElement       | 通话消息             |
| 27   | faceBubbleElement     | 弹射表情包           |
| 28   | shareLocationElement  | 位置共享             |



