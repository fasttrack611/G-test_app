#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/__assert.h>

const struct device *get_gpio_device(const char *label)
{
    const struct device *dev = device_get_binding(label);
    __ASSERT(dev != NULL, "GPIO device not found");
    return dev;
}

int configure_gpio(const struct device *dev, gpio_pin_t pin, 
                   gpio_flags_t flags)
{
    return gpio_pin_configure(dev, pin, flags);
}

int set_gpio(const struct device *dev, gpio_pin_t pin, int value)
{
    return gpio_pin_set(dev, pin, value);
}

int get_gpio(const struct device *dev, gpio_pin_t pin)
{
    return gpio_pin_get(dev, pin);
}
