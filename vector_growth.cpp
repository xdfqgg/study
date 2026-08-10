#include <iostream>
#include <vector>

int main() {

    std::vector<int> v;
    std::cout << "初始容量: " << v.capacity() << "\n";

    for (int i = 0; i < 100; ++i) {
        v.push_back(i);
        std::cout << "添加元素 " << i << ", 容量: " << v.capacity() << "\n";
    }
    std::vector<int> v2;
    v2.reserve(100);
    for (int i = 0; i < 100; ++i) {
        v2.push_back(i);
        std::cout << "添加元素 " << i << ", 容量: " << v2.capacity() << "\n";
    }

    return 0;
}