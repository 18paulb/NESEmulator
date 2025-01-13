//
// Created by Brandon Paul on 1/12/25.
//

#include "../CPU.h"


template<typename T>
void CPU::executeDEC(AddressingMode mode, T value) {
    switch (mode) {
        case ZeroPage:
            DEC_ZeroPage(value);
        break;

        case ZeroPageX:
            DEC_ZeroPageX(value);
        break;

        case Absolute:
            DEC_Absolute(value);
        break;

        case AbsoluteX:
            DEC_AbsoluteX(value);
        break;

        default:
            cout << "Invalid addressing mode for DEC" << endl;
    }
}
template void CPU::executeDEC<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeDEC<uint16_t>(AddressingMode addressingMode, uint16_t value);


void CPU::DEC_ZeroPage(uint8_t address) {
    memory[address] -= 1;
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::DEC_ZeroPageX(uint8_t address) {
    memory[address + xRegister] -= 1;
    setZeroAndNegativeFlag(memory[address + xRegister]);
}

void CPU::DEC_Absolute(uint16_t address) {
    memory[address] -= 1;
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::DEC_AbsoluteX(uint16_t address) {
    memory[address + xRegister] -= 1;
    setZeroAndNegativeFlag(memory[address + xRegister]);
}

void CPU::executeDEX() {
    xRegister -= 1;
    setZeroAndNegativeFlag(xRegister);
}

void CPU::executeDEY() {
    yRegister -= 1;
    setZeroAndNegativeFlag(yRegister);
}

template<typename T>
void CPU::executeINC(AddressingMode mode, T value) {
    switch (mode) {
        case ZeroPage:
            INC_ZeroPage(value);
        break;

        case ZeroPageX:
            INC_ZeroPageX(value);
        break;

        case Absolute:
            INC_Absolute(value);
        break;

        case AbsoluteX:
            INC_AbsoluteX(value);
        break;

        default:
            cout << "Invalid addressing mode for DEC" << endl;
    }
}
template void CPU::executeINC<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeINC<uint16_t>(AddressingMode addressingMode, uint16_t value);

void CPU::INC_ZeroPage(uint8_t address) {
    memory[address] += 1;
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::INC_ZeroPageX(uint8_t address) {
    memory[address + xRegister] += 1;
    setZeroAndNegativeFlag(memory[address + xRegister]);
}

void CPU::INC_Absolute(uint16_t address) {
    memory[address] += 1;
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::INC_AbsoluteX(uint16_t address) {
    memory[address + xRegister] += 1;
    setZeroAndNegativeFlag(memory[address + xRegister]);
}

void CPU::executeINX() {
    xRegister += 1;
    setZeroAndNegativeFlag(xRegister);
}

void CPU::executeINY() {
    yRegister += 1;
    setZeroAndNegativeFlag(yRegister);
}