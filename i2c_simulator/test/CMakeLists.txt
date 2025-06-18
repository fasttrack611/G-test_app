# Use FetchContent to download GoogleTest (includes GMock)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test executable
add_executable(I2CDeviceTest
    I2CDeviceTest.cpp
)

# Link to GTest/GMock and your library
target_link_libraries(I2CDeviceTest
    GTest::gmock_main
    I2CDevice
    pthread
)

include(GoogleTest)
gtest_discover_tests(I2CDeviceTest)

