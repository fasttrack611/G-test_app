#ifndef GPIO_TEST_UTILS_H  // Header guard start - prevents double inclusion
#define GPIO_TEST_UTILS_H  // Defines this unique identifier for the header

#include <zephyr/device.h>  // Include Zephyr's device model core API

/**
 * @brief Get a GPIO device controller by its device tree label
 * 
 * This function provides a standardized way to retrieve GPIO devices for testing.
 * 
 * @param label Device tree label of the GPIO controller (e.g., "GPIO_0")
 * @return Pointer to the GPIO device structure
 * 
 * Usage example:
 * @code
 * const struct device *gpio0 = get_gpio_device("GPIO_0");
 * if (!device_is_ready(gpio0)) {
 *     printk("Device not ready\n");
 * }
 * @endcode
 */
const struct device *get_gpio_device(const char *label);

#endif // GPIO_TEST_UTILS_H  // Header guard end
