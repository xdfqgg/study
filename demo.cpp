#include <iostream>

// 一个简单的加法函数
int add(int a, int b)
{
    return a + b;
}

int main()
{
    int sum = 0;

    for (int i = 1; i <= 5; i++)
    {
        sum = add(sum, i); // ← 在这里设断点
        std::cout << "第 " << i << " 次累加后 sum = " << sum << std::endl;
    }

    std::cout << "最终结果: " << sum << std::endl;
    return 0;
}
