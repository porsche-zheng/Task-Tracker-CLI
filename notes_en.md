# Implementation Notes

## 1. Class `task` and `task_manager`

### 1.1. enum class
- Definition:
  `enum class status {a, b, c...}`
- Declaration:
  `status s = status::a`

### 1.2. Get current time
How to get current time in C++:
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

### 1.3. Header file circular dependency
#### Problem:
`A.hpp` defines `class A`, `B.hpp` defines `class B`, and `B.hpp` needs `#include "A.hpp"`, but you want to make `class B` a friend of `class A`. To avoid circular include:
#### Solution:
In `A.hpp`, **forward declare** `class B` and set as friend, no need to `#include "B.hpp"`.

## 2. Main function and command handling

### 2.1. string_view
C++17 lightweight string view type:
- Purpose:
    - No copy, just references a part of the original string
    - Efficient for substring, search, compare
- Usage scenarios:
    - CLI command parsing
    - Protocol analysis
- Notes:
    - `string_view` is read-only, cannot modify original string
    - If the original string is destroyed, `string_view` becomes invalid
```cpp
void check_prefix(std::string_view sv) {
    if (sv.substr(0, 9) == "task-cli ") {
        cout << "Valid prefix!" << endl;
    }
}
```

### 2.2. Common string operations
- `str.length()`/`str.size()`: get length
- `str.substr(pos, len)`: get substring from `str[pos]` of length `len`
- `str[index]`: access character at index
- `str.at(index)`: safe access with bounds checking
- `str.insert(pos, str0)`: insert `str0` after `str[pos]`
- `str.append(str0)`: append `str0` to the end
- `str.push_back(ch)`: add character to end
- `str.pop_back()`: remove last character
- `str.front()`/`str.back()`: first/last character
- `str.compare(str0)`: compare strings
- `str.empty()`: check if empty
- `str.clear()`: clear string
- `str.find(sub)`/`rfind(sub)`: find substring
- `str.replace(pos, len, str0)`: replace substring
- `str.erase(pos, len)`: erase substring
- `str.c_str()`: get C-style string

### 2.3. Efficient CLI string matching
- Use `string_view` to avoid copy
- Use `starts_with` (C++20) or `substr`+`==` for prefix matching
- Use `find`, `rfind`, `compare` for efficient search
```cpp
std::string_view cmd = "task-cli add \"learn python\"";
if(cmd.substr(0, 13) == "task-cli add" && cmd.back() == '"'){
    Add(cmd.substr(14, cmd.length()-15));
}
```

## 3. File read and write
### 3.1. C++ file operation library
Standard `<fstream>` provides 3 file streams:
- `ifstream`: read only
- `ofstream`: write (overwrites original content)
- `fstream`: read and write
```cpp
#include <fstream>
ifstream fin(filename);
getline(fin, line);
fin.close();
// Read line by line
ofstream fout(filename);
fout << "Write Into The File:" << endl;
fout << "    This is a\n    demo!";
fout.close();
```

### 3.2. File path and name
- `../task.json`: parent directory
- `task.json`: current directory
- Note: use `/` or `\\` as path separator, not single `\`

### 3.3. int to string
- Use `std::to_string(int)`

### 3.4. Additional notes
- File streams do not add quotes or commas automatically, JSON format must be handled manually
- Logical deletion is best with a boolean flag, skip when traversing
- Error logs should use a unified format, e.g. `[ERROR] [Input] <description>`
- Use forward declaration to solve header circular dependency
- `string_view` is for efficient, read-only string handling, but watch out for lifetime issues
