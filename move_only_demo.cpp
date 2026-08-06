#include <iostream>
#include <vector>

struct MoveOnly {
    int id;
    MoveOnly(int id_) : id(id_){}
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;
    MoveOnly(MoveOnly&& other) noexcept : id(other.id){
        other.id = -1; // 转移所有权
        std::cout <<"move(构造)"<<std::endl;
    }
    MoveOnly& operator=(MoveOnly&& other) noexcept {
        if(this != &other){
            id = other.id;
            other.id = -1; // 转移所有权
            std::cout <<"move(赋值)"<<std::endl;
        }
        return *this;
    }

};
int main() {
    std::vector<MoveOnly> v;
    v.reserve(3);                 // 先预留 3 个位置
    v.emplace_back(1);            // 容器内直接构造，无移动
    MoveOnly m2(2);
    v.push_back(std::move(m2));   // 必须 move（不能拷贝）
    MoveOnly m3(3);
    v.push_back(std::move(m3));

    for (auto& e : v) std::cout << e.id << ' ';
    std::cout << "\n";
    return 0;
}