cmake_minimum_required(VERSION 3.14)
project(ct15-bst-remove)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Main executable
add_executable(ct15-bst-remove
    src/main.cpp
    src/BinarySearchTree.cpp
)
target_include_directories(ct15-bst-remove PRIVATE include)

# Test executable
add_executable(ct15_tests
    tests/ct15_test.cpp
    src/BinarySearchTree.cpp
)
target_include_directories(ct15_tests PRIVATE include)
target_link_libraries(ct15_tests gtest gtest_main)

enable_testing()
add_test(NAME ct15_tests COMMAND ct15_tests)
