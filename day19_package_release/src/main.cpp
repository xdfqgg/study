#include "message.hpp"

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    const std::string name = argc >= 2 ? argv[1] : "world";
    std::cout << make_message(name) << '\n';
    return 0;
}
