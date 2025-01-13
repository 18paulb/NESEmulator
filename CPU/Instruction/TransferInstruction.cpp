//
// Created by Brandon Paul on 1/12/25.
//

#include "../CPU.h"


//template<typename T>
//void TransferInstruction::executeLDA(AddressingMode mode, T value) {
//    // Switch based on the addressing mode
//    switch (mode) {
//        case Immediate:
//            LDA_Immediate(static_cast<uint8_t>(value));
//            break;
//        case ZeroPage:
//            LDA_ZeroPage(static_cast<uint8_t>(value));
//            break;
//        case ZeroPageX:
//            LDA_ZeroPageX(static_cast<uint8_t>(value));
//            break;
//        case IndirectX:
//            LDA_IndirectX(static_cast<uint8_t>(value));
//            break;
//        case IndirectY:
//            LDA_IndirectY(static_cast<uint8_t>(value));
//            break;
//        case Absolute:
//            LDA_Absolute(static_cast<uint16_t>(value));
//            break;
//        case AbsoluteX:
//            LDA_AbsoluteX(static_cast<uint16_t>(value));
//            break;
//        case AbsoluteY:
//            LDA_AbsoluteY(static_cast<uint16_t>(value));
//            break;
//        default:
//            cout << "Error with LDA type" << endl;
//    }
//
//    cpu.setZeroAndNegativeFlag(cpu.getAccumulator());
//}
//
//void TransferInstruction::LDA_Immediate(uint8_t value) {
//    // Load value at memory address into the accumulator
//    cpu.setAccumulator(value);
//}
//
//void TransferInstruction::LDA_ZeroPage(uint8_t address) {
//    cpu.setAccumulator(cpu[address]);
//}
//
//void TransferInstruction::LDA_ZeroPageX(uint8_t address) {
//    uint8_t newAddress = address + cpu.getXRegister();
//    cpu.setAccumulator(cpu[newAddress]);
//}
//
//void TransferInstruction::LDA_Absolute(uint16_t address) {
//    cpu.setAccumulator(cpu[address]);
//}
//
//void TransferInstruction::LDA_AbsoluteX(uint16_t address) {
//    uint16_t newAddress = address + cpu.getXRegister();
//    cpu.setAccumulator(cpu[newAddress]);
//}
//
//void TransferInstruction::LDA_AbsoluteY(uint16_t address) {
//    uint16_t newAddress = address + cpu.getYRegister();
//    cpu.setAccumulator(cpu[newAddress]);
//}
//
//void TransferInstruction::LDA_IndirectX(uint8_t address) {
//    uint8_t val = address + cpu.getXRegister();
//    uint8_t lowByte = cpu[val];
//    uint8_t highByte = cpu[val + 1];
//
//    // Combine the low and high bytes to form a 16-bit target address
//    uint16_t targetAddress = (highByte << 8) | lowByte;
//    cpu.setAccumulator(cpu[targetAddress]);
//}
//
//void TransferInstruction::LDA_IndirectY(uint8_t address) {
//    uint8_t lowByte = cpu[address];
//    uint8_t highByte = cpu[address + 1];
//    uint16_t targetAddress = (highByte << 8) | lowByte;
//    targetAddress += cpu.getYRegister();
//
//    cpu.setAccumulator(cpu[targetAddress]);
//}
//
//template<typename T>
//void TransferInstruction::executeLDX(AddressingMode mode, T value) {
//    switch (mode) {
//        case Immediate:
//            LDX_Immediate(static_cast<uint8_t>(value));
//            break;
//        case ZeroPage:
//            LDX_ZeroPage(static_cast<uint8_t>(value));
//            break;
//        case ZeroPageY:
//            LDX_ZeroPageY(static_cast<uint8_t>(value));
//            break;
//        case Absolute:
//            LDX_Absolute(static_cast<uint16_t>(value));
//            break;
//        case AbsoluteY:
//            LDX_AbsoluteY(static_cast<uint16_t>(value));
//            break;
//        default:
//            cout << "Error with LDX type" << endl;
//    }
//
//    cpu.setZeroAndNegativeFlag(cpu.getXRegister());
//}
//
//void TransferInstruction::LDX_Immediate(uint8_t value) {
//    cpu.setXRegister(value);
//}
//
//void TransferInstruction::LDX_ZeroPage(uint8_t address) {
//    cpu.setXRegister(cpu[address]);
//}
//
//void TransferInstruction::LDX_ZeroPageY(uint8_t address) {
//    uint8_t newAddress = address + cpu.getYRegister();
//    cpu.setXRegister(cpu[newAddress]);
//}
//
//void TransferInstruction::LDX_Absolute(uint16_t address) {
//    cpu.setXRegister(cpu[address]);
//}
//
//void TransferInstruction::LDX_AbsoluteY(uint16_t address) {
//    uint16_t newAddress = address + cpu.getYRegister();
//    cpu.setXRegister(cpu[newAddress]);
//}
//
//template<typename T>
//void TransferInstruction::executeLDY(AddressingMode mode, T value) {
//    switch (mode) {
//        case Immediate:
//            LDY_Immediate(static_cast<uint8_t>(value));
//            break;
//        case ZeroPage:
//            LDY_ZeroPage(static_cast<uint8_t>(value));
//            break;
//        case ZeroPageX:
//            LDY_ZeroPageX(static_cast<uint8_t>(value));
//            break;
//        case Absolute:
//            LDY_Absolute(static_cast<uint16_t>(value));
//            break;
//        case AbsoluteX:
//            LDY_AbsoluteX(static_cast<uint16_t>(value));
//            break;
//        default:
//            cout << "Error with LDY type" << endl;
//    }
//
//    cpu.setZeroAndNegativeFlag(cpu.getYRegister());
//}
//
//
//void TransferInstruction::LDY_Immediate(uint8_t value) {
//    cpu.setYRegister(value);
//}
//
//void TransferInstruction::LDY_ZeroPage(uint8_t address) {
//    cpu.setYRegister(cpu[address]);
//}
//
//void TransferInstruction::LDY_ZeroPageX(uint8_t address) {
//    uint8_t newAddress = address + cpu.getXRegister();
//    cpu.setYRegister(cpu[newAddress]);
//}
//
//void TransferInstruction::LDY_Absolute(uint16_t address) {
//    cpu.setYRegister(cpu.getMemory(address));
//}
//
//void TransferInstruction::LDY_AbsoluteX(uint16_t address) {
//    uint16_t newAddress = address + cpu.getXRegister();
//    cpu.setYRegister(cpu.getMemory(newAddress));
//}

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

    setZeroAndNegativeFlag(accumulator);
}

template void CPU::executeLDA<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeLDA<uint16_t>(AddressingMode addressingMode, uint16_t value);

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

    setZeroAndNegativeFlag(xRegister);
}

template void CPU::executeLDX<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeLDX<uint16_t>(AddressingMode addressingMode, uint16_t value);

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

    setZeroAndNegativeFlag(yRegister);
}

template void CPU::executeLDY<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeLDY<uint16_t>(AddressingMode addressingMode, uint16_t value);

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

template void CPU::executeSTA<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeSTA<uint16_t>(AddressingMode addressingMode, uint16_t value);

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

template void CPU::executeSTX<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeSTX<uint16_t>(AddressingMode addressingMode, uint16_t value);

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

template void CPU::executeSTY<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeSTY<uint16_t>(AddressingMode addressingMode, uint16_t value);

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

void CPU::executeTAX() {
    xRegister = accumulator;
    setZeroAndNegativeFlag(xRegister);
}

void CPU::executeTAY() {
    yRegister = accumulator;
    setZeroAndNegativeFlag(yRegister);
}

void CPU::executeTSX() {
    xRegister = stackPointer;
    setZeroAndNegativeFlag(xRegister);
}

void CPU::executeTXA() {
    accumulator = xRegister;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::executeTXS() {
    stackPointer = xRegister;
}

void CPU::executeTYA() {
    accumulator = yRegister;
    setZeroAndNegativeFlag(accumulator);
}
