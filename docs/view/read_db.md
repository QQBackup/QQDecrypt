---
title: NTQQ 读取数据库
prev: false
order: 1
---

# NTQQ 读取数据库

阅读本文前，您应当已经通过其他方法，获取到了数据库的已解密文件。如果没有，请参考：[NTQQ 解密数据库](/decrypt/decode_db.md)。

以下以 `nt_msg.db` 代指已解密的数据库文件。

目前已知消息格式为`protobuf`，较为复杂，可使用 [CyberChef](https://gchq.github.io/CyberChef/#recipe=Protobuf_Decode('',false,false)Decode_text('UTF-8%20(65001)')) 工具进行自动解析，相关解析代码可以参考[提取QQ NT数据库 group_msg_table 中的纯文本](https://github.com/QQBackup/ntdb-plaintext-extracter)、[这份 Python 代码](https://github.com/QQBackup/QQ-History-Backup/issues/9#issuecomment-1929105881)与[这份 protobuf 定义](https://github.com/QQBackup/qq-win-db-key/issues/38#issuecomment-2294619828)，完整实现暂无，欢迎贡献。

## db文件内容说明

/data/user/0/com.tencent.mobileqq/databases/nt_db/nt_qq_{QQ_path_hash}/路径下db文件分析
| 是否完成分析 | 数据库名字                                                   | 分析                                         |
| ------------ | ------------------------------------------------------------ | -------------------------------------------- |
| 🤔            | <span style="color:blue;">nt_msg.db</span>  | 聊天数据文件                               |
| ✅            | <span style="color:blue;">profile_info.db</span>        | 联系人信息                               |
| 🤔            | <span style="color:blue;">rich_media.db</span>          | 群聊或私聊发送/接收的文件信息存贮路径    |
| ✅            | <span style="color:blue;">files_in_chat.db</span>       | 媒体文件信息（包括下载的图片视频路径）    |
| 🤔            | <span style="color:blue;">recent_contact.db</span>      | (推测为黑名单，待测试)                       |
| ❓             | <span style="color:blue;">gpro_v1-6_{nt_uid}.db</span> | (由于暂未实现数据库解密无法分析)             |
| ✅            | <span style="color:blue;">group_info.db</span>          | 	群聊信息 |
| 🤔            | <span style="color:blue;"> guild_msg.db</span>           | 频道聊天数据 |
| ✅ | collection.db | QQ收藏数据 |
| 🤔 | file_assistant.db | 已下载文件存放数据 |
| 🤔 | misc.db | 见下表 |
| ✅ | emoji.db | (存贮QQ表情包的数据库) |
| ✅            | group_msg_fts.db      |  	本地搜索使用的数据库                     |
| ✅            | data_line_msg_fts.db| 本地搜索使用的数据库                 |
| ✅            | buddy_msg_fts.db     | 本地搜索使用的数据库                    |
| ✅            | discuss_msg_fts.db     | 本地搜索使用的数据库         |
| ✅            | msg_fts.db             | 本地搜索使用的数据库         |
| ✅            | ~~rdelivery.db~~           | (文件中未发现有效信息)                       |
| ✅            | ~~settings.db~~            | (无法理解的设置信息，有效信息很少，不再分析) |
| ✅            | ~~yffm.db~~                | (文件中未发现有效信息)                       |


# 注：
 ~~已被删除~~是在本人数据库中未发现有意义的数据，因此后续不再探查                                              
 <span style="color:blue;">蓝色字体</span>是存在有效信息的数据库，有待继续分析                                                               
 <span style="color:green;">✅</span>的是已完成对表名的分析（列名会单独重开分析）                                                              
 当然如果你发现你号对应的db中含有有价值的数据也欢迎提出，再分析……（                                           



## 社区项目

网站收集了互联网上其他有关解析 NTQQ 数据库的开源项目，具体可在[这里](/about/projects)查看