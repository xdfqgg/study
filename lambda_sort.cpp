#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

struct Item {
    std::string name;
    int score;
};

int main() {
    std::vector<Item> v = {{"alice", 90}, {"bob", 95}, {"amy", 90}, {"charlie", 85}};

    // 用 stable_sort + lambda 排序：分数降序，相同按名字升序
    std::stable_sort(v.begin(), v.end(), [](const Item& a, const Item& b) {
        if (a.score != b.score) return a.score > b.score;
        return a.name < b.name;
    });

    std::cout << "stable_sort 结果:\n";
    for (auto& it : v) std::cout << "  " << it.name << ":" << it.score << '\n';

    // 函数对象示例：带计数
    struct Comp {
        mutable int calls = 0;
        bool operator()(const Item& a, const Item& b) const {
            ++calls;
            if (a.score != b.score) return a.score > b.score;
            return a.name < b.name;
        }
    } comp;

    std::sort(v.begin(), v.end(), std::ref(comp));
    std::cout << "sort 结果:\n";
    for (auto& it : v) std::cout << "  " << it.name << ":" << it.score << '\n';
    std::cout << "比较器被调用了 " << comp.calls << " 次\n";
    return 0;
}