#include <iostream>
#include <string>

template<typename T>
T add(T a, T b) {
    return a + b;
}

// 对 const char* 用重载处理，返回 std::string
std::string add(const char* a, const char* b) {
    return std::string(a) + std::string(b);
}

int main() {
    std::cout << add(1, 2) << '\n';                              // 3
    std::cout << add(1.5, 2.5) << '\n';                          // 4
    std::cout << add(std::string("a"), std::string("b")) << '\n'; // ab
    std::cout << add("hello", "world") << '\n';                  // helloworld
    return 0;
}