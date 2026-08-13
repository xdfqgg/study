#include <iostream>

int main() {
    int* p = new int[100];     // 借了 100 个 int
    std::cout << p[0] << '\n'; // 用了
    // 忘了 delete[] p          // ← 泄漏！（一次性小程序，退出就回收，看不太出来）
    return 0;
}