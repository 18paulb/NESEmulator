//
// Created by Brandon Paul on 5/6/24.
//

#ifndef NESEMULATOR_OPCODEHELPER_H
#define NESEMULATOR_OPCODEHELPER_H

#include <cstdint>

#include "AddressingMode.h"
#include "CPU/OpCode/Instruction.h"
#include "HelperClasses/InstructionMetadata.h"

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

    // FIXME: Honestly this could probably just be a lookup table, it would probably be more efficient
    InstructionMetadata getInstructionMetadata(uint8_t opcode) {
        switch (opcode) {
            // ADC
            case 0x69: return {Instruction::ADC, 2, 2};
            case 0x65: return {Instruction::ADC, 2, 3};
            case 0x75: return {Instruction::ADC, 2, 4};
            case 0x6D: return {Instruction::ADC, 3, 4};
            case 0x7D: return {Instruction::ADC, 3, 4};
            case 0x79: return {Instruction::ADC, 3, 4};
            case 0x61: return {Instruction::ADC, 2, 6};
            case 0x71: return {Instruction::ADC, 2, 5};

            // AND
            case 0x29: return {Instruction::AND, 2, 2};
            case 0x25: return {Instruction::AND, 2, 3};
            case 0x35: return {Instruction::AND, 2, 4};
            case 0x2D: return {Instruction::AND, 3, 4};
            case 0x3D: return {Instruction::AND, 3, 4};
            case 0x39: return {Instruction::AND, 3, 4};
            case 0x21: return {Instruction::AND, 2, 6};
            case 0x31: return {Instruction::AND, 2, 5};

            // ASL
            case 0x0A: return {Instruction::ASL, 1, 2};
            case 0x06: return {Instruction::ASL, 2, 5};
            case 0x16: return {Instruction::ASL, 2, 6};
            case 0x0E: return {Instruction::ASL, 3, 6};
            case 0x1E: return {Instruction::ASL, 3, 7};

            // BCC
            case 0x90: return {Instruction::BCC, 2, 2};

            // BCS
            case 0xB0: return {Instruction::BCS, 2, 2};

            // BEQ
            case 0xF0: return {Instruction::BEQ, 2, 2};

            // BIT
            case 0x24: return {Instruction::BIT, 2, 3};
            case 0x2C: return {Instruction::BIT, 3, 4};

            // BMI
            case 0x30: return {Instruction::BMI, 2, 2};

            // BNE
            case 0xD0: return {Instruction::BNE, 2, 2};

            // BPL
            case 0x10: return {Instruction::BPL, 2, 2};

            // BRK
            case 0x00: return {Instruction::BRK, 1, 7};

            // BVC
            case 0x50: return {Instruction::BVC, 2, 2};

            // BVS
            case 0x70: return {Instruction::BVS, 2, 2};

            // CLC
            case 0x18: return {Instruction::CLC, 1, 2};

            // CLD
            case 0xD8: return {Instruction::CLD, 1, 2};

            // CLI
            case 0x58: return {Instruction::CLI, 1, 2};

            // CLV
            case 0xB8: return {Instruction::CLV, 1, 2};

            // CMP
            case 0xC9: return {Instruction::CMP, 2, 2};
            case 0xC5: return {Instruction::CMP, 2, 3};
            case 0xD5: return {Instruction::CMP, 2, 4};
            case 0xCD: return {Instruction::CMP, 3, 4};
            case 0xDD: return {Instruction::CMP, 3, 4};
            case 0xD9: return {Instruction::CMP, 3, 4};
            case 0xC1: return {Instruction::CMP, 2, 6};
            case 0xD1: return {Instruction::CMP, 2, 5};

            // CPX
            case 0xE0: return {Instruction::CPX, 2, 2};
            case 0xE4: return {Instruction::CPX, 2, 3};
            case 0xEC: return {Instruction::CPX, 3, 4};

            // CPY
            case 0xC0: return {Instruction::CPY, 2, 2};
            case 0xC4: return {Instruction::CPY, 2, 3};
            case 0xCC: return {Instruction::CPY, 3, 4};

            // DEC
            case 0xC6: return {Instruction::DEC, 2, 5};
            case 0xD6: return {Instruction::DEC, 2, 6};
            case 0xCE: return {Instruction::DEC, 3, 6};
            case 0xDE: return {Instruction::DEC, 3, 7};

            // DEX
            case 0xCA: return {Instruction::DEX, 1, 2};

            // DEY
            case 0x88: return {Instruction::DEY, 1, 2};

            // EOR
            case 0x49: return {Instruction::EOR, 2, 2};
            case 0x45: return {Instruction::EOR, 2, 3};
            case 0x55: return {Instruction::EOR, 2, 4};
            case 0x4D: return {Instruction::EOR, 3, 4};
            case 0x5D: return {Instruction::EOR, 3, 4};
            case 0x59: return {Instruction::EOR, 3, 4};
            case 0x41: return {Instruction::EOR, 2, 6};
            case 0x51: return {Instruction::EOR, 2, 5};

            // INC
            case 0xE6: return {Instruction::INC, 2, 5};
            case 0xF6: return {Instruction::INC, 2, 6};
            case 0xEE: return {Instruction::INC, 3, 6};
            case 0xFE: return {Instruction::INC, 3, 7};

            // INX
            case 0xE8: return {Instruction::INX, 1, 2};

            // INY
            case 0xC8: return {Instruction::INY, 1, 2};

            // JMP
            case 0x4C: return {Instruction::JMP, 3, 3};
            case 0x6C: return {Instruction::JMP, 3, 5};

            // JSR
            case 0x20: return {Instruction::JSR, 3, 6};

            // LDA
            case 0xA9: return {Instruction::LDA, 2, 2};
            case 0xA5: return {Instruction::LDA, 2, 3};
            case 0xB5: return {Instruction::LDA, 2, 4};
            case 0xAD: return {Instruction::LDA, 3, 4};
            case 0xBD: return {Instruction::LDA, 3, 4};
            case 0xB9: return {Instruction::LDA, 3, 4};
            case 0xA1: return {Instruction::LDA, 2, 6};
            case 0xB1: return {Instruction::LDA, 2, 5};

            // LDX
            case 0xA2: return {Instruction::LDX, 2, 2};
            case 0xA6: return {Instruction::LDX, 2, 3};
            case 0xB6: return {Instruction::LDX, 2, 4};
            case 0xAE: return {Instruction::LDX, 3, 4};
            case 0xBE: return {Instruction::LDX, 3, 4};

            // LDY
            case 0xA0: return {Instruction::LDY, 2, 2};
            case 0xA4: return {Instruction::LDY, 2, 3};
            case 0xB4: return {Instruction::LDY, 2, 4};
            case 0xAC: return {Instruction::LDY, 3, 4};
            case 0xBC: return {Instruction::LDY, 3, 4};

            // LSR
            case 0x4A: return {Instruction::LSR, 1, 2};
            case 0x46: return {Instruction::LSR, 2, 5};
            case 0x56: return {Instruction::LSR, 2, 6};
            case 0x4E: return {Instruction::LSR, 3, 6};
            case 0x5E: return {Instruction::LSR, 3, 7};

            // NOP
            case 0xEA: return {Instruction::NOP, 1, 2};

            // ORA
            case 0x09: return {Instruction::ORA, 2, 2};
            case 0x05: return {Instruction::ORA, 2, 3};
            case 0x15: return {Instruction::ORA, 2, 4};
            case 0x0D: return {Instruction::ORA, 3, 4};
            case 0x1D: return {Instruction::ORA, 3, 4};
            case 0x19: return {Instruction::ORA, 3, 4};
            case 0x01: return {Instruction::ORA, 2, 6};
            case 0x11: return {Instruction::ORA, 2, 5};

            // PHA
            case 0x48: return {Instruction::PHA, 1, 3};

            // PHP
            case 0x08: return {Instruction::PHP, 1, 3};

            // PLA
            case 0x68: return {Instruction::PLA, 1, 4};

            // PLP
            case 0x28: return {Instruction::PLP, 1, 4};

            // ROL
            case 0x2A: return {Instruction::ROL, 1, 2};
            case 0x26: return {Instruction::ROL, 2, 5};
            case 0x36: return {Instruction::ROL, 2, 6};
            case 0x2E: return {Instruction::ROL, 3, 6};
            case 0x3E: return {Instruction::ROL, 3, 7};

            // ROR
            case 0x6A: return {Instruction::ROR, 1, 2};
            case 0x66: return {Instruction::ROR, 2, 5};
            case 0x76: return {Instruction::ROR, 2, 6};
            case 0x6E: return {Instruction::ROR, 3, 6};
            case 0x7E: return {Instruction::ROR, 3, 7};

            // RTI
            case 0x40: return {Instruction::RTI, 1, 6};

            // RTS
            case 0x60: return {Instruction::RTS, 1, 6};

            // SBC
            case 0xE9: return {Instruction::SBC, 2, 2};
            case 0xE5: return {Instruction::SBC, 2, 3};
            case 0xF5: return {Instruction::SBC, 2, 4};
            case 0xED: return {Instruction::SBC, 3, 4};
            case 0xFD: return {Instruction::SBC, 3, 4};
            case 0xF9: return {Instruction::SBC, 3, 4};
            case 0xE1: return {Instruction::SBC, 2, 6};
            case 0xF1: return {Instruction::SBC, 2, 5};

            // SEC
            case 0x38: return {Instruction::SEC, 1, 2};

            // SED
            case 0xF8: return {Instruction::SED, 1, 2};

            // SEI
            case 0x78: return {Instruction::SEI, 1, 2};

            // STA
            case 0x85: return {Instruction::STA, 2, 3};
            case 0x95: return {Instruction::STA, 2, 4};
            case 0x8D: return {Instruction::STA, 3, 4};
            case 0x9D: return {Instruction::STA, 3, 5};
            case 0x99: return {Instruction::STA, 3, 5};
            case 0x81: return {Instruction::STA, 2, 6};
            case 0x91: return {Instruction::STA, 2, 6};

            // STX
            case 0x86: return {Instruction::STX, 2, 3};
            case 0x96: return {Instruction::STX, 2, 4};
            case 0x8E: return {Instruction::STX, 3, 4};

            // STY
            case 0x84: return {Instruction::STY, 2, 3};
            case 0x94: return {Instruction::STY, 2, 4};
            case 0x8C: return {Instruction::STY, 3, 4};

            // TAX
            case 0xAA: return {Instruction::TAX, 1, 2};

            // TAY
            case 0xA8: return {Instruction::TAY, 1, 2};

            // TSX
            case 0xBA: return {Instruction::TSX, 1, 2};

            // TXA
            case 0x8A: return {Instruction::TXA, 1, 2};

            // TXS
            case 0x9A: return {Instruction::TXS, 1, 2};

            // TYA
            case 0x98: return {Instruction::TYA, 1, 2};

            default: return {Instruction::INVALID, -1, -1};
        }
    }
};

#endif //NESEMULATOR_OPCODEHELPER_H
