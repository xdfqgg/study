#include <memory>
#include <iostream>

std::unique_ptr<int> good() {
    return std::make_unique<int>(42);   // 分配到堆上，用智能指针管理
}                                        // 生命周期跟着 unique_ptr 走，不悬垂！
int main() {
    auto p = good();
    std::cout << *p << '\n';   // 输出 42 ✅（p 活着，内存就活着）
}