#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

const struct device *get_gpio_device(const char *label) {
    return device_get_binding(label);
}

