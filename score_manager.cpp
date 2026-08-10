#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    int score;
};

int main(){
    std::vector<Student> v ;
    std::string name;
    int score;
    while (std::cin >> name >> score) {
        v.push_back({name, score}); 
    }
    std::sort(v.begin(), v.end(), [](const Student &a, const Student &b) {
        return a.score > b.score; // 按分数降序排序
    });
    for (const auto &s : v) {
        std::cout << s.name << ": " << s.score << std::endl;
    }
    double average = 0;
    for (const auto &s : v) {
        average += s.score;
    }
    if (v.empty()){
        return 0;
    }
    average /= v.size();
    std::cout << "平均分: " << average << std::endl;
}