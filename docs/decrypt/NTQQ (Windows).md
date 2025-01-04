---
title: NTQQ (Windows)
description: NTQQ (Windows)解密教程
---

# NTQQ (Windows)
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

## IDA分析

[QQ NT Windows 数据库解密+图片/文件清理](https://github.com/Mythologyli/qq-nt-db)：本仓库使用 IDA debugger 完成了逆向分析到解密的全过程，并实现了图片与文件清理。

> [!TIP] 转载说明
原文发表于[Myth's Blog](https://myth.cx/p/qq-nt-db)，作者为Myth，根据 CC BY-SA 4.0 授权协议发布，内容经[issues #50](https://github.com/QQBackup/qq-win-db-key/issues/50)补充
>

QQ NT Windows 数据库解密+图片/文件清理

笔者测试时使用的 QQ 版本：9.9.3-17412

经验证的 QQ 版本：9.9.3-17749 9.9.12-26339

### 找到数据库 `passphrase`

1. 使用 IDA Pro 打开 `C:\Program Files\Tencent\QQNT\resources\app\versions\9.9.3-17412\wrapper.node`。打开 Strings 视图，搜索 `nt_sqlite3_key_v2: db=%p zDb=%s`

    ![](/img/Myth1.png)



2. 跳转到主视图，再跳转到引用该字符串的位置
    ![](/img/Myth2.png)
    JumpOpXref 后发现在    
    ![](/img/Myth3.png)

3. 按下 F5 反编译此函数
    ![](/img/Myth4.png)
    
    参考[文档](https://www.zetetic.net/sqlcipher/sqlcipher-api/#sqlite3_key)可知 `sqlite3_key_v2` 的参数为：

    ```c
    int sqlite3_key_v2(
        sqlite3 *db,                   /* Database to be keyed */
        const char *zDbName,           /* Name of the database */
        const void *pKey, int nKey     /* The key */
    );
    ```
   
    可以猜测 a3 为我们所需的 `passphrase`。打上断点

4. 退出 QQ 并重新打开，但不要登录。打开 IDA Debug -> Attach to Process ，选择 QQ.exe
，或许等待后发现程序已经被停止了，卡在了登录界面，点一下继续，让它先跑起来
然后登录 QQ，此时成功在断点处停下，打开 Locals 可以看到一些变量
    ![](/img/Myth5.png)

    打开一个 Locals 视图(调试器视图->本地变量)查看参数的值

5. 命中后，跳转到 a3 对应的位置，直到看到如下图所示的 16 位字符串。`#8xxxxxxxxxxx@uJ` 即为我们需要的 `passphrase` (不一定是这个格式，但总字符数是一样的)
    ![](/img/Myth6.png)

### 导出/修复数据库

数据库位置：`C:\Users\<USERNAME>\Documents\Tencent Files\<QQ>\nt_qq\nt_db`

你需要的是 .db 格式的文件。

首先，每个数据库文件头部有 1024 个字符的无用内容，去除这部分内容：

+ Windows
    ```bash
    type nt_msg.db | more +1025 > nt_msg.clean.db
    ```

+ UNIX
    ```bash
    cat nt_msg.db | tail -c +1025 > nt_msg.clean.db
    ```

此时文件已经可以通过 DB Browser for SQLCipher 直接查看，注意迭代次数填写 4000。

下面解释直接解密数据库的方法。

考虑到在 Windows 上编译 sqlcipher 较为困难，笔者使用了 MSYS2 环境并直接安装了`mingw-w64-x86_64-sqlcipher`

笔者处理了 `nt_msg.db`、`files_in_chat.db` 两个文件，并将处理后的文件移动到 `data/clean_db`

根据 sqlcipher 的文档，解密数据的流程为：

1. 打开数据库

    ```bash
    $ sqlcipher
    sqlite> .open nt_msg.clean.db
    ```
   
2. 输入 `passphrase`

    ```bash
    sqlite> PRAGMA key = '#8xxxxxxxxxxx@uJ'; PRAGMA kdf_iter = '4000';
    ```

3. 导出无加密的数据库

    ```bash
    sqlite> ATTACH DATABASE 'nt_msg.db' AS plaintext KEY ''; SELECT sqlcipher_export('plaintext'); DETACH DATABASE plaintext;
    sqlite> .exit 
    ```

不过，很有可能在导出时提示数据库损坏 `Runtime error: database disk image is malformed`。此时需要对数据库进行修复：

```bash
sqlite> .output nt_msg.sql
sqlite> .dump
sqlite> .exit
```

之后对得到的 `nt_msg.sql` 进行处理，并使用 `sqlite3` 生成无加密的数据库

```bash
$ cat nt_msg.sql | sed -e 's|^ROLLBACK;\( -- due to errors\)*$|COMMIT;|g' | sqlite3 nt_msg.db
```
将解密后的数据库移动到 `data/decrypted_db`

### 图片/文件清理

下图是 `nt_msg.db` 中的表：

![](/img/Myth7.png)

注意 `c2c/group_msg_table` 中的 `40800`（消息内容）是 Protobuf 二进制。笔者暂时没有弄明白每个字段的意义

图片/文件清理可以参考仓库中的两个 Python 脚本

### 致谢

[QQBackup/qq-win-db-key](https://github.com/QQBackup/qq-win-db-key)

[https://lengyue.me/2023/09/19/ntqq-db/](https://lengyue.me/2023/09/19/ntqq-db/)
