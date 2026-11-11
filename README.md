# ATmega644P / Il Matto HAL

A register-level C++ hardware abstraction layer for the ATmega644P on the Il Matto board.

## Why the include folder is now flat

The previous package used `include/hal/`, which is a common library layout because it prevents header-name clashes and allows includes such as `#include <hal/Adc.hpp>`.

This package uses the simpler layout requested:

```text
include/
├── Adc.hpp
├── Gpio.hpp
├── Pwm.hpp
├── Usart.hpp
└── ...
```

There is no second folder inside `include`. Add `include/` to the compiler's search path and include headers directly, for example `#include "Adc.hpp"` or `#include "Hal.hpp"`.

## What is included

- GPIO
- USART0 and USART1
- ADC0 to ADC7
- PWM outputs OC0A, OC0B, OC1A, OC1B, OC2A, and OC2B
- SPI
- TWI / I2C
- Analogue comparator
- EEPROM
- Watchdog

All configurable peripherals use direct ATmega644P register access. No Arduino peripheral implementation is used.

## Start here

1. Install AVR-GCC, AVR Binutils, AVR Libc, Make, and a suitable programmer tool such as AVRDUDE.
2. Extract the archive into the application repository.
3. Run `make` inside the HAL directory to create `libhal.a`.
4. Add the HAL `include/` directory to the application's include paths.
5. Add `libhal.a` to the application's linker inputs.
6. Define `F_CPU=12000000UL` unless the board clock has been changed.
7. Create each peripheral's configuration structure.
8. Construct the peripheral object and call `init()` before using it.
9. Check the Il Matto pin table before enabling two functions that share a pin or timer.

Detailed instructions are in:

- `docs/BUILDING.md`
- `docs/USING_THE_HAL.md`
- `docs/PERIPHERALS.md`
- `docs/PIN_MAPPING.md`

## Build the library

```bash
make
```

The result is `libhal.a`. Clean build files with:

```bash
make clean
```

Override the defaults if required:

```bash
make MCU=atmega644p F_CPU=12000000UL
```

## Generate API documentation

The headers use Doxygen comments. With Doxygen installed, run:

```bash
doxygen Doxyfile
```

Open `docs/api/html/index.html` after generation.

## Project structure

```text
include/          Public header files, with no nested folder
src/              Register-level implementations
docs/             Build, integration, peripheral, and pin documentation
Doxyfile          Doxygen configuration
Makefile          Static-library build
README.md         Project overview
```

## Important limitations

- USART, SPI, TWI, and ADC operations are blocking.
- TWI currently implements the common controller transmit/receive sequence, not a full target-mode state machine.
- PWM channels sharing the same timer also share its prescaler and waveform mode.
- The GPIO class does not prevent an application from selecting a pin already used by another peripheral.
- Application code, test programs, and examples are deliberately excluded.
