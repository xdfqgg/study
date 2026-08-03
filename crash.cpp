#include <iostream>

// 危险的函数：访问空指针，会崩溃
int dangerous(int n)
{
    int *p = nullptr; // 空指针
    return *p;        // ← 这里会崩溃（解引用空指针）
}

// 中间层函数，调用 dangerous
int middle(int x)
{
    return dangerous(x) + 1;
}

int main()
{
    std::cout << "程序开始..." << std::endl;
    int result = middle(42); // main → middle → dangerous
    std::cout << "结果: " << result << std::endl;
    return 0;
}
