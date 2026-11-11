#pragma once
#include <avr/io.h>
#include <stdint.h>
#include "Peripheral.hpp"

namespace hal {

struct TwiConfig { uint32_t frequency = 100000; uint8_t localAddress = 0; };

/** Blocking TWI/I2C controller. */
class Twi final : public Peripheral {
public:
    explicit Twi(const TwiConfig& config);
    void init() override;
    void enable() override;
    void disable() override;
    bool start(uint8_t addressWithReadWriteBit);
    void stop();
    bool write(uint8_t value);
    uint8_t read(bool acknowledge);
private:
    TwiConfig config_;
};

} // namespace hal
