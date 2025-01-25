//
// Created by Brandon Paul on 4/21/24.
//

#ifndef NESEMULATOR_CPU_H
#define NESEMULATOR_CPU_H

#include <cstdint>
#include <iostream>

#include "StatusFlag.h"
#include "CPU/Opcode/AddressingMode.h"
#include "CPU/Memory/Memory.h"
#include "System/SystemPart.h"
#include "CPU/Opcode/OpcodeHelper.h"

using namespace std;

#define STACK_POINTER_OFFSET 0x0100

#define FLAG_C (1 << 0)    // Carry
#define FLAG_Z (1 << 1)    // Zero
#define FLAG_I (1 << 2)    // Interrupt Disable
#define FLAG_D (1 << 3)    // Decimal
#define FLAG_B (1 << 4)    // Break
#define FLAG_EXTRA (1 << 5) // Extra Bit
#define FLAG_V (1 << 6)    // Overflow
#define FLAG_N (1 << 7)    // Negative

#define BIT_7 0x80

// bit is 0-indexed
#define GET_BIT(value, bit) ((value >> (bit)) & 0b00000001)

class CPU final : public SystemPart {
public:
private:
    // 16-bit register which points to the next instruction to be executed
    uint16_t programCounter;

    /*
    The Stack Pointer is an 8-bit register is offset from $0100.
    The stack works top-down, so when a byte is pushed on to the stack, the stack pointer is decremented
    and when a byte is pulled from the stack, the stack pointer is incremented.
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
        cycle = 0;

        accumulator = 0;
        xRegister = 0;
        yRegister = 0;
        programCounter = 0;
        pStatus = 0;
        setFlag(StatusFlag::EXTRA);

        // FROM NES docs:
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
        const uint8_t currOpcode = getMemory(programCounter++);

        // Get all metadata for instruction such as: AddressingMode, Instruction, Bytes, Cycles
        const InstructionMetadata instruction = OpcodeHelper::getInstructionMetadata(currOpcode);

        if (instruction.instruction == Instruction::INVALID || instruction.addressingMode == AddressingMode::UNKNOWN) {
            cerr << "Error reading instruction" << endl;
        }

        cout << toString(instruction.instruction) << " " << toString(instruction.addressingMode) << endl;

        // Grab the data from the following bytes depending on instruction
        // With all official opcodes (not counting unofficial) there is max 3 bytes
        if (instruction.byteCount == 1) {
            // Don't pass in a value, default 0.
            uint8_t placeholder = 0;
            delegateInstructionExecution(instruction, placeholder);
        }
        else if (instruction.byteCount == 2) {
            const uint8_t val = getMemory(programCounter++);
            delegateInstructionExecution(instruction, val);
        }
        else if (instruction.byteCount == 3) {
            const uint8_t lowByte = getMemory(programCounter++);
            const uint8_t highByte = getMemory(programCounter++);
            // Combine the two bytes together using bit shifting
            const uint16_t val = (highByte << 8) | lowByte;

            delegateInstructionExecution(instruction, val);
        }

        // Grabbing the next bytes from memory for the data
        // cycle++;
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

    void pushToStack(uint8_t value) {
        memory[STACK_POINTER_OFFSET + stackPointer--] = value;
    }

    uint8_t popFromStack() {
        return memory[STACK_POINTER_OFFSET + ++stackPointer];
    }

    /*
    Manipulate flags like this:
    Set a flag:
        status |= STATUS_Z;    // Set Zero flag
    */
    void setFlag(StatusFlag);

    /*
    Manipulate flags like this:
    Clear a flag:
        status &= ~STATUS_C;   // Clear Carry flag
    */
    void clearFlag(StatusFlag flag);

    bool isFlagSet(StatusFlag flag) const;

    // This is a pretty specific function but it is used a decent amount
    // Whenever the accumulator, xRegister, or yRegister change values, make sure to update Zero and Negative flags
    void setZeroAndNegativeFlag(uint8_t val);


    // Everything below this strictly deals with instructions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename T>
    void delegateInstructionExecution(InstructionMetadata, T);

    template<typename T>
    void executeADC(AddressingMode, T);

    // Add with Carry - opcode $69
    void ADC_Immediate(uint8_t);

    // Add with Carry - opcode $65
    void ADC_ZeroPage(uint8_t);

    // Add with Carry - opcode $75
    void ADC_ZeroPageX(uint8_t);

    // Add with Carry - opcode $6D
    void ADC_Absolute(uint16_t);

    // Add with Carry - opcode $7D
    void ADC_AbsoluteX(uint16_t);

    // Add with Carry - opcode $79
    void ADC_AbsoluteY(uint16_t);

    // Add with Carry - opcode $61
    void ADC_IndirectX(uint8_t);

    // Add with Carry - opcode $71
    void ADC_IndirectY(uint8_t);

    template<typename T>
    void executeAND(AddressingMode, T);

    // Bitwise AND - opcode $29
    void AND_Immediate(uint8_t);

    // Bitwise AND - opcode $25
    void AND_ZeroPage(uint8_t);

    // Bitwise AND - opcode $35
    void AND_ZeroPageX(uint8_t);

    // Bitwise AND - opcode $2D
    void AND_Absolute(uint16_t);

    // Bitwise AND - opcode $3D
    void AND_AbsoluteX(uint16_t);

    // Bitwise AND - opcode $39
    void AND_AbsoluteY(uint16_t);

    // Bitwise AND - opcode $21
    void AND_IndirectX(uint8_t);

    // Bitwise AND - opcode $31
    void AND_IndirectY(uint8_t);

    template<typename T>
    void executeASL(AddressingMode, T);

    // Arithmetic Shift Left - opcode $0A
    void ASL_Accumulator();

    // Arithmetic Shift Left - opcode $06
    void ASL_ZeroPage(uint8_t);

    // Arithmetic Shift Left - opcode $16
    void ASL_ZeroPageX(uint8_t);

    // Arithmetic Shift Left - opcode $0E
    void ASL_Absolute(uint16_t);

    // Arithmetic Shift Left - opcode $1E
    void ASL_AbsoluteX(uint16_t);

    // Branch if Carry Clear - opcode $90
    void executeBCC(uint8_t);

    // Branch if Carry Set - opcode $B0
    void executeBCS(uint8_t);

    // Branch if Equal - opcode $F0
    void executeBEQ(uint8_t);

    template<typename T>
    // Bit Test - opcodes $24 and $2C
    // Even though there are multiple addressing modes for this instruction, the implementation is the same
    void executeBIT(T);

    // Branch if Minus - opcode $30
    void executeBMI(uint8_t);

    // Branch if Not Equal - opcode $D0
    void executeBNE(uint8_t);

    // Branch if Positive - opcode $10
    void executeBPL(uint8_t);

    // Force Interrupt - opcode $00
    void executeBRK();

    // Branch if Overflow clear - opcode $50
    void executeBVC(uint8_t);

    // Branch if Overflow Set - opcode $70
    void executeBVS(uint8_t);

    // Clear Carry - opcode $18
    void executeCLC();

    // Clear Decimal - opcode $D8
    void executeCLD();

    // Clear Interrupt Disable - opcode $58
    void executeCLI();

    // Clear Overflow - opcode $B8
    void executeCLV();

    template<typename T>
    void executeCMP(AddressingMode, T);

    // Compare A - opcode $C9
    void CMP_Immediate(uint8_t);

    // Compare A - opcode $C5
    void CMP_ZeroPage(uint8_t);

    // Compare A - opcode $D5
    void CMP_ZeroPageX(uint8_t);

    // Compare A - opcode $CD
    void CMP_Absolute(uint16_t);

    // Compare A - opcode $DD
    void CMP_AbsoluteX(uint16_t);

    // Compare A - opcode $D9
    void CMP_AbsoluteY(uint16_t);

    // Compare A - opcode $C1
    void CMP_IndirectX(uint8_t);

    // Compare A - opcode $D1
    void CMP_IndirectY(uint8_t);

    template<typename T>
    void executeCPX(AddressingMode, T);

    // Compare X - opcode $E0
    void CPX_Immediate(uint8_t);

    // Compare X - opcode $E4
    void CPX_ZeroPage(uint8_t);

    // Compare X - opcode $EC
    void CPX_Absolute(uint16_t);

    template<typename T>
    void executeCPY(AddressingMode, T);

    // Compare Y - opcode $C0
    void CPY_Immediate(uint8_t);

    // Compare Y - opcode $C4
    void CPY_ZeroPage(uint8_t);

    // Compare Y - opcode $CC
    void CPY_Absolute(uint16_t);

    template<typename T>
    void executeDEC(AddressingMode, T);

    // Decrement Memory - opcode $C6
    void DEC_ZeroPage(uint8_t);

    // Decrement Memory - opcode $D6
    void DEC_ZeroPageX(uint8_t);

    // Decrement Memory - opcode $CE
    void DEC_Absolute(uint16_t);

    // Decrement Memory - opcode $DE
    void DEC_AbsoluteX(uint16_t);

    // Decrement X - opcode $CA
    void executeDEX();

    // Decrement Y - opcode $88
    void executeDEY();

    template<typename T>
    void executeEOR(AddressingMode, T);

    // Bitwise Exclusive OR - opcode $49
    void EOR_Immediate(uint8_t);

    // Bitwise Exclusive OR - opcode $45
    void EOR_ZeroPage(uint8_t);

    // Bitwise Exclusive OR - opcode $55
    void EOR_ZeroPageX(uint8_t);

    // Bitwise Exclusive OR - opcode $4D
    void EOR_Absolute(uint16_t);

    // Bitwise Exclusive OR - opcode $5D
    void EOR_AbsoluteX(uint16_t);

    // Bitwise Exclusive OR - opcode $59
    void EOR_AbsoluteY(uint16_t);

    // Bitwise Exclusive OR - opcode $41
    void EOR_IndirectX(uint8_t);

    // Bitwise Exclusive OR - opcode $51
    void EOR_IndirectY(uint8_t);

    template<typename T>
    void executeINC(AddressingMode, T);

    // Increment Memory - opcode $E6
    void INC_ZeroPage(uint8_t);

    // Increment Memory - opcode $F6
    void INC_ZeroPageX(uint8_t);

    // Increment Memory - opcode $EE
    void INC_Absolute(uint16_t);

    // Increment Memory - opcode $FE
    void INC_AbsoluteX(uint16_t);

    // Increment X - opcode $E8
    void executeINX();

    // Increment Y - opcode $C8
    void executeINY();

    template<typename T>
    void executeJMP(AddressingMode, T);

    // Jump - opcode $4C
    void JMP_Absolute(uint16_t);

    // Jump - opcode $6C
    void JMP_Indirect(uint16_t);

    // Jump to Subroutine
    void executeJSR(uint16_t);

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
    void executeLSR(AddressingMode, T);

    // Logical Shift Right - opcode $4A
    void LSR_Accumulator();

    // Logical Shift Right - opcode $46
    void LSR_ZeroPage(uint8_t);

    // Logical Shift Right - opcode $56
    void LSR_ZeroPageX(uint8_t);

    // Logical Shift Right - opcode $4E
    void LSR_Absolute(uint16_t);

    // Logical Shift Right - opcode $5E
    void LSR_AbsoluteX(uint16_t);

    template<typename T>
    void executeORA(AddressingMode, T);

    // Bitwise OR - opcode $09
    void ORA_Immediate(uint8_t);

    // Bitwise OR - opcode $05
    void ORA_ZeroPage(uint8_t);

    // Bitwise OR - opcode $15
    void ORA_ZeroPageX(uint8_t);

    // Bitwise OR - opcode $0D
    void ORA_Absolute(uint16_t);

    // Bitwise OR - opcode $1D
    void ORA_AbsoluteX(uint16_t);

    // Bitwise OR - opcode $19
    void ORA_AbsoluteY(uint16_t);

    // Bitwise OR - opcode $01
    void ORA_IndirectX(uint8_t);

    // Bitwise OR - opcode $11
    void ORA_IndirectY(uint8_t);

    // Push A - opcode $48
    void executePHA();

    // Push Processor Status - opcode $08
    void executePHP();

    // Pull A - opcode $68
    void executePLA();

    // Pull Processor Status - opcode $28
    void executePLP();

    template<typename T>
    void executeROL(AddressingMode, T);

    // Arithmetic Shift Left - opcode $2A
    void ROL_Accumulator();

    // Arithmetic Shift Left - opcode $26
    void ROL_ZeroPage(uint8_t);

    // Arithmetic Shift Left - opcode $36
    void ROL_ZeroPageX(uint8_t);

    // Arithmetic Shift Left - opcode $2E
    void ROL_Absolute(uint16_t);

    // Arithmetic Shift Left - opcode $3E
    void ROL_AbsoluteX(uint16_t);

    template<typename T>
    void executeROR(AddressingMode, T);

    // Arithmetic Shift Left - opcode $6A
    void ROR_Accumulator();

    // Arithmetic Shift Left - opcode $66
    void ROR_ZeroPage(uint8_t);

    // Arithmetic Shift Left - opcode $76
    void ROR_ZeroPageX(uint8_t);

    // Arithmetic Shift Left - opcode $6E
    void ROR_Absolute(uint16_t);

    // Arithmetic Shift Left - opcode $7E
    void ROR_AbsoluteX(uint16_t);

    // Return from Interrupt - opcode $40
    void executeRTI();

    // Return from Subroutine - opcode $60
    void executeRTS();

    template<typename T>
    void executeSBC(AddressingMode, T);

    void SBC_Immediate(uint8_t);

    void SBC_ZeroPage(uint8_t);

    void SBC_ZeroPageX(uint8_t);

    void SBC_Absolute(uint16_t);

    void SBC_AbsoluteX(uint16_t);

    void SBC_AbsoluteY(uint16_t);

    void SBC_IndirectX(uint8_t);

    void SBC_IndirectY(uint8_t);

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

    // Set Carry - opcode $38
    void executeSEC();

    // Set Decimal - opcode $F8
    void executeSED();

    // Set Interrupt Disable - opcode $78
    void executeSEI();

    // Transfer A to X - opcode $AA
    void executeTAX();

    // Transfer A to Y - opcode $A8
    void executeTAY();

    // Transfer SP to X - opcode $BA
    void executeTSX();

    // Transfer X to A - opcode $8A
    void executeTXA();

    // Transfer X to Stack Pointer - opcode $9A
    void executeTXS();

    // Transfer Y to A - opcode $98
    void executeTYA();


};


#endif //NESEMULATOR_CPU_H
