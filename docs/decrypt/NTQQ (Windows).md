---
title: NTQQ (Windows)
order: 3
---

# NTQQ (Windows)

## IDA分析

[QQ NT Windows 数据库解密+图片/文件清理](https://github.com/Mythologyli/qq-nt-db)：本仓库使用 IDA debugger 完成了逆向分析到解密的全过程，并实现了图片与文件清理。

[IDA](https://down.52pojie.cn/Tools/Disassemblers/IDA_Pro_v8.3_Portable.zip)下载（吾爱破解提供）

> [!TIP] 转载说明
原文发表于[Myth's Blog](https://myth.cx/p/qq-nt-db)，作者为Myth，根据 CC BY-SA 4.0 授权协议发布，内容经[issues #50](https://github.com/QQBackup/qq-win-db-key/issues/50)补充
>
>部分图片来自[GroupChatAnnualReport](https://github.com/mobyw/GroupChatAnnualReport)
>

QQ NT Windows 数据库解密+图片/文件清理

笔者测试时使用的 QQ 版本：9.9.3-17412

经验证的 QQ 版本：9.9.3-17749 9.9.12-26339

### 找到数据库 `passphrase`

1. 解压IDA压缩包，双击打开 `ida64.exe` ，选择 `new` , 在弹出的资源管理器界面中定位到 QQNT 安装目录下的 `./versions/{version}/resources/app`文件夹，其中 `{version}` 为 QQNT 的版本号。在右下角过滤器中选择全部文件，单击 `wrapper.node`文件，并点击右下角的 "Open" 按钮。
![](/img/mobyw_ida_0.png)
>[!note] wrapper.node文件路径说明
早期 Windows QQ_NT 版本 `wrapper.node` 文件位于 `./resources/app/versions/{version}` 文件夹中

保持默认导入选项，点击 "OK" 按钮。如果有弹出让选择PDB文件相关提示框点击 "No"。等待文件加载完成。

**分析时间较长，请耐心等待**

分析完成后打开 Strings 视图（如果没有同时按 <kbd>shift</kbd> + <kbd>F12</kbd> 或按图片示例打开），<kbd>CTRL</kbd>+<kbd>F</kbd>搜索 `nt_sqlite3_key_v2: db=%p zDb=%s` 字符串, 双击 `nt_sqlite3_key_v2: db=%p zDb=%s` 一行，跳转到 IDA View-A 标签的对应行。


![](/img/strings-view.png)
![](/img/Myth1.png)


2. 在 IDA View-A 标签中，单击 `nt_sqlite3_key_v2` 的名称 `aNtSqlite3KeyV2`，按快捷键 <kbd>X</kbd> 打开交叉引用窗口。双击第一条结果，转到引用位置。
    ![](/img/mobyw_ida_4.png)
    或者右键此处点击`Jump to xref to operand..`
    ![](/img/Myth2.png)    
    JumpOpXref 后发现在    
    ![](/img/Myth3.png)

3. 按下 <kbd>F5</kbd> 反编译此函数, 如果有弹出窗口点击 "Yes"。等待反编译完成。单击引用语句的左侧蓝色圆点添加断点。
    ![](/img/Myth4.png)
    
4. 退出 QQ 并重新打开，但不要登录。在上端工具栏右侧选择**Local Windows debugger**
   ![](/img/debug_windows.png)
   在 IDA 中点击顶部导航栏 "Debugger" 中的 "Attach to process..." 菜单项, 从列表最后开始找到第一个 `QQ.exe` 进程，双击打开。
   ![](/img/Attach_to_process.png)
>如果等待附加进程时QQ已经无响应了（卡在登录界面无法点击），等待加载完成后按快捷键 <kbd>F9</kbd> 继续运行。

点击登录 QQ，此时成功在断点处停下，打开一个 Locals 视图(Debugger->Debugger windows->Locals)查看参数的值
![](/img/locals.png)   

5. 在 a3 对应的位置右键jump to，直到看到如下图所示的 16 位字符串。`#8xxxxxxxxxxx@uJ` 即为我们需要的 `passphrase` (不一定是这个格式，但总字符数是一样的)
    ![](/img/mobyw_ida_b.png)
    ![](/img/Myth6.png)

### 打开数据库

请参考 [NTQQ 解密数据库](decode_db.md)。

## 使用 frida hook
### 1. 定位 `nt_sqlite3_key_v2:`

   此处采用 [IDA](https://down.52pojie.cn/Tools/Disassemblers/IDA_Pro_v8.3_Portable.zip) 演示，您可以替换成您喜欢的任何反编译器

   ![在 Strings 窗口中搜索 nt_sqlite3_key_v2，得到多个结果](/img/image-win-1.webp)

   定位到字符串 `nt_sqlite3_key_v2: db=%p zDb=%s`

   ![在 IDA View 中定位到此字符串](/img/image-win-2.webp)

   在此字符串上按`x`，或右键选此字符串并选择`Jump to xref`查看引用，进入引用的函数

   ![通过字符串找到目标函数](/img/image-win-3.webp)

   记录函数地址，切换到 Hex View，复制从函数地址开始的一段字节序列，作为特征 Hex

   QQ 9.9.1.15043 为

   ```plain
   48 89 5C 24 08 48 89 6C  24 10 48 89 74 24 18 57
   48 83 EC 20 41 8B F9 49  8B F0 4C 8B CA 4C 8B C1
   48 8B EA 48 8B D9 48 8D  15 33 05 A0 00 B9 08 00
   ```

### 2. Hook 并找到 Key

   根据 <https://www.zetetic.net/sqlcipher/sqlcipher-api/#sqlite3_key> 指出

   `sqlite3_key_v2` 的签名为

   ```c
   int sqlite3_key_v2(
     sqlite3 *db,                   /* Database to be keyed */
     const char *zDbName,           /* Name of the database */
     const void *pKey, int nKey     /* The key */
   );
   ```

   其中对我们有用的是 `pKey` 和 `nKey`

   作者本人采用 frida hook

   根据 repo 提供的脚本略加修改，很容易得到我们需要的 `pKey` 和 `nKey`

   （如果你对如何修改有疑问，可以使用 [msojocs/nt-hook](https://github.com/msojocs/nt-hook/tree/4414f372ee4847be9d91d7436abb7653f8908f91) 中给出的完整脚本。注意，编译此脚本需要你的系统安装有 Node.js 环境，但编译得到的`.js`文件可以直接运行。注意，本仓库最新版本可能不能在 Windows 平台下直接使用，请自行根据 commit 信息找到可用版本（比如超链接给出的版本），或自行更改相关代码。）

   PS：有概率你会得到的一个长度为 20 的 key，但那不是我们想要的，可以挂上一个动态调试器来观察 key 对应的具体数据库
   
## 使用Python脚本（暂时废弃）   
::: details (需要帮助)

下载脚本<a href="/files/windows_ntqq_key.py" download>windows_ntqq_key.py</a>

先退出QQ，运行脚本，然后运行登录QQ获取密钥

>  [!WARNING]  注意
> 此方法只适用于已被适配的版本，具体可在[QQ_Offset.json](/files/QQ_Offset.json)中查看
>
> **9.9.21.38503**之后的版本**已失效**, 笔者尝试在内存中搜索已知密钥也一无所获，怀疑QQ在登陆成功后从内存销毁了密钥

> [!TIP] 社区共建
> 
> 我们期待社区成员共同分享各版本的基址信息，便于后续获取密钥。如果你有兴趣参与，请按照以下方式投稿：
> 
> 按照[IDA分析](NTQQ%20(Windows).md#找到数据库-passphrase)走到步骤2，向上翻找到偏移地址
> 
> 示例，QQ（9.9.20.37625）偏移地址为0x20A6E
> 
> ![>](/img/wrapper_node_offset.png)
> 
>找到后，请发送版本号和偏移地址（并配图）到 issues 。
:::   

## 使用 PowerShell 脚本

仅支持 x86-64 架构。

右键开始菜单，选择“终端”或者“Windows PowerShell”。在弹出的窗口输入：

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
irm https://docs.aaqwq.top/files/windows_ntqq_get_key.ps1 | iex
```

你也可以单独下载<a href="/files/windows_ntqq_get_key.ps1" download>windows_ntqq_get_key.ps1</a>脚本，然后右键点击运行，或者在 PowerShell 中执行：

```powershell
# 支持的参数
# -Verbose : 输出详细信息
# -NoDebugForKey: 只执行静态分析得到关键函数地址，不进行动态调试。
.\windows_ntqq_get_key.ps1
```

### 3. 打开数据库

请参考 [NTQQ 解密数据库](decode_db.md)。
