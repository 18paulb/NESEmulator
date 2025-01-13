//
// Created by Brandon Paul on 1/12/25.
//

#include "../CPU.h"

template<typename T>
void CPU::executeCMP(AddressingMode mode, T val) {
    switch (mode) {
        case Immediate:
            CMP_Immediate(val);
            break;

        case ZeroPage:
            CMP_ZeroPage(val);
            break;

        case ZeroPageX:
            CMP_ZeroPageX(val);
            break;

        case Absolute:
            CMP_Absolute(val);
            break;

        case AbsoluteX:
            CMP_AbsoluteX(val);
            break;

        case AbsoluteY:
            CMP_AbsoluteY(val);
            break;

        case IndirectX:
            CMP_IndirectX(val);
            break;

        case IndirectY:
            CMP_IndirectY(val);
            break;

        default:
            cerr << "Invalid addressing mode for CMP" << endl;
    }
}
template void CPU::executeCMP<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeCMP<uint16_t>(AddressingMode addressingMode, uint16_t value);


void CPU::CMP_Immediate(uint8_t val) {
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_ZeroPageX(uint8_t address) {
    uint8_t val = memory[address + xRegister];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_AbsoluteX(uint16_t address) {
    uint8_t val = memory[address + xRegister];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_AbsoluteY(uint16_t address) {
    uint8_t val = memory[address + yRegister];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_IndirectX(uint8_t address) {
    uint8_t indirectAddress = address + xRegister;
    uint8_t lowByte = memory[indirectAddress];
    uint8_t highByte = memory[indirectAddress + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;

    uint8_t val = memory[targetAddress];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;
    targetAddress += yRegister;

    uint8_t val = memory[targetAddress];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

template<typename T>
void CPU::executeCPX(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            CPX_Immediate(value);
            break;

        case ZeroPage:
            CPX_ZeroPage(value);
            break;

        case Absolute:
            CPX_Absolute(value);
            break;

        default:
            cout << "Invalid addressing mode for CPX" << endl;
    }
}
template void CPU::executeCPX<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeCPX<uint16_t>(AddressingMode addressingMode, uint16_t value);

void CPU::CPX_Immediate(uint8_t val) {
    uint8_t result = xRegister - val;
    uint8_t bit7 = GET_BIT(result, 7);

    xRegister >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    xRegister == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CPX_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    uint8_t result = xRegister - val;
    uint8_t bit7 = GET_BIT(result, 7);

    xRegister >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    xRegister == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CPX_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    uint8_t result = xRegister - val;
    uint8_t bit7 = GET_BIT(result, 7);

    xRegister >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    xRegister == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

template<typename T>
void CPU::executeCPY(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            CPY_Immediate(value);
        break;

        case ZeroPage:
            CPY_ZeroPage(value);
        break;

        case Absolute:
            CPY_Absolute(value);
        break;

        default:
            cout << "Invalid addressing mode for CPX" << endl;
    }
}
template void CPU::executeCPY<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeCPY<uint16_t>(AddressingMode addressingMode, uint16_t value);

void CPU::CPY_Immediate(uint8_t val) {
    uint8_t result = yRegister - val;
    uint8_t bit7 = GET_BIT(result, 7);

    yRegister >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    yRegister == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CPY_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    uint8_t result = yRegister - val;
    uint8_t bit7 = GET_BIT(result, 7);

    yRegister >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    yRegister == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CPY_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    uint8_t result = yRegister - val;
    uint8_t bit7 = GET_BIT(result, 7);

    yRegister >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    yRegister == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}
