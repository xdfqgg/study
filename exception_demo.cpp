#include <iostream>
#include "demo_utils.h"   // MyError 和 divide 都在这里

int main() {
    try {
        std::cout << divide(10, 2) << '\n';   // 正常 → 打印 5
        std::cout << divide(10, 0) << '\n';   // 除零 → 抛 MyError
    } catch (const MyError& e) {
        std::cerr << "MyError caught: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "std::exception: " << e.what() << '\n';
    }
    return 0;
}