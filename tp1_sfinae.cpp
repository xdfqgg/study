#include <iostream>
#include <type_traits>
#include<concepts>

// SFINAE：只有 T 是整数类型时才启用这个版本
template <std::integral T>
bool is_even(T v)
{
    return (v % 2) == 0;
}

// 备选：其他类型走这个"兜底"版本，返回 false
template <typename T>
bool is_even(T)
{
    return false;
}

// constexpr 阶乘：编译期就能算出结果
constexpr unsigned long long factorial(unsigned n)
{
    return n <= 1 ? 1 : (n * factorial(n - 1));
}

int main()
{
    std::cout << std::boolalpha;                              // 让 bool 输出 true/false
    std::cout << "is_even(4)   = " << is_even(4) << '\n';     // 整型 → true
    std::cout << "is_even(3.14) = " << is_even(3.14) << '\n'; // 浮点 → 走兜底 → false
    std::cout << "fact(10)     = " << factorial(10) << '\n';  // 10! = 3628800
    return 0;
}