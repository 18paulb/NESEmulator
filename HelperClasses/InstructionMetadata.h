//
// Created by Brandon Paul on 1/8/25.
//

#ifndef NESEMULATOR_INSTRUCTIONMETADATA_H
#define NESEMULATOR_INSTRUCTIONMETADATA_H

#include "CPU/OpCode/Instruction.h"

struct InstructionMetadata {
    // The instruction type (ie LDA, LDX) these have multiple addressing modes
    Instruction instruction;

    // Type of addressing mode (ie Immediate, ZeroPage), basically how it accesses memory
    AddressingMode addressingMode;

    // Number of bytes that the instruction uses in memory
    int byteCount;

    // Number of cycles it takes to execute
    int cycles;

    InstructionMetadata(Instruction instruction, AddressingMode addressingMode, int byteCount, int cycles) {
        this->instruction = instruction;
        this->addressingMode = addressingMode;
        this->byteCount = byteCount;
        this->cycles = cycles;
    }
};

#endif //NESEMULATOR_INSTRUCTIONMETADATA_H