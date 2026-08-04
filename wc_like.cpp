#include <iostream>
#include <string>
#include <sstream>

void count_stream(std::istream& in,long long &lines,long long &words,long long &chars){
    lines = words = chars = 0;
    std::string line;
    while(std::getline(in,line)){
        lines++;
        chars += line.size() + 1; // +1 for newline
        std::istringstream iss(line);
        std::string word;
        while(iss >> word){
            words++;
        }
    }
}
int main() {
    long long lines, words, chars;
    count_stream(std::cin, lines, words, chars);
    std::cout << "Lines: " << lines << ", Words: " << words << ", Chars: " << chars << std::endl;
    return 0;
}