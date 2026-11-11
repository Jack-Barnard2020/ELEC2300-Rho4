#include "Gpio.hpp"

namespace hal {

Gpio::Gpio(const GpioConfig& config) : config_(config) {}

void Gpio::init() {
    const uint8_t mask = _BV(config_.bit);

    if (config_.mode == PinMode::Output) {
        *config_.ddr |= mask;
        *config_.port &= static_cast<uint8_t>(~mask);
        return;
    }

    *config_.ddr &= static_cast<uint8_t>(~mask);

    if (config_.mode == PinMode::InputPullup) {
        *config_.port |= mask;
    } else {
        *config_.port &= static_cast<uint8_t>(~mask);
    }
}

void Gpio::enable() { init(); }

void Gpio::disable() {
    const uint8_t mask = _BV(config_.bit);
    *config_.ddr &= static_cast<uint8_t>(~mask);
    *config_.port &= static_cast<uint8_t>(~mask);
}

void Gpio::write(bool high) {
    const uint8_t mask = _BV(config_.bit);

    if (high) *config_.port |= mask;
    else *config_.port &= static_cast<uint8_t>(~mask);
}

bool Gpio::read() const { return (*config_.pin & _BV(config_.bit)) != 0; }
void Gpio::toggle() { *config_.port ^= _BV(config_.bit); }

} // namespace hal
