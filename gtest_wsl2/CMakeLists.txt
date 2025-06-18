cmake_minimum_required(VERSION 3.10)
project(GMockWSL2Test)

# Find GoogleTest and GMock
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Create test executable
add_executable(hw_tests
    test_device_controller.cpp
)

# Link libraries
target_link_libraries(hw_tests
    GTest::gtest_main
    GTest::gmock
    pthread
)
