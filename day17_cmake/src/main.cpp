#include "mylib.hpp"

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    std::string name = (argc >= 2) ? argv[1] : "world";
    std::cout << greet(name) << std::endl;
    return 0;
}
