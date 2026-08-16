#include <concepts>
#include <iostream>
#include <type_traits>

template<typename T>
concept Im = std::is_integral_v<T>;
 

auto square(Im auto x) {
    return x * x;
}

template<typename V>
concept jiajia = requires(V a) {
    { ++a } -> std::same_as <V&>;
    { a++ } -> std::convertible_to<V>;
};

template<typename A>
concept Addable = requires(A a, A b) {
    { a + b } -> std::convertible_to<A>;
};

template<Addable A>
A add(A a, A b){
    return a + b;
}


int main() {
    std::cout << square(5) << '\n';   // 25
    std::cout << add(5, 4) << '\n';
    return 0;
}