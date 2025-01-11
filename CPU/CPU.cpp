//
// Created by Brandon Paul on 4/21/24.
//

#include "CPU/CPU.h"

// Manually increment PC during cases to add more control to PC since some instructions don't increment
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

        // Changes PC in different ways depending on Negative Flag (Check Method)
        case BPL:
            executeBPL(value);
            break;

        // Doesn't increment PC, sets value during execution
        case BRK:
            executeBRK();
            break;

        case BVC:
            break;

        case BVS:
            break;

        case CLC:
            break;

        case CLD:
            executeCLD();
            programCounter += instruction.byteCount;
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
            executeDEY();
            programCounter += instruction.byteCount;
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
            programCounter += instruction.byteCount;
            break;

        case LDX:
            executeLDX(addressingMode, value);
            programCounter += instruction.byteCount;
            break;

        case LDY:
            executeLDY(addressingMode, value);
            programCounter += instruction.byteCount;
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
            executeSEI();
            programCounter += instruction.byteCount;
            break;

        case STA:
            executeSTA(addressingMode, value);
            programCounter += instruction.byteCount;
            break;

        case STX:
            executeSTX(addressingMode, value);
            programCounter += instruction.byteCount;
            break;

        case STY:
            executeSTY(addressingMode, value);
            programCounter += instruction.byteCount;
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
            executeTXS();
            programCounter += instruction.byteCount;
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
        default:
            cout << "Error with LDA type" << endl;
    }

    // If value is 0
    accumulator == 0 ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);

    // if bit 7 of accumulator is set
    accumulator & BIT_7 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
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
        default:
            cout << "Error with LDX type" << endl;
    }

    // If value is 0
    xRegister == 0 ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);

    // if bit 7 of accumulator is set
    xRegister & BIT_7 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);

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
        default:
            cout << "Error with LDY type" << endl;
    }

    // If value is 0
    yRegister == 0 ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);

    // if bit 7 of accumulator is set
    yRegister & BIT_7 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);

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
            break;
        case ZeroPageX:
            STA_ZeroPageX(static_cast<uint8_t>(value));
            break;
        case Absolute:
            STA_Absolute(static_cast<uint16_t>(value));
            break;
        case AbsoluteX:
            STA_AbsoluteX(static_cast<uint16_t>(value));
            break;
        case AbsoluteY:
            STA_AbsoluteY(static_cast<uint16_t>(value));
            break;
        case IndirectX:
            STA_IndirectX(static_cast<uint8_t>(value));
            break;
        case IndirectY:
            STA_IndirectY(static_cast<uint8_t>(value));
            break;
        default:
            cout << "Error with STA type" << endl;
    }
}

void CPU::STA_ZeroPage(uint8_t address) {
    memory[address] = accumulator;
}

void CPU::STA_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xRegister;
    memory[newAddress] = accumulator;
}

void CPU::STA_Absolute(uint16_t address) {
    memory[address] = accumulator;
}

void CPU::STA_AbsoluteX(uint16_t address) {
    uint16_t newAddress = address + xRegister;
    memory[newAddress] = accumulator;
}

void CPU::STA_AbsoluteY(uint16_t address) {
    uint16_t newAddress = address + yRegister;
    memory[newAddress] = accumulator;
}

void CPU::STA_IndirectX(uint8_t address) {
    uint8_t val = address + xRegister;

    uint8_t lowByte = memory[val];

    uint8_t highByte = memory[val + 1];

    // Combine the low and high bytes to form a 16-bit target address
    uint16_t targetAddress = (highByte << 8) | lowByte;

    memory[targetAddress] = accumulator;
}

void CPU::STA_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];

    uint16_t targetAddress = (highByte << 8) | lowByte;

    targetAddress += yRegister;

    memory[targetAddress] = accumulator;
}


template<typename T>
void CPU::executeSTX(AddressingMode mode, T value) {
    switch (mode) {
        case ZeroPage:
            STX_ZeroPage(static_cast<uint8_t>(value));
            break;
        case ZeroPageY:
            STX_ZeroPageY(static_cast<uint8_t>(value));
            break;
        case Absolute:
            STX_Absolute(static_cast<uint16_t>(value));
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
            break;
        case ZeroPageX:
            STY_ZeroPageX(static_cast<uint8_t>(value));
            break;
        case Absolute:
            STY_Absolute(static_cast<uint16_t>(value));
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

// FIXME: Warning: I've seen different things for the necessity of step 3-4 so if bugs happen, it could be that
/*
 Three things happen during the BRK instruction
 1. The PC+2 is pushed to the stack
 2. A copy of the status register will be pushed to the stack with the break flag set to 1.
 3. Set the interrupt flag on the status register,
 4. Set PC to 0xFFFE 0xFFFF
*/
void CPU::executeBRK() {
    // 1.
    // First calculate PC + 2 (return address)
    uint16_t pcPlusTwo = programCounter + 2;

    // Break PC into high and low bytes
    uint8_t highByte = (pcPlusTwo >> 8) & 0xFF;
    uint8_t lowByte = pcPlusTwo & 0xFF;

    // Push high byte first (due to 6502 being little-endian)
    pushToStack(highByte);

    // Then push low byte
    pushToStack(lowByte);

    // 2.
    uint8_t tmpPStatus = pStatus;
    // Manually do the bitwise operation here so that the original pStatus is not altered
    tmpPStatus |= FLAG_B;
    setMemory(STACK_POINTER_OFFSET + stackPointer, tmpPStatus);
    stackPointer--;

    // 3.
    setFlag(StatusFlag::InterruptDisable);

    // 4.
    lowByte = memory[0xFFFE];
    highByte = memory[0xFFFD];
    // Combine the two bytes together using bit shifting
    uint16_t val = (highByte << 8) | lowByte;

    programCounter = val;
}

/*
 If the zero flag is clear, BNE branches to a nearby location by adding the branch offset to the program counter.
 The offset is signed and has a range of [-128, 127] relative to the first byte after the branch instruction.
*/
//FIXME: Potential Issues
void CPU::executeBPL(uint8_t val) {
    // Increment program counter normally
    programCounter += 2;

    if (!isFlagSet(StatusFlag::Negative)) {
        auto displacement = static_cast<int8_t>(val);
        programCounter += displacement;
    }
}

void CPU::executeSEI() {
    setFlag(StatusFlag::InterruptDisable);
}

void CPU::executeCLD() {
    clearFlag(StatusFlag::Decimal);
}

void CPU::executeTXS() {
    stackPointer = xRegister;
}

void CPU::executeDEY() {
    yRegister -= 1;

    // If value is 0
    yRegister == 0 ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);

    // if bit 7 of accumulator is set
    yRegister & BIT_7 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}




