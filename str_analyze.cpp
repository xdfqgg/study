#include <iostream>
#include <string>
#include<cctype>

int main(){
    std::string line;
    std::getline(std::cin, line);
    if(line.empty()) {
        std::cout << "No input provided." << std::endl;
        return 0;
    }
    int words = 0;
    int numbers = 0;
    int blocks = 0;
    int others = 0;
    for (char c : line) {
        if (std::isspace(c)) {
            blocks++;
        } else if (std::isalpha(c)) {
            words++;
        } else if (std::isdigit(c)) {
            numbers++;
        } else {
            others++;
        }
    }
    std::cout << "Words: " << words << ", Numbers: " << numbers << ", Blocks: " << blocks << ", Others: " << others << std::endl;
}