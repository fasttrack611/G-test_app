#pragma once
#include "hardware_interface.h"
#include <gmock/gmock.h>

class MockHardware : public HardwareInterface {
public:
    MOCK_METHOD(bool, initialize, (), (override));
    MOCK_METHOD(int, read_register, (uint32_t address), (override));
    MOCK_METHOD(void, write_register, (uint32_t address, int value), (override));
    MOCK_METHOD(std::string, get_device_id, (), (override));
};
