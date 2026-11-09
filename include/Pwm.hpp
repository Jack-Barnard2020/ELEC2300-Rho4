#pragma once
#include "Peripheral.hpp"

class Pwm : public OutputPeripheral {
public:
    void begin() override;
    void write(uint16_t duty) override; // 0..255
};
