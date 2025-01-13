//
// Created by Brandon Paul on 4/23/24.
//

#ifndef NESEMULATOR_ADRESSINGMODE_H
#define NESEMULATOR_ADRESSINGMODE_H

#include <string>
#include <unordered_map>

enum AddressingMode {
    Accumulator, // Acts directly upon the accumulator
    Immediate, // Loads content itself, ex. LDA #$04 will load 0x04 into the Accumulator Register
    ZeroPage, // Addresses first 256 bytes of memory
    ZeroPageX, // takes zero-page address and adds the current value of the X register to it
    ZeroPageY, // takes zero-page address and adds the current value of the Y register to it
    Relative, // A signed 8 bit offset (-128 -> +127) is added to the program counter
    Absolute, // loads contents of some absolute 16-bit address
    AbsoluteX, // loads contents of some (absolute 16-bit address + contents of X Register)
    AbsoluteY, // loads contents of some (absolute 16-bit address + contents of Y Register)
    Indirect,
    IndirectX,
    IndirectY,
    Implied,
    UNKNOWN
};

inline std::string toString(AddressingMode mode) {
    static const std::unordered_map<AddressingMode, std::string> modeToString = {
        {Accumulator, "Accumulator"},
        {Immediate, "Immediate"},
        {ZeroPage, "ZeroPage"},
        {ZeroPageX, "ZeroPageX"},
        {ZeroPageY, "ZeroPageY"},
        {Relative, "Relative"},
        {Absolute, "Absolute"},
        {AbsoluteX, "AbsoluteX"},
        {AbsoluteY, "AbsoluteY"},
        {Indirect, "Indirect"},
        {IndirectX, "IndirectX"},
        {IndirectY, "IndirectY"},
        {Implied, "Implied"},
        {UNKNOWN, "UNKNOWN"}
    };

    auto it = modeToString.find(mode);
    return it != modeToString.end() ? it->second : "INVALID_MODE";
}

#endif //NESEMULATOR_ADRESSINGMODE_H
