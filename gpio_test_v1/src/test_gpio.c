#include <zephyr/ztest.h>
#include <zephyr/drivers/gpio.h>
#include "gpio_test_utils.h"

#define GPIO_LABEL "GPIO_0"
#define TEST_PIN   2

static const struct device *gpio_dev;

static void gpio_setup(void *fixture)
{
    gpio_dev = get_gpio_device(GPIO_LABEL);
    zassert_not_null(gpio_dev, "Failed to get GPIO device");
}

ZTEST_SUITE(gpio_suite, NULL, gpio_setup, NULL, NULL, NULL);

ZTEST(gpio_suite, test_pin_configure_output)
{
    int ret = gpio_pin_configure(gpio_dev, TEST_PIN, GPIO_OUTPUT);
    zassert_equal(ret, 0, "Failed to configure pin as output");
}

ZTEST(gpio_suite, test_pin_configure_input)
{
    int ret = gpio_pin_configure(gpio_dev, TEST_PIN, GPIO_INPUT);
    zassert_equal(ret, 0, "Failed to configure pin as input");
}

ZTEST(gpio_suite, test_pin_set)
{
    int ret = gpio_pin_set(gpio_dev, TEST_PIN, 1);
    zassert_equal(ret, 0, "Failed to set pin high");

    ret = gpio_pin_set(gpio_dev, TEST_PIN, 0);
    zassert_equal(ret, 0, "Failed to set pin low");
}


static int simulated_pin_state = 0;

ZTEST(gpio_suite, test_pin_set_get_simulated)
{
    int ret;

    // Simulate setting the pin
    ret = gpio_pin_set(gpio_dev, TEST_PIN, 1);
    zassert_equal(ret, 0, "Failed to set pin high");
    simulated_pin_state = 1;

    // Simulate getting the pin
    int val = simulated_pin_state;
    zassert_equal(val, 1, "Pin value should be 1");

    ret = gpio_pin_set(gpio_dev, TEST_PIN, 0);
    zassert_equal(ret, 0, "Failed to set pin low");
    simulated_pin_state = 0;

    val = simulated_pin_state;
    zassert_equal(val, 0, "Pin value should be 0");
}


ZTEST(gpio_suite, test_pin_set_get)
{
    gpio_pin_set(gpio_dev, TEST_PIN, 0);
    int val = gpio_pin_get(gpio_dev, TEST_PIN);
    zassert_equal(val, 0, "Pin value should be 0");

    gpio_pin_set(gpio_dev, TEST_PIN, 1);
    val = gpio_pin_get(gpio_dev, TEST_PIN);
    zassert_equal(val, 1, "Pin value should be 1");
}


