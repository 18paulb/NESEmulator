//
// Created by Brandon Paul on 5/6/24.
//

#ifndef NESEMULATOR_OPCODEHELPER_H
#define NESEMULATOR_OPCODEHELPER_H

#include <cstdint>
#include "CPU/AddressingMode.h"

class OpcodeHelper {
public:
    AddressingMode getAddressingMode(uint8_t opcode) {
        switch (opcode) {
            // All the Immediate
            case 0xA9:
            case 0xA2:
            case 0xA0:
                return AddressingMode::Immediate;

            // All ZeroPage
            case 0xA5:
            case 0xA6:
            case 0xA4:
            case 0x85:
            case 0x86:
            case 0x84:
                return AddressingMode::ZeroPage;

            // All ZeroPageX
            case 0xB5:
            case 0xB4:
            case 0x95:
            case 0x94:
                return AddressingMode::ZeroPageX;

            // All ZeroPageY
            case 0xB6:
            case 0x96:
                return AddressingMode::ZeroPageY;

            // All Absolute
            case 0xAD:
            case 0xAE:
            case 0xAC:
            case 0x8D:
            case 0x8E:
            case 0x8C:
                return AddressingMode::Absolute;

            // All AbsoluteX
            case 0xBD:
            case 0xBC:
            case 0x9D:
                return AddressingMode::AbsoluteX;

            // All AbsoluteY
            case 0xB9:
            case 0xBE:
            case 0x99:
                return AddressingMode::AbsoluteY;

            // All IndirectX
            case 0xA1:
            case 0x81:
                return AddressingMode::IndirectX;

            // All IndirectY
            case 0xB1:
            case 0x91:
                return AddressingMode::IndirectY;

            default:
                return AddressingMode::UNKNOWN;
        }
    }
};

#endif //NESEMULATOR_OPCODEHELPER_H
