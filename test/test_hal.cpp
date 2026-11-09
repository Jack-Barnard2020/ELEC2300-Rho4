#include <cassert>
#include "Serial.hpp"
#include "Pwm.hpp"
#include "Adc.hpp"
#include "Registers.hpp"

namespace reg {
uint8_t DDRA, DDRB, UCSR0A, UCSR0B, UCSR0C, UBRR0H, UBRR0L, UDR0;
uint8_t TCCR0A, TCCR0B, OCR0A, ADMUX, ADCSRA, ADCL, ADCH;
}

int main() {
    Serial serial; serial.begin();
    assert(reg::UBRR0L == 77); // 9600 baud at 12 MHz
    reg::UCSR0A = 1 << 5; serial.write('A'); assert(reg::UDR0 == 'A');
    reg::UCSR0A = 1 << 7; reg::UDR0 = 'B'; assert(serial.read() == 'B');

    Pwm pwm; pwm.begin(); pwm.write(300);
    assert((reg::DDRB & (1 << 3)) && reg::OCR0A == 255);

    Adc adc(0); adc.begin(); reg::ADCL = 0x34; reg::ADCH = 0x02;
    assert(adc.read() == 0x234);
}
