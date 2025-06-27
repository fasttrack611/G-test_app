#ifndef GPIO_TEST_UTILS_H
#define GPIO_TEST_UTILS_H

#include <zephyr/drivers/gpio.h>

const struct device *get_gpio_device(const char *label);
int configure_gpio(const struct device *dev, gpio_pin_t pin, gpio_flags_t flags);
int set_gpio(const struct device *dev, gpio_pin_t pin, int value);
int get_gpio(const struct device *dev, gpio_pin_t pin);

#endif /* GPIO_TEST_UTILS_H */
