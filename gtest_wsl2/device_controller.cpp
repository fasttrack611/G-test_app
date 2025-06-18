#include "hardware_interface.h"

class DeviceController {
public:
    DeviceController(HardwareInterface* hw) : hardware(hw) {}
    
    bool setup() {
        if(!hardware->initialize()) return false;
        return hardware->get_device_id() == "DEV123";
    }
    
    int read_temperature() {
        return hardware->read_register(0x1000);
    }
    
    void set_led(bool on) {
        hardware->write_register(0x2000, on ? 1 : 0);
    }

private:
    HardwareInterface* hardware;
};
