//
// Created by Brandon Paul on 5/6/24.
//

#ifndef NESEMULATOR_OPCODEHELPER_H
#define NESEMULATOR_OPCODEHELPER_H

#include <cstdint>
#include "CPU/AddressingMode.h"
#include "CPU/Instruction.h"

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


    Instruction getInstruction(uint8_t opcode) {
        switch (opcode) {
            // ADC
            case 0x69:
            case 0x65:
            case 0x75:
            case 0x6D:
            case 0x7D:
            case 0x79:
            case 0x61:
            case 0x71:
                return Instruction::ADC;

            // AND
            case 0x29:
            case 0x25:
            case 0x35:
            case 0x2D:
            case 0x3D:
            case 0x39:
            case 0x21:
            case 0x31:
                return Instruction::AND;

            // ASL
            case 0x0A:
            case 0x06:
            case 0x16:
            case 0x0E:
            case 0x1E:
                return Instruction::ASL;

            // BCC
            case 0x90:
                return Instruction::BCC;

            // BCS
            case 0xB0:
                return Instruction::BCS;

            // BEQ
            case 0xF0:
                return Instruction::BEQ;

            // BIT
            case 0x24:
            case 0x2C:
                return Instruction::BIT;

            // BMI
            case 0x30:
                return Instruction::BMI;

            // BNE
            case 0xD0:
                return Instruction::BNE;

            // BPL
            case 0x10:
                return Instruction::BPL;

            // BRK
            case 0x00:
                return Instruction::BRK;

            // BVC
            case 0x50:
                return Instruction::BVC;

            // BVS
            case 0x70:
                return Instruction::BVS;

            // CLC
            case 0x18:
                return Instruction::CLC;

            // CLC
            case 0xD8:
                return Instruction::CLD;

            // CLI
            case 0x58:
                return Instruction::CLI;

            // CLV
            case 0xB8:
                return Instruction::CLV;

            // CMP
            case 0xC9:
            case 0xC5:
            case 0xD5:
            case 0xCD:
            case 0xDD:
            case 0xD9:
            case 0xC1:
            case 0xD1:
                return Instruction::CMP;

            // CPX
            case 0xE0:
            case 0xE4:
            case 0xEC:
                return Instruction::CPX;

            // CPY
            case 0xC0:
            case 0xC4:
            case 0xCC:
                return Instruction::CPY;

            // DEC
            case 0xC6:
            case 0xD6:
            case 0xCE:
            case 0xDE:
                return Instruction::DEC;

            // DEX
            case 0xCA:
                return Instruction::DEX;

            // DEY
            case 0x88:
                return Instruction::DEY;

            // EOR
            case 0x49:
            case 0x45:
            case 0x55:
            case 0x4D:
            case 0x5D:
            case 0x59:
            case 0x41:
            case 0x51:
                return Instruction::EOR;

            // INC
            case 0xE6:
            case 0xF6:
            case 0xEE:
            case 0xFE:
                return Instruction::INC;

            // INX
            case 0xE8:
                return Instruction::INX;

            // INY
            case 0xC8:
                return Instruction::INY;

            // JMP
            case 0x4C:
            case 0x6C:
                return Instruction::JMP;

            // JSR
            case 0x20:
                return Instruction::JSR;

            // LDA
            case 0xA9:
            case 0xA5:
            case 0xB5:
            case 0xAD:
            case 0xBD:
            case 0xB9:
            case 0xA1:
            case 0xB1:
                return Instruction::LDA;

            // LDX
            case 0xA2:
            case 0xA6:
            case 0xB6:
            case 0xAE:
            case 0xBE:
                return Instruction::LDX;

            // LDY
            case 0xA0:
            case 0xA4:
            case 0xB4:
            case 0xAC:
            case 0xBC:
                return Instruction::LDY;

            // LSR
            case 0x4A:
            case 0x46:
            case 0x56:
            case 0x4E:
            case 0x5E:
                return Instruction::LSR;

            // NOP
            case 0xEA:
                return Instruction::NOP;

            // ORA
            case 0x09:
            case 0x05:
            case 0x15:
            case 0x0D:
            case 0x1D:
            case 0x19:
            case 0x01:
            case 0x11:
                return Instruction::ORA;

            // PHA
            case 0x48:
                return Instruction::PHA;

            // PHP
            case 0x08:
                return Instruction::PHP;

            // PLA
            case 0x68:
                return Instruction::PLA;

            // PLP
            case 0x28:
                return Instruction::PLP;

            // ROL
            case 0x2A:
            case 0x26:
            case 0x36:
            case 0x2E:
            case 0x3E:
                return Instruction::ROL;

            // ROR
            case 0x6A:
            case 0x66:
            case 0x76:
            case 0x6E:
            case 0x7E:
                return Instruction::ROR;

            // RTI
            case 0x40:
                return Instruction::RTI;

            // RTS
            case 0x60:
                return Instruction::RTS;

            // SBC
            case 0xE9:
            case 0xE5:
            case 0xF5:
            case 0xED:
            case 0xFD:
            case 0xF9:
            case 0xE1:
            case 0xF1:
                return Instruction::SBC;

            // SEC
            case 0x38:
                return Instruction::SEC;

            // SED
            case 0xF8:
                return Instruction::SED;

            // SEI
            case 0x78:
                return Instruction::SEI;

            // STA
            case 0x85:
            case 0x95:
            case 0x8D:
            case 0x9D:
            case 0x99:
            case 0x81:
            case 0x91:
                return Instruction::STA;

            // STX
            case 0x86:
            case 0x96:
            case 0x8E:
                return Instruction::STX;

            // STY
            case 0x84:
            case 0x94:
            case 0x8C:
                return Instruction::STY;

            // TAX
            case 0xAA:
                return Instruction::TAX;

            // TAY
            case 0xA8:
                return Instruction::TAY;

            // TSX
            case 0xBA:
                return Instruction::TSX;

            // TXA
            case 0x8A:
                return Instruction::TXA;

            // TXS
            case 0x9A:
                return Instruction::TXS;

            // TYA
            case 0x98:
                return Instruction::TYA;

            default:
                return Instruction::INVALID;
        }
    }
};

#endif //NESEMULATOR_OPCODEHELPER_H
