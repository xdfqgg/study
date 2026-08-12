#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <type_traits>

using U = std::variant<int, std::string>;

void print_U(const U &t)
{
    std::visit([](auto&& arg){
        if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, int>){
            std::cout << "INT(" << arg << ")";
        }
        else{ 
            std::cout << "STRING(" << arg << ")";
        }
        },t);
}

int main() {
        std::vector<U> v{std::string(), std::string("hello"), 7, std::string("x")};
        for (auto &t : v)
        {
            print_U(t);
            std::cout << '\n';
        }

        // 安全访问：get_if 返回指针，不是 int 就返回 nullptr
        if (auto p = std::get_if<int>(&v[0]))
            std::cout << "first is int = " << *p << '\n';
        return 0;
}