#pragma once
#include <avr/eeprom.h>
#include <stddef.h>
#include <stdint.h>

namespace hal {

/** EEPROM read/update wrapper. Update calls avoid unnecessary erase cycles. */
class Eeprom {
public:
    static uint8_t readByte(const uint8_t* address) { return eeprom_read_byte(address); }
    static void writeByte(uint8_t* address, uint8_t value) { eeprom_update_byte(address, value); }
    static void readBlock(void* destination, const void* source, size_t size) { eeprom_read_block(destination, source, size); }
    static void writeBlock(const void* source, void* destination, size_t size) { eeprom_update_block(source, destination, size); }
};

} // namespace hal
