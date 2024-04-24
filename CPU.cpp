//
// Created by Brandon Paul on 4/21/24.
//

#include "CPU.h"

void CPU::incrementCounter() {
    programCounter++;
}

template<typename T>
void CPU::LDA(AddressingMode mode, T value) {
    // Switch based on the addressing mode
    switch (mode) {
        case Immediate:
            LDA_Immediate(static_cast<uint8_t>(value));
            break;
        case ZeroPage:
            LDA_ZeroPage(static_cast<uint8_t>(value));
            break;
        case ZeroPageX:
            LDA_ZeroPageX(static_cast<uint8_t>(value));
            break;
        case IndirectX:
            LDA_IndirectX(static_cast<uint8_t>(value));
            break;
        case IndirectY:
            LDA_IndirectY(static_cast<uint8_t>(value));
            break;
        case Absolute:
            LDA_Absolute(static_cast<uint16_t>(value));
            break;
        case AbsoluteX:
            LDA_AbsoluteX(static_cast<uint16_t>(value));
            break;
        case AbsoluteY:
            LDA_AbsoluteY(static_cast<uint16_t>(value));
            break;
    }

    // Set Flags
    if (accumulator == 0) {
        setFlag(StatusFlag::Zero);
    }

    // if bit 7 of accumulator is set
    if (accumulator & 0x80) {
        setFlag(StatusFlag::Negative);
    }
}

void CPU::LDA_Immediate(uint8_t value) {
    // Load value at memory address into the accumulator
    accumulator = value;
}

void CPU::LDA_ZeroPage(uint8_t address) {
    accumulator = memory[address];
}

void CPU::LDA_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xIndex;

    accumulator = memory[newAddress];
}

void CPU::LDA_Absolute(uint16_t address) {
    accumulator = memory[address];
}

void CPU::LDA_AbsoluteX(uint16_t address) {
    uint16_t newAddress = address + xIndex;

    accumulator = memory[newAddress];
}

void CPU::LDA_AbsoluteY(uint16_t address) {
    uint16_t newAddress = address + yIndex;

    accumulator = memory[newAddress];
}

void CPU::LDA_IndirectX(uint8_t address) {
    uint8_t val = address + xIndex;

    uint8_t lowByte = memory[val];
    uint8_t highByte = memory[val+1];

    // Combine the low and high bytes to form a 16-bit target address
    uint16_t targetAddress = (highByte << 8) | lowByte;

    accumulator = memory[targetAddress];
}

void CPU::LDA_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address+1];

    uint16_t targetAddress = (highByte << 8) | lowByte;

    targetAddress += yIndex;

    accumulator = memory[targetAddress];
}

template<typename T>
void CPU::LDX(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            LDX_Immediate(static_cast<uint8_t>(value));
            break;
        case ZeroPage:
            LDX_ZeroPage(static_cast<uint8_t>(value));
            break;
        case ZeroPageY:
            LDX_ZeroPageY(static_cast<uint8_t>(value));
            break;
        case Absolute:
            LDX_Absolute(static_cast<uint16_t>(value));
            break;
        case AbsoluteY:
            LDX_AbsoluteY(static_cast<uint16_t>(value));
            break;
    }

    // Set Flags
    if (xIndex == 0) {
        setFlag(StatusFlag::Zero);
    }

    // if bit 7 of accumulator is set
    if (xIndex & 0x80) {
        setFlag(StatusFlag::Negative);
    }
}

void CPU::LDX_Immediate(uint8_t value) {
    xIndex = value;
}

void CPU::LDX_ZeroPage(uint8_t address) {
    xIndex = memory[address];
}

void CPU::LDX_ZeroPageY(uint8_t address) {
    uint8_t newAddress = address + yIndex;

    xIndex = memory[newAddress];
}

void CPU::LDX_Absolute(uint16_t address) {
    xIndex = memory[address];
}

void CPU::LDX_AbsoluteY(uint16_t address) {
    uint16_t newAddress = address + yIndex;

    xIndex = memory[newAddress];
}

template<typename T>
void CPU::LDY(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            LDY_Immediate(static_cast<uint8_t>(value));
            break;
        case ZeroPage:
            LDY_ZeroPage(static_cast<uint8_t>(value));
            break;
        case ZeroPageX:
            LDY_ZeroPageX(static_cast<uint8_t>(value));
            break;
        case Absolute:
            LDY_Absolute(static_cast<uint16_t>(value));
            break;
        case AbsoluteX:
            LDY_AbsoluteX(static_cast<uint16_t>(value));
            break;
    }

    // Set Flags
    if (yIndex == 0) {
        setFlag(StatusFlag::Zero);
    }

    // if bit 7 of accumulator is set
    if (yIndex & 0x80) {
        setFlag(StatusFlag::Negative);
    }
}


void CPU::LDY_Immediate(uint8_t value) {
    yIndex = value;
}

void CPU::LDY_ZeroPage(uint8_t address) {
    yIndex = memory[address];
}

void CPU::LDY_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xIndex;

    yIndex = memory[newAddress];
}

void CPU::LDY_Absolute(uint16_t address) {
    yIndex = memory[address];
}

void CPU::LDY_AbsoluteX(uint16_t address) {
    uint16_t newAddress = address + xIndex;

    yIndex = memory[newAddress];
}



