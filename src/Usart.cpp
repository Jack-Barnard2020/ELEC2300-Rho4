#include "Usart.hpp"

namespace hal {

Usart::Usart(const UsartConfig& config) : config_(config) {}

uint16_t Usart::baudRegisterValue() const {
    const uint32_t divisor = config_.doubleSpeed ? 8UL : 16UL;
    return static_cast<uint16_t>((F_CPU / (divisor * config_.baudRate)) - 1UL);
}

uint8_t Usart::frameFormat() const {
    uint8_t value = 0;

    if (config_.parity == UsartParity::Even) value |= _BV(UPM01);
    else if (config_.parity == UsartParity::Odd) value |= _BV(UPM01) | _BV(UPM00);

    if (config_.stopBits == UsartStopBits::Two) value |= _BV(USBS0);

    switch (config_.dataBits) {
        case 5: break;
        case 6: value |= _BV(UCSZ00); break;
        case 7: value |= _BV(UCSZ01); break;
        default: value |= _BV(UCSZ01) | _BV(UCSZ00); break;
    }

    return value;
}

void Usart::init() {
    const uint16_t baud = baudRegisterValue();
    const uint8_t frame = frameFormat();

    if (config_.channel == UsartChannel::Usart0) {
        UCSR0A = config_.doubleSpeed ? _BV(U2X0) : 0;
        UBRR0H = static_cast<uint8_t>(baud >> 8);
        UBRR0L = static_cast<uint8_t>(baud);
        UCSR0B = (config_.receiverEnabled ? _BV(RXEN0) : 0)
               | (config_.transmitterEnabled ? _BV(TXEN0) : 0);
        UCSR0C = frame;
    } else {
        UCSR1A = config_.doubleSpeed ? _BV(U2X1) : 0;
        UBRR1H = static_cast<uint8_t>(baud >> 8);
        UBRR1L = static_cast<uint8_t>(baud);
        UCSR1B = (config_.receiverEnabled ? _BV(RXEN1) : 0)
               | (config_.transmitterEnabled ? _BV(TXEN1) : 0);
        UCSR1C = frame;
    }
}

void Usart::enable() { init(); }
void Usart::disable() { if (config_.channel == UsartChannel::Usart0) UCSR0B = 0; else UCSR1B = 0; }
bool Usart::readable() const { return config_.channel == UsartChannel::Usart0 ? (UCSR0A & _BV(RXC0)) : (UCSR1A & _BV(RXC1)); }
bool Usart::writable() const { return config_.channel == UsartChannel::Usart0 ? (UCSR0A & _BV(UDRE0)) : (UCSR1A & _BV(UDRE1)); }

uint8_t Usart::read() {
    while (!readable()) {}
    return config_.channel == UsartChannel::Usart0 ? UDR0 : UDR1;
}

void Usart::write(uint8_t value) {
    while (!writable()) {}
    if (config_.channel == UsartChannel::Usart0) UDR0 = value;
    else UDR1 = value;
}

void Usart::print(const char* text) {
    while (*text != '\0') write(static_cast<uint8_t>(*text++));
}

void Usart::printUnsigned(uint16_t value) {
    char digits[5];
    uint8_t count = 0;

    if (value == 0) { write('0'); return; }
    while (value != 0) { digits[count++] = static_cast<char>('0' + value % 10); value /= 10; }
    while (count != 0) write(static_cast<uint8_t>(digits[--count]));
}

} // namespace hal
