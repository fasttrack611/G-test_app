# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.14)

# Define the name of the project
project(GMockTurtleExample)

# Specify that we want to use C++17 features
set(CMAKE_CXX_STANDARD 17)

# Add an include directory for header files
# This lets the compiler find files under 'include/' using #include "..."
include_directories(include)

# Define a static or shared library named 'Painter' built from painter.cpp
# This is the code you want to test (e.g., the class that uses Turtle)
add_library(Painter src/painter.cpp)

# Recursively process the 'tests' directory
# This assumes there’s another CMakeLists.txt in 'tests/' to define test executables
add_subdirectory(tests)

