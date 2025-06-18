#pragma once

#include <gmock/gmock.h>
#include "I2CInterface.h"

class MockI2C : public I2CInterface {
public:
    MOCK_METHOD(bool, write, (uint8_t deviceAddr, const std::vector<uint8_t>& data), (override));
    MOCK_METHOD(bool, read, (uint8_t deviceAddr, std::vector<uint8_t>& data, size_t length), (override));
};

