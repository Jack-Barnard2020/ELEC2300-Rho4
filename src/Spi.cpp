#include "Spi.hpp"

namespace hal {

Spi::Spi(const SpiConfig& config) : config_(config) {}

void Spi::init() {
    if (config_.master) {
        DDRB |= _BV(PB4) | _BV(PB5) | _BV(PB7);
        DDRB &= ~_BV(PB6);
        PORTB |= _BV(PB4);
    } else {
        DDRB |= _BV(PB6);
        DDRB &= ~(_BV(PB4) | _BV(PB5) | _BV(PB7));
    }

    uint8_t control = _BV(SPE) | (config_.master ? _BV(MSTR) : 0);
    if (config_.leastSignificantBitFirst) control |= _BV(DORD);
    if (config_.mode & 2) control |= _BV(CPOL);
    if (config_.mode & 1) control |= _BV(CPHA);

    SPSR = 0;
    switch (config_.clockDivider) {
        case 2: SPSR = _BV(SPI2X); break; case 4: break;
        case 8: control |= _BV(SPR0); SPSR = _BV(SPI2X); break;
        case 16: control |= _BV(SPR0); break;
        case 32: control |= _BV(SPR1); SPSR = _BV(SPI2X); break;
        case 64: control |= _BV(SPR1); break;
        default: control |= _BV(SPR1) | _BV(SPR0); break;
    }
    SPCR = control;
}

void Spi::enable() { SPCR |= _BV(SPE); }
void Spi::disable() { SPCR &= ~_BV(SPE); }

uint8_t Spi::transfer(uint8_t value) {
    SPDR = value;
    while (!(SPSR & _BV(SPIF))) {}
    return SPDR;
}

} // namespace hal
