//
// Created by Brandon Paul on 4/24/24.
//

#ifndef NESEMULATOR_STATUSFLAGS_H
#define NESEMULATOR_STATUSFLAGS_H

enum StatusFlag {
    // (C) Set if last instruction resulted in overflow from bit 8 or underflow with bit 0
    Carry,

    // (Z) Set if result of last instruction was a 0
    Zero,

    // (I) Set to prevent system interrupts
    InterruptDisable,

    // (B) Set when a BRK instruction has been executed
    Break,

    // (D) Set to switch the 6502 into BCD mode
    Decimal,

    // Extra bit that does nothing
    EXTRA,

    // (V) Set if an invalid two's complement results was obtained by the previous instruction
    // This means that a negative result has been obtained when a positive one was expected or vice versa.
    Overflow,

    // (N) Bit 7 of a byte represents the sign of that byte, with 0 being positive and 1 being negative
    Negative
};

#endif //NESEMULATOR_STATUSFLAGS_H
