//
// Created by Brandon Paul on 1/12/25.
//

#include "../CPU.h"

template<typename T>
void CPU::executeJMP(AddressingMode mode, T value) {
    switch (mode) {
        case Absolute:
            JMP_Absolute(value);
        break;

        case Indirect:
            JMP_Indirect(value);
        break;

        default:
            cout << "Invalid addressing mode for JMP" << endl;
    }
}
template void CPU::executeJMP<uint8_t>(AddressingMode addressingMode, uint8_t value);
template void CPU::executeJMP<uint16_t>(AddressingMode addressingMode, uint16_t value);


void CPU::JMP_Absolute(uint16_t address) {
    programCounter = memory[address];
}

/*
    Unfortunately, because of a CPU bug, if this 2-byte variable has an address ending in $FF and thus crosses a page,
    then the CPU fails to increment the page when reading the second byte and thus reads the wrong address.
    For example, JMP ($03FF) reads $03FF and $0300 instead of $0400.
    Care should be taken to ensure this variable does not cross a page.
*/
void CPU::JMP_Indirect(uint16_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    uint16_t targetAddress = highByte << 8 | lowByte;

    programCounter = memory[targetAddress];
}

/*
    Notably, the return address on the stack points 1 byte before the start of the next instruction,
    rather than directly at the instruction.
    This is because RTS increments the program counter before the next instruction is fetched.
*/
void CPU::executeJSR(uint16_t address) {
    // This is the return address that we will be pushing to the stack, 1 byte LESS than the start
    // of the next instruction
    uint16_t returnAddress = programCounter - 1;

    // Break PC into high and low bytes
    uint8_t highByte = (returnAddress >> 8) & 0xFF;
    uint8_t lowByte = returnAddress & 0xFF;

    // Push high byte first (due to 6502 being little-endian)
    pushToStack(highByte);
    pushToStack(lowByte);

    programCounter = address;
}

void CPU::executeRTS() {
    uint8_t lowByte = popFromStack();
    uint8_t highByte = popFromStack();

    programCounter = (highByte << 8) | lowByte;
    programCounter += 1;
}
