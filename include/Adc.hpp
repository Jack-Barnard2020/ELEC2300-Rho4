#pragma once
#include <avr/io.h>
#include <stdint.h>
#include "Peripheral.hpp"

namespace hal {

enum class AdcReference : uint8_t { Aref, Avcc, Internal1V1 };
enum class AdcPrescaler : uint8_t { DivideBy2=1, DivideBy4, DivideBy8, DivideBy16, DivideBy32, DivideBy64, DivideBy128 };

struct AdcConfig {
    uint8_t channel = 0;
    AdcReference reference = AdcReference::Avcc;
    AdcPrescaler prescaler = AdcPrescaler::DivideBy128;
    bool leftAdjust = false;
};

/** Register-level 10-bit ADC driver for ADC0 through ADC7. */
class Adc final : public Peripheral {
public:
    explicit Adc(const AdcConfig& config);
    void init() override;
    void enable() override;
    void disable() override;
    void selectChannel(uint8_t channel);
    uint16_t read();
private:
    AdcConfig config_;
};

} // namespace hal
