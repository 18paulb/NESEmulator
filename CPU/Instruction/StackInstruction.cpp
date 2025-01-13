//
// Created by Brandon Paul on 1/12/25.
//

#include "../CPU.h"

void CPU::executePHA() {
    pushToStack(accumulator);
}

void CPU::executePHP() {
    uint8_t pStatusCopy = pStatus;
    // Set Break flag on copy
    pStatusCopy |= FLAG_B;

    pushToStack(pStatusCopy);
}

void CPU::executePLA() {
    accumulator = popFromStack();;

    setZeroAndNegativeFlag(accumulator);
}

/*
    FIXME: It says B flag and extra bit are ignored but I don't think it really matters

    FIXME:  Note that the effect of changing I is delayed one instruction because the flag is changed after IRQ is polled,
    delaying the effect until IRQ is polled in the next instruction like with CLI and SEI.

    TLDR; if problems occur with IRQ being active, might have to delay changing I flag 1 instruction
*/
void CPU::executePLP() {
    pStatus = popFromStack();
}