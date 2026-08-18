# CMake generated Testfile for 
# Source directory: F:/c++20study/day17_cmake
# Build directory: F:/c++20study/day17_cmake/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unit_tests "F:/c++20study/day17_cmake/build/tests.exe")
set_tests_properties(unit_tests PROPERTIES  _BACKTRACE_TRIPLES "F:/c++20study/day17_cmake/CMakeLists.txt;28;add_test;F:/c++20study/day17_cmake/CMakeLists.txt;0;")
subdirs("_deps/catch2-build")
