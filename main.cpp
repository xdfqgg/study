#include <bits/stdc++.h>

int main()
{
    std::cout << "Enter your name: ";
    std::string name;
    if (!getline(std::cin, name))
        return 0;
    std::cout << "Hello, " << name << "!" << std::endl;

    std::cout << "Enter two integers a b (EOF to skip):\n";
    long long a, b;
    while (std::cin >> a >> b)
    {
        std::cout << "a + b = " << a + b << std::endl;
        if (b == 0)
            std::cout << "Division by zero" << std::endl;
        else
            std::cout << "a / b = " << (a / b) << std::endl;
        std::cout << "Enter two integers a b (EOF to skip):\n";
    }
    return 0;
}