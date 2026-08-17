#include <chrono>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

int main()
{
    const int N = 2'000'00000;
    std::vector<int> v(N);
    std::iota(v.begin(), v.end(), 1);

    auto t0 = std::chrono::steady_clock::now();
    auto view = v | std::views::filter([](int x)
                                       { return x % 3 == 0; }) 
                  | std::views::transform([](int x)
                                      { return x * 2; });

    long long s = 0;
    for (int x : view)
    {
        s += x;
    }
    auto t1 = std::chrono::steady_clock::now();
    std::cout << "ranges sum=" << s
              << " ms=" << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << '\n';

    t0 = std::chrono::steady_clock::now();
    std::vector<int> tmp;
    tmp.reserve(N / 3);
    for (int x : v)
    {
        if (x % 3 == 0)
        {
            tmp.push_back(x * 2);
        }
    }

    long long s2 = 0;
    for (int x : tmp)
    {
        s2 += x;
    }
    t1 = std::chrono::steady_clock::now();
    std::cout << "temp sum=" << s2
              << " ms=" << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << '\n';

    return 0;
}
