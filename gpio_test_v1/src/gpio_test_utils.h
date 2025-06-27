#ifndef GPIO_TEST_UTILS_H
#define GPIO_TEST_UTILS_H

#include <zephyr/device.h>

const struct device *get_gpio_device(const char *label);

#endif // GPIO_TEST_UTILS_H

