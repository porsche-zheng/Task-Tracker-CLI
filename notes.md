# 实现笔记

## 1. 类 `task` 和 `task_manager`

### 1.1. enum class
- 定义：
  `enum class status {a, b, c...}`
- 声明：
  `status s = status::a`

### 1.2. 获取当前时间
C++ 获取当前时间的常用方法：
```cpp
#include <chrono>
#include <ctime>
chrono::system_clock::time_point now = chrono::system_clock::now();
time_t now_c = chrono::system_clock::to_time_t(now);
tm* local_tm = localtime(&now_c);
std::cout << "year: " << local_tm->tm_year + 1900 << std::endl;
std::cout << "month: " << local_tm->tm_mon + 1 << std::endl;
std::cout << "day: " << local_tm->tm_mday << std::endl;
std::cout << "hour: " << local_tm->tm_hour << std::endl;
std::cout << "minute: " << local_tm->tm_min << std::endl;
std::cout << "second: " << local_tm->tm_sec << std::endl;
```

### 1.3. 头文件循环依赖
#### 需求描述：
`A.hpp` 定义 `class A`，`B.hpp` 定义 `class B`，且 `B.hpp` 需要 `#include "A.hpp"`，但又要将 `class B` 设为 `class A` 的友元。为避免头文件循环：
#### 解决方案：
在 `A.hpp` 中**前置声明** `class B`，并设置友元，无需 `#include "B.hpp"`。

## 2. 主函数与命令处理

### 2.1. string_view
C++17 引入的轻量级字符串视图类型：
- 作用：
    - 不复制，仅引用原字符串的一段
    - 高效完成子串、查找、比较等操作
- 使用场景：
    - CLI 命令解析
    - 协议分析
- 注意事项：
    - `string_view` 只读，不能修改原字符串
    - 原字符串销毁后，`string_view` 失效
```cpp
void check_prefix(std::string_view sv) {
    if (sv.substr(0, 9) == "task-cli ") {
        cout << "Valid prefix!" << endl;
    }
}
```

### 2.2. 字符串常用操作
- `str.length()`/`str.size()`：返回长度
- `str.substr(pos, len)`：获取子串，从 `str[pos]` 开始，长度为 `len`
- `str[index]`：访问指定位置字符
- `str.at(index)`：安全访问指定位置字符
- `str.insert(pos, str0)`：在 `pos` 后插入 `str0`
- `str.append(str0)`：在末尾追加 `str0`
- `str.push_back(ch)`：末尾添加字符
- `str.pop_back()`：删除末尾字符
- `str.front()`/`str.back()`：首/尾字符
- `str.compare(str0)`：字符串比较
- `str.empty()`：判断是否为空
- `str.clear()`：清空字符串
- `str.find(sub)`/`rfind(sub)`：查找子串
- `str.replace(pos, len, str0)`：替换子串
- `str.erase(pos, len)`：删除子串
- `str.c_str()`：转为C风格字符串

### 2.3. CLI中高效字符串匹配
- 用 `string_view` 处理命令，避免拷贝
- 用 `starts_with`（C++20）或 `substr`+`==` 判断前缀
- 用 `find`、`rfind`、`compare` 等高效查找
```cpp
std::string_view cmd = "task-cli add \"learn python\"";
if(cmd.substr(0, 13) == "task-cli add" && cmd.back() == '"'){
    Add(cmd.substr(14, cmd.length()-15));
}
```

## 3. 文件读写与路径

### 3.1. C++ 文件操作库
标准库 `<fstream>` 提供三种文件流：
- `ifstream`：只读
- `ofstream`：写入（会覆盖原内容）
- `fstream`：读写
```cpp
#include <fstream>
ifstream fin(filename);
getline(fin, line);
fin.close();
// 逐行读取，且不会包含末尾换行符
ofstream fout(filename);
fout << "Write Into The File:" << endl;
fout << "    This is a\n    demo!";
fout.close();
```

### 3.2. 文件路径与文件名
- `../task.json`：上级目录
- `task.json`：当前目录
- 注意：路径分隔符推荐用 `/` 或 `\\`，不要用单个 `\`

### 3.3. int 转 string
- 用 `std::to_string(int)`

### 3.4. 其他补充
- 文件流不会自动加引号、逗号，JSON格式要手动拼接
- 逻辑删除建议用布尔标记，遍历时跳过
- 错误日志建议统一格式，如 `[ERROR] [Input] <描述>`
- 头文件循环用前置声明解决
- `string_view` 适合高效只读处理，注意生命周期
