---
title: NTQQ (macOS x86)
order: 5
---

# NTQQ (macOS x86)

> [!WARNING] 教程验证状态
> 
> **当前状态：** 尚未确认本教程在近期版本上仍可用
> 
> **已确认 QQ 版本：** 暂无
> 
> **最后确认时间：** 暂无
>
> 如果你确认本教程在 macOS x86 平台上依然可用，请打开 [PR](https://github.com/QQBackup/QQDecrypt/pulls) 或 [issue](https://github.com/QQBackup/QQDecrypt/issues) 通知维护者，并注明 QQ 版本、macOS 版本、架构，以及是否成功提取原始数据库和 key。
## 0. 背景信息

*   **测试系统**：`macOS Sequoia 15.5`
*   **CPU 架构**：`x86_64`
*   **QQ 版本**：[6.9.58-28971](https://qq.en.uptodown.com/mac/download/1033570073)
    *   **发布日期**：2024 年 10 月 28 日
    *   **SHA256**：`47a09e5ea5211012ca0f7e7ef634aef0c4a3fe87c27bac61ac0b74afdbd577d1`
    *   **备份链接**：[Google Drive](https://drive.google.com/file/d/1ktW7jg1ZdkOrnmEyWAT0LUyyO3eBgXr_/view?usp=sharing)
    *   **备注**：为确保文件完整性，请在使用前核对 SHA256 值。您也可以从官网下载最新版本，但请注意，新版本的函数地址和结构可能与本教程有所不同。

> **特别注意**：本教程仅适用于 **x86 (Intel) 架构**的 macOS 系统。如果您的设备是 **ARM (Apple Silicon) 架构**，请参考[这篇文章](https://gilbert.vicp.io/2024/03/20/Unlocking-Memories-Extracting-QQ-NT-Chat-History-from-Encrypted-Databases/)。

## 1. 准备阶段

我们要用到 `lldb` 调试器，需要暂时禁用系统的完整性保护 (System Integrity Protection, SIP)。

具体操作步骤请参考[这篇资料](https://gist.github.com/imhet/c96889529826915343d7b41a4c6ec770)。

## 2. 获取密钥 (Key)

### 2.1 定位 `nt_sqlite3_key_v2` 函数的偏移地址

首先，我们需要在 QQ 的核心库文件 `wrapper.node` 中找到加密函数 `nt_sqlite3_key_v2` 的位置。

```bash
# 将核心库文件复制到当前目录以便分析
cp /Applications/QQ.app/Contents/Resources/app/wrapper.node .

# 使用 objdump 反汇编并查找关键函数
objdump -d wrapper.node | grep -B 20 "nt_sqlite3_key_v2"

# --- 输出结果示例 ---
 332cdd7:	48 8d 35 73 cb 57 00	leaq	0x57cb73(%rip), %rsi ## literal pool for: "main"
 332cdde:	48 89 df	movq	%rbx, %rdi
 332cde1:	4c 89 fa	movq	%r15, %rdx
 332cde4:	44 89 f1	movl	%r14d, %ecx
 332cde7:	48 83 c4 08	addq	$0x8, %rsp
 332cdeb:	5b	popq	%rbx
 332cdec:	41 5e	popq	%r14
 332cdee:	41 5f	popq	%r15
 332cdf0:	5d	popq	%rbp
 332cdf1:	e9 00 00 00 00	jmp	0x332cdf6
 332cdf6:	55	pushq	%rbp                # <--- 函数实际入口
 332cdf7:	48 89 e5	movq	%rsp, %rbp
 332cdfa:	41 57	pushq	%r15
 332cdfc:	41 56	pushq	%r14
 332cdfe:	41 54	pushq	%r12
 332ce00:	53	pushq	%rbx
 332ce01:	41 89 ce	movl	%ecx, %r14d
 332ce04:	49 89 d7	movq	%rdx, %r15
 332ce07:	49 89 f4	movq	%rsi, %r12
 332ce0a:	48 89 fb	movq	%rdi, %rbx
 332ce0d:	48 8d 35 cb a3 65 00	leaq	0x65a3cb(%rip), %rsi ## literal pool for: "nt_sqlite3_key_v2: db=%p zDb=%s"
```

**分析**：
1.  `jmp` 指令将程序执行流无条件转移至 `0x332cdf6`，这是一种常见的尾调用优化。
2.  在地址 `0x332cdf6` 处，我们看到了 x86-64 架构标准的函数序言（function prologue）指令：
    *   `pushq %rbp`：保存调用者的栈底指针。
    *   `movq %rsp, %rbp`：建立本函数的新栈帧。

综上所述，我们可以确定 `nt_sqlite3_key_v2` 函数的实际入口**偏移地址**为 `0x332cdf6`。

### 2.2 使用 lldb 附加进程并读取密钥

`sqlite3_key_v2` 函数原型如下，它决定了我们将从哪些寄存器中读取参数：

```c
int sqlite3_key_v2(
  sqlite3 *db,         // 目标数据库对象 (第一个参数, 存放在 rdi 寄存器)
  const char *zDbName, // 数据库名 (第二个参数, 存放在 rsi 寄存器)
  const void *pKey,    // 密钥地址 (第三个参数, 存放在 rdx 寄存器)
  int nKey             // 密钥长度 (第四个参数, 存放在 rcx 寄存器)
);
```

现在，我们通过 `lldb` 调试器在运行时捕获这些参数。

```bash
# 查找正在运行的 QQ 进程的 PID
ps aux | grep 'QQ$' | awk '{print $2}'
2349 # <-- 这是示例 PID，请替换为您自己的

# 启动 lldb 并附加到 QQ 进程
lldb --attach-pid 2349

# 获取 wrapper.node 库在内存中的基地址
(lldb) image list -o -f | grep /Applications/QQ.app/Contents/Resources/app/wrapper.node
[  0] 0x0000000110068000 /Applications/QQ.app/Contents/Resources/app/wrapper.node

# 计算函数的实际内存地址 (基地址 + 偏移地址)
(lldb) expr 0x0000000110068000 + 0x332cdf6
(long) $0 = 4617489910

# 在该地址设置断点
(lldb) br s -a 4617489910

# continue，让 QQ 继续运行
(lldb) c

# 点击 QQ 的任意聊天窗口
# 一般情况下，lldb 将在我们设置的断点处暂停执行

# 读取密钥长度 (从 rcx 寄存器)
# 如果值为 0x10 (十进制的 16)，通常表示已成功捕获。
(lldb) register read rcx
      rcx = 0x0000000000000010

# 读取密钥的内存地址 (从 rdx 寄存器)
(lldb) register read rdx
      rdx = 0x0000010805f442c0

# 从该地址读取 16 字节的密钥内容
# 下方的 "Z[12?_]7OMsX?X22" 即为密钥。注意：密钥在不同环境下是不同的，此值仅作示例。
(lldb) memory read --format c --count 16 --size 1 0x0000010805f442c0
0x10805f442c0: Z[12?_]7OMsX?X22

# 密钥获取成功，退出调试
(lldb) detach
(lldb) exit
```

## 3. 转移到 Windows

本页到这里完成 macOS 端的 key 提取。请复制原始数据库文件和 key 到 Windows，不要在 macOS 上直接改写数据库；后续按[统一解密](../decrypt_db)处理。
