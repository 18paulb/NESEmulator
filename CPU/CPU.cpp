//
// Created by Brandon Paul on 4/21/24.
//

#include "CPU/CPU.h"

void CPU::incrementCounter() {
    programCounter++;
}

template<typename T>
void CPU::LDA(AddressingMode mode, T value) {
    // Switch based on the addressing mode
    switch (mode) {
        case Immediate:
            LDA_Immediate(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case ZeroPage:
            LDA_ZeroPage(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case ZeroPageX:
            LDA_ZeroPageX(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case IndirectX:
            LDA_IndirectX(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case IndirectY:
            LDA_IndirectY(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case Absolute:
            LDA_Absolute(static_cast<uint16_t>(value));
            programCounter += 3;
            break;
        case AbsoluteX:
            LDA_AbsoluteX(static_cast<uint16_t>(value));
            programCounter += 3;
            break;
        case AbsoluteY:
            LDA_AbsoluteY(static_cast<uint16_t>(value));
            programCounter += 3;
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
    accumulator = memory->getMemory(address);
}

void CPU::LDA_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xRegister;

    accumulator = memory->getMemory(newAddress);
}

void CPU::LDA_Absolute(uint16_t address) {
    accumulator = memory->getMemory(address);
}

void CPU::LDA_AbsoluteX(uint16_t address) {
    uint16_t newAddress = address + xRegister;

    accumulator = memory->getMemory(newAddress);
}

void CPU::LDA_AbsoluteY(uint16_t address) {
    uint16_t newAddress = address + yRegister;

    accumulator = memory->getMemory(newAddress);
}

void CPU::LDA_IndirectX(uint8_t address) {
    uint8_t val = address + xRegister;

    uint8_t lowByte = memory->getMemory(val);

    uint8_t highByte = memory->getMemory(val + 1);

    // Combine the low and high bytes to form a 16-bit target address
    uint16_t targetAddress = (highByte << 8) | lowByte;

    accumulator = memory->getMemory(targetAddress);
}

void CPU::LDA_IndirectY(uint8_t address) {
    uint8_t lowByte = memory->getMemory(address);
    uint8_t highByte = memory->getMemory(address + 1);

    uint16_t targetAddress = (highByte << 8) | lowByte;

    targetAddress += yRegister;

    accumulator = memory->getMemory(targetAddress);
}

template<typename T>
void CPU::LDX(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            LDX_Immediate(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case ZeroPage:
            LDX_ZeroPage(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case ZeroPageY:
            LDX_ZeroPageY(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case Absolute:
            LDX_Absolute(static_cast<uint16_t>(value));
            programCounter += 3;
            break;
        case AbsoluteY:
            LDX_AbsoluteY(static_cast<uint16_t>(value));
            programCounter += 3;
            break;
    }

    // Set Flags
    if (xRegister == 0) {
        setFlag(StatusFlag::Zero);
    }

    // if bit 7 of accumulator is set
    if (xRegister & 0x80) {
        setFlag(StatusFlag::Negative);
    }
}

void CPU::LDX_Immediate(uint8_t value) {
    xRegister = value;
}

void CPU::LDX_ZeroPage(uint8_t address) {
    xRegister = memory->getMemory(address);
}

void CPU::LDX_ZeroPageY(uint8_t address) {
    uint8_t newAddress = address + yRegister;

    xRegister = memory->getMemory(newAddress);
}

void CPU::LDX_Absolute(uint16_t address) {
    xRegister = memory->getMemory(address);
}

void CPU::LDX_AbsoluteY(uint16_t address) {
    uint16_t newAddress = address + yRegister;

    xRegister = memory->getMemory(newAddress);
}

template<typename T>
void CPU::LDY(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            LDY_Immediate(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case ZeroPage:
            LDY_ZeroPage(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case ZeroPageX:
            LDY_ZeroPageX(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case Absolute:
            LDY_Absolute(static_cast<uint16_t>(value));
            programCounter += 3;
            break;
        case AbsoluteX:
            LDY_AbsoluteX(static_cast<uint16_t>(value));
            programCounter += 3;
            break;
    }

    // Set Flags
    if (yRegister == 0) {
        setFlag(StatusFlag::Zero);
    }

    // if bit 7 of accumulator is set
    if (yRegister & 0x80) {
        setFlag(StatusFlag::Negative);
    }
}


void CPU::LDY_Immediate(uint8_t value) {
    yRegister = value;
}

void CPU::LDY_ZeroPage(uint8_t address) {
    yRegister = memory->getMemory(address);
}

void CPU::LDY_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xRegister;

    yRegister = memory->getMemory(newAddress);
}

void CPU::LDY_Absolute(uint16_t address) {
    yRegister = memory->getMemory(address);
}

void CPU::LDY_AbsoluteX(uint16_t address) {
    uint16_t newAddress = address + xRegister;

    yRegister = memory->getMemory(newAddress);
}

template<typename T>
void CPU::STA(AddressingMode mode, T value) {
    switch (mode) {
        case ZeroPage:
            STA_ZeroPage(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case ZeroPageX:
            STA_ZeroPageX(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case Absolute:
            STA_Absolute(static_cast<uint16_t>(value));
            programCounter += 3;
            break;
        case AbsoluteX:
            STA_AbsoluteX(static_cast<uint16_t>(value));
            programCounter += 3;
            break;
        case AbsoluteY:
            STA_AbsoluteY(static_cast<uint16_t>(value));
            programCounter += 3;
            break;
        case IndirectX:
            STA_IndirectX(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case IndirectY:
            STA_IndirectY(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
    }
}

void CPU::STA_ZeroPage(uint8_t address) {
    memory->setMemory(address, accumulator);
}

void CPU::STA_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xRegister;

    memory->setMemory(newAddress, accumulator);
}

void CPU::STA_Absolute(uint16_t address) {
    memory->setMemory(address, accumulator);
}

void CPU::STA_AbsoluteX(uint16_t address) {
    uint16_t newAddress = address + xRegister;

    memory->setMemory(newAddress, accumulator);
}

void CPU::STA_AbsoluteY(uint16_t address) {
    uint16_t newAddress = address + yRegister;

    memory->setMemory(newAddress, accumulator);
}

void CPU::STA_IndirectX(uint8_t address) {
    uint8_t val = address + xRegister;

    uint8_t lowByte = memory->getMemory(val);

    uint8_t highByte = memory->getMemory(val + 1);

    // Combine the low and high bytes to form a 16-bit target address
    uint16_t targetAddress = (highByte << 8) | lowByte;

    memory->setMemory(targetAddress, accumulator);
}

void CPU::STA_IndirectY(uint8_t address) {
    uint8_t lowByte = memory->getMemory(address);
    uint8_t highByte = memory->getMemory(address + 1);

    uint16_t targetAddress = (highByte << 8) | lowByte;

    targetAddress += yRegister;

    memory->setMemory(targetAddress, accumulator);
}


template<typename T>
void CPU::STX(AddressingMode mode, T value) {
    switch (mode) {
        case ZeroPage:
            STX_ZeroPage(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case ZeroPageY:
            STX_ZeroPageY(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case Absolute:
            STX_Absolute(static_cast<uint16_t>(value));
            programCounter += 3;
            break;
    }
}

void CPU::STX_ZeroPage(uint8_t address) {
    memory->setMemory(address, xRegister);
}

void CPU::STX_ZeroPageY(uint8_t address) {
    uint8_t newAddress = address + yRegister;

    memory->setMemory(newAddress, xRegister);
}

void CPU::STX_Absolute(uint16_t address) {
    memory->setMemory(address, xRegister);
}


template<typename T>
void CPU::STY(AddressingMode mode, T value) {
    switch (mode) {
        case ZeroPage:
            STY_ZeroPage(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case ZeroPageX:
            STY_ZeroPageX(static_cast<uint8_t>(value));
            programCounter += 2;
            break;
        case Absolute:
            STY_Absolute(static_cast<uint16_t>(value));
            programCounter += 3;
            break;
    }
}


void CPU::STY_ZeroPage(uint8_t address) {
    memory->setMemory(address, yRegister);
}

void CPU::STY_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xRegister;

    memory->setMemory(newAddress, yRegister);
}

void CPU::STY_Absolute(uint16_t address) {
    memory->setMemory(address, yRegister);
}



