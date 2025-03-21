---
title: NTQQ (Windows)
description: NTQQ (Windows)解密教程
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

1. 解压IDA压缩包，双击打开 `ida64.exe` ，选择 `new` , 在弹出的资源管理器界面中定位到 QQNT 安装目录下的 `./resources/app/versions/{version} `文件夹，其中 `{version}` 为 QQNT 的版本号。在右下角过滤器中选择全部文件，单击 `wrapper.node `文件，并点击右下角的 "Open" 按钮。
![](/img/mobyw_ida_0.png)

保持默认导入选项，点击 "OK" 按钮。如果有弹出让选择PDB文件相关提示框点击 "No"。等待文件加载完成。

**建议晚上睡觉时打开分析捏＞﹏＜分析时间很长而且会生成超大超大的ida文件(⊙﹏⊙)**

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
   在 IDA 中点击顶部导航栏 "Debugger" 中的 "Attach to process..." 菜单项, 选择 QQ.exe
   ::: details 有多个QQ进程不知道附加哪个？
   1 可以先CTRL+SHIFT+ESC或者任务栏右键打开任务管理器，然后如图所示勾选显示PID和命令行
    ![](/img/Crafty_QQ_process1.png)
   2 找到QQ进程双击展开，其中不带任何附加参数的进程即为要附加的进程
    ![](/img/Crafty_QQ_process2.png)  
   3 在IDA中选择即可
    ![](/img/Crafty_QQ_process3.png)
   :::

如果等待附加进程时QQ已经无响应了（卡在登录界面无法点击），等待加载完成后按快捷键 <kbd>F9</kbd> 继续运行。

点击登录 QQ，此时成功在断点处停下，打开一个 Locals 视图(Debugger->Debugger windows->Locals)查看参数的值
![](/img/locals.png)   

5. 在 a3 对应的位置右键jump to，直到看到如下图所示的 16 位字符串。`#8xxxxxxxxxxx@uJ` 即为我们需要的 `passphrase` (不一定是这个格式，但总字符数是一样的)
    ![](/img/mobyw_ida_b.png)
    ![](/img/Myth6.png)

### 打开数据库

请参考 [NTQQ 解密数据库](NTQQ%20解密数据库.md)。

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

### 3. 打开数据库

请参考 [NTQQ 解密数据库](NTQQ%20解密数据库.md)。
