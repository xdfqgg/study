#include <iostream>
#include <optional>
#include <string>

std::optional<int> parse_int(const std::string& s){
    try{
        size_t idx = 0;
        long val = std::stol(s, &idx);
        if (idx != s.size()) return std::nullopt;
        return static_cast<int>(val); 
    }
    catch(...){
        return std::nullopt;
    }
}

int main(){
    std::string line;
    while (std::getline(std::cin, line)){
        auto v = parse_int(line);
        if(v)std::cout <<"parsed:"<< *v <<std::endl;
        else std::cout <<"invalid integer:"<< line <<std::endl;
    }

}