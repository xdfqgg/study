#include <iostream>
#include <memory>

int main()
{
    auto p = std::make_unique<int>(42);
    std::unique_ptr<int> m; // ① 释放了 p
    std::cout << *p << '\n';
    return 0;
}