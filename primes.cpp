#include <iostream>
#include <vector>

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int a;
    if(!(std::cin >> a)) return 0;

    std::vector<int> primes;
    for (int i = 1; i <= a; ++i) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }

    for (int p : primes) {
        std::cout << p << " ";
    }
    std::cout <<"\ncount of primes: " << primes.size() << std::endl;
}