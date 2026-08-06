#include <iostream>
#include <memory>

struct B;

struct A {
    std::shared_ptr<B> bptr;
    ~A() { std::cout << "A dtor\n"; }
};

struct B {
    std::weak_ptr<A> aptr;   // 先保持 shared_ptr（故意制造循环引用）
    ~B() { std::cout << "B dtor\n"; }
};

int main() {
    {
        auto a = std::make_shared<A>();
        auto b = std::make_shared<B>();
        a->bptr = b;
        b->aptr = a;
    }
    std::cout << "end scope\n";
    return 0;
}