// sieve_prof.cpp —— 用于 gprof 剖析的版本（N 调大，让试除法跑够时间）
#include <chrono>
#include <iostream>
#include <vector>

// 试除法：判断单个 n 是否质数（会被调用几百万次 → 热点候选）
bool is_prime_trial(int n)
{
    if (n < 2)
        return false;
    for (int d = 2; d * d <= n; ++d)
        if (n % d == 0)
            return false;
    return true;
}

// 试除法生成 <= n 的所有质数
std::vector<int> trial_upto(int n)
{
    std::vector<int> primes;
    for (int i = 2; i <= n; ++i)
        if (is_prime_trial(i))
            primes.push_back(i);
    return primes;
}

// 埃拉托斯特尼筛法生成 <= n 的所有质数
std::vector<int> sieve(int n)
{
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; (long long)p * p <= n; ++p)
    {
        if (is_prime[p])
        {
            for (long long m = (long long)p * p; m <= n; m += p)
                is_prime[(int)m] = false;
        }
    }
    std::vector<int> primes;
    for (int i = 2; i <= n; ++i)
        if (is_prime[i])
            primes.push_back(i);
    return primes;
}

int main()
{
    const int N = 15'000'000; // 1500万：确保程序跑 5 秒以上，gprof 采到样（输出用英文避免乱码）

    auto t1 = std::chrono::steady_clock::now();
    auto p1 = trial_upto(N);
    auto t2 = std::chrono::steady_clock::now();
    auto ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "trial: " << ms1 << " ms, " << p1.size() << " primes\n";

    auto t3 = std::chrono::steady_clock::now();
    auto p2 = sieve(N);
    auto t4 = std::chrono::steady_clock::now();
    auto ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();
    std::cout << "sieve: " << ms2 << " ms, " << p2.size() << " primes\n";
    return 0;
}
