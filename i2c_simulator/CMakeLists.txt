cmake_minimum_required(VERSION 3.10)
project(I2CSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
include_directories(${PROJECT_SOURCE_DIR}/include)
# Add source and test directories
add_subdirectory(src)
add_subdirectory(test)

