cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(gpio_test)

target_sources(app PRIVATE src/test_gpio.c src/gpio_test_utils.c)

