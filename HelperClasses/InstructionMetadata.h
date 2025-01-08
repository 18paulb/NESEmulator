//
// Created by Brandon Paul on 1/8/25.
//

#ifndef NESEMULATOR_INSTRUCTIONMETADATA_H
#define NESEMULATOR_INSTRUCTIONMETADATA_H

#endif //NESEMULATOR_INSTRUCTIONMETADATA_H

#include "CPU/OpCode/Instruction.h"

struct InstructionMetadata {
    Instruction instruction;
    int byteCount;
    int cycles;

    InstructionMetadata(Instruction instruction, int byteCount, int cycles) {
        this->instruction = instruction;
        this->byteCount = byteCount;
        this->cycles = cycles;
    }
};