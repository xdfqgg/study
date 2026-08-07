#include <functional>
#include <iostream>
#include <memory>
#include <string>

int main() {
    auto up = std::make_shared<std::string>("moved-string");

    // 用 init-capture 把 unique_ptr 搬进 lambda，再存进 std::function
    auto f = [p = std::move(up)]() {
        if (p) std::cout << *p << '\n';   // p 拥有资源，能读取
    };

    // 此时 up 已经空了（资源被搬到 lambda 里的 p）
    std::cout << "up 是空指针吗? " << (up ? "否" : "是") << "\n";

    f();   // 调用 lambda → 输出 moved-string
    return 0;
}