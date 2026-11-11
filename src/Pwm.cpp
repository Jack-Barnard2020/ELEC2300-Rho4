#include "Pwm.hpp"

namespace hal {

Pwm::Pwm(const PwmConfig& config) : config_(config) {}

uint8_t Pwm::clockBits() const {
    const bool timer2 = config_.output == PwmOutput::OC2A || config_.output == PwmOutput::OC2B;

    if (timer2) {
        switch (config_.prescaler) {
            case 1: return 1; case 8: return 2; case 32: return 3; case 64: return 4;
            case 128: return 5; case 256: return 6; default: return 7;
        }
    }

    switch (config_.prescaler) {
        case 1: return 1; case 8: return 2; case 64: return 3; case 256: return 4; default: return 5;
    }
}

void Pwm::init() {
    const uint8_t compare = config_.inverted ? 3 : 2;
    const uint8_t clock = clockBits();

    switch (config_.output) {
        case PwmOutput::OC0A:
            DDRB |= _BV(PB3);
            TCCR0A = (compare << COM0A0) | _BV(WGM00) | (config_.mode == PwmMode::Fast ? _BV(WGM01) : 0);
            TCCR0B = clock;
            break;
        case PwmOutput::OC0B:
            DDRB |= _BV(PB4);
            TCCR0A = (compare << COM0B0) | _BV(WGM00) | (config_.mode == PwmMode::Fast ? _BV(WGM01) : 0);
            TCCR0B = clock;
            break;
        case PwmOutput::OC1A:
            DDRD |= _BV(PD5);
            TCCR1A = (compare << COM1A0) | _BV(WGM10);
            TCCR1B = (config_.mode == PwmMode::Fast ? _BV(WGM12) : 0) | clock;
            break;
        case PwmOutput::OC1B:
            DDRD |= _BV(PD4);
            TCCR1A = (compare << COM1B0) | _BV(WGM10);
            TCCR1B = (config_.mode == PwmMode::Fast ? _BV(WGM12) : 0) | clock;
            break;
        case PwmOutput::OC2A:
            DDRD |= _BV(PD7);
            TCCR2A = (compare << COM2A0) | _BV(WGM20) | (config_.mode == PwmMode::Fast ? _BV(WGM21) : 0);
            TCCR2B = clock;
            break;
        case PwmOutput::OC2B:
            DDRD |= _BV(PD6);
            TCCR2A = (compare << COM2B0) | _BV(WGM20) | (config_.mode == PwmMode::Fast ? _BV(WGM21) : 0);
            TCCR2B = clock;
            break;
    }
}

void Pwm::enable() { init(); }

void Pwm::disable() {
    switch (config_.output) {
        case PwmOutput::OC0A: TCCR0A &= ~(_BV(COM0A1)|_BV(COM0A0)); break;
        case PwmOutput::OC0B: TCCR0A &= ~(_BV(COM0B1)|_BV(COM0B0)); break;
        case PwmOutput::OC1A: TCCR1A &= ~(_BV(COM1A1)|_BV(COM1A0)); break;
        case PwmOutput::OC1B: TCCR1A &= ~(_BV(COM1B1)|_BV(COM1B0)); break;
        case PwmOutput::OC2A: TCCR2A &= ~(_BV(COM2A1)|_BV(COM2A0)); break;
        case PwmOutput::OC2B: TCCR2A &= ~(_BV(COM2B1)|_BV(COM2B0)); break;
    }
}

void Pwm::write(uint16_t duty) {
    switch (config_.output) {
        case PwmOutput::OC0A: OCR0A = duty; break; case PwmOutput::OC0B: OCR0B = duty; break;
        case PwmOutput::OC1A: OCR1A = duty; break; case PwmOutput::OC1B: OCR1B = duty; break;
        case PwmOutput::OC2A: OCR2A = duty; break; case PwmOutput::OC2B: OCR2B = duty; break;
    }
}

} // namespace hal
