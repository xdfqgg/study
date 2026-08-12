#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = 0;
    // 管道：v → 过滤偶数 → 平方
    auto view = v | std::views::filter([&n](int x)
                                       {
              std::cout << n++ << std::endl;
              return x % 2 == 0; }) |
                std::views::transform([](int x)
                                      { return x * x; });

    for (int x : view)
        std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}