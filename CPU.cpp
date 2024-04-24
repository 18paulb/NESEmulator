//
// Created by Brandon Paul on 4/21/24.
//

#include "CPU.h"

void CPU::incrementCounter() {
    programCounter++;
}

void CPU::LDA_Immediate(uint8_t value) {
    // Load value at memory address into the accumulator
    accumulator = value;

    // Set Flags
    if (accumulator == 0) {
        setFlag(StatusFlag::Zero);
    }

    // Check if bit 7 of the accumulator is set
    // This does bitwise & with hex 0x80 (which is binary 10000000)
    if (accumulator & 0x80) {
        setFlag(StatusFlag::Negative);
    }
}
