cmake_minimum_required(VERSION 3.21)
project(Day19PackageRelease VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_library(day19lib STATIC src/message.cpp)
target_include_directories(day19lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(day19lib PUBLIC fmt::fmt spdlog::spdlog)
target_compile_features(day19lib PUBLIC cxx_std_20)

add_executable(day19_demo src/main.cpp)
target_link_libraries(day19_demo PRIVATE day19lib)

enable_testing()
add_executable(day19_tests tests/test_message.cpp)
target_link_libraries(day19_tests PRIVATE day19lib)
add_test(NAME unit_test COMMAND day19_tests)
add_test(NAME smoke_test COMMAND day19_demo Alice)

include(GNUInstallDirs)
install(TARGETS day19lib day19_demo
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(CPACK_PACKAGE_NAME "day19-package-release")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP")
include(CPack)
