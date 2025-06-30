// Include Zephyr's device model header.
// This provides access to core device structures and functions like device_get_binding().
#include <zephyr/device.h>

// Include the GPIO driver API definitions.
// Needed when working with GPIO devices retrieved via device_get_binding().
#include <zephyr/drivers/gpio.h>

/*
 * Function: get_gpio_device
 * -------------------------
 * Takes a string 'label' representing the device label defined in the devicetree
 * and returns a pointer to the corresponding 'device' structure.
 *
 * This device structure can then be used with GPIO API functions such as
 * gpio_pin_configure(), gpio_pin_set(), etc.
 *
 * Parameters:
 *  - label: Name of the GPIO device, e.g., "GPIOA" or "GPIO_0", as defined in devicetree.
 *
 * Returns:
 *  - Pointer to the device structure if the label is valid and the device is found.
 *  - NULL if no matching device was found.
 */
const struct device *get_gpio_device(const char *label) {
    return device_get_binding(label);
}
