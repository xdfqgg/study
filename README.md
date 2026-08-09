# Todo 命令行应用

一个简单的命令行 Todo 管理工具（C++20），支持添加、列出、完成、删除任务，并持久化到文件。

## 编译

```powershell
g++ -std=c++20 -g todo_main.cpp todo.cpp -o todo.exe
```

## 使用

```powershell
.\todo.exe add "Buy milk"        # 添加任务
.\todo.exe list                   # 列出所有任务
.\todo.exe done 1                 # 标记 id=1 完成
.\todo.exe rm 2                   # 删除 id=2
.\todo.exe clear                  # 清空所有任务（需确认 yes）
.\todo.exe help                   # 显示帮助
```

## 存储格式

数据保存在当前目录的 `todo.txt`，每行一条任务：

```
id|done(0/1)|text
```

## 已知限制

- 简单文本格式：任务文本含 `|` 时解析可能出错
- 无并发写锁：多进程同时写可能冲突（MVP 阶段）
