//
// Created by Brandon Paul on 4/21/24.
//

#ifndef NESEMULATOR_CPU_H
#define NESEMULATOR_CPU_H

#include <cstdint>
#include "StatusFlag.h"
#include "AddressingMode.h"
#include "CPU/Memory/Memory.h"

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

    uint8_t xRegister;

    uint8_t yRegister;

    // Memory storage, 6502 has a total of 64 KB of memory (up to a 16-bit address)
    Memory* memory;

public:

    CPU() {
        // This is the reset vector, and it should give the starting location of the PC
        // Lower byte starts at 0xFFC and high byte at 0xFFFD, combine
        memory = new Memory();
//        programCounter = memory.getMemory(0xFFFC) | memory.getMemory(0xFFFC) << 8;

        // Just for now start it at the beginning of PRG_ROM loaded data
        programCounter = 0x8000;

        // FROM NES docs:
        // The stack is located at memory locations $0100-$01FF. The stack pointer is an 8-bit register which serves as an offset from $0100.
        stackPointer = 0x0100;
    }

    Memory* getMemory() {
        return memory;
    }

    void executeInstruction();

    uint8_t peek(uint16_t address) {
        return memory->getMemory(address);
    }

    uint8_t getXRegister() {
        return xRegister;
    }

    uint8_t getYRegister() {
        return yRegister;
    }

    uint8_t getAccumulator() {
        return accumulator;
    }

    void incrementCounter();

    void setFlag(StatusFlag flag) {
        pStatus = flag;
    }

    template<typename T>
    void LDA(AddressingMode, T);

    // Load Accumulator - opcode $A9
    void LDA_Immediate(uint8_t);

    // Load Accumulator - opcode $A5
    void LDA_ZeroPage(uint8_t);

    // Load Accumulator - opcode $B5
    void LDA_ZeroPageX(uint8_t);

    // Load Accumulator - opcode $AD
    void LDA_Absolute(uint16_t);

    // Load Accumulator - opcode $BD
    void LDA_AbsoluteX(uint16_t);

    // Load Accumulator - opcode $B9
    void LDA_AbsoluteY(uint16_t);

    // Load Accumulator - opcode $A1
    void LDA_IndirectX(uint8_t);

    // Load Accumulator - opcode $B1
    void LDA_IndirectY(uint8_t);

    template<typename T>
    void LDX(AddressingMode, T);

    // Load X Register - opcode $A2
    void LDX_Immediate(uint8_t);

    // Load X Register - opcode $A6
    void LDX_ZeroPage(uint8_t);

    // Load X Register - opcode $B6
    void LDX_ZeroPageY(uint8_t);

    // Load X Register - opcode $AE
    void LDX_Absolute(uint16_t);

    // Load X Register - opcode $BE
    void LDX_AbsoluteY(uint16_t);

    template<typename T>
    void LDY(AddressingMode, T);

    // Load Y Register - opcode $A0
    void LDY_Immediate(uint8_t);

    // Load Y Register - opcode $A4
    void LDY_ZeroPage(uint8_t);

    // Load Y Register - opcode $B4
    void LDY_ZeroPageX(uint8_t);

    // Load Y Register - opcode $AC
    void LDY_Absolute(uint16_t);

    // Load Y Register - opcode $BC
    void LDY_AbsoluteX(uint16_t);

    template<typename T>
    void STA(AddressingMode, T);

    // Store Accumulator - opcode $85
    void STA_ZeroPage(uint8_t);

    // Store Accumulator - opcode $95
    void STA_ZeroPageX(uint8_t);

    // Store Accumulator - opcode $8D
    void STA_Absolute(uint16_t);

    // Store Accumulator - opcode $9D
    void STA_AbsoluteX(uint16_t);

    // Store Accumulator - opcode $99
    void STA_AbsoluteY(uint16_t);

    // Store Accumulator - opcode $81
    void STA_IndirectX(uint8_t);

    // Store Accumulator - opcode $91
    void STA_IndirectY(uint8_t);

    template<typename T>
    void STX(AddressingMode, T);

    // Store X Register - opcode $86
    void STX_ZeroPage(uint8_t);

    // Store X Register - opcode $96
    void STX_ZeroPageY(uint8_t);

    // Store X Register - opcode $8E
    void STX_Absolute(uint16_t);

    template<typename T>
    void STY(AddressingMode, T);

    void STY_ZeroPage(uint8_t);

    void STY_ZeroPageX(uint8_t);

    void STY_Absolute(uint16_t);

};


#endif //NESEMULATOR_CPU_H
