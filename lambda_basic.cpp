#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    int x = 10;
    auto by_value = [x]() { std::cout << "by_value x=" << x << '\n'; };
    auto by_ref   = [&x]() { std::cout << "by_ref x=" << x << '\n'; };

    x = 20;                    // 改外面
    by_value();                // 输出 10（复印件不变）
    by_ref();                  // 输出 20（原件变了）

    // mutable：允许改"按值拷进来的副本"
    int cnt = 0;
    auto inc = [cnt]() mutable { ++cnt; std::cout << "cnt in lambda=" << cnt << '\n'; };
    inc(); inc();
    std::cout << "cnt outside=" << cnt << '\n';   // 还是 0（外面没变）

    // 泛型 lambda：参数自动推断
    auto add1 = [](auto a, auto b) { return a + b; };
    std::cout << add1(1, 2) << ' '            // 3
              << add1(std::string("a"), "b") << '\n';  // ab

    // init-capture：把变量"搬"进 lambda（移动捕获）
    std::string s = "hello";
    auto mover = [s2 = std::move(s)]() { std::cout << s2 << '\n'; };
    // 现在 s 已经是空的了（被搬走了）
    if (s.empty()) std::cout << "s is empty after move\n";
    mover();

    return 0;
}