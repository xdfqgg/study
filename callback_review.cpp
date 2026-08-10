#include <functional>
#include <iostream>
#include <vector>

void notify(const std::vector<std::function<void(int)>>& handlers, int v) {
    for (const auto& h : handlers)
        h(v);                       // 逐个调用（第5天的 kv.second(v) 还记得吗）
}

int main() {
    std::vector<std::function<void(int)>> handlers;

    // 回调1：直接打印 x*2（无捕获）
    handlers.push_back([](int x) { std::cout << "h1: " << x * 2 << '\n'; });

    // 回调2：值捕获 factor（固定值）
    int factor = 10;
    handlers.push_back([factor](int x) { std::cout << "h2: " << x * factor << '\n'; });

    // 回调3：引用捕获 counter（会改变外部变量！）
    int counter = 0;
    handlers.push_back([&counter](int x) {
        ++counter;
        std::cout << "h3: x=" << x << " counter=" << counter << '\n';
    });

    notify(handlers, 5);   // 第一次通知
    notify(handlers, 7);   // 第二次通知（counter 应该累积！）
    std::cout << "main 里 counter = " << counter << '\n';   // 应该是 2
    return 0;
}