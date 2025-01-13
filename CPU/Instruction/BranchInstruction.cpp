//
// Created by Brandon Paul on 1/12/25.
//

#include "../CPU.h"

/*
 If the carry flag is clear, BCC branches to a nearby location by adding the branch offset to the program counter.
 The offset is signed and has a range of [-128, 127] relative to the first byte after the branch instruction.

 Important: Some docs say to add + 2 + offset to PC, but since we increment PC during fetch cycles, we don't need to add
 the + 2 since it is already incremented to the next instruction
*/
//FIXME: Potential Issues
void CPU::executeBCC(uint8_t val) {
    if (!isFlagSet(StatusFlag::Carry)) {
        auto displacement = static_cast<int8_t>(val);
        programCounter += displacement;
    }
}

/*
 If the carry flag is set, BCS branches to a nearby location by adding the branch offset to the program counter.
 The offset is signed and has a range of [-128, 127] relative to the first byte after the branch instruction.

 Important: Some docs say to add + 2 + offset to PC, but since we increment PC during fetch cycles, we don't need to add
 the + 2 since it is already incremented to the next instruction
*/
//FIXME: Potential Issues
void CPU::executeBCS(uint8_t val) {
    if (isFlagSet(StatusFlag::Carry)) {
        auto displacement = static_cast<int8_t>(val);
        programCounter += displacement;
    }
}

/*
 If the zero flag is set, BEQ branches to a nearby location by adding the branch offset to the program counter.
 The offset is signed and has a range of [-128, 127] relative to the first byte after the branch instruction.

 Important: Some docs say to add + 2 + offset to PC, but since we increment PC during fetch cycles, we don't need to add
 the + 2 since it is already incremented to the next instruction
*/
//FIXME: Potential Issues
void CPU::executeBEQ(uint8_t val) {
    if (isFlagSet(StatusFlag::Zero)) {
        auto displacement = static_cast<int8_t>(val);
        programCounter += displacement;
    }
}

/*
 If the negative flag is set, BMI branches to a nearby location by adding the branch offset to the program counter.
 The offset is signed and has a range of [-128, 127] relative to the first byte after the branch instruction.

 Important: Some docs say to add + 2 + offset to PC, but since we increment PC during fetch cycles, we don't need to add
 the + 2 since it is already incremented to the next instruction
*/
//FIXME: Potential Issues
void CPU::executeBMI(uint8_t val) {
    if (isFlagSet(StatusFlag::Negative)) {
        auto displacement = static_cast<int8_t>(val);
        programCounter += displacement;
    }
}

/*
 If the negative flag is clear, BNE branches to a nearby location by adding the branch offset to the program counter.
 The offset is signed and has a range of [-128, 127] relative to the first byte after the branch instruction.

 Important: Some docs say to add + 2 + offset to PC, but since we increment PC during fetch cycles, we don't need to add
 the + 2 since it is already incremented to the next instruction
*/
//FIXME: Potential Issues
void CPU::executeBNE(uint8_t val) {
    if (!isFlagSet(StatusFlag::Zero)) {
        auto displacement = static_cast<int8_t>(val);
        programCounter += displacement;
    }
}

/*
 If the negative flag is clear, BPL branches to a nearby location by adding the branch offset to the program counter.
 The offset is signed and has a range of [-128, 127] relative to the first byte after the branch instruction.

 Important: Some docs say to add + 2 + offset to PC, but since we increment PC during fetch cycles, we don't need to add
 the + 2 since it is already incremented to the next instruction
*/
//FIXME: Potential Issues
void CPU::executeBPL(uint8_t val) {
    if (!isFlagSet(StatusFlag::Negative)) {
        auto displacement = static_cast<int8_t>(val);
        programCounter += displacement;
    }
}

/*
 If the overflow flag is clear, BVC branches to a nearby location by adding the branch offset to the program counter.
 The offset is signed and has a range of [-128, 127] relative to the first byte after the branch instruction.

 Important: Some docs say to add + 2 + offset to PC, but since we increment PC during fetch cycles, we don't need to add
 the + 2 since it is already incremented to the next instruction
*/
//FIXME: Potential Issues
void CPU::executeBVC(uint8_t val) {
    if (!isFlagSet(StatusFlag::Overflow)) {
        auto displacement = static_cast<int8_t>(val);
        programCounter += displacement;
    }
}

/*
 If the overflow flag is set, BVS branches to a nearby location by adding the branch offset to the program counter.
 The offset is signed and has a range of [-128, 127] relative to the first byte after the branch instruction.

 Important: Some docs say to add + 2 + offset to PC, but since we increment PC during fetch cycles, we don't need to add
 the + 2 since it is already incremented to the next instruction
*/
//FIXME: Potential Issues
void CPU::executeBVS(uint8_t val) {
    if (isFlagSet(StatusFlag::Overflow)) {
        auto displacement = static_cast<int8_t>(val);
        programCounter += displacement;
    }
}