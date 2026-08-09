#include <iostream>

// fold 表达式：把所有参数依次打印
template<typename... Ts>
void print_all(const Ts&... args) {
    ( (std::cout << args << " "), ... );   // 逗号折叠：逐个输出
    std::cout << '\n';
}

// fold 表达式：把所有参数求和
template<typename... Ts>
auto sum_all(Ts... args) {
    return (args + ... + 0);   // + 折叠，初始值 0（兼容空包）
}

int main() {
    print_all(1, "hello", 3.14);       // 三种不同类型一次打印
    std::cout << sum_all(1, 2, 3, 4) << '\n';   // 求和 = 10
    return 0;
}