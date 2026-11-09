# Hardware Abstraction Layer

A small C++ hardware abstraction layer for the Il Matto board. It provides a common interface for the peripherals used in the Rho4 lab, while keeping the register-level setup and control code inside separate classes.

## Features

- Serial communication over UART
- PWM output for driving the low-pass filter and DAC
- ADC input for measuring analogue voltage
- A shared peripheral interface using inheritance and virtual functions
- Direct register-level implementation for the ATmega microcontroller

## Structure

The HAL is built around an abstract base class for common peripheral behaviour. The concrete `Serial`, `PWM`, and `ADC` classes handle the hardware-specific setup and operations for each peripheral.

```text
HAL/
├── include/        Header files
├── src/            Peripheral implementations
└── main.cpp        Example usage and hardware tests
```

The exact layout may differ depending on how the project is organised.

## Building

Build the project using AVR-GCC or TurboAVR for the ATmega device fitted to the Il Matto board. Make sure the selected device and clock frequency match the board configuration.

Example AVR-GCC build:

```bash
avr-g++ -mmcu=atmega644p -DF_CPU=12000000UL -Os -std=c++11   -Iinclude src/*.cpp main.cpp -o hal.elf
avr-objcopy -O ihex hal.elf hal.hex
```

Change `atmega644p` if your board uses a different compatible ATmega device.

## Usage

Create the required peripheral objects, initialise them, then use their public methods instead of accessing registers from application code.

```cpp
Serial serial;
PWM pwm;
ADC adc;

int main() {
    serial.init();
    pwm.init();
    adc.init();

    while (true) {
        uint8_t command = serial.read();
        pwm.write(command);

        uint16_t sample = adc.read();
        serial.write(sample);
    }
}
```

Method names may need changing to match the implementation.

## Hardware notes

- The Il Matto runs at 3.3 V and 12 MHz.
- Connect the PWM output to the RC low-pass filter to produce the analogue output.
- Connect the filtered voltage to an ADC input if feedback is required.
- Keep all peripheral control register-level. Arduino-style libraries are not used.

## Testing

Test each peripheral separately before combining them:

1. Send and receive a known value over serial.
2. Check the PWM waveform with an oscilloscope.
3. Apply a known voltage to the ADC and verify the reading.
4. Run the combined serial, PWM, and ADC example.

## Purpose

This HAL separates hardware access from the DAC and control logic, making the application code easier to read and allowing peripherals to be changed or extended without rewriting the whole program.
