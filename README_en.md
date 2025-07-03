# Task Tracker CLI

[Task Tracker CLI](https://roadmap.sh/projects/task-tracker)

A simple command-line tool for tracking your daily tasks, written in C++.

## Features
- Add, update, delete tasks
- Mark tasks as in progress or done
- List all, done, todo, or in-progress tasks
- Persistent storage using JSON file
- Simple and efficient CLI interface

## Getting Started

### Prerequisites
- C++17 or above
- A C++ compiler (e.g. g++, clang++)

### Build
```sh
g++ src/main.cpp -o task_tracker
```

### Usage
```sh
./task_tracker
```

Example commands:
```
task-cli add "learn C++"
task-cli update 1 "learn modern C++"
task-cli mark-in-progress 1
task-cli mark-done 1
task-cli delete 1
task-cli list
task-cli list done
task-cli list todo
task-cli list in-progress
```

## File Structure
```text
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

## Project Roadmap
- [x] Basic CLI task management
- [x] JSON file persistence
- [ ] More robust error handling
- [ ] Unit tests
- [ ] Cross-platform support

## License
MIT