#pragma once
#include <stdint.h>
#ifdef HAL_TEST
namespace reg {
extern uint8_t DDRA, DDRB, UCSR0A, UCSR0B, UCSR0C, UBRR0H, UBRR0L, UDR0;
extern uint8_t TCCR0A, TCCR0B, OCR0A, ADMUX, ADCSRA, ADCL, ADCH;
}
#else
#include <avr/io.h>
namespace reg {
#define R(name) inline volatile uint8_t& name = ::name
R(DDRA); R(DDRB); R(UCSR0A); R(UCSR0B); R(UCSR0C); R(UBRR0H); R(UBRR0L); R(UDR0);
R(TCCR0A); R(TCCR0B); R(OCR0A); R(ADMUX); R(ADCSRA); R(ADCL); R(ADCH);
#undef R
}
#endif
