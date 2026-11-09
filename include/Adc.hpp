#pragma once
#include "Peripheral.hpp"

class Adc : public InputPeripheral {
public:
    explicit Adc(uint8_t channel = 0) : channel_(channel & 7) {}
    void begin() override;
    uint16_t read() override; // 0..1023
private:
    uint8_t channel_;
};
