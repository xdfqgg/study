#include <concepts>
#include <iostream>
#include <string>

template <typename T>
concept HasToString = requires(T a) {
    { a.to_string() } -> std::convertible_to<std::string>;
};

template <typename T>
class Wrapper
{
public:
    void print() const
        requires HasToString<T>
    {
        std::cout << "can print\n";
    }
};

struct S
{
    std::string to_string() const
    {
        return "hello";
    }
};

int main()
{
    Wrapper<S> w;
    w.print();
}
