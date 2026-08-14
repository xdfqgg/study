#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

long long sum_range(const std::vector<int> &data, std::size_t begin, std::size_t end)
{
    long long total = 0;
    for (std::size_t i = begin; i < end; ++i)
    {
        total += data[i];
    }
    return total;
}

int main()
{
    std::vector<int> data;
    const std::size_t n = 1'000'000;
    data.reserve(n);

    for (std::size_t i = 1; i <= n; ++i)
    {
        data.push_back(static_cast<int>(i));
    }

    const std::size_t workers = std::thread::hardware_concurrency() > 0
                                    ? std::thread::hardware_concurrency()
                                    : 4;

    const std::size_t block = (n + workers - 1) / workers;
    std::vector<std::future<long long>> futures;
    futures.reserve(workers);

    for (std::size_t i = 0; i < workers; ++i)
    {
        const std::size_t begin = i * block;
        const std::size_t end = std::min(begin + block, n);

        if (begin < end)
        {
            futures.emplace_back(
                std::async(std::launch::async, sum_range, std::cref(data), begin, end));
        }
    }

    long long total = 0;
    for (auto &f : futures)
    {
        total += f.get();
    }

    std::cout << "sum = " << total << '\n';
    std::cout << "expected = " << (n * (n + 1LL) / 2) << '\n';

    return 0;
}
