#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

class IntRange {
public:
    struct Iterator {
        // ★ 身份牌：告诉标准库"我是随机访问迭代器"
        using value_type        = int;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const int*;
        using reference         = int;
        using iterator_category = std::random_access_iterator_tag;

        Iterator(int cur, int step = 1) : cur_(cur), step_(step) {}

        // 读取
        int operator*() const { return cur_; }

        // 前后移动（++ 前进一个 step）
        Iterator& operator++() { cur_ += step_; return *this; }
        Iterator operator++(int) { Iterator t = *this; ++(*this); return t; }
        Iterator& operator--() { cur_ -= step_; return *this; }
        Iterator operator--(int) { Iterator t = *this; --(*this); return t; }

        // ★ 随机访问：直接跳 n 步
        Iterator& operator+=(difference_type n) { cur_ += n * step_; return *this; }
        Iterator& operator-=(difference_type n) { cur_ -= n * step_; return *this; }
        Iterator operator+(difference_type n) const { Iterator t = *this; t += n; return t; }
        Iterator operator-(difference_type n) const { Iterator t = *this; t -= n; return t; }
        friend Iterator operator+(difference_type n, const Iterator& it) { return it + n; }

        // ★ 距离（以元素个数为单位）
        difference_type operator-(const Iterator& o) const { return (cur_ - o.cur_) / step_; }

        // ★ 下标访问
        int operator[](difference_type n) const { return *(*this + n); }

        // 比较
        bool operator==(const Iterator& o) const { return cur_ == o.cur_ && step_ == o.step_; }
        bool operator!=(const Iterator& o) const { return !(*this == o); }
        bool operator<(const Iterator& o) const  { return cur_ < o.cur_; }
        bool operator>(const Iterator& o) const  { return o < *this; }
        bool operator<=(const Iterator& o) const { return !(o < *this); }
        bool operator>=(const Iterator& o) const { return !(*this < o); }

    private:
        int cur_;     // 当前值
        int step_;    // 步长
    };

    IntRange(int begin, int end, int step = 1) : b_(begin), e_(end), step_(step) {}
    Iterator begin() const { return Iterator(b_, step_); }
    Iterator end()   const { return Iterator(e_, step_); }

private:
    int b_, e_, step_;
};

int main() {
    // ① 基本遍历（带步长 2）→ 0 2 4 6 8
    for (int i : IntRange(0, 10, 2)) std::cout << i << ' ';
    std::cout << '\n';

    IntRange r(0, 10);

    // ② 随机访问专属操作（升级点！）
    auto it = r.begin();
    std::cout << "*(it+3) = " << *(it + 3) << '\n';    // 3
    std::cout << "it[4]   = " << it[4] << '\n';         // 4
    std::cout << "end-begin = " << (r.end() - it) << '\n';  // 10
    std::cout << "it < end = " << (it < r.end()) << '\n';   // 1

    // ③ 喂给 std::sort —— 只有 RandomAccess 迭代器才配！
    std::vector<int> v(r.begin(), r.end());
    std::sort(v.begin(), v.end(), std::greater<>());
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}