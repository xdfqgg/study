#include <cmath>
#include <numbers>
#include <iostream>
#include <memory>
#include <vector>

struct Shape
{
    virtual ~Shape() = default;      // virtual 析构（必须！）
    virtual double area() const = 0; // 纯虚函数（抽象接口）
    virtual void info() const { std::cout << "Shape\n"; }
};

struct Rectangle : Shape
{
    double w, h;
    Rectangle(double w_, double h_) : w(w_), h(h_) {}
    double area() const override { return w * h; }
    void info() const override { std::cout << "Rectangle\n"; }
};

struct Circle : Shape
{
    double r;
    Circle(double r_) : r(r_) {}
    double area() const override { return std::numbers::pi * r * r; } // C++20 标准 π
    void info() const override { std::cout << "Circle\n"; }
};

int main()
{
    std::vector<std::unique_ptr<Shape>> v;
    v.push_back(std::make_unique<Rectangle>(3.0, 4.0));
    v.push_back(std::make_unique<Circle>(1.0));
    for (const auto &s : v)
    {
        s->info();
        std::cout << "area=" << s->area() << '\n';
    }
    return 0;
}