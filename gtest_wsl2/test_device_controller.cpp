#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "device_controller.cpp"
#include "mock_hardware.h"

using ::testing::Return;
using ::testing::_;

TEST(DeviceControllerTest, SetupSucceedsWithValidDevice) {
    MockHardware mock_hw;
    DeviceController controller(&mock_hw);
    
    // Setup expectations
    EXPECT_CALL(mock_hw, initialize()).WillOnce(Return(true));
    EXPECT_CALL(mock_hw, get_device_id()).WillOnce(Return("DEV123"));
    
    ASSERT_TRUE(controller.setup());
}

TEST(DeviceControllerTest, TemperatureReadsCorrectly) {
    MockHardware mock_hw;
    DeviceController controller(&mock_hw);
    
    EXPECT_CALL(mock_hw, read_register(0x1000))
        .WillOnce(Return(25));  // Simulate 25°C reading
    
    EXPECT_EQ(controller.read_temperature(), 25);
}

TEST(DeviceControllerTest, LedTurnsOn) {
    MockHardware mock_hw;
    DeviceController controller(&mock_hw);
    
    // Expect write to register 0x2000 with value 1
    EXPECT_CALL(mock_hw, write_register(0x2000, 1)).Times(1);
    
    controller.set_led(true);
}
