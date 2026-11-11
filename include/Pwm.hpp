#pragma once
#include <avr/io.h>
#include <stdint.h>
#include "Peripheral.hpp"

namespace hal {

enum class PwmOutput : uint8_t { OC0A, OC0B, OC1A, OC1B, OC2A, OC2B };
enum class PwmMode : uint8_t { Fast, PhaseCorrect };

struct PwmConfig {
    PwmOutput output = PwmOutput::OC0A;
    PwmMode mode = PwmMode::Fast;
    uint16_t prescaler = 64;
    bool inverted = false;
};

/** Register-level PWM driver for all six Il Matto PWM outputs. */
class Pwm final : public Peripheral {
public:
    explicit Pwm(const PwmConfig& config);
    void init() override;
    void enable() override;
    void disable() override;
    void write(uint16_t duty);
private:
    uint8_t clockBits() const;
    PwmConfig config_;
};

} // namespace hal
