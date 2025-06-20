# Tell CMake to locate the installed GoogleTest framework (which includes gMock too)
# REQUIRED means configuration will fail if GTest is not found
find_package(GTest REQUIRED)

# Include CMake module to use GoogleTest's helper macros like gtest_discover_tests
include(GoogleTest)

# Define a test executable called 'PainterTests'
# It compiles two files: the test implementation and the mock header
# - 'painter_test.cpp' contains the test logic
# - 'mock_turtle.h' defines the mocked Turtle class used in testing
add_executable(PainterTests
  painter_test.cpp
  mock_turtle.h
)

# Link the test executable with the required libraries:
# - GTest::gtest_main: provides a main() for test discovery
# - GTest::gmock: enables mocking features
# - Painter: the library under test (defined in your main CMakeLists.txt)
target_link_libraries(PainterTests
  GTest::gtest_main
  GTest::gmock
  Painter
)

# Automatically discover and register tests inside 'PainterTests' using GoogleTest
# This lets CTest know what tests exist without manually listing them
gtest_discover_tests(PainterTests)

