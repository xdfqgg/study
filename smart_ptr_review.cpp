#include <iostream>
#include <string>
#include <memory>

std::unique_ptr<int> make_number(int x)
{ // ✅ 移到 main 外面（全局函数）
    return std::make_unique<int>(x);
}

int main()
{
    auto p = make_number(42);
    std::cout << *p << '\n'; // 42
    auto q = std::move(p);   // 所有权从 p 转到 q
                             // p 现在是空的！
    auto s = std::make_shared<int>(10);
    std::cout << s.use_count() << '\n'; // 1（只有 s 一个）
    auto s2 = s;                        // 拷贝一个 shared_ptr（不是 unique！）
    std::cout << s.use_count() << '\n'; // 2（s 和 s2 共享）
}