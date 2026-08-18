cmake_minimum_required(VERSION 3.16)
project(Day17Demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.10
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_library(mylib STATIC src/mylib.cpp)
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_features(mylib PUBLIC cxx_std_20)

add_executable(demo src/main.cpp)
target_link_libraries(demo PRIVATE mylib)

add_executable(tests tests/test_main.cpp)
target_link_libraries(tests PRIVATE mylib Catch2::Catch2)
add_test(NAME unit_tests COMMAND tests)
