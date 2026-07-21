---
title: 统一解密 NTQQ 数据库
next: false
order: 3
---

# 统一解密 NTQQ 数据库

本文是[分平台提取](./extract/)之后的唯一解密教程。所有平台都先得到原始 `nt_msg.db` 和 key，再在 Windows 上使用 [QQBackup/nt_msg_db_util](https://github.com/QQBackup/nt_msg_db_util) 的脚本 1 `1.decrypt.py`。

本教程只负责得到**未加密的原始 SQLite 数据库**，不包含数据库精简、消息转换或其它导出步骤。

## 快速流程

1. 准备 `nt_msg.db`（原始加密数据库）和 key
2. 克隆脚本仓库，放入 `nt_msg.db`
3. 编辑 `1.decrypt.py`，填入 **数据库路径** 和 **key** 两项即可
4. 运行脚本，生成两个产物文件

## 准备材料

从平台提取教程得到两样东西：

- `nt_msg.db` — 原始加密数据库
- key — 一段 hex 字符串

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

```powershell
git clone https://github.com/QQBackup/nt_msg_db_util.git
Set-Location nt_msg_db_util
uv sync
```

将 `nt_msg.db` 复制到 `nt_msg_db_util` 目录下（或修改脚本中的路径指向它）。

## 配置并执行

编辑 `1.decrypt.py`，**只需改两项**：

```python
INPUT_DB  = "nt_msg.db"   # ← 原始加密数据库的路径
DB_KEY    = "在此粘贴 key"  # ← 粘贴你的 key，不要带换行
```

其余配置保持默认即可。然后运行：

```powershell
uv run python 1.decrypt.py
```

成功后目录下生成两个文件：

| 文件 | 说明 |
| --- | --- |
| `nt_msg_clear.db` | 去掉 1024 字节 NTQQ 文件头后的中间文件 |
| `nt_msg_plain.db` | **最终产物**：未加密 SQLite 数据库 |

用 DB Browser for SQLite、SQLiteStudio 或 DBeaver 直接打开 `nt_msg_plain.db`，无需密码。

## 下一步

`nt_msg_plain.db` 是解密阶段的最终结果。请进入[读取数据库](../database/read_db)继续查看表结构、解析消息或进行后续导出。
