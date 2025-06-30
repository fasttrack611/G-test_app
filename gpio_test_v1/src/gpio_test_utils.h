#ifndef GPIO_TEST_UTILS_H
#define GPIO_TEST_UTILS_H

// Include the Zephyr device API header for working with struct device and device binding functions
#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Retrieve a GPIO device pointer using a device label.
 *
 * This utility function looks up a GPIO device from the Zephyr device tree
 * based on the string label provided. It wraps the DEVICE_DT_GET binding logic.
 *
 * Example usage:
 *   const struct device *gpio_dev = get_gpio_device("GPIO_0");
 *
 * @param label The devicetree label (e.g., "GPIO_0", "GPIOA", etc.)
 * @return const struct device* Pointer to device structure, or NULL if not found.
 */
const struct device *get_gpio_device(const char *label);

#ifdef __cplusplus
}
#endif

#endif // GPIO_TEST_UTILS_H
