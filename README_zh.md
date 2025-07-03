# 任务追踪命令行工具（Task Tracker CLI）

[Task Tracker CLI](https://roadmap.sh/projects/task-tracker)

一个用 C++ 编写的简单命令行任务管理工具。

## 功能特性
- 添加、更新、删除任务
- 标记任务为进行中或已完成
- 支持列出所有、已完成、待办、进行中的任务
- 使用 JSON 文件持久化存储
- 简洁高效的命令行交互

## 快速开始

### 依赖环境
- C++17 或更高版本
- C++ 编译器（如 g++、clang++）

### 编译
```sh
g++ src/main.cpp -o task_tracker
```

### 使用方法
```sh
./task_tracker
```

示例命令：
```text
task-cli add "学习 C++"
task-cli update 1 "学习现代 C++"
task-cli mark-in-progress 1
task-cli mark-done 1
task-cli delete 1
task-cli list
task-cli list done
task-cli list todo
task-cli list in-progress
```

## 项目结构
```
src/
  main.cpp
  task_manager.hpp
  task.hpp
  file_operation.hpp
task.json
README.md
notes_en.md
notes_zh.md
```

## 项目规划
- [x] 基本命令行任务管理
- [x] JSON 文件持久化
- [ ] 更健壮的错误处理
- [ ] 单元测试
- [ ] 跨平台支持

## 许可证
MIT
