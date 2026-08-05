#include <algorithm>
#include<iostream>
#include <span>
#include <vector>

void reverse_span(std::span<int> s){
    std::reverse(s.begin(), s.end());
}
int main() {
    std::vector<int> v{1, 2, 3, 4, 5};

    std::cout << "反转前: ";
    for (int x : v) std::cout << x << ' ';
    std::cout << "\n";

    reverse_span(v);   // 传 vector 给 span，就地反转

    std::cout << "反转后: ";
    for (int x : v) std::cout << x << ' ';
    std::cout << "\n";
    return 0;
}