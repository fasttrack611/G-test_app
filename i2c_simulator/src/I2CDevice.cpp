#include "I2CInterface.h"
#include <iostream>

class I2CDevice {
public:
    I2CDevice(I2CInterface* bus, uint8_t addr) : i2c(bus), address(addr) {}

    bool writeConfig(uint8_t configValue) {
        std::vector<uint8_t> data = {0x01, configValue}; // Register 0x01
        return i2c->write(address, data);
    }

    uint8_t readStatus() {
        std::vector<uint8_t> data;
        if (!i2c->read(address, data, 1)) {
            return 0xFF;  // Indicate error
        }
        return data[0];
    }

private:
    I2CInterface* i2c;
    uint8_t address;
};

