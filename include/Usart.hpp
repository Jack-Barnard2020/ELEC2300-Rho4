#pragma once
#include <avr/io.h>
#include <stdint.h>
#include "Peripheral.hpp"

namespace hal {

enum class UsartChannel : uint8_t { Usart0, Usart1 };
enum class UsartParity : uint8_t { None, Even, Odd };
enum class UsartStopBits : uint8_t { One, Two };

/** Settings for asynchronous USART communication. */
struct UsartConfig {
    UsartChannel channel = UsartChannel::Usart0;
    uint32_t baudRate = 9600;
    UsartParity parity = UsartParity::None;
    UsartStopBits stopBits = UsartStopBits::One;
    uint8_t dataBits = 8;
    bool doubleSpeed = false;
    bool receiverEnabled = true;
    bool transmitterEnabled = true;
};

/** Blocking register-level driver for USART0 and USART1. */
class Usart final : public Peripheral {
public:
    explicit Usart(const UsartConfig& config);
    void init() override;
    void enable() override;
    void disable() override;
    bool readable() const;
    bool writable() const;
    uint8_t read();
    void write(uint8_t value);
    void print(const char* text);
    void printUnsigned(uint16_t value);
private:
    uint8_t frameFormat() const;
    uint16_t baudRegisterValue() const;
    UsartConfig config_;
};

} // namespace hal
