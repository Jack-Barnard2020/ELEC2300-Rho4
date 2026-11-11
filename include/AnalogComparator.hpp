#pragma once
#include <avr/io.h>
#include "Peripheral.hpp"

namespace hal {

struct AnalogComparatorConfig { bool useBandgapPositive = false; bool interruptEnabled = false; };

/** Register-level analogue comparator controller. */
class AnalogComparator final : public Peripheral {
public:
    explicit AnalogComparator(const AnalogComparatorConfig& config) : config_(config) {}
    void init() override { ACSR=(config_.useBandgapPositive?_BV(ACBG):0)|(config_.interruptEnabled?_BV(ACIE):0); }
    void enable() override { ACSR &= ~_BV(ACD); }
    void disable() override { ACSR |= _BV(ACD); }
    bool output() const { return (ACSR & _BV(ACO)) != 0; }
private:
    AnalogComparatorConfig config_;
};

} // namespace hal
