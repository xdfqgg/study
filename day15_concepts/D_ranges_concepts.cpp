#include <concepts>
#include <ranges>
#include <vector>
#include <iostream>

template <std::ranges::input_range R, typename Pred>
    requires std::invocable<Pred, std::ranges::range_reference_t<R>>
auto filter_sum(R &&range, Pred pred)
{
    using T = std::remove_cvref_t<std::ranges::range_reference_t<R>>;
    T total{};

    for (auto &x : range)
    {
        if (pred(x))
        {
            total += x;
        }
    }

    return total;
}

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    std::cout << filter_sum(v, [](int x)
                            { return x % 2 == 0; })
              << '\n';
}
