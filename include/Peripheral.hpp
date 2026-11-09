#pragma once
#include <stdint.h>

class Peripheral {
public:
    virtual void begin() = 0;
    virtual ~Peripheral() = default;
};

class InputPeripheral : public virtual Peripheral {
public:
    virtual uint16_t read() = 0;
};

class OutputPeripheral : public virtual Peripheral {
public:
    virtual void write(uint16_t value) = 0;
};
