add_library(I2CDevice STATIC
    I2CDevice.cpp
)

target_include_directories(I2CDevice PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

