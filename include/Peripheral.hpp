#pragma once

namespace hal {

/** Common lifecycle interface for hardware peripherals. */
class Peripheral {
public:
    virtual ~Peripheral() = default;

    /** Write the stored configuration to the hardware registers. */
    virtual void init() = 0;

    /** Enable the peripheral using its stored configuration. */
    virtual void enable() = 0;

    /** Disable the peripheral without deleting its configuration. */
    virtual void disable() = 0;
};

} // namespace hal
