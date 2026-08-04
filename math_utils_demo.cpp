#include <iostream>
#include <vector>

int add(int a,int b){
    return a + b;
}

void swap_values(int &a,int &b){
    int temp = a;
    a = b;
    b = temp;
}

double average(const std::vector<int> &v,bool exclude_negatives =false){
    long long sum = 0;
    int cnt = 0;
    for(int x:v){
        if(exclude_negatives && x < 0) continue;
        sum += x;
        cnt++;
    }
    return cnt ? static_cast<double>(sum) / cnt : 0.0;
}
int main() {
    int a = 3, b = 7;
    swap_values(a, b);                       // 引用交换

    std::vector<int> v{1, -2, 3, 4};
    double avg = average(v, true);           // 排除负数求平均
    // 也可以 average(v) —— 默认 exclude_negatives = false

    std::cout << "a=" << a << " b=" << b << " avg=" << avg << "\n";
    return 0;
}