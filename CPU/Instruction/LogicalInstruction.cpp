//
// Created by Brandon Paul on 1/12/25.
//

#include "../CPU.h"


template<typename T>
void CPU::executeAND(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            AND_Immediate(value);
            break;

        case ZeroPage:
            AND_ZeroPage(value);
            break;

        case ZeroPageX:
            AND_ZeroPageX(value);
            break;

        case Absolute:
            AND_Absolute(value);
            break;

        case AbsoluteX:
            AND_AbsoluteX(value);
            break;

        case AbsoluteY:
            AND_AbsoluteY(value);
            break;

        case IndirectX:
            AND_IndirectX(value);
            break;

        case IndirectY:
            AND_IndirectY(value);
            break;

        default:
            cerr << "Invalid addressing mode for AND" << endl;
    }
}
template void CPU::executeAND<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeAND<uint16_t>(AddressingMode addressingMode, uint16_t value);

void CPU::AND_Immediate(uint8_t value) {
    accumulator = accumulator & value;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::AND_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);

}

void CPU::AND_ZeroPageX(uint8_t address) {
    uint8_t val = memory[address + xRegister];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::AND_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::AND_AbsoluteX(uint16_t address) {
    uint8_t val = memory[address + xRegister];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::AND_AbsoluteY(uint16_t address) {
    uint8_t val = memory[address + yRegister];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::AND_IndirectX(uint8_t address) {
    uint8_t indirectAddress = address + xRegister;
    uint8_t lowByte = memory[indirectAddress];
    uint8_t highByte = memory[indirectAddress + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;

    uint8_t val = memory[targetAddress];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::AND_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;
    targetAddress += yRegister;

    uint8_t val = memory[targetAddress];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);
}

template<typename T>
void CPU::executeEOR(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            EOR_Immediate(value);
            break;

        case ZeroPage:
            EOR_ZeroPage(value);
            break;

        case ZeroPageX:
            EOR_ZeroPageX(value);
            break;

        case Absolute:
            EOR_Absolute(value);
            break;

        case AbsoluteX:
            EOR_AbsoluteX(value);
            break;

        case AbsoluteY:
            EOR_AbsoluteY(value);
            break;

        case IndirectX:
            EOR_IndirectX(value);
            break;

        case IndirectY:
            EOR_IndirectY(value);
            break;

        default:
            cout << "Invalid addressing mode for EOR" << endl;
    }
}

void CPU::EOR_Immediate(uint8_t val) {
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_ZeroPageX(uint8_t address) {
    uint8_t val = memory[address + xRegister];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_AbsoluteX(uint16_t address) {
    uint8_t val = memory[address + xRegister];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_AbsoluteY(uint16_t address) {
    uint8_t val = memory[address + yRegister];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_IndirectX(uint8_t address) {
    uint8_t indirectAddress = address + xRegister;
    uint8_t lowByte = memory[indirectAddress];
    uint8_t highByte = memory[indirectAddress + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;

    uint8_t val = memory[targetAddress];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;
    targetAddress += yRegister;

    uint8_t val = memory[targetAddress];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}
template void CPU::executeEOR<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeEOR<uint16_t>(AddressingMode addressingMode, uint16_t value);

template<typename T>
void CPU::executeORA(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            ORA_Immediate(value);
            break;

        case ZeroPage:
            ORA_ZeroPage(value);
            break;

        case ZeroPageX:
            ORA_ZeroPageX(value);
            break;

        case Absolute:
            ORA_Absolute(value);
            break;

        case AbsoluteX:
            ORA_AbsoluteX(value);
            break;

        case AbsoluteY:
            ORA_AbsoluteY(value);
            break;

        case IndirectX:
            ORA_IndirectX(value);
            break;

        case IndirectY:
            ORA_IndirectY(value);
            break;

        default:
            cout << "Invalid addressing mode for EOR" << endl;
    }
}

void CPU::ORA_Immediate(uint8_t val) {
    accumulator |= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ORA_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    accumulator |= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ORA_ZeroPageX(uint8_t address) {
    uint8_t val = memory[address + xRegister];
    accumulator |= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ORA_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    accumulator |= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ORA_AbsoluteX(uint16_t address) {
    uint8_t val = memory[address + xRegister];
    accumulator |= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ORA_AbsoluteY(uint16_t address) {
    uint8_t val = memory[address + yRegister];
    accumulator |= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ORA_IndirectX(uint8_t address) {
    uint8_t indirectAddress = address + xRegister;
    uint8_t lowByte = memory[indirectAddress];
    uint8_t highByte = memory[indirectAddress + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;

    uint8_t val = memory[targetAddress];
    accumulator |= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ORA_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;
    targetAddress += yRegister;

    uint8_t val = memory[targetAddress];
    accumulator |= val;
    setZeroAndNegativeFlag(accumulator);
}
template void CPU::executeORA<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeORA<uint16_t>(AddressingMode addressingMode, uint16_t value);