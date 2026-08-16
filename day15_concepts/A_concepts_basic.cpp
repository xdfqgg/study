#include <concepts>
#include <iostream>
#include <type_traits>

template <typename T>
concept Integral = std::is_integral_v<T>;

auto square(Integral auto x)
{
    return x * x;
}

int main()
{
    std::cout << square(5) << '\n';
    return 0;
}
