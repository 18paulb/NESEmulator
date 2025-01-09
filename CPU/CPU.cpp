//
// Created by Brandon Paul on 4/21/24.
//

#include "CPU/CPU.h"

template<typename T>
void CPU::delegateInstructionExecution(InstructionMetadata instruction, T value) {
    Instruction instructionType = instruction.instruction;
    AddressingMode addressingMode = instruction.addressingMode;
    switch (instructionType) {

        case ADC:
            break;

        case AND:
            break;

        case ASL:
            break;

        case BCC:
            break;

        case BCS:
            break;

        case BEQ:
            break;

        case BIT:
            break;

        case BMI:
            break;

        case BNE:
            break;

        case BPL:
            break;

        case BRK:
            break;

        case BVC:
            break;

        case BVS:
            break;

        case CLC:
            break;

        case CLD:
            break;

        case CLI:
            break;

        case CLV:
            break;

        case CMP:
            break;

        case CPX:
            break;

        case CPY:
            break;

        case DEC:
            break;

        case DEX:
            break;

        case DEY:
            break;

        case EOR:
            break;

        case INC:
            break;

        case INX:
            break;

        case INY:
            break;

        case JMP:
            break;

        case JSR:
            break;

        case LDA:
            executeLDA(addressingMode, value);
            break;

        case LDX:
            executeLDX(addressingMode, value);
            break;

        case LDY:
            executeLDY(addressingMode, value);
            break;

        case LSR:
            break;

        case NOP:
            break;

        case ORA:
            break;

        case PHA:
            break;

        case PHP:
            break;

        case PLA:
            break;

        case PLP:
            break;

        case ROL:
            break;

        case ROR:
            break;

        case RTI:
            break;

        case RTS:
            break;

        case SBC:
            break;

        case SEC:
            break;

        case SED:
            break;

        case SEI:
            break;

        case STA:
            executeSTA(addressingMode, value);
            break;

        case STX:
            executeSTX(addressingMode, value);
            break;

        case STY:
            executeSTY(addressingMode, value);
            break;

        case TAX:
            break;

        case TAY:
            break;
        case TSX:
            break;

        case TXA:
            break;

        case TXS:
            break;

        case TYA:
            break;

        default:
            cout << "Invalid" << endl;
    }
}

template void CPU::delegateInstructionExecution<uint8_t>(InstructionMetadata, uint8_t);
template void CPU::delegateInstructionExecution<uint16_t>(InstructionMetadata, uint16_t);

template<typename T>
void CPU::executeLDA(AddressingMode mode, T value) {
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
        default:
            cout << "Error with LDA type" << endl;
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
    uint8_t newAddress = address + xRegister;

    accumulator = memory[newAddress];
}

void CPU::LDA_Absolute(uint16_t address) {
    accumulator = memory[address];
}

void CPU::LDA_AbsoluteX(uint16_t address) {
    uint16_t newAddress = address + xRegister;

    accumulator = memory[newAddress];
}

void CPU::LDA_AbsoluteY(uint16_t address) {
    uint16_t newAddress = address + yRegister;

    accumulator = memory[newAddress];
}

void CPU::LDA_IndirectX(uint8_t address) {
    uint8_t val = address + xRegister;

    uint8_t lowByte = memory[val];

    uint8_t highByte = memory[val + 1];

    // Combine the low and high bytes to form a 16-bit target address
    uint16_t targetAddress = (highByte << 8) | lowByte;

    accumulator = memory[targetAddress];
}

void CPU::LDA_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];

    uint16_t targetAddress = (highByte << 8) | lowByte;

    targetAddress += yRegister;

    accumulator = memory[targetAddress];
}

template<typename T>
void CPU::executeLDX(AddressingMode mode, T value) {
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
        default:
            cout << "Error with LDX type" << endl;
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
    xRegister = memory[address];
}

void CPU::LDX_ZeroPageY(uint8_t address) {
    uint8_t newAddress = address + yRegister;

    xRegister = memory[newAddress];
}

void CPU::LDX_Absolute(uint16_t address) {
    xRegister = memory[address];
}

void CPU::LDX_AbsoluteY(uint16_t address) {
    uint16_t newAddress = address + yRegister;

    xRegister = memory[newAddress];
}

template<typename T>
void CPU::executeLDY(AddressingMode mode, T value) {
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
        default:
            cout << "Error with LDY type" << endl;
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
    yRegister = memory[address];
}

void CPU::LDY_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xRegister;

    yRegister = memory[newAddress];
}

void CPU::LDY_Absolute(uint16_t address) {
    yRegister = memory[address];
}

void CPU::LDY_AbsoluteX(uint16_t address) {
    uint16_t newAddress = address + xRegister;

    yRegister = memory[newAddress];
}

template<typename T>
void CPU::executeSTA(AddressingMode mode, T value) {
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
        default:
            cout << "Error with STA type" << endl;
    }
}

void CPU::STA_ZeroPage(uint8_t address) {
    memory.setMemory(address, accumulator);
}

void CPU::STA_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xRegister;

    memory.setMemory(newAddress, accumulator);
}

void CPU::STA_Absolute(uint16_t address) {
    memory.setMemory(address, accumulator);
}

void CPU::STA_AbsoluteX(uint16_t address) {
    uint16_t newAddress = address + xRegister;

    memory.setMemory(newAddress, accumulator);
}

void CPU::STA_AbsoluteY(uint16_t address) {
    uint16_t newAddress = address + yRegister;

    memory.setMemory(newAddress, accumulator);
}

void CPU::STA_IndirectX(uint8_t address) {
    uint8_t val = address + xRegister;

    uint8_t lowByte = memory[val];

    uint8_t highByte = memory[val + 1];

    // Combine the low and high bytes to form a 16-bit target address
    uint16_t targetAddress = (highByte << 8) | lowByte;

    memory.setMemory(targetAddress, accumulator);
}

void CPU::STA_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];

    uint16_t targetAddress = (highByte << 8) | lowByte;

    targetAddress += yRegister;

    memory.setMemory(targetAddress, accumulator);
}


template<typename T>
void CPU::executeSTX(AddressingMode mode, T value) {
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
        default:
            cout << "Error with STX type" << endl;
    }
}

void CPU::STX_ZeroPage(uint8_t address) {
    memory.setMemory(address, xRegister);
}

void CPU::STX_ZeroPageY(uint8_t address) {
    uint8_t newAddress = address + yRegister;

    memory.setMemory(newAddress, xRegister);
}

void CPU::STX_Absolute(uint16_t address) {
    memory.setMemory(address, xRegister);
}


template<typename T>
void CPU::executeSTY(AddressingMode mode, T value) {
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
        default:
            cout << "Error with STY type" << endl;
    }
}


void CPU::STY_ZeroPage(uint8_t address) {
    memory.setMemory(address, yRegister);
}

void CPU::STY_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xRegister;

    memory.setMemory(newAddress, yRegister);
}

void CPU::STY_Absolute(uint16_t address) {
    memory.setMemory(address, yRegister);
}



