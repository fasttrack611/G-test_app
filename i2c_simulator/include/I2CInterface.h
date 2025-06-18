#pragma once
#include <cstdint>
#include <vector>

class I2CInterface {
public:
    virtual ~I2CInterface() = default;
    virtual bool write(uint8_t deviceAddr, const std::vector<uint8_t>& data) = 0;
    virtual bool read(uint8_t deviceAddr, std::vector<uint8_t>& data, size_t length) = 0;
};

