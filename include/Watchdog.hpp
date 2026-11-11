#pragma once
#include <avr/wdt.h>
#include <stdint.h>
#include "Peripheral.hpp"

namespace hal {

/** Watchdog controller using AVR timeout constants such as WDTO_1S. */
class Watchdog final : public Peripheral {
public:
    explicit Watchdog(uint8_t timeout = WDTO_1S) : timeout_(timeout) {}
    void init() override { wdt_enable(timeout_); }
    void enable() override { wdt_enable(timeout_); }
    void disable() override { wdt_disable(); }
    void reset() { wdt_reset(); }
private:
    uint8_t timeout_;
};

} // namespace hal
