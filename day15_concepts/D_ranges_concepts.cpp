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
    std::vector<std::string> v{"a", "bb", "ccc", "d"};
    std::cout << filter_sum(v, [](auto x)
                            { return x.size() > 1;  })
              << '\n';
}
