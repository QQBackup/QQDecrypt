---
title: 消息导出计划
order: 3
---

# 消息导出计划

## 关于聊天图片本地缓存路径

<QQCachePath />

QQ的图片缓存路径位于`/storage/emulated/0/Android/data/com.tencent.mobileqq/Tencent/MobileQQ/chatpic`，以下用`./`代指

这个目录下包含三个文件夹：

- `chatraw`：原图
- `chatimg`：压缩后的普通图片
- `chatthumb`：缩略图，聊天界面的小图预览

::: details 关于接收图片存放逻辑
<img src="/misc/pic_categorized.svg" alt="pic_categorized" width="500" />

①类图片会先将压缩过的图片存放至`chatimg`文件夹，在用户**手动点击下载原图**后将原图保存至`chatraw`文件夹中

②③类会将图片放至`charaw`文件夹

④类会将GIF本体保存在`chatraw`文件夹，静态预览图放在`chatimg`文件夹

所有类型都将缩略图存放在`chattumb`文件夹


|      | chatraw | chaimg | chattumb |
| ---- | ------- | ------ | -------- |
| ①    | ⬜       | ✔      | ✔        |
| ②    | ✔       | ❌      | ✔        |
| ③    | ✔       | ❌      | ✔        |
| ④    | ✔       | ✔      | ✔        |

⬜需手动触发下载 ✔存在 ❌不存在

:::

::: details 发送表情的分类

QQ中的表情元素可分为四类

| 类型        | 所属ElementType   | 说明                   |
| ----------- | ----------------- | ---------------------- |
| ①QQ系统表情 | FaceElement       | 超级表情与小黄脸表情   |
| ②emoji表情  | TextElement       | 包括手机系统的原生表情 |
| ③收藏表情   | PicElement        | 用户自主收藏的表情     |
| ④原创表情   | marketFaceElement | 表情商城中的表情       |

①类表情属于特殊Element，其公共表情可通过`faceid`在[QQBOT文档](https://bot.q.qq.com/wiki/develop/api-v2/openapi/emoji/model.html)中查询，在一些活动中QQ官方会增加**隐藏表情**，其`faceid`未被公开，但可通过已发送消息推断

②类表情将以文本形式发送（所以有时出现显示异常）

③类表情以图片形式发送

④类表情属于特殊Element，文件缓存在`.emotionsm`文件夹中

:::

>[!TIP]说明
>关于发送是否为原图，可通过查询`original`（对应40080的Field Number=45418）判断
>
>0为非原图，1为原图

### 路径生成规律

在图片消息的<a href="https://qq.sbcnm.top/view/db_file_analysis/nt_msg.db.html#:~:text=%E6%AD%A4%E5%AD%97%E6%AE%B5-,40080,-protobuf" target="_blank">40080</a> 值中，Field Number`45406`称作 `md5HexStr` 值（32位小写），以下称为 ``{MD5}``,**所需格式为32位大写**

将目标文件夹名与 `{MD5}` 拼接，格式：
```
chatimg:{MD5}
```
对拼接好的字符串执行 CRC64 哈希，使用固定多项式：
```
0x9A6C9329AC4BC9B5
```
得到一个 64 位整数。

将该整数转 16 进制，去掉 `0x` 前缀，并在前面加上 `Cache_`，得到文件名，并将文件名最后三位作为子文件夹名称

例如：Cache_d20372e27ef63b0 普通图片位于./chatimg/3b0/Cache_d20372e27ef63b0

若需原图路径，只需将代码中的 `chatimg` 替换为 `chatraw`，再进行CRC64运算即可，`chatthumb`同理

 示例脚本代码

::: code-group

````python [Python]
import os

def crc64(s):
    _crc64_table = [0] * 256
    for i in range(256):
        bf = i
        for _ in range(8):
            bf = bf >> 1 ^ -7661587058870466123 if bf & 1 else bf >> 1
        _crc64_table[i] = bf
    v = -1
    for c in s:
        v = _crc64_table[(ord(c) ^ v) & 255] ^ v >> 8
    return v

def get_img_path(md5, folder):
    url = f"{folder}:{md5}"
    filename = 'Cache_' + hex(crc64(url)).replace('0x', '')
    return os.path.join(f"./{folder}/", filename[-3:], filename).replace("\\", "/")
:::

## 已挖到的api
-   群头像

api地址
```
https://p.qlogo.cn/gh/{random}/{groupid}/{s}
```
其中`groupid`为群号，`{random}`可为任意值不影响最终查询，在`groupid`后加_blank{order}，可以获取历史头像


`s`为头像大小，目前发现tx提供有40、100、140、640几种，当值为`0`时为原始图片大小，也可不附加此参数，默认返回等同参数`0`

例子
```
https://p.qlogo.cn/gh/0/9********1_1/140
```
获取群号为`9********1`大小为140x140的群头像
-   ⬜  群名称api
-   用户头像

api地址
```
https://q1.qlogo.cn/g?b=qq&nk={uin}&s={s}
```
其中`{uin}`为QQ号,`{s}`值用法同上，**必须携带有效s值才可查询**
-   ⬜  用户名称api


以上信息或许会从本地进行获取
