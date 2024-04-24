//
// Created by Brandon Paul on 4/21/24.
//

#ifndef NESEMULATOR_CPU_H
#define NESEMULATOR_CPU_H

#include <cstdint>
#include "StatusFlag.h"
#include "AddressingMode.h"

class CPU {
private:

    // 16-bit register which points to the next instruction to be executed
    uint16_t programCounter;

    uint8_t stackPointer;

    // Processor Status
    // Composed of six one-bit registers, but we are representing as an enumerator
    StatusFlag pStatus;

    // This performs arithmetic operations
    uint8_t accumulator;

    uint8_t xIndex;

    uint8_t yIndex;

    // Memory storage, 6502 has
    uint8_t memory[65536];

public:

    void incrementCounter();

    void setFlag(StatusFlag flag) {
        pStatus = flag;
    }

    template<typename T>
    void LDA(AddressingMode mode, T value);

    // Load Accumulator - opcode $A9
    void LDA_Immediate(uint8_t value);

    // Load Accumulator - opcode $A5
    void LDA_ZeroPage(uint8_t address);

    // Load Accumulator - opcode $B5
    void LDA_ZeroPageX(uint8_t address);

    // Load Accumulator - opcode $AD
    void LDA_Absolute(uint16_t address);

    // Load Accumulator - opcode $BD
    void LDA_AbsoluteX(uint16_t address);

    // Load Accumulator - opcode $B9
    void LDA_AbsoluteY(uint16_t address);

    // Load Accumulator - opcode $A1
    void LDA_IndirectX(uint8_t address);

    // Load Accumulator - opcode $B1
    void LDA_IndirectY(uint8_t address);

    template<typename T>
    void LDX(AddressingMode mode, T value);

    // Load X Register - opcode $A2
    void LDX_Immediate(uint8_t value);

    // Load X Register - opcode $A6
    void LDX_ZeroPage(uint8_t address);

    // Load X Register - opcode $B6
    void LDX_ZeroPageY(uint8_t address);

    // Load X Register - opcode $AE
    void LDX_Absolute(uint16_t address);

    // Load X Register - opcode $BE
    void LDX_AbsoluteY(uint16_t address);

    template<typename T>
    void LDY(AddressingMode mode, T value);

    // Load Y Register - opcode $A0
    void LDY_Immediate(uint8_t value);

    // Load Y Register - opcode $A4
    void LDY_ZeroPage(uint8_t address);

    // Load Y Register - opcode $B4
    void LDY_ZeroPageX(uint8_t address);

    // Load Y Register - opcode $AC
    void LDY_Absolute(uint16_t address);

    // Load Y Register - opcode $BC
    void LDY_AbsoluteX(uint16_t address);


};


#endif //NESEMULATOR_CPU_H
