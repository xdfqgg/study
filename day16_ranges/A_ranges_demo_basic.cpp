#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> v(100);
    std::iota(v.begin(), v.end(), 1);

    auto view = v
        | std::views::filter([](int x) { return x % 2 == 0; })
        | std::views::transform([](int x) { return x * x; })
        | std::views::take(10);

    for (int x : view) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    return 0;
}
