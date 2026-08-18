#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "mylib.hpp"

TEST_CASE("greet returns greeting", "[greet]")
{
    REQUIRE(greet("Alice") == "Hello, Alice!");
}
