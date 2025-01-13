//
// Created by Brandon Paul on 1/12/25.
//

#include "../CPU.h"

template<typename T>
void CPU::executeBIT(T address) {
    // Set Zero Flag on result of A & memory
    uint8_t val = memory[address];
    (accumulator & val) == 0 ? setFlag(Zero) : clearFlag(Zero);

    uint8_t bit6 = GET_BIT(val, 6);
    uint8_t bit7 = GET_BIT(val, 7);

    bit6 != 0 ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}
template void CPU::executeBIT<uint8_t>(uint8_t value);
template void CPU::executeBIT<uint16_t>(uint16_t value);
