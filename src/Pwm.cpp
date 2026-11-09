#include "Pwm.hpp"
#include "Registers.hpp"

void Pwm::begin() {
    reg::DDRB |= (1 << 3);                 // PB3 is OC0A
    reg::TCCR0A = (1 << 7) | (1 << 1) | 1; // Non-inverting fast PWM
    reg::TCCR0B = 1;                       // No prescaler
}

void Pwm::write(uint16_t duty) {
    reg::OCR0A = duty > 255 ? 255 : uint8_t(duty);
}
