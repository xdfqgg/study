#include <iostream>
#include <string>
#include <utility>

struct Base {
    std::string name;
    Base(std::string n) : name(std::move(n)) {}
    virtual ~Base() = default;
    virtual void who() const { std::cout << "Base: " << name << '\n'; }
};

struct Derived : Base {
    int extra;
    Derived(std::string n, int e) : Base(std::move(n)), extra(e) {}
    void who() const override { std::cout << "Derived: " << name << " extra=" << extra << '\n'; }
};

void by_value(Base b) { b.who(); }        // ① 按值传 → 会切片
void by_ref(const Base& b) { b.who(); }   // ② 按引用传 → 多态

int main() {
    Derived d("d", 42);
    by_value(d);    // 会怎样？
    by_ref(d);      // 会怎样？
    return 0;
}