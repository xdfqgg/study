#include <iostream>
#include <typeinfo>

// 主模板：装值
template<typename T>
struct Holder {
    T value;
    Holder(T v) : value(v) {}
    void print() const {
        std::cout << "Holder<" << typeid(T).name() << ">: " << value << '\n';
    }
};

// 偏特化：装指针
template<typename T>
struct Holder<T*> {
    T* value;
    Holder(T* v) : value(v) {}
    void print() const {
        if (value)
            std::cout << "Holder<" << typeid(T).name() << "*>: " << *value << '\n';
        else
            std::cout << "null ptr\n";
    }
};

int main() {
    Holder<int> h1(42);
    h1.print();       // 用主模板

    int x = 7;
    Holder<int*> h2(&x);
    h2.print();       // 用偏特化（打印指针指向的值）
    return 0;
}