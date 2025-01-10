//
// Created by Brandon Paul on 4/21/24.
//

#ifndef NESEMULATOR_CPU_H
#define NESEMULATOR_CPU_H

#include <cstdint>
#include <iostream>

#include "StatusFlag.h"
#include "CPU/OpCode/AddressingMode.h"
#include "CPU/Memory/Memory.h"
#include "System/SystemPart.h"
#include "CPU/OpCode/OpcodeHelper.h"

using namespace std;

#define STACK_POINTER_OFFSET 0x0100

#define FLAG_C (1 << 0)    // Carry
#define FLAG_Z (1 << 1)    // Zero
#define FLAG_I (1 << 2)    // Interrupt Disable
#define FLAG_D (1 << 3)    // Decimal
#define FLAG_B (1 << 4)    // Break
#define FLAG_V (1 << 6)    // Overflow
#define FLAG_N (1 << 7)    // Negative

class CPU final : public SystemPart {
public:
private:
    // 16-bit register which points to the next instruction to be executed
    uint16_t programCounter;

    /*
    The Stack Pointer is an 8-bit register
    which serves as an offset from $0100. The stack works top-down, so when a byte is pushed
    on to the stack, the stack pointer is decremented and when a byte is pulled from the stack,
    the stack pointer is incremented.
    */
    uint8_t stackPointer;

    // Processor Status
    // Each bit in the uint8_t is a separate flag
    uint8_t pStatus;

    // This performs arithmetic operations
    uint8_t accumulator;

    uint8_t xRegister;

    uint8_t yRegister;

    // Memory storage, 6502 has a total of 64 KB of memory (up to a 16-bit address)
    Memory memory = Memory();

    int cycle;

public:

    CPU() : SystemPart() {
        // This is the reset vector, and it should give the starting location of the PC
        // Lower byte starts at 0xFFC and high byte at 0xFFFD, combine
        cycle = 0;

        accumulator = 0;
        xRegister = 0;
        yRegister = 0;
        programCounter = 0;
        pStatus = 0;

        // FROM NES docs:
        // The stack is located at memory locations $0100-$01FF. The stack pointer is an 8-bit register which serves as an offset from $0100.
        // IMPORTANT: When pushing to stack make sure to add offset of $0100.
        // We could just make the stack a 16-bit number however making it 8-bit is more faithful to the hardware. We add the offset because
        // The addresses of the stack can't fit into an 8-bit number
        // Stack should be initialized to 0xFF because it grows top down, when pushing you decrement, when pulling you increment
        stackPointer = 0xFF;
    }

    void initializeProgramCounter() {
        // When ROM is loaded, look at address 0xFFFC & 0xFFFD in order to find reset vector
        uint8_t lsb = memory[0xFFFC]; // LSB of the reset vector
        uint8_t msb = memory[0xFFFD]; // MSB of the reset vector

        // Get the address that the reset vector is pointing to
        uint16_t resetVectorAddress = (msb << 8) | lsb;

        programCounter = resetVectorAddress;
    };

    uint8_t getMemory(uint16_t address) {
        return memory[address];
    }

    void setMemory(uint16_t address, uint8_t value) {
        memory.setMemory(address, value);
    }

    void executeInstruction() {
        const uint8_t currOpcode = getMemory(programCounter);

        // Get all metadata for instruction such as: AddressingMode, Instruction, Bytes, Cycles
        const InstructionMetadata instruction = OpcodeHelper::getInstructionMetadata(currOpcode);

        if (instruction.instruction == Instruction::INVALID || instruction.addressingMode == AddressingMode::UNKNOWN) {
            cerr << "Error reading instruction" << endl;
        }

        // Grab the data from the following bytes depending on instruction
        // With all official opcodes (not counting unofficial) there is max 3 bytes
        if (instruction.byteCount == 2) {
            const uint8_t val = getMemory(programCounter+1);
            delegateInstructionExecution(instruction, val);
        }
        else if (instruction.byteCount == 3) {
            const uint8_t lowByte = getMemory(programCounter+1);
            const uint8_t highByte = getMemory(programCounter+2);
            // Combine the two bytes together using bit shifting
            const uint16_t val = (highByte << 8) | lowByte;

            delegateInstructionExecution(instruction, val);
        }

        // Increment the program counter by the byteCount of the instruction so that it goes to next instruction
        // FIXME: Some instructions don't automatically update programCounter, so I might need to change this
        programCounter += instruction.byteCount;

        // Grabbing the next bytes from memory for the data
        // cycle++;
        incrementPC();
    }

    void step_to(int newCount) override {
        while (cycle < newCount) {
            executeInstruction();
        }
    }

    uint8_t getXRegister() const {
        return xRegister;
    }

    uint8_t getYRegister() const {
        return yRegister;
    }

    uint8_t getAccumulator() const {
        return accumulator;
    }

    void incrementPC() {
        this->programCounter++;
    }

    /*
    Manipulate flags like this:
    Set a flag:
        status |= STATUS_Z;    // Set Zero flag
    */
    void setFlag(StatusFlag flag) {
        switch (flag) {
            case Carry:
                pStatus |= FLAG_C;
                break;
            case Zero:
                pStatus |= FLAG_Z;
                break;
            case InterruptDisable:
                pStatus |= FLAG_I;
                break;
            case Break:
                pStatus |= FLAG_B;
                break;
            case Decimal:
                pStatus |= FLAG_D;
                break;
            case Overflow:
                pStatus |= FLAG_V;
                break;
            case Negative:
                pStatus |= FLAG_N;
                break;
            default:
                cerr << "Unknown flag " << flag << endl;
        }
    }

    /*
    Manipulate flags like this:
    Clear a flag:
        status &= ~STATUS_C;   // Clear Carry flag
    */
    void clearFlag(StatusFlag flag) {
        switch (flag) {
            case Carry:
                pStatus &= ~FLAG_C;
                break;
            case Zero:
                pStatus &= ~FLAG_Z;
                break;
            case InterruptDisable:
                pStatus &= ~FLAG_I;
                break;
            case Break:
                pStatus &= ~FLAG_B;
                break;
            case Decimal:
                pStatus &= ~FLAG_D;
                break;
            case Overflow:
                pStatus &= ~FLAG_V;
                break;
            case Negative:
                pStatus &= ~FLAG_N;
                break;
            default:
                cerr << "Unknown flag " << flag << endl;
        }
    }

    template<typename T>
    void delegateInstructionExecution(InstructionMetadata, T);

    template<typename T>
    void executeLDA(AddressingMode, T);

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
    void executeLDX(AddressingMode, T);

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
    void executeLDY(AddressingMode, T);

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
    void executeSTA(AddressingMode, T);

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
    void executeSTX(AddressingMode, T);

    // Store X Register - opcode $86
    void STX_ZeroPage(uint8_t);

    // Store X Register - opcode $96
    void STX_ZeroPageY(uint8_t);

    // Store X Register - opcode $8E
    void STX_Absolute(uint16_t);

    template<typename T>
    void executeSTY(AddressingMode, T);

    // Store Y Register - opcode $84
    void STY_ZeroPage(uint8_t);

    // Store Y Register - opcode $94
    void STY_ZeroPageX(uint8_t);

    // Store Y Register - opcode $8C
    void STY_Absolute(uint16_t);

    void executeBRK();

};


#endif //NESEMULATOR_CPU_H
