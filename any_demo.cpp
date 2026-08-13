#include <any>
#include <iostream>
#include <string>
#include <typeinfo>

int main (){
    std::any a = 1;
    a = std::string("hello");
    
    try{
        std::cout << std::any_cast<std::string>(a) << "\n";
        std::cout << std::any_cast<int>(a) <<"\n";
    } catch(const std::bad_any_cast& e) {
        std::cerr <<"bad_any_cast" << e.what() << "\n";
    }

    if(a.type() == typeid(std::string)){
        std::cout << "is string\n";
    }
}