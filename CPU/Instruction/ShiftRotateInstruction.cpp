//
// Created by Brandon Paul on 1/12/25.
//

#include "../CPU.h"

// FIXME: Potential Issues
// 1. Not sure if N and Z flags should be set when changing memory, only accumulator
template<typename T>
void CPU::executeASL(AddressingMode mode, T value) {
    switch (mode) {
        case Accumulator:
            ASL_Accumulator();
            break;

        case ZeroPage:
            ASL_ZeroPage(value);
            break;

        case ZeroPageX:
            ASL_ZeroPageX(value);
            break;

        case Absolute:
            ASL_Absolute(value);
            break;

        case AbsoluteX:
            ASL_AbsoluteX(value);
            break;

        default:
            cerr << "Invalid addressing mode for ASL" << endl;
    }
}
template void CPU::executeASL<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeASL<uint16_t>(AddressingMode addressingMode, uint16_t value);

void CPU::ASL_Accumulator() {
    // Capture bit 7 of the accumulator before the shift
    uint8_t bit7 = GET_BIT(accumulator, 7);
    accumulator = accumulator << 1;

    // bit 7 of original accumulator is the new value of the carry flag
    bit7 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ASL_ZeroPage(uint8_t address) {
    // Capture bit 7 of the accumulator before the shift
    uint8_t bit7 = GET_BIT(memory[address], 7);
    memory[address] = memory[address] << 1;

    // bit 7 of original memory value is the new value of the carry flag
    bit7 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::ASL_ZeroPageX(uint8_t address) {
    // Capture bit 7 of the accumulator before the shift
    uint8_t adjustedAddress = address + xRegister;
    uint8_t bit7 = GET_BIT(memory[adjustedAddress], 7);
    memory[adjustedAddress] = memory[adjustedAddress] << 1;

    // bit 7 of original memory value is the new value of the carry flag
    bit7 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[adjustedAddress]);
}

void CPU::ASL_Absolute(uint16_t address) {
    // Capture bit 7 of the accumulator before the shift
    uint8_t bit7 = GET_BIT(memory[address], 7);
    memory[address] = memory[address] << 1;

    // bit 7 of original memory value is the new value of the carry flag
    bit7 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::ASL_AbsoluteX(uint16_t address) {
    // Capture bit 7 of the accumulator before the shift
    uint16_t adjustedAddress = address + xRegister;
    uint8_t bit7 = GET_BIT(memory[adjustedAddress], 7);
    memory[adjustedAddress] = memory[adjustedAddress] << 1;

    // bit 7 of original memory value is the new value of the carry flag
    bit7 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[adjustedAddress]);
}

// FIXME: Potential Issues
// 1. Not sure if N and Z flags should be set when changing memory, only accumulator
template<typename T>
void CPU::executeLSR(AddressingMode mode, T value) {
    switch (mode) {
        case Accumulator:
            LSR_Accumulator();
            break;

        case ZeroPage:
            LSR_ZeroPage(value);
            break;

        case ZeroPageX:
            LSR_ZeroPageX(value);
            break;

        case Absolute:
            LSR_Absolute(value);
            break;

        case AbsoluteX:
            LSR_AbsoluteX(value);
            break;

        default:
            cerr << "Invalid addressing mode for ASL" << endl;
    }
}
template void CPU::executeLSR<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeLSR<uint16_t>(AddressingMode addressingMode, uint16_t value);

void CPU::LSR_Accumulator() {
    // Capture bit 0 of the accumulator before the shift
    uint8_t bit0 = GET_BIT(accumulator, 0);
    accumulator = accumulator >> 1;

    // bit 0 of original accumulator is the new value of the carry flag
    bit0 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::LSR_ZeroPage(uint8_t address) {
    // Capture bit 0 of the accumulator before the shift
    uint8_t bit0 = GET_BIT(memory[address], 0);
    memory[address] = memory[address] >> 1;

    // bit 0 of original memory value is the new value of the carry flag
    bit0 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::LSR_ZeroPageX(uint8_t address) {
    // Capture bit 0 of the accumulator before the shift
    uint8_t adjustedAddress = address + xRegister;
    uint8_t bit0 = GET_BIT(memory[adjustedAddress], 0);
    memory[adjustedAddress] = memory[adjustedAddress] >> 1;

    // bit 0 of original memory value is the new value of the carry flag
    bit0 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[adjustedAddress]);
}

void CPU::LSR_Absolute(uint16_t address) {
    // Capture bit 0 of the accumulator before the shift
    uint8_t bit0 = GET_BIT(memory[address], 0);
    memory[address] = memory[address] >> 1;

    // bit 0 of original memory value is the new value of the carry flag
    bit0 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::LSR_AbsoluteX(uint16_t address) {
    // Capture bit 0 of the accumulator before the shift
    uint16_t adjustedAddress = address + xRegister;
    uint8_t bit0 = GET_BIT(memory[adjustedAddress], 0);
    memory[adjustedAddress] = memory[adjustedAddress] >> 1;

    // bit 0 of original memory value is the new value of the carry flag
    bit0 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[adjustedAddress]);
}

template<typename T>
void CPU::executeROL(AddressingMode mode, T value) {
    switch (mode) {
        case Accumulator:
            ROL_Accumulator();
            break;

        case ZeroPage:
            ROL_ZeroPage(value);
            break;

        case ZeroPageX:
            ROL_ZeroPageX(value);
            break;

        case Absolute:
            ROL_Absolute(value);
            break;

        case AbsoluteX:
            ROL_AbsoluteX(value);
            break;

        default:
            cerr << "Invalid addressing mode for ROL" << endl;
    }
}
template void CPU::executeROL<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeROL<uint16_t>(AddressingMode addressingMode, uint16_t value);

void CPU::ROL_Accumulator() {
    uint8_t bit7 = GET_BIT(accumulator, 7);
    uint8_t carryFlag = isFlagSet(StatusFlag::Carry);
    // The value of the carryFlag is shifted to bit 0
    accumulator = (accumulator << 1) | (carryFlag);

    // The value of bit7 is now shifted into carryFlag
    bit7 == 0 ? clearFlag(StatusFlag::Carry) : setFlag(StatusFlag::Carry);

    // Carry Flag, Negative Flag, and Zero flags should be changed
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ROL_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    uint8_t bit7 = GET_BIT(val, 7);
    uint8_t carryFlag = isFlagSet(StatusFlag::Carry);
    // The value of the carryFlag is shifted to bit 0
    val = (val << 1) | (carryFlag);
    memory[address] = val;

    // The value of bit7 is now shifted into carryFlag
    bit7 == 0 ? clearFlag(StatusFlag::Carry) : setFlag(StatusFlag::Carry);

    // Carry Flag, Negative Flag, and Zero flags should be changed
    setZeroAndNegativeFlag(val);
}

void CPU::ROL_ZeroPageX(uint8_t address) {
    uint8_t adjustedAddress = address + xRegister;
    uint8_t val = memory[adjustedAddress];
    uint8_t bit7 = GET_BIT(val, 7);
    uint8_t carryFlag = isFlagSet(StatusFlag::Carry);
    // The value of the carryFlag is shifted to bit 0
    val = (val << 1) | (carryFlag);
    memory[adjustedAddress] = val;

    // The value of bit7 is now shifted into carryFlag
    bit7 == 0 ? clearFlag(StatusFlag::Carry) : setFlag(StatusFlag::Carry);

    // Carry Flag, Negative Flag, and Zero flags should be changed
    setZeroAndNegativeFlag(val);

}

void CPU::ROL_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    uint8_t bit7 = GET_BIT(val, 7);
    uint8_t carryFlag = isFlagSet(StatusFlag::Carry);
    // The value of the carryFlag is shifted to bit 0
    val = (val << 1) | (carryFlag);
    memory[address] = val;

    // The value of bit7 is now shifted into carryFlag
    bit7 == 0 ? clearFlag(StatusFlag::Carry) : setFlag(StatusFlag::Carry);

    // Carry Flag, Negative Flag, and Zero flags should be changed
    setZeroAndNegativeFlag(val);
}

void CPU::ROL_AbsoluteX(uint16_t address) {
    uint16_t adjustedAddress = address + xRegister;
    uint8_t val = memory[adjustedAddress];
    uint8_t bit7 = GET_BIT(val, 7);
    uint8_t carryFlag = isFlagSet(StatusFlag::Carry);
    // The value of the carryFlag is shifted to bit 0
    val = (val << 1) | (carryFlag);
    memory[adjustedAddress] = val;

    // The value of bit7 is now shifted into carryFlag
    bit7 == 0 ? clearFlag(StatusFlag::Carry) : setFlag(StatusFlag::Carry);

    // Carry Flag, Negative Flag, and Zero flags should be changed
    setZeroAndNegativeFlag(val);
}

template<typename T>
void CPU::executeROR(AddressingMode mode, T value) {
    switch (mode) {
        case Accumulator:
            ROR_Accumulator();
            break;

        case ZeroPage:
            ROR_ZeroPage(value);
            break;

        case ZeroPageX:
            ROR_ZeroPageX(value);
            break;

        case Absolute:
            ROR_Absolute(value);
            break;

        case AbsoluteX:
            ROR_AbsoluteX(value);
            break;

        default:
            cerr << "Invalid addressing mode for ROL" << endl;
    }
}
template void CPU::executeROR<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeROR<uint16_t>(AddressingMode addressingMode, uint16_t value);

void CPU::ROR_Accumulator() {
    uint8_t bit0 = GET_BIT(accumulator, 0);
    uint8_t carryFlag = isFlagSet(StatusFlag::Carry);
    // The value of the carryFlag is shifted to bit 0
    accumulator = (accumulator >> 1) | (carryFlag << 7);

    // The value of bit0 is now shifted into carryFlag
    bit0 == 0 ? clearFlag(StatusFlag::Carry) : setFlag(StatusFlag::Carry);

    // Carry Flag, Negative Flag, and Zero flags should be changed
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ROR_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    uint8_t bit0 = GET_BIT(val, 0);
    uint8_t carryFlag = isFlagSet(StatusFlag::Carry);
    // The value of the carryFlag is shifted to bit 0
    val = (val >> 1) | (carryFlag << 7);
    memory[address] = val;

    // The value of bit7 is now shifted into carryFlag
    bit0 == 0 ? clearFlag(StatusFlag::Carry) : setFlag(StatusFlag::Carry);

    // Carry Flag, Negative Flag, and Zero flags should be changed
    setZeroAndNegativeFlag(val);
}

void CPU::ROR_ZeroPageX(uint8_t address) {
    uint8_t adjustedAddress = address + xRegister;
    uint8_t val = memory[adjustedAddress];
    uint8_t bit0 = GET_BIT(val, 0);
    uint8_t carryFlag = isFlagSet(StatusFlag::Carry);
    // The value of the carryFlag is shifted to bit 0
    val = (val >> 1) | (carryFlag << 7);
    memory[adjustedAddress] = val;

    // The value of bit7 is now shifted into carryFlag
    bit0 == 0 ? clearFlag(StatusFlag::Carry) : setFlag(StatusFlag::Carry);

    // Carry Flag, Negative Flag, and Zero flags should be changed
    setZeroAndNegativeFlag(val);
}

void CPU::ROR_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    uint8_t bit0 = GET_BIT(val, 0);
    uint8_t carryFlag = isFlagSet(StatusFlag::Carry);
    // The value of the carryFlag is shifted to bit 0
    val = (val >> 1) | (carryFlag << 7);
    memory[address] = val;

    // The value of bit7 is now shifted into carryFlag
    bit0 == 0 ? clearFlag(StatusFlag::Carry) : setFlag(StatusFlag::Carry);

    // Carry Flag, Negative Flag, and Zero flags should be changed
    setZeroAndNegativeFlag(val);
}

void CPU::ROR_AbsoluteX(uint16_t address) {
    uint16_t adjustedAddress = address + xRegister;
    uint8_t val = memory[adjustedAddress];
    uint8_t bit0 = GET_BIT(val, 0);
    uint8_t carryFlag = isFlagSet(StatusFlag::Carry);
    // The value of the carryFlag is shifted to bit 0
    val = (val >> 1) | (carryFlag << 7);
    memory[adjustedAddress] = val;

    // The value of bit7 is now shifted into carryFlag
    bit0 == 0 ? clearFlag(StatusFlag::Carry) : setFlag(StatusFlag::Carry);

    // Carry Flag, Negative Flag, and Zero flags should be changed
    setZeroAndNegativeFlag(val);
}