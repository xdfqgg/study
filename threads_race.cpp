#include <iostream>
#include <thread>
#include <vector>
#include <functional>

void inc_non_atomic(long long& counter, int increments){
    for (int i = 0; i < increments; ++i) ++counter;
}

int main(){
    const int N = 4;
    const int INC = 1000000;
    long long counter = 0;
    std::vector<std::thread> ths;
    for (int i = 0; i < N; i++)
    {
        ths.emplace_back(inc_non_atomic,std::ref(counter),INC);
    };
    for (auto& t : ths) t.join();   // 等所有线程干完
    std::cout << "counter = " << counter << " (expected " << (long long)N * INC << ")\n";
    return 0;
    
}