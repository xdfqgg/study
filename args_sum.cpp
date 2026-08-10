#include <iostream>
#include <string>

int main(int argc, char **argv){
    int sum = 0;
    for (int i = 1; i < argc; i++) {
        sum += std::stoi(argv[i]);
    }
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}