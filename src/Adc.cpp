#include "Adc.hpp"
#include "Registers.hpp"

void Adc::begin() {
    reg::DDRA &= ~(1 << channel_);          // Analogue pin is an input
    reg::ADMUX = (1 << 6) | channel_;       // AVCC reference, selected channel
    reg::ADCSRA = (1 << 7) | 7;             // ADC on, clock /128
}

uint16_t Adc::read() {
    reg::ADMUX = (reg::ADMUX & 0xF8) | channel_;
    reg::ADCSRA |= (1 << 6);                // Start conversion
#ifndef HAL_TEST
    while (reg::ADCSRA & (1 << 6)) {}
#endif
    const uint8_t low = reg::ADCL;           // Low byte must be read first
    return low | (uint16_t(reg::ADCH) << 8);
}
