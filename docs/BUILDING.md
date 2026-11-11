# Building the HAL

## Required tools

Install an AVR toolchain containing:

- `avr-g++`
- `avr-ar`
- AVR Libc headers
- GNU Make
- AVRDUDE or the programmer software used by the laboratory setup

On Debian or Ubuntu, the normal packages are `gcc-avr`, `binutils-avr`, `avr-libc`, `make`, and `avrdude`.

## Build settings

The Makefile defaults are:

| Setting | Default | Meaning |
|---|---:|---|
| `MCU` | `atmega644p` | AVR-GCC target device |
| `F_CPU` | `12000000UL` | Il Matto clock frequency |
| C++ standard | GNU++11 | Language mode |
| Optimisation | `-Os` | Optimise for program size |

Run `make` from the project root. The compiler creates one object per `.cpp` file and `avr-ar` packages the objects into `libhal.a`.

## Add it to an application

The application compile command needs:

```text
-I/path/to/atmega644p-hal/include
-DF_CPU=12000000UL
-mmcu=atmega644p
```

The final link command needs:

```text
/path/to/atmega644p-hal/libhal.a
-mmcu=atmega644p
```

The application and HAL must use the same MCU and `F_CPU` values. A mismatch can produce incorrect USART baud rates, TWI speed, and timing.

## Rebuild after changes

Run `make clean` after changing compiler, MCU, clock, or important compiler flags. Then run `make` again.

## Uploading

The HAL builds a library, not firmware. The application must provide `main()` and be linked into an ELF/HEX file. Upload that application HEX file using the board's ISP, JTAG, or USB programming arrangement.

## Troubleshooting

- `avr/io.h: No such file`: AVR Libc is not installed or the wrong compiler is being used.
- `F_CPU was not declared`: pass `-DF_CPU=12000000UL` to every relevant compilation unit.
- Undefined HAL methods: link `libhal.a` after the application objects.
- Wrong serial baud: confirm the physical clock, `F_CPU`, baud setting, and double-speed setting.
- Output on the wrong pin: compare the selected peripheral channel with `docs/PIN_MAPPING.md`.
