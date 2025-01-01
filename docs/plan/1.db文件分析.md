---
title: db文件分析
description: db文件分析
---

# db文件内容分析

/data/user/0/com.tencent.mobileqq/databases/nt_db/nt_qq_{QQ_path_hash}/路径下db文件分析
| 是否完成分析 | 数据库名字                                                   | 分析                                         |
| ------------ | ------------------------------------------------------------ | -------------------------------------------- |
| 🤔            | <span style="color:blue;">nt_msg.db</span>  | 聊天数据文件                               |
| 🤔            | <span style="color:blue;">profile_info.db</span>        | 联系人信息                               |
| 🤔            | <span style="color:blue;">buddy_msg_fts.db </span>      | (疑似部分临时会话信息)                    |
| 🤔            | <span style="color:blue;">rich_media.db</span>          | (群聊或私聊发送/接收的文件信息，有待分析)    |
| ✔            | <span style="color:blue;">data_line_msg_fts.db</span>   | (推测为我的设备接收文件信息)                 |
| 🤔            | <span style="color:blue;">files_in_chat.db</span>       | (暂时未解析出信息含义)                       |
| 🤔            | <span style="color:blue;">recent_contact.db</span>      | (推测为黑名单，待测试)                       |
| ❓            | <span style="color:blue;">gpro_v1-6_u_******.db</span>  | (由于暂未实现数据库解密无法分析)             |
| 🤔            | <span style="color:blue;">group_info.db</span>          |                                              |
| 🤔            | <span style="color:blue;">group_msg_fts.db</span>       |                                              |
| 🤔            | <span style="color:blue;"> guild_msg.db</span>           |                                              |
| ✔            | ~~discuss_msg_fts.db~~     | (文件中未发现有效聊天信息)                   |
| ✔            | ~~file_assistant.db~~      | (文件中未发现有效信息)                       |
| ✔            | ~~collection.db~~          | (文件中未发现有效信息)                       |
| ✔            | ~~misc.db~~                | (文件中未发现有效聊天信息)                   |
| ✔            | ~~msg_fts.db~~             | (文件中未发现有效聊天信息)                   |
| ✔            | ~~rdelivery.db~~           | (文件中未发现有效信息)                       |
| ✔            | ~~emoji.db~~              | (疑似存贮QQ热门表情包的数据库，不再分析)     |
| ✔            | ~~settings.db~~            | (无法理解的设置信息，有效信息很少，不再分析) |
| ✔            | ~~yffm.db~~                | (文件中未发现有效信息)                       |


# 注：
 ~~已被删除~~是在本人数据库中未发现具有有效数据的，因此后续不再探查实际意义                                               
 <span style="color:blue;">蓝色字体</span>是存在有效信息的数据库，有待继续分析                                                               
 <span style="color:green;">✔</span>的是已完成对表名的分析（列名会单独重开分析）                                                              
 当然如果你发现你号对应的db中含有有价值的数据也欢迎提出，再分析……（                                           


