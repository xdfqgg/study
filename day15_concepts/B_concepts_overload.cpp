#include <concepts>
#include <iostream>

template <typename T>
concept Integral = std::is_integral_v<T>;

template <typename T>
concept Floating = std::is_floating_point_v<T>;

int process(Integral auto x)
{
    std::cout << "integral\n";
    return x * 2;
}

double process(Floating auto x)
{
    std::cout << "floating\n";
    return x * 1.5;
}

int main()
{
    std::cout << process(3) << '\n';
    std::cout << process(3.14) << '\n';
}
