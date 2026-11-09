#include "Serial.hpp"
#include "Registers.hpp"

namespace { constexpr uint32_t CPU_HZ = 12000000UL; }

void Serial::begin() {
    const uint16_t ubrr = CPU_HZ / (16UL * baud_) - 1;
    reg::UBRR0H = uint8_t(ubrr >> 8); reg::UBRR0L = uint8_t(ubrr);
    reg::UCSR0B = (1 << 4) | (1 << 3); // RX and TX on
    reg::UCSR0C = (1 << 2) | (1 << 1); // 8 data, no parity, 1 stop
}

bool Serial::available() const { return reg::UCSR0A & (1 << 7); }

uint16_t Serial::read() {
    while (!available()) {} // Blocking is fine for this small lab HAL
    return reg::UDR0;
}

void Serial::write(uint16_t value) {
    while (!(reg::UCSR0A & (1 << 5))) {}
    reg::UDR0 = uint8_t(value);
}
