#include <ztest.h>
#include <zephyr/drivers/gpio.h>
#include "gpio_test_utils.h"

#define GPIO0_LABEL "GPIO_0"
#define GPIO1_LABEL "GPIO_1"
#define TEST_PIN_0  5
#define TEST_PIN_1  7
#define INVALID_PIN 255  // Max value for uint8_t

static const struct device *gpio0;
static const struct device *gpio1;

/* Setup before each test */
static void gpio_setup(void *fixture)
{
    ARG_UNUSED(fixture);
    gpio0 = get_gpio_device(GPIO0_LABEL);
    gpio1 = get_gpio_device(GPIO1_LABEL);
}

/* Callback function for interrupts */
static volatile int interrupt_count;
static void callback_fn(const struct device *dev, 
                       struct gpio_callback *gpio_cb, 
                       uint32_t pins)
{
    interrupt_count++;
}

/* Test GPIO configuration */
ZTEST(gpio_tests, test_gpio_configuration)
{
    int ret;
    
    /* Test valid configurations */
    ret = configure_gpio(gpio0, TEST_PIN_0, GPIO_OUTPUT);
    zassert_equal(ret, 0, "Output config failed");
    
    ret = configure_gpio(gpio0, TEST_PIN_1, GPIO_INPUT);
    zassert_equal(ret, 0, "Input config failed");
    
    /* Test invalid configurations */
    ret = configure_gpio(NULL, TEST_PIN_0, GPIO_INPUT);
    zassert_not_equal(ret, 0, "NULL device should fail");
    
    ret = configure_gpio(gpio0, INVALID_PIN, GPIO_OUTPUT);
    zassert_not_equal(ret, 0, "Invalid pin should fail");
}

/* Test GPIO output operations */
ZTEST(gpio_tests, test_gpio_output)
{
    configure_gpio(gpio0, TEST_PIN_0, GPIO_OUTPUT);
    
    /* Test set high */
    set_gpio(gpio0, TEST_PIN_0, 1);
    zassert_equal(get_gpio(gpio0, TEST_PIN_0), 1, "Set high failed");
    
    /* Test set low */
    set_gpio(gpio0, TEST_PIN_0, 0);
    zassert_equal(get_gpio(gpio0, TEST_PIN_0), 0, "Set low failed");
    
    /* Test toggle */
    set_gpio(gpio0, TEST_PIN_0, 1);
    int initial = get_gpio(gpio0, TEST_PIN_0);
    set_gpio(gpio0, TEST_PIN_0, !initial);
    zassert_not_equal(get_gpio(gpio0, TEST_PIN_0), initial, 
                     "Toggle failed");
}

/* Test GPIO input operations */
ZTEST(gpio_tests, test_gpio_input)
{
    configure_gpio(gpio0, TEST_PIN_0, GPIO_OUTPUT);
    configure_gpio(gpio1, TEST_PIN_1, GPIO_INPUT);
    
    /* Test input reading */
    set_gpio(gpio0, TEST_PIN_0, 1);
    zassert_equal(get_gpio(gpio1, TEST_PIN_1), 1, "Read high failed");
    
    set_gpio(gpio0, TEST_PIN_0, 0);
    zassert_equal(get_gpio(gpio1, TEST_PIN_1), 0, "Read low failed");
}

/* Test GPIO interrupts */
ZTEST(gpio_tests, test_gpio_interrupts)
{
    static struct gpio_callback cb;
    interrupt_count = 0;
    
    configure_gpio(gpio0, TEST_PIN_0, GPIO_OUTPUT);
    configure_gpio(gpio1, TEST_PIN_1, GPIO_INPUT | GPIO_INT_EDGE_RISING);
    
    // Initialize callback
    gpio_init_callback(&cb, callback_fn, BIT(TEST_PIN_1));
    
    gpio_add_callback(gpio1, &cb);
    gpio_pin_interrupt_configure(gpio1, TEST_PIN_1, GPIO_INT_EDGE_RISING);
    
    /* Trigger interrupt */
    set_gpio(gpio0, TEST_PIN_0, 1);
    k_sleep(K_MSEC(10));
    
    zassert_equal(interrupt_count, 1, "Interrupt not triggered");
    
    /* Test disable interrupt */
    gpio_pin_interrupt_configure(gpio1, TEST_PIN_1, GPIO_INT_DISABLE);
    set_gpio(gpio0, TEST_PIN_0, 0);
    set_gpio(gpio0, TEST_PIN_0, 1);
    k_sleep(K_MSEC(10));
    
    zassert_equal(interrupt_count, 1, "Interrupt not disabled");
}

/* Test suite registration */
ZTEST_SUITE(gpio_tests, NULL, NULL, gpio_setup, NULL, NULL);
