#include <gtest/gtest.h>
#include "MockI2C.h"
#include "../src/I2CDevice.cpp"  // Include implementation

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgReferee;

TEST(I2CDeviceTest, WriteConfigSuccess) {
    MockI2C mockBus;
    I2CDevice device(&mockBus, 0x50);

    std::vector<uint8_t> expectedData = {0x01, 0xAB};
    EXPECT_CALL(mockBus, write(0x50, expectedData))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_TRUE(device.writeConfig(0xAB));
}

TEST(I2CDeviceTest, ReadStatusSuccess) {
    MockI2C mockBus;
    I2CDevice device(&mockBus, 0x50);

    std::vector<uint8_t> dummy = {0x42};
    EXPECT_CALL(mockBus, read(0x50, _, 1))
        .WillOnce(DoAll(SetArgReferee<1>(dummy), Return(true)));

    EXPECT_EQ(device.readStatus(), 0x42);
}

