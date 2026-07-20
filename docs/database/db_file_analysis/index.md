---
order: 4
title: db 文件分析
---

# db 文件分析

已解密 QQ 数据库的表结构分析。按数据库分目录，每个表独立成页，便于单独维护和更新。

## 数据库索引

| 数据库 | 说明 | 入口 |
| --- | --- | --- |
| `nt_msg.db` | 聊天消息（私聊、群聊、会话） | [nt_msg.db](./nt_msg/) |
| `profile_info.db` | 用户信息（好友、分组、个人资料） | [profile_info.db](./profile_info/) |
| `group_info.db` | 群信息（成员、公告、精华、通知） | [group_info.db](./group_info/) |
| `emoji.db` | 表情（系统表情、收藏、原创市场） | [emoji.db](./emoji/) |
| `collection.db` | 收藏 | [collection.db](./collection/) |
| `files_in_chat.db` | 聊天媒体文件 | [files_in_chat.db](./files_in_chat/) |
| `rich_media.db` | 富媒体文件下载 | [rich_media.db](./rich_media/) |
| `login.db` | 已登录账号列表（密钥为固定值） | [login.db](./login/) |

---

本项目仅供学习交流使用，严禁用于任何违反中国大陆法律法规、您所在地区法律法规、[QQ软件许可及服务协议](https://rule.tencent.com/rule/preview/46a15f24-e42c-4cb6-a308-2347139b1201)的行为，开发者不承担任何相关行为导致的直接或间接责任。

本项目不对分析内容的完整性、准确性作任何担保，需要更多的帮助来验证真实性。

本项目基本遵循 [LICENSE](/about/LICENSE) 里的开源协议。