# Il Matto peripheral pin mapping

| Function | ATmega644P pin |
|---|---|
| ADC0 to ADC7 | PA0 to PA7 |
| SPI SS | PB4 |
| SPI MOSI | PB5 |
| SPI MISO | PB6 |
| SPI SCK | PB7 |
| OC0A | PB3 |
| OC0B | PB4 |
| Analogue comparator AIN0 | PB3 |
| Analogue comparator AIN1 | PB4 |
| TWI SCL | PC0 |
| TWI SDA | PC1 |
| USART0 RXD | PD0 |
| USART0 TXD | PD1 |
| USART1 RXD | PD2 |
| USART1 TXD | PD3 |
| OC1B | PD4 |
| OC1A | PD5 |
| OC2B | PD6 |
| OC2A | PD7 |

Every listed pin can also be used as GPIO. Selecting a peripheral function takes ownership of the relevant pin. PB3 and PB4 deserve particular care because PWM, comparator, SPI chip select, and GPIO functions overlap there.
