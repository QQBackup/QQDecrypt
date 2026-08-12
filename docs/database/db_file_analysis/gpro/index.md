---
title: gpro_v1-6_{nt_uid}.db
order: 9
---

# gpro_v1-6_{nt_uid}.db

QQ 频道（Guild/GPro）相关数据库，仅 Android 平台存在。

> [!NOTE] 分析状态
> 当前维护者不怎么使用 QQ 频道，数据库内数据量极少，无法对各表做深入字段分析。欢迎有频道数据的读者提交分析结果。

## 获取密钥与解密

见 [NTQQ (Android) — gpro 数据库密钥](/decrypt/extract/NTQQ%20(Android)#gpro-%E6%95%B0%E6%8D%AE%E5%BA%93%E5%AF%86%E9%92%A5)。

## 表列表

| 表名 | 推测用途 |
| --- | --- |
| `t_GPro_ChannelAuthStore` | 频道权限缓存 |
| `t_GPro_QQMsgListGuild` | 频道消息列表 |
| `t_GPro_QQMsgListChannel` | 子频道消息列表 |
| `t_GPro_MemberListStatusInfo` | 成员在线状态信息 |
| `t_GPro_Preference` | 频道偏好/设置 |
| `t_GPro_Guild_v15` | 频道（Guild）基本信息 |
| `t_GPro_Channel_v2` | 子频道信息 |
| `t_GPro_CategoryInfo_v1` | 频道分类信息 |
| `t_GPro_Category` | 分类数据 |
| `t_GPro_Role` | 频道身份组 |
| `t_GPro_GuildRoleOrder` | 身份组排序 |
| `t_GPro_TopRoleInfo` | 置顶身份组信息 |
| `t_GPro_PersistPollingData` | 持久轮询数据 |
| `t_GPro_GuildUserProfile_v3` | 频道内用户资料 |
| `t_GPro_AISearchRspBufModel` | AI 搜索响应缓存 |
| `t_GPro_SpeakPermissionInfoV2` | 发言权限信息 |
| `t_GPro_ProfileInfo` | 用户资料 |
| `t_GPro_CommonUserProfile_v2` | 通用用户资料 |
| `t_GPro_GuildSearchHistory` | 频道搜索历史 |
| `t_GPro_AIAppConversationsRspBufModel` | AI 应用会话响应缓存 |
| `t_GProAIApp_GrantTicketItem_v1` | AI 应用授权凭据 |
