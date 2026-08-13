#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// 方式1：mutex + lock_guard（加锁保护，正确但慢）
void inc_with_mutex(long long &c, std::mutex &m, int increments)
{
    for (int i = 0; i < increments; ++i)
    {
        std::lock_guard<std::mutex> lk(m); // 进门上锁
        ++c;                               // 屋里只有我一个，安全
    } // 出门自动解锁
}

// 方式2：atomic 原子加（无锁，通常更快）
void inc_with_atomic(std::atomic<long long> &c, int increments)
{
    for (int i = 0; i < increments; ++i)
        c.fetch_add(1, std::memory_order_relaxed);
}

int main()
{
    const int N = 4;
    const int INC = 500'00000;

    // ---- mutex 版 ----
    {
        long long counter = 0;
        std::mutex m;
        auto t0 = std::chrono::steady_clock::now();
        std::vector<std::thread> ths;
        for (int i = 0; i < N; ++i)
            ths.emplace_back(inc_with_mutex, std::ref(counter), std::ref(m), INC);
        for (auto &t : ths)
            t.join(); // ⚠️ 这里一定是 t.join()！计划里误写成 ths.join()
        auto t1 = std::chrono::steady_clock::now();
        std::cout << "mutex  counter=" << counter
                  << " time=" << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms\n";
    }

    // ---- atomic 版 ----
    {
        std::atomic<long long> counter{0};
        auto t0 = std::chrono::steady_clock::now();
        std::vector<std::thread> ths;
        for (int i = 0; i < N; ++i)
            ths.emplace_back(inc_with_atomic, std::ref(counter), INC);
        for (auto &t : ths)
            t.join(); // ⚠️ 同上，别写成 ths.join()
        auto t1 = std::chrono::steady_clock::now();
        std::cout << "atomic counter=" << counter.load()
                  << " time=" << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms\n";
    }
    return 0;
}