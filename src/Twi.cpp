#include "Twi.hpp"

namespace hal {

Twi::Twi(const TwiConfig& config) : config_(config) {}
void Twi::init() { TWSR = 0; TWBR = static_cast<uint8_t>((F_CPU / config_.frequency - 16UL) / 2UL); TWAR = config_.localAddress << 1; TWCR = _BV(TWEN); }
void Twi::enable() { TWCR |= _BV(TWEN); }
void Twi::disable() { TWCR &= ~_BV(TWEN); }

bool Twi::start(uint8_t address) {
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    while (!(TWCR & _BV(TWINT))) {}
    TWDR = address;
    TWCR = _BV(TWINT) | _BV(TWEN);
    while (!(TWCR & _BV(TWINT))) {}
    const uint8_t status = TWSR & 0xF8;
    return status == 0x18 || status == 0x40;
}

void Twi::stop() { TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN); }
bool Twi::write(uint8_t value) { TWDR=value; TWCR=_BV(TWINT)|_BV(TWEN); while(!(TWCR&_BV(TWINT))){} return (TWSR&0xF8)==0x28; }
uint8_t Twi::read(bool acknowledge) { TWCR=_BV(TWINT)|_BV(TWEN)|(acknowledge?_BV(TWEA):0); while(!(TWCR&_BV(TWINT))){} return TWDR; }

} // namespace hal
