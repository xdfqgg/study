#include <iostream>
#include "demo_utils.h"   // safer_save 在这里，fs 别名也在这里

int main() {
    fs::path p = "data.txt";                  // 用文件系统路径类型
    if (safer_save(p, "hello world\n"))       // 返回 bool：成功 true / 失败 false
        std::cout << "saved\n";
    return 0;
}