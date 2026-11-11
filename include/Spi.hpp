#pragma once
#include <avr/io.h>
#include <stdint.h>
#include "Peripheral.hpp"

namespace hal {

struct SpiConfig {
    bool master = true;
    uint8_t mode = 0;
    uint8_t clockDivider = 16;
    bool leastSignificantBitFirst = false;
};

/** Blocking full-duplex SPI driver. Chip-select remains application controlled. */
class Spi final : public Peripheral {
public:
    explicit Spi(const SpiConfig& config);
    void init() override;
    void enable() override;
    void disable() override;
    uint8_t transfer(uint8_t value);
private:
    SpiConfig config_;
};

} // namespace hal
