# Peripheral reference

## Peripheral base class

`Peripheral` defines `init()`, `enable()`, and `disable()`. GPIO, USART, ADC, PWM, SPI, TWI, analogue comparator, and watchdog implement this interface.

## GPIO

`GpioConfig` contains pointers to `DDRx`, `PORTx`, and `PINx`, plus the pin bit and mode. Output initialisation drives low. Disabling returns the pin to a high-impedance input without an internal pull-up.

## USART

`UsartConfig` selects USART0 or USART1, baud rate, parity, stop bits, character size, double-speed mode, receiver, and transmitter. Reads and writes block until the relevant status flag is set. Five to eight data bits are supported. Nine-bit frames are not implemented.

## ADC

`AdcConfig` selects ADC0 to ADC7, AREF/AVCC/internal reference, prescaler, and result alignment. `read()` starts one conversion and returns the 16-bit ADC register value. With right adjustment, the conversion occupies the lower ten bits.

At a 12 MHz system clock, divide-by-128 gives a 93.75 kHz ADC clock, which is suitable for normal 10-bit conversion accuracy.

## PWM

`PwmConfig` selects one of six output-compare channels, fast or phase-correct PWM, clock prescaler, and normal/inverted output. The driver uses 8-bit PWM modes for all timers. Timer 1's 16-bit compare registers are accessible, but values above the selected 8-bit TOP do not provide a wider duty range in the configured mode.

## SPI

`SpiConfig` selects controller/peripheral role, clock mode 0 to 3, divider, and bit order. `transfer()` sends and receives one byte. The application controls chip-select GPIO lines because different devices have different selection requirements.

## TWI / I2C

`TwiConfig` sets bus frequency and local address. `start()` takes the seven-bit address shifted left with the read/write bit in bit zero. The methods implement blocking controller transfers and basic ACK checking.

## Analogue comparator

The comparator can use the internal bandgap on its positive input and can enable its interrupt source. The class exposes the current comparator output.

## EEPROM

`Eeprom` wraps AVR EEPROM read and update calls. Update operations avoid a write when the existing value already matches, reducing unnecessary EEPROM wear.

## Watchdog

The watchdog accepts AVR Libc timeout constants such as `WDTO_1S`. Once enabled, application code must call `reset()` often enough to prevent a watchdog reset.
