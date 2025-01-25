//
// Created by Brandon Paul on 1/12/25.
//

#include "../CPU.h"

// FIXME: Warning: I've seen different things for the necessity of step 3-4 so if bugs happen, it could be that
/*
 Three things happen during the BRK instruction
 1. The PC+2 is pushed to the stack
 2. A copy of the status register will be pushed to the stack with the break flag set to 1.
 3. Set the interrupt flag on the status register,
 4. Set PC to 0xFFFE 0xFFFF
*/
void CPU::executeBRK() {
    // 1.
    // First calculate PC + 2 (return address)
    // We add plus one because the PC has already been incremented once already in fetch cycle
    uint16_t pcPlusTwo = programCounter + 1;

    // Break PC into high and low bytes
    uint8_t highByte = (pcPlusTwo >> 8) & 0xFF;
    uint8_t lowByte = pcPlusTwo & 0xFF;

    // Push high byte first (due to 6502 being little-endian)
    pushToStack(highByte);

    // Then push low byte
    pushToStack(lowByte);

    // 2.
    uint8_t tmpPStatus = pStatus;
    // Manually do the bitwise operation here so that the original pStatus is not altered
    tmpPStatus |= FLAG_B;
    setMemory(STACK_POINTER_OFFSET + stackPointer, tmpPStatus);
    stackPointer--;

    // 3.
    setFlag(StatusFlag::InterruptDisable);

    // 4.
    lowByte = memory[0xFFFE];
    highByte = memory[0xFFFD];
    // Combine the two bytes together using bit shifting
    uint16_t val = (highByte << 8) | lowByte;

    programCounter = val;
}

void CPU::executeRTI() {
    uint8_t statusFlags = popFromStack();

    // Clear the Break Flag
    statusFlags &= ~FLAG_B;

    pStatus = statusFlags;

    uint8_t lowByte = popFromStack();
    uint8_t highByte = popFromStack();

    programCounter = (highByte << 8) | lowByte;
}