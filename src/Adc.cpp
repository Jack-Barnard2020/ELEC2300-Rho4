#include "Adc.hpp"

namespace hal {

Adc::Adc(const AdcConfig& config) : config_(config) {}

void Adc::init() {
    uint8_t reference = 0;

    if (config_.reference == AdcReference::Avcc) reference = _BV(REFS0);
    else if (config_.reference == AdcReference::Internal1V1) reference = _BV(REFS1) | _BV(REFS0);

    config_.channel &= 0x07;
    ADMUX = reference | (config_.leftAdjust ? _BV(ADLAR) : 0) | config_.channel;
    DIDR0 |= _BV(config_.channel);
    ADCSRA = _BV(ADEN) | static_cast<uint8_t>(config_.prescaler);
}

void Adc::enable() { ADCSRA |= _BV(ADEN); }
void Adc::disable() { ADCSRA &= static_cast<uint8_t>(~_BV(ADEN)); }

void Adc::selectChannel(uint8_t channel) {
    config_.channel = channel & 0x07;
    ADMUX = (ADMUX & 0xF0) | config_.channel;
    DIDR0 |= _BV(config_.channel);
}

uint16_t Adc::read() {
    ADCSRA |= _BV(ADSC);
    while (ADCSRA & _BV(ADSC)) {}
    return ADC;
}

} // namespace hal
