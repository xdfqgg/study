#include <chrono>
#include <iostream>
#include <vector>

// 试除法：判断单个 n 是否质数
bool is_prime_trial(int n) {
    if (n < 2) return false;
    for (int d = 2; d * d <= n; ++d)
        if (n % d == 0) return false;
    return true;
}

// 试除法生成 <= n 的所有质数
std::vector<int> trial_upto(int n) {
    std::vector<int> primes;
    for (int i = 2; i <= n; ++i)
        if (is_prime_trial(i)) primes.push_back(i);
    return primes;
}

// 埃拉托斯特尼筛法生成 <= n 的所有质数
std::vector<int> sieve(int n) {
    std::vector<bool> is_prime(n + 1, true);   // 默认都认为是质数
    is_prime[0] = is_prime[1] = false;         // 0 和 1 不是质数

    for (int p = 2; (long long)p * p <= n; ++p) {   // ⚠️ 见下方"坑"
        if (is_prime[p]) {                         // p 是质数
            for (long long m = (long long)p * p; m <= n; m += p)
                is_prime[(int)m] = false;          // 标掉 p 的倍数
        }
    }

    std::vector<int> primes;
    for (int i = 2; i <= n; ++i)
        if (is_prime[i]) primes.push_back(i);
    return primes;
}

int main() {
    const int N = 1'000'000;   // 100万

    auto t1 = std::chrono::steady_clock::now();
    auto p1 = trial_upto(N);
    auto t2 = std::chrono::steady_clock::now();
    auto ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "试除法: " << ms1 << " ms, 找到 " << p1.size() << " 个质数\n";

    auto t3 = std::chrono::steady_clock::now();
    auto p2 = sieve(N);
    auto t4 = std::chrono::steady_clock::now();
    auto ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();
    std::cout << "筛法  : " << ms2 << " ms, 找到 " << p2.size() << " 个质数\n";
    return 0;
}