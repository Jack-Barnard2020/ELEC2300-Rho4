#pragma once
#include <avr/io.h>
#include <stdint.h>
#include "Peripheral.hpp"

namespace hal {

enum class PinMode : uint8_t { Input, InputPullup, Output };

/** Addresses and settings needed to control one GPIO pin. */
struct GpioConfig {
    volatile uint8_t* ddr;
    volatile uint8_t* port;
    volatile uint8_t* pin;
    uint8_t bit;
    PinMode mode;
};

/** Register-level GPIO input/output driver. */
class Gpio final : public Peripheral {
public:
    explicit Gpio(const GpioConfig& config);
    void init() override;
    void enable() override;
    void disable() override;
    void write(bool high);
    bool read() const;
    void toggle();
private:
    GpioConfig config_;
};

} // namespace hal
