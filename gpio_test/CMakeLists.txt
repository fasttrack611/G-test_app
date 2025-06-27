cmake_minimum_required(VERSION 3.20)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(gpio_test)

# Main application sources
target_sources(app PRIVATE
    src/main.c
    src/gpio_test_utils.c
)

# Add test sources directly
if (CONFIG_ZTEST)
    target_sources(app PRIVATE
        tests/test_gpio.c
    )
    
    # Manually set include directories
    target_include_directories(app PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${ZEPHYR_BASE}/tests/ztest/include
    )
    
    # Link ztest library
    zephyr_link_libraries_ifdef(CONFIG_ZTEST ztest)
endif()
