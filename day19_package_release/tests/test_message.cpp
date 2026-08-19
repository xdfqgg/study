#include "message.hpp"

#include <iostream>
#include <string>

int main()
{
    if (make_message("Alice") != "Hello, Alice!")
    {
        std::cerr << "make_message returned an unexpected value\n";
        return 1;
    }

    return 0;
}
