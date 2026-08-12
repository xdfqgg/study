#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    // ① 从 stdin 读整数直到 EOF，直接构造 vector（两个迭代器作范围）
    std::vector<int> v{std::istream_iterator<int>(std::cin),
                       std::istream_iterator<int>()};

    // ② transform：每个元素平方，直接写进 cout（ostream_iterator 带空格分隔）
    std::transform(v.begin(), v.end(),
                   std::ostream_iterator<int>(std::cout, " "),
                   [](int x){ return x * x; });
    std::cout << '\n';

    // ③ partial_sum 前缀和 → 通过 back_inserter 自动追加到空容器 w
    std::vector<int> w;
    std::partial_sum(v.begin(), v.end(), std::back_inserter(w));
    for (int x : w) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}