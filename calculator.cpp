#include <bits/stdc++.h>

int main() {
    std::vector<std::string> results;
    long long a, b;
    
    while (std::cin >> a >> b) {
        std::string line ="a + b = " + std::to_string(a + b) ;
        line += ", a - b = " + std::to_string(a - b);
        line += ", a * b = " + std::to_string(a * b);
        if (b == 0) {
            line += ", Division by zero";
        } else {
            line += ", a / b = " + std::to_string(a / b);
        }
        results.push_back(line);
    }

    std::cout <<"-------所有结果----------" <<std::endl;
    for (const auto& result : results) {
        std::cout << result << std::endl;
    }
    return 0;
}