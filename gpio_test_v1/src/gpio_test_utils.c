#include <zephyr/device.h>       // Zephyr device model core APIs
#include <zephyr/drivers/gpio.h> // GPIO driver specific APIs

/**
 * @brief Get a GPIO device by its device tree label
 * 
 * This function retrieves a pointer to a GPIO device controller using Zephyr's
 * device binding mechanism. The device must be defined in the device tree with
 * the specified label.
 * 
 * @param label The device tree label of the GPIO controller (e.g., "GPIO_0")
 * @return Pointer to the GPIO device structure
 * @retval NULL if the device could not be found or is not ready
 * 
 * @note This function does not check if the device is ready - that should be
 *       done by the caller using device_is_ready()
 */
const struct device *get_gpio_device(const char *label) {
    // Use Zephyr's device binding mechanism to get the device pointer
    // device_get_binding() searches for a device with the given label
    return device_get_binding(label);
}
