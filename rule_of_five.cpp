#include <iostream>
#include <utility>
#include <algorithm>

class Buffer {
    int* data_;      // 资源：自己 new 出来的数组
    size_t size_;
public:
    explicit Buffer(size_t n) : data_(new int[n]{}), size_(n) {
        std::cout << "[构造] Buffer(" << n << ")\n";
    }

    // ① 析构：释放资源
    ~Buffer() {
        std::cout << "[析构] Buffer(" << size_ << ")\n";
        delete[] data_;
    }

    // ② 拷贝构造：复印（new 一块新的，逐个复制）
    Buffer(const Buffer& other)
        : data_(new int[other.size_]), size_(other.size_) {
        std::cout << "[拷贝构造]\n";
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    // ③ 拷贝赋值：先删旧的，再复印
    Buffer& operator=(const Buffer& other) {
        std::cout << "[拷贝赋值]\n";
        if (this != &other) {                 // 防止 a = a 自赋值
            delete[] data_;
            data_ = new int[other.size_];
            size_ = other.size_;
            std::copy(other.data_, other.data_ + other.size_, data_);
        }
        return *this;
    }

    // ④ 移动构造：搬家（偷指针，原对象置空）
    Buffer(Buffer&& other) noexcept
        : data_(other.data_), size_(other.size_) {
        std::cout << "[移动构造]\n";
        other.data_ = nullptr;   // 重要：原对象置空，防止析构时二次释放
        other.size_ = 0;
    }

    // ⑤ 移动赋值：先删旧的，再偷指针
    Buffer& operator=(Buffer&& other) noexcept {
        std::cout << "[移动赋值]\n";
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    void fill(int v) { std::fill(data_, data_ + size_, v); }

    void print() const {
        for (size_t i = 0; i < size_; ++i)
            std::cout << data_[i] << ' ';
        std::cout << '\n';
    }
};

Buffer make_buffer(int n) {
    Buffer b(n);
    b.fill(n);
    return b;          // 返回值 → 移动构造（或 RVO 省略）
}

int main() {
    Buffer a(5);
    a.fill(1);
    a.print();                 // 1 1 1 1 1

    Buffer b = a;              // ？→ 拷贝构造
    b.print();

    Buffer c(3);
    c = a;                     // ？→ 拷贝赋值
    c.print();

    Buffer d = std::move(b);   // ？→ 移动构造（b 被搬空）
    d.print();

    Buffer e(2);
    e = std::move(d);          // ？→ 移动赋值（d 被搬空）
    e.print();

    Buffer f = make_buffer(4); // 返回值 → 移动构造（或 RVO）
    f.print();
    return 0;
}

