//
// Created by Brandon Paul on 5/6/24.
//

#ifndef NESEMULATOR_OPCODEHELPER_H
#define NESEMULATOR_OPCODEHELPER_H

#include <cstdint>

#include "AddressingMode.h"
#include "HelperClasses/InstructionMetadata.h"

class OpcodeHelper {
public:
    // FIXME: Honestly this could probably just be a lookup table, it would probably be more efficient
    static InstructionMetadata getInstructionMetadata(const uint8_t& opcode) {
        switch (opcode) {
            // ADC
            case 0x69: return {Instruction::ADC, AddressingMode::Immediate, 2, 2};
            case 0x65: return {Instruction::ADC, AddressingMode::ZeroPage,2, 3};
            case 0x75: return {Instruction::ADC, AddressingMode::ZeroPageX, 2, 4};
            case 0x6D: return {Instruction::ADC, AddressingMode::Absolute, 3, 4};
            case 0x7D: return {Instruction::ADC,AddressingMode::AbsoluteX, 3, 4};
            case 0x79: return {Instruction::ADC, AddressingMode::AbsoluteY,3, 4};
            case 0x61: return {Instruction::ADC, AddressingMode::IndirectX,2, 6};
            case 0x71: return {Instruction::ADC, AddressingMode::IndirectY, 2, 5};

            // AND
            case 0x29: return {Instruction::AND, AddressingMode::Immediate,2, 2};
            case 0x25: return {Instruction::AND, AddressingMode::ZeroPage,2, 3};
            case 0x35: return {Instruction::AND, AddressingMode::ZeroPageX,2, 4};
            case 0x2D: return {Instruction::AND, AddressingMode::Absolute, 3, 4};
            case 0x3D: return {Instruction::AND, AddressingMode::AbsoluteX, 3, 4};
            case 0x39: return {Instruction::AND, AddressingMode::AbsoluteY,3, 4};
            case 0x21: return {Instruction::AND, AddressingMode::IndirectX, 2, 6};
            case 0x31: return {Instruction::AND, AddressingMode::IndirectY ,2, 5};

            // ASL
            case 0x0A: return {Instruction::ASL, AddressingMode::Accumulator, 1, 2};
            case 0x06: return {Instruction::ASL, AddressingMode::ZeroPage, 2, 5};
            case 0x16: return {Instruction::ASL, AddressingMode::ZeroPageX, 2, 6};
            case 0x0E: return {Instruction::ASL, AddressingMode::Absolute, 3, 6};
            case 0x1E: return {Instruction::ASL, AddressingMode::AbsoluteX, 3, 7};

            // BCC
            case 0x90: return {Instruction::BCC, AddressingMode::Relative,2, 2};

            // BCS
            case 0xB0: return {Instruction::BCS, AddressingMode::Relative, 2, 2};

            // BEQ
            case 0xF0: return {Instruction::BEQ, AddressingMode::Relative,2, 2};

            // BIT
            case 0x24: return {Instruction::BIT, AddressingMode::ZeroPage, 2, 3};
            case 0x2C: return {Instruction::BIT, AddressingMode::Absolute, 3, 4};

            // BMI
            case 0x30: return {Instruction::BMI, AddressingMode::Relative, 2, 2};

            // BNE
            case 0xD0: return {Instruction::BNE, AddressingMode::Relative, 2, 2};

            // BPL
            case 0x10: return {Instruction::BPL, AddressingMode::Relative, 2, 2};

            // BRK
            // Special case, even though it is 1 byte, it is treated as a 2 byte instruction
            case 0x00: return {Instruction::BRK, AddressingMode::Implied ,1, 7};

            // BVC
            case 0x50: return {Instruction::BVC, AddressingMode::Relative,2, 2};

            // BVS
            case 0x70: return {Instruction::BVS, AddressingMode::Relative, 2, 2};

            // CLC
            case 0x18: return {Instruction::CLC, AddressingMode::Implied,1, 2};

            // CLD
            case 0xD8: return {Instruction::CLD, AddressingMode::Implied, 1, 2};

            // CLI
            case 0x58: return {Instruction::CLI, AddressingMode::Implied, 1, 2};

            // CLV
            case 0xB8: return {Instruction::CLV, AddressingMode::Implied, 1, 2};

            // CMP
            case 0xC9: return {Instruction::CMP, AddressingMode::Immediate, 2, 2};
            case 0xC5: return {Instruction::CMP, AddressingMode::ZeroPage,2, 3};
            case 0xD5: return {Instruction::CMP, AddressingMode::ZeroPageX, 2, 4};
            case 0xCD: return {Instruction::CMP, AddressingMode::Absolute,3, 4};
            case 0xDD: return {Instruction::CMP, AddressingMode::AbsoluteX, 3, 4};
            case 0xD9: return {Instruction::CMP, AddressingMode::AbsoluteY,3, 4};
            case 0xC1: return {Instruction::CMP, AddressingMode::IndirectX, 2, 6};
            case 0xD1: return {Instruction::CMP, AddressingMode::IndirectY, 2, 5};

            // CPX
            case 0xE0: return {Instruction::CPX, AddressingMode::Immediate,2, 2};
            case 0xE4: return {Instruction::CPX, AddressingMode::ZeroPage, 2, 3};
            case 0xEC: return {Instruction::CPX, AddressingMode::Absolute, 3, 4};

            // CPY
            case 0xC0: return {Instruction::CPY, AddressingMode::Immediate, 2, 2};
            case 0xC4: return {Instruction::CPY, AddressingMode::ZeroPage, 2, 3};
            case 0xCC: return {Instruction::CPY, AddressingMode::Absolute,  3, 4};

            // DEC
            case 0xC6: return {Instruction::DEC, AddressingMode::ZeroPage, 2, 5};
            case 0xD6: return {Instruction::DEC, AddressingMode::ZeroPageX,  2, 6};
            case 0xCE: return {Instruction::DEC, AddressingMode::Absolute,  3, 6};
            case 0xDE: return {Instruction::DEC, AddressingMode::AbsoluteX,  3, 7};

            // DEX
            case 0xCA: return {Instruction::DEX, AddressingMode::Implied,  1, 2};

            // DEY
            case 0x88: return {Instruction::DEY, AddressingMode::Implied, 1, 2};

            // EOR
            case 0x49: return {Instruction::EOR, AddressingMode::Immediate,  2, 2};
            case 0x45: return {Instruction::EOR, AddressingMode::ZeroPage,  2, 3};
            case 0x55: return {Instruction::EOR, AddressingMode::ZeroPageX,  2, 4};
            case 0x4D: return {Instruction::EOR, AddressingMode::Absolute,  3, 4};
            case 0x5D: return {Instruction::EOR, AddressingMode::AbsoluteX,  3, 4};
            case 0x59: return {Instruction::EOR, AddressingMode::AbsoluteY,  3, 4};
            case 0x41: return {Instruction::EOR, AddressingMode::IndirectX,  2, 6};
            case 0x51: return {Instruction::EOR, AddressingMode::IndirectY,  2, 5};

            // INC
            case 0xE6: return {Instruction::INC, AddressingMode::ZeroPage,  2, 5};
            case 0xF6: return {Instruction::INC, AddressingMode::ZeroPageX,  2, 6};
            case 0xEE: return {Instruction::INC, AddressingMode::Absolute,  3, 6};
            case 0xFE: return {Instruction::INC, AddressingMode::AbsoluteX,  3, 7};

            // INX
            case 0xE8: return {Instruction::INX, AddressingMode::Implied, 1, 2};

            // INY
            case 0xC8: return {Instruction::INY, AddressingMode::Implied, 1, 2};

            // JMP
            case 0x4C: return {Instruction::JMP, AddressingMode::Absolute, 3, 3};
            case 0x6C: return {Instruction::JMP, AddressingMode::Indirect, 3, 5};

            // JSR
            case 0x20: return {Instruction::JSR, AddressingMode::Absolute, 3, 6};

            // LDA
            case 0xA9: return {Instruction::LDA, AddressingMode::Immediate, 2, 2};
            case 0xA5: return {Instruction::LDA, AddressingMode::ZeroPage, 2, 3};
            case 0xB5: return {Instruction::LDA, AddressingMode::ZeroPageX, 2, 4};
            case 0xAD: return {Instruction::LDA, AddressingMode::Absolute, 3, 4};
            case 0xBD: return {Instruction::LDA, AddressingMode::AbsoluteX, 3, 4};
            case 0xB9: return {Instruction::LDA, AddressingMode::AbsoluteY, 3, 4};
            case 0xA1: return {Instruction::LDA, AddressingMode::IndirectX, 2, 6};
            case 0xB1: return {Instruction::LDA, AddressingMode::IndirectY, 2, 5};

            // LDX
            case 0xA2: return {Instruction::LDX, AddressingMode::Immediate, 2, 2};
            case 0xA6: return {Instruction::LDX, AddressingMode::ZeroPage, 2, 3};
            case 0xB6: return {Instruction::LDX, AddressingMode::ZeroPageY,2, 4};
            case 0xAE: return {Instruction::LDX, AddressingMode::Absolute,3, 4};
            case 0xBE: return {Instruction::LDX, AddressingMode::AbsoluteY, 3, 4};

            // LDY
            case 0xA0: return {Instruction::LDY, AddressingMode::Immediate,2, 2};
            case 0xA4: return {Instruction::LDY, AddressingMode::ZeroPage, 2, 3};
            case 0xB4: return {Instruction::LDY, AddressingMode::ZeroPageX, 2, 4};
            case 0xAC: return {Instruction::LDY, AddressingMode::Absolute, 3, 4};
            case 0xBC: return {Instruction::LDY, AddressingMode::AbsoluteX, 3, 4};

            // LSR
            case 0x4A: return {Instruction::LSR, AddressingMode::Accumulator, 1, 2};
            case 0x46: return {Instruction::LSR, AddressingMode::ZeroPage, 2, 5};
            case 0x56: return {Instruction::LSR, AddressingMode::ZeroPageX, 2, 6};
            case 0x4E: return {Instruction::LSR, AddressingMode::Absolute, 3, 6};
            case 0x5E: return {Instruction::LSR, AddressingMode::AbsoluteX, 3, 7};

            // NOP
            case 0xEA: return {Instruction::NOP, AddressingMode::Implied,1, 2};

            // ORA
            case 0x09: return {Instruction::ORA, AddressingMode::Immediate, 2, 2};
            case 0x05: return {Instruction::ORA, AddressingMode::ZeroPage, 2, 3};
            case 0x15: return {Instruction::ORA, AddressingMode::ZeroPageX, 2, 4};
            case 0x0D: return {Instruction::ORA, AddressingMode::Absolute, 3, 4};
            case 0x1D: return {Instruction::ORA, AddressingMode::AbsoluteX, 3, 4};
            case 0x19: return {Instruction::ORA, AddressingMode::AbsoluteY, 3, 4};
            case 0x01: return {Instruction::ORA, AddressingMode::IndirectX, 2, 6};
            case 0x11: return {Instruction::ORA, AddressingMode::IndirectY, 2, 5};

            // PHA
            case 0x48: return {Instruction::PHA, AddressingMode::Implied, 1, 3};

            // PHP
            case 0x08: return {Instruction::PHP, AddressingMode::Implied, 1, 3};

            // PLA
            case 0x68: return {Instruction::PLA, AddressingMode::Implied, 1, 4};

            // PLP
            case 0x28: return {Instruction::PLP, AddressingMode::Implied, 1, 4};

            // ROL
            case 0x2A: return {Instruction::ROL, AddressingMode::Accumulator, 1, 2};
            case 0x26: return {Instruction::ROL, AddressingMode::ZeroPage, 2, 5};
            case 0x36: return {Instruction::ROL, AddressingMode::ZeroPageX, 2, 6};
            case 0x2E: return {Instruction::ROL, AddressingMode::Absolute, 3, 6};
            case 0x3E: return {Instruction::ROL, AddressingMode::AbsoluteX, 3, 7};

            // ROR
            case 0x6A: return {Instruction::ROR, AddressingMode::Accumulator, 1, 2};
            case 0x66: return {Instruction::ROR, AddressingMode::ZeroPage, 2, 5};
            case 0x76: return {Instruction::ROR, AddressingMode::ZeroPageX, 2, 6};
            case 0x6E: return {Instruction::ROR, AddressingMode::Absolute, 3, 6};
            case 0x7E: return {Instruction::ROR, AddressingMode::AbsoluteX, 3, 7};

            // RTI
            case 0x40: return {Instruction::RTI, AddressingMode::Implied, 1, 6};

            // RTS
            case 0x60: return {Instruction::RTS, AddressingMode::Implied, 1, 6};

            // SBC
            case 0xE9: return {Instruction::SBC, AddressingMode::Immediate, 2, 2};
            case 0xE5: return {Instruction::SBC, AddressingMode::ZeroPage, 2, 3};
            case 0xF5: return {Instruction::SBC, AddressingMode::ZeroPageX, 2, 4};
            case 0xED: return {Instruction::SBC, AddressingMode::Absolute, 3, 4};
            case 0xFD: return {Instruction::SBC, AddressingMode::AbsoluteX, 3, 4};
            case 0xF9: return {Instruction::SBC, AddressingMode::AbsoluteY, 3, 4};
            case 0xE1: return {Instruction::SBC, AddressingMode::IndirectX, 2, 6};
            case 0xF1: return {Instruction::SBC, AddressingMode::IndirectY, 2, 5};

            // SEC
            case 0x38: return {Instruction::SEC, AddressingMode::Implied, 1, 2};

            // SED
            case 0xF8: return {Instruction::SED, AddressingMode::Implied, 1, 2};

            // SEI
            case 0x78: return {Instruction::SEI, AddressingMode::Implied, 1, 2};

            // STA
            case 0x85: return {Instruction::STA, AddressingMode::ZeroPage, 2, 3};
            case 0x95: return {Instruction::STA, AddressingMode::ZeroPageX, 2, 4};
            case 0x8D: return {Instruction::STA, AddressingMode::Absolute, 3, 4};
            case 0x9D: return {Instruction::STA, AddressingMode::AbsoluteX, 3, 5};
            case 0x99: return {Instruction::STA, AddressingMode::AbsoluteY, 3, 5};
            case 0x81: return {Instruction::STA,AddressingMode::IndirectX, 2, 6};
            case 0x91: return {Instruction::STA, AddressingMode::IndirectY, 2, 6};

            // STX
            case 0x86: return {Instruction::STX, AddressingMode::ZeroPage, 2, 3};
            case 0x96: return {Instruction::STX, AddressingMode::ZeroPageY, 2, 4};
            case 0x8E: return {Instruction::STX, AddressingMode::Absolute, 3, 4};

            // STY
            case 0x84: return {Instruction::STY, AddressingMode::ZeroPage, 2, 3};
            case 0x94: return {Instruction::STY, AddressingMode::ZeroPageX, 2, 4};
            case 0x8C: return {Instruction::STY, AddressingMode::Absolute, 3, 4};

            // TAX
            case 0xAA: return {Instruction::TAX, AddressingMode::Implied, 1, 2};

            // TAY
            case 0xA8: return {Instruction::TAY, AddressingMode::Implied, 1, 2};

            // TSX
            case 0xBA: return {Instruction::TSX, AddressingMode::Implied, 1, 2};

            // TXA
            case 0x8A: return {Instruction::TXA, AddressingMode::Implied, 1, 2};

            // TXS
            case 0x9A: return {Instruction::TXS, AddressingMode::Implied, 1, 2};

            // TYA
            case 0x98: return {Instruction::TYA,AddressingMode::Implied,  1, 2};

            default: return {Instruction::INVALID, AddressingMode::UNKNOWN, -1, -1};
        }
    }
};

#endif //NESEMULATOR_OPCODEHELPER_H
