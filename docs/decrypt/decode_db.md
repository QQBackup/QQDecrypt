---
title: 统一解密 NTQQ 数据库
next: false
order: 3
---

# 统一解密 NTQQ 数据库

本文是[分平台提取](./extract/)之后的唯一解密教程。所有平台都先得到原始 `nt_msg.db` 和 key，再在 Windows 上使用 [QQBackup/ntqq_msg_db_util](https://github.com/QQBackup/ntqq_msg_db_util) 的脚本 1 `1.decrypt.py`。

本教程只负责得到**未加密的原始 SQLite 数据库**，不包含数据库精简、消息转换或其它导出步骤。

## 输入与输出

将以下文件放在同一个工作目录：

```text
work/
├── nt_msg.db       # 从 QQ 数据目录原样复制的原始数据库
└── key.txt         # 平台提取教程得到的 key；稍后粘贴到脚本配置中
```

脚本会生成：

```text
nt_msg_clear.db     # 去掉 NTQQ 1024 字节文件头后的 SQLCipher 中间文件
nt_msg_plain.db     # 最终结果：未加密的原始 SQLite 数据库
```

`nt_msg_plain.db` 不再需要 key，可以直接使用 DB Browser for SQLite、SQLiteStudio、DBeaver 或其它普通 SQLite 工具打开。请保留 `nt_msg.db` 不变，并将所有操作放在副本或独立工作目录中。

## Windows 环境

本教程在 Windows 上执行。需要：

- Python 3.14（上游项目的 `pyproject.toml` 当前要求 Python `>=3.14`）
- [uv](https://docs.astral.sh/uv/)
- 从平台提取教程获得的 key

PowerShell 安装 uv：

```powershell
irm https://astral.sh/uv/install.ps1 | iex
```

## 获取脚本

在 PowerShell 中克隆上游仓库并进入目录：

```powershell
git clone https://github.com/QQBackup/ntqq_msg_db_util.git
Set-Location ntqq_msg_db_util
uv sync
```

将原始 `nt_msg.db` 复制到该目录，或修改脚本配置中的输入路径。脚本文件为 [`1.decrypt.py`](https://github.com/QQBackup/ntqq_msg_db_util/blob/master/1.decrypt.py)。

## 配置脚本

编辑 `1.decrypt.py` 顶部配置：

```python
INPUT_DB  = "nt_msg.db"        # 原始输入
CLEAR_DB  = "nt_msg_clear.db"  # 去掉 1024 字节头部后的中间文件
OUTPUT_DB = "nt_msg_plain.db"  # 未加密 SQLite 输出
DB_KEY    = "在此粘贴 key"      # 粘贴 key.txt 内容，不要带换行或多余空格
```

脚本 1 当前使用的 SQLCipher 参数顺序是固定的：

```sql
PRAGMA cipher_page_size = 4096;
PRAGMA key = '你的 key';
PRAGMA kdf_iter = 4000;
PRAGMA cipher_hmac_algorithm = HMAC_SHA1;
PRAGMA cipher_kdf_algorithm = PBKDF2_HMAC_SHA512;
```

## 执行

```powershell
uv run python 1.decrypt.py
```

执行完成后，确认目录中生成 `nt_msg_plain.db`。用普通 SQLite 工具打开它时不再需要输入密码；能够看到数据库表，即表示未加密数据库导出成功。

脚本支持断点续跑，并会对部分损坏页进行容错处理。如果执行中断，优先保留现有输出并重新执行，不要删除或覆盖原始 `nt_msg.db`。

## 下一步

`nt_msg_plain.db` 是解密阶段的最终结果。请进入[读取数据库](../database/read_db)继续查看表结构、解析消息或进行后续导出。
