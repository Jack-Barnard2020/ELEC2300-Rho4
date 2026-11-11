# Using the HAL

## 1. Add the headers

Add the HAL `include/` directory to the compiler include path. Include individual peripheral headers or `Hal.hpp` for the complete public interface.

The folder is intentionally flat. There is no `include/hal/` directory.

## 2. Choose the hardware resource

Before creating an object, identify:

- the required physical pin;
- the peripheral instance, such as USART0 or USART1;
- the timer used by a PWM output;
- any shared pins or timer settings;
- the required clock or baud rate.

Use `PIN_MAPPING.md` for the Il Matto mappings.

## 3. Fill in the configuration

Each configurable driver has a configuration structure. Default values are provided for common settings. Change only the fields required by the application.

Configuration objects are copied into their peripheral objects. They do not need to remain alive afterwards.

## 4. Construct the peripheral

Construct the object once and keep it alive while the hardware is in use. Avoid creating multiple objects that control the same hardware registers.

## 5. Initialise it

Call `init()` once after reset and before the first read or write. `init()` writes the configuration to the hardware registers and enables the peripheral.

`enable()` reapplies or enables the existing configuration. `disable()` turns off the selected hardware function while keeping the C++ object available.

## 6. Use the peripheral

Input and communication operations are blocking unless stated otherwise. A call such as a USART read waits until data arrives. Design the application loop so that a blocking operation cannot prevent required control or safety work.

## 7. Resolve shared-resource conflicts

The ATmega644P multiplexes peripheral functions onto GPIO pins. A pin should not be simultaneously controlled as GPIO and as a peripheral signal.

PWM channels on the same timer share waveform and clock settings:

- OC0A and OC0B share Timer 0.
- OC1A and OC1B share Timer 1.
- OC2A and OC2B share Timer 2.

Creating two PWM objects on the same timer with different modes or prescalers causes the most recently initialised object to change the timer settings for both outputs.

## 8. Keep register writes inside the HAL

Application code should call the HAL rather than modify the same peripheral registers directly. Mixing direct application writes with HAL calls makes the stored configuration inaccurate and can cause hard-to-find faults.

## 9. Test one peripheral at a time

Verify electrical levels and pin selection before combining peripherals. For PWM and serial signals, an oscilloscope or logic analyser is more reliable than checking only application output.
