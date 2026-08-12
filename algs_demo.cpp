#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> v = {1, -2, 3, -4, 5, 3, 2, -2};

    // ① erase-remove：删除所有负数（两步走！）
    v.erase(std::remove_if(v.begin(), v.end(), [](int x){ return x < 0; }), v.end());

    // ② transform：每个元素原地乘 2
    std::transform(v.begin(), v.end(), v.begin(), [](int x){ return x * 2; });

    // ③ partition：小于 6 的放前面（不保证稳定）
    auto it = std::partition(v.begin(), v.end(), [](int x){ return x < 6; });

    // ④ stable_sort：降序（稳定）
    std::stable_sort(v.begin(), v.end(), std::greater<>());

    for (int x : v) std::cout << x << ' ';
    std::cout << "\npartition point idx=" << std::distance(v.begin(), it) << "\n";

    // ⑤ unique + erase 去重（先排序了才能 unique）
    v.erase(std::unique(v.begin(), v.end()), v.end());
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}