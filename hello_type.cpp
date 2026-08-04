#include <iostream>
#include <string>

int main () 
{
    std::cout <<"Enter your name: ";
    std::string name;
    if(!std::getline(std::cin,name)) return 0;

    std::cout << "Enter your age (or blank): ";
    std::string age_line;
    std::getline(std::cin, age_line);
    
    int age = -1;
    if(!age_line.empty()) {
        age = std::stoi(age_line);
    }
    auto x = 42;
    auto s = name;
    if (age >= 18)
        std::cout << "Hello, " << name << "! You are an adult.\n";
    else
        std::cout << "Hello, " << name << "! You are a minor.\n";
    return 0;
}