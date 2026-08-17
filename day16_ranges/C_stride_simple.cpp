#include <iostream>
#include <vector>

template <typename R>
auto stride_view(R &r, std::size_t step)
{
    struct Wrapper
    {
        R &ref;
        std::size_t step;

        struct Iterator
        {
            R *ref;
            std::size_t index;
            std::size_t end_index;
            std::size_t step;

            using value_type = typename R::value_type;

            value_type operator*() const
            {
                return (*ref)[index];
            }

            Iterator &operator++()
            {
                index += step;
                return *this;
            }

            bool operator!=(const Iterator &other) const
            {
                return index < end_index;
            }
        };

        Iterator begin()
        {
            return {&ref, 0, ref.size(), step};
        }

        Iterator end()
        {
            return {&ref, ref.size(), ref.size(), step};
        }
    };

    return Wrapper{r, step};
}

int main()
{
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int x : stride_view(v, 3))
    {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    return 0;
}
