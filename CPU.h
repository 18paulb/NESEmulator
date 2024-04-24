//
// Created by Brandon Paul on 4/21/24.
//

#ifndef NESEMULATOR_CPU_H
#define NESEMULATOR_CPU_H

#include <cstdint>
#include "StatusFlag.h"

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


    // Load Accumulator - opcode A9
    void LDA_Immediate(uint8_t value);

};


#endif //NESEMULATOR_CPU_H
