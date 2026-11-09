#pragma once
#include "Peripheral.hpp"

class Serial : public InputPeripheral, public OutputPeripheral {
public:
    explicit Serial(uint32_t baud = 9600) : baud_(baud) {}
    void begin() override;
    uint16_t read() override;
    void write(uint16_t value) override;
    bool available() const;
private:
    uint32_t baud_;
};
