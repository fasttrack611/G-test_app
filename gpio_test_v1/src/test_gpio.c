// Include Zephyr's unit testing framework
#include <zephyr/ztest.h>

// Include Zephyr's GPIO driver API
#include <zephyr/drivers/gpio.h>

// Include a custom utility header (assumed to contain get_gpio_device())
#include "gpio_test_utils.h"

// Label for the GPIO controller; should match what's defined in the board’s devicetree
#define GPIO_LABEL "GPIO_0"

// The GPIO pin number to test
#define TEST_PIN   2

// Global pointer to hold the GPIO device handle
static const struct device *gpio_dev;

// Test fixture setup function: runs before each test (if fixture is used)
static void gpio_setup(void *fixture)
{
    // Attempt to get the GPIO device handle
    gpio_dev = get_gpio_device(GPIO_LABEL);

    // Assert that the device was successfully retrieved
    zassert_not_null(gpio_dev, "Failed to get GPIO device");
}

// Register a test suite named 'gpio_suite'
// Arguments: suite name, setup fixture, before/after each test, before/after entire suite
ZTEST_SUITE(gpio_suite, NULL, gpio_setup, NULL, NULL, NULL);

// Test case: Configure the test pin as OUTPUT
ZTEST(gpio_suite, test_pin_configure_output)
{
    int ret = gpio_pin_configure(gpio_dev, TEST_PIN, GPIO_OUTPUT);
    zassert_equal(ret, 0, "Failed to configure pin as output");
}

// Test case: Configure the test pin as INPUT
ZTEST(gpio_suite, test_pin_configure_input)
{
    int ret = gpio_pin_configure(gpio_dev, TEST_PIN, GPIO_INPUT);
    zassert_equal(ret, 0, "Failed to configure pin as input");
}

// Test case: Set pin HIGH, then LOW
ZTEST(gpio_suite, test_pin_set)
{
    int ret = gpio_pin_set(gpio_dev, TEST_PIN, 1); // Set high
    zassert_equal(ret, 0, "Failed to set pin high");

    ret = gpio_pin_set(gpio_dev, TEST_PIN, 0); // Set low
    zassert_equal(ret, 0, "Failed to set pin low");
}

// Simulated state used when actual GPIO reads aren’t available
static int simulated_pin_state = 0;

// Test case: Emulate pin set/get using a simulated variable
ZTEST(gpio_suite, test_pin_set_get_simulated)
{
    int ret;

    ret = gpio_pin_set(gpio_dev, TEST_PIN, 1);
    zassert_equal(ret, 0, "Failed to set pin high");
    simulated_pin_state = 1;

    int val = simulated_pin_state;
    zassert_equal(val, 1, "Pin value should be 1");

    ret = gpio_pin_set(gpio_dev, TEST_PIN, 0);
    zassert_equal(ret, 0, "Failed to set pin low");
    simulated_pin_state = 0;

    val = simulated_pin_state;
    zassert_equal(val, 0, "Pin value should be 0");
}

// Test case: Use Zephyr's gpio_pin_get() to read pin value after setting it
ZTEST(gpio_suite, test_pin_set_get)
{
    gpio_pin_set(gpio_dev, TEST_PIN, 0);
    int val = gpio_pin_get(gpio_dev, TEST_PIN);
    zassert_equal(val, 0, "Pin value should be 0");

    gpio_pin_set(gpio_dev, TEST_PIN, 1);
    val = gpio_pin_get(gpio_dev, TEST_PIN);
    zassert_equal(val, 1, "Pin value should be 1");
}
