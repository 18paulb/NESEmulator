//
// Created by Brandon Paul on 1/12/25.
//

#include "../CPU.h"

template<typename T>
void CPU::executeADC(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            ADC_Immediate(value);
            break;

        case ZeroPage:
            ADC_ZeroPage(value);
            break;

        case ZeroPageX:
            ADC_ZeroPageX(value);
            break;

        case Absolute:
            ADC_Absolute(value);
            break;

        case AbsoluteX:
            ADC_AbsoluteX(value);
            break;

        case AbsoluteY:
            ADC_AbsoluteY(value);
            break;

        case IndirectX:
            ADC_IndirectX(value);
            break;

        case IndirectY:
            ADC_IndirectY(value);
            break;

        default:
            cerr << "Invalid Addressing Mode for ADC" << endl;
    }
}
template void CPU::executeADC<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeADC<uint16_t>(AddressingMode addressingMode, uint16_t value);

void CPU::ADC_Immediate(uint8_t val) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_ZeroPage(uint8_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;
    uint8_t val = memory[address];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_ZeroPageX(uint8_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;
    uint8_t val = memory[address + xRegister];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_Absolute(uint16_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;
    uint8_t val = memory[address];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_AbsoluteX(uint16_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;
    uint8_t val = memory[address + xRegister];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_AbsoluteY(uint16_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;
    uint8_t val = memory[address + yRegister];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_IndirectX(uint8_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;

    // Calculate the memory address
    uint8_t indirectAddress = address + xRegister;
    uint8_t lowByte = memory[indirectAddress];
    uint8_t highByte = memory[indirectAddress + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;
    uint8_t val = memory[targetAddress];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_IndirectY(uint8_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;

    // Calculate the memory address
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;
    targetAddress += yRegister;
    uint8_t val = memory[targetAddress];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}