//
// Created by Brandon Paul on 1/12/25.
//

#include "../CPU.h"

void CPU::executeCLC() {
    clearFlag(StatusFlag::Carry);
}

void CPU::executeCLD() {
    clearFlag(StatusFlag::Decimal);
}

void CPU::executeCLI() {
    clearFlag(StatusFlag::InterruptDisable);
}

void CPU::executeCLV() {
    clearFlag(StatusFlag::Overflow);
}

void CPU::executeSEC() {
    setFlag(StatusFlag::Carry);
}

void CPU::executeSED() {
    setFlag(StatusFlag::Decimal);
}

void CPU::executeSEI() {
    setFlag(StatusFlag::InterruptDisable);
}