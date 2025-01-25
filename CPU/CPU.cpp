//
// Created by Brandon Paul on 4/21/24.
//

#include "CPU/CPU.h"

template<typename T>
void CPU::delegateInstructionExecution(InstructionMetadata instruction, T value) {
    Instruction instructionType = instruction.instruction;
    AddressingMode addressingMode = instruction.addressingMode;
    switch (instructionType) {
        case ADC:
            executeADC(addressingMode, value);
            break;

        case AND:
            executeAND(addressingMode, value);
            break;

        case ASL:
            executeASL(addressingMode, value);
            break;

        // Changes PC in different ways depending on Carry Flag (Check Method)
        case BCC:
            executeBCC(value);
            break;

        // Changes PC in different ways depending on Carry Flag (Check Method)
        case BCS:
            executeBCS(value);
            break;

        case BEQ:
            // Changes PC in different ways depending on Zero Flag (Check Method)
            executeBEQ(value);
            break;

        case BIT:
            executeBIT(value);
            break;

        case BMI:
            executeBMI(value);
            break;

        // Changes PC in different ways depending on Zero Flag (Check Method)
        case BNE:
            executeBNE(value);
            break;

        // Changes PC in different ways depending on Negative Flag (Check Method)
        case BPL:
            executeBPL(value);
            break;

        // Doesn't increment PC, sets value during execution
        case BRK:
            executeBRK();
            break;

        // Changes PC in different ways depending on Overflow Flag (Check Method)
        case BVC:
            executeBVC(value);
            break;

        // Changes PC in different ways depending on Overflow Flag (Check Method)
        case BVS:
            executeBVS(value);
            break;

        case CLC:
            executeCLC();
            break;

        case CLD:
            executeCLD();
            break;

        case CLI:
            executeCLI();
            break;

        case CLV:
            executeCLV();
            break;

        case CMP:
            executeCMP(addressingMode, value);
            break;

        case CPX:
            executeCPX(addressingMode, value);
            break;

        case CPY:
            executeCPY(addressingMode, value);
            break;

        case DEC:
            executeDEC(addressingMode, value);
            break;

        case DEX:
            executeDEX();
            break;

        case DEY:
            executeDEY();
            break;

        case EOR:
            executeEOR(addressingMode, value);
            break;

        case INC:
            executeINC(addressingMode, value);
            break;

        case INX:
            executeINX();
            break;

        case INY:
            executeINY();
            break;

        case JMP:
            executeJMP(addressingMode, value);
            break;

        case JSR:
            executeJSR(value);
            break;

        case LDA:
            executeLDA(addressingMode, value);
            break;

        case LDX:
            executeLDX(addressingMode, value);
            break;

        case LDY:
            executeLDY(addressingMode, value);
            break;

        case LSR:
            executeLSR(addressingMode, value);
            break;

        case NOP:
            // No instruction, used to waste CPU cycles
            break;

        case ORA:
            executeORA(addressingMode, value);
            break;

        case PHA:
            executePHA();
            break;

        case PHP:
            executePHP();
            break;

        case PLA:
            executePLA();
            break;

        case PLP:
            executePLP();
            break;

        case ROL:
            executeROL(addressingMode, value);
            break;

        case ROR:
            executeROR(addressingMode, value);
            break;

        case RTI:
            executeRTI();
            break;

        case RTS:
            executeRTS();
            break;

        case SBC:
            break;

        case SEC:
            executeSEC();
            break;

        case SED:
            executeSED();
            break;

        case SEI:
            executeSEI();
            break;

        case STA:
            executeSTA(addressingMode, value);
            break;

        case STX:
            executeSTX(addressingMode, value);
            break;

        case STY:
            executeSTY(addressingMode, value);
            break;

        case TAX:
            executeTAX();
            break;

        case TAY:
            executeTAY();
            break;

        case TSX:
            executeTSX();
            break;

        case TXA:
            executeTXA();
            break;

        case TXS:
            executeTXS();
            break;

        case TYA:
            executeTYA();
            break;

        default:
            cout << "Invalid" << endl;
    }
}
template void CPU::delegateInstructionExecution<uint8_t>(InstructionMetadata, uint8_t);
template void CPU::delegateInstructionExecution<uint16_t>(InstructionMetadata, uint16_t);

void CPU::setFlag(StatusFlag flag) {
    switch (flag) {
        case Carry:
            pStatus |= FLAG_C;
        break;
        case Zero:
            pStatus |= FLAG_Z;
        break;
        case InterruptDisable:
            pStatus |= FLAG_I;
        break;
        case Break:
            pStatus |= FLAG_B;
        break;
        case Decimal:
            pStatus |= FLAG_D;
        break;
        case EXTRA:
            pStatus |= FLAG_EXTRA;
        break;
        case Overflow:
            pStatus |= FLAG_V;
        break;
        case Negative:
            pStatus |= FLAG_N;
        break;
        default:
            cerr << "Unknown flag " << flag << endl;
    }
}

void CPU::clearFlag(StatusFlag flag) {
    switch (flag) {
        case Carry:
            pStatus &= ~FLAG_C;
        break;
        case Zero:
            pStatus &= ~FLAG_Z;
        break;
        case InterruptDisable:
            pStatus &= ~FLAG_I;
        break;
        case Break:
            pStatus &= ~FLAG_B;
        break;
        case Decimal:
            pStatus &= ~FLAG_D;
        break;
        case EXTRA:
            pStatus &= ~FLAG_EXTRA;
        break;
        case Overflow:
            pStatus &= ~FLAG_V;
        break;
        case Negative:
            pStatus &= ~FLAG_N;
        break;
        default:
            cerr << "Unknown flag " << flag << endl;
    }
}

bool CPU::isFlagSet(StatusFlag flag) const {
    switch (flag) {
        case Carry:
            return pStatus & FLAG_C;

        case Zero:
            return pStatus & FLAG_Z;

        case InterruptDisable:
            return pStatus & FLAG_I;

        case Break:
            return pStatus & FLAG_B;

        case Decimal:
            return pStatus & FLAG_D;

        case EXTRA:
            return pStatus & FLAG_EXTRA;

        case Overflow:
            return pStatus & FLAG_V;

        case Negative:
            return pStatus & FLAG_N;

        default:
            return false;
    }
}

void CPU::setZeroAndNegativeFlag(uint8_t val) {
    // If value is 0
    val == 0 ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);

    // if bit 7 of the register is set
    val & BIT_7 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}