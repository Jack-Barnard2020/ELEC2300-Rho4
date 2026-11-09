#include "Hal.hpp"

int main() {
    Serial serial; Pwm pwm; Adc adc(0);
    serial.begin(); pwm.begin(); adc.begin();

    while (true) {
        if (serial.available()) pwm.write(serial.read());
        const uint16_t sample = adc.read();
        serial.write(sample >> 8); serial.write(sample & 0xFF);
    }
}
