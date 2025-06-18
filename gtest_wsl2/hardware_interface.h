#pragma once

class HardwareInterface {
public:
    virtual ~HardwareInterface() = default;
    
    virtual bool initialize() = 0;
    virtual int read_register(uint32_t address) = 0;
    virtual void write_register(uint32_t address, int value) = 0;
    virtual std::string get_device_id() = 0;
};
