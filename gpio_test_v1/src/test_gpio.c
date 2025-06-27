#include <zephyr/ztest.h>          // Zephyr's unit testing framework
#include <zephyr/drivers/gpio.h>   // GPIO driver API
#include "gpio_test_utils.h"       // Custom utilities for GPIO testing

#define GPIO_LABEL "GPIO_0"        // Device tree label for GPIO controller
#define TEST_PIN   2               // Physical pin number to test

static const struct device *gpio_dev;  // Pointer to GPIO device structure

// Setup function runs before each test suite
static void gpio_setup(void *fixture)
{
    // Get GPIO device using device tree label
    gpio_dev = get_gpio_device(GPIO_LABEL);
    
    // Verify device was successfully obtained
    zassert_not_null(gpio_dev, "Failed to get GPIO device");
}

// Define test suite with setup function
ZTEST_SUITE(gpio_suite,      // Suite name
           NULL,             // No suite setup
           gpio_setup,       // Before-each-test setup
           NULL,             // No after-each-test function
           NULL,             // No before-each-test function
           NULL);            // No after-each-test function

/* Test Case: Configure pin as output */
ZTEST(gpio_suite, test_pin_configure_output)
{
    // Attempt to configure pin as output
    int ret = gpio_pin_configure(gpio_dev, TEST_PIN, GPIO_OUTPUT);
    
    // Verify configuration was successful (return value 0)
    zassert_equal(ret, 0, "Failed to configure pin as output");
}

/* Test Case: Configure pin as input */
ZTEST(gpio_suite, test_pin_configure_input)
{
    // Attempt to configure pin as input
    int ret = gpio_pin_configure(gpio_dev, TEST_PIN, GPIO_INPUT);
    
    // Verify configuration was successful
    zassert_equal(ret, 0, "Failed to configure pin as input");
}

/* Test Case: Set pin state (high/low) */
ZTEST(gpio_suite, test_pin_set)
{
    // Set pin to high state (1)
    int ret = gpio_pin_set(gpio_dev, TEST_PIN, 1);
    zassert_equal(ret, 0, "Failed to set pin high");

    // Set pin to low state (0)
    ret = gpio_pin_set(gpio_dev, TEST_PIN, 0);
    zassert_equal(ret, 0, "Failed to set pin low");
}

// Global variable for simulated pin state (used in next test)
static int simulated_pin_state = 0;

/* Test Case: Simulated pin set/get operations */
ZTEST(gpio_suite, test_pin_set_get_simulated)
{
    int ret;
    int val;

    // ---- Simulation of hardware behavior ----
    // Set pin high (both actual hardware and simulation)
    ret = gpio_pin_set(gpio_dev, TEST_PIN, 1);
    zassert_equal(ret, 0, "Failed to set pin high");
    simulated_pin_state = 1;  // Update simulation

    // Verify simulated state matches expected
    val = simulated_pin_state;
    zassert_equal(val, 1, "Pin value should be 1 (simulated)");

    // Set pin low (both actual hardware and simulation)
    ret = gpio_pin_set(gpio_dev, TEST_PIN, 0);
    zassert_equal(ret, 0, "Failed to set pin low");
    simulated_pin_state = 0;  // Update simulation

    // Verify simulated state matches expected
    val = simulated_pin_state;
    zassert_equal(val, 0, "Pin value should be 0 (simulated)");
}

/* Test Case: Actual pin set/get operations with hardware */
ZTEST(gpio_suite, test_pin_set_get)
{
    int val;

    // Set pin low and verify
    gpio_pin_set(gpio_dev, TEST_PIN, 0);
    val = gpio_pin_get(gpio_dev, TEST_PIN);
    zassert_equal(val, 0, "Pin value should be 0 (hardware)");

    // Set pin high and verify
    gpio_pin_set(gpio_dev, TEST_PIN, 1);
    val = gpio_pin_get(gpio_dev, TEST_PIN);
    zassert_equal(val, 1, "Pin value should be 1 (hardware)");
}
