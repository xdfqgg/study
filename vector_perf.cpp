#include <chrono>
#include <iostream>
#include <vector>

int main() {
    const int N = 5000000;

    {
        std::vector<int> v;
        auto start = std::chrono::steady_clock::now();
        for(int i = 0; i < N; i++)v.push_back(i);
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "1. push_back 无 reserve: " << ms << " ms"
                << "capacity=" << v.capacity() << std::endl;
    }
    {
        std::vector<int> v;
        v.reserve(N);
        auto start = std::chrono::steady_clock::now();
        for(int i = 0; i < N; i++)v.push_back(i);
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "2. reserve后push_back: " << ms << " ms"
                << "capacity=" << v.capacity() << std::endl;
    }
    {
        std::vector<int> v;
        v.reserve(N);
        auto start = std::chrono::steady_clock::now();
        for(int i = 0; i < N; i++)v.emplace_back(i);
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "3. reserve + emplace_back: " << ms << " ms"
                << "capacity=" << v.capacity() << std::endl;
    }

}