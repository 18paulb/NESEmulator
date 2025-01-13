//
// Created by Brandon Paul on 4/21/24.
//

#include "CPU/CPU.h"

#include <numeric>

// Manually increment PC during cases to add more control to PC since some instructions don't increment
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
            break;

        case PHA:
            executePHA();
            break;

        case PHP:
            break;

        case PLA:
            break;

        case PLP:
            break;

        case ROL:
            break;

        case ROR:
            break;

        case RTI:
            break;

        case RTS:
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

// TODO: Test
template<typename T>
void CPU::executeADC(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            ADC_Immediate(value);
            break;

        case ZeroPage:
            ADC_ZeroPage(value);
            break;

        case ZeroPageX:
            ADC_ZeroPageX(value);
            break;

        case Absolute:
            ADC_Absolute(value);
            break;

        case AbsoluteX:
            ADC_AbsoluteX(value);
            break;

        case AbsoluteY:
            ADC_AbsoluteY(value);
            break;

        case IndirectX:
            ADC_IndirectX(value);
            break;

        case IndirectY:
            ADC_IndirectY(value);
            break;

        default:
            cerr << "Invalid Addressing Mode for ADC" << endl;
    }
}

void CPU::ADC_Immediate(uint8_t val) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_ZeroPage(uint8_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;
    uint8_t val = memory[address];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_ZeroPageX(uint8_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;
    uint8_t val = memory[address + xRegister];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_Absolute(uint16_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;
    uint8_t val = memory[address];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_AbsoluteX(uint16_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;
    uint8_t val = memory[address + xRegister];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_AbsoluteY(uint16_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;
    uint8_t val = memory[address + yRegister];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_IndirectX(uint8_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;

    // Calculate the memory address
    uint8_t indirectAddress = address + xRegister;
    uint8_t lowByte = memory[indirectAddress];
    uint8_t highByte = memory[indirectAddress + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;
    uint8_t val = memory[targetAddress];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ADC_IndirectY(uint8_t address) {
    // Check if carry flag is set
    uint8_t carryIn = isFlagSet(StatusFlag::Carry) ? 1 : 0;
    uint8_t ogAccumulator = accumulator;

    // Calculate the memory address
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;
    targetAddress += yRegister;
    uint8_t val = memory[targetAddress];

    // Use 16-bit addition to detect carry
    // Not super faithful to hardware but a good shortcut
    uint16_t sum = accumulator + val + carryIn;
    accumulator = static_cast<uint8_t>(sum); // Automatic truncation to 8 bits

    // Check for signed overflow
    // Check if both inputs have same sign (NOT XOR) AND result has different sign from original
    // (result ^ A) & (result ^ memory) & $80
    bool overflowOccurred = (accumulator ^ ogAccumulator) & (accumulator ^ val) & BIT_7;

    // Update flags
    // Explain: sum > 0xFF, that means an int overflow occurred so a carry must be made
    (sum > 0xFF) ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    overflowOccurred ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    setZeroAndNegativeFlag(accumulator);
}

template<typename T>
void CPU::executeAND(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            AND_Immediate(value);
            break;

        case ZeroPage:
            AND_ZeroPage(value);
            break;

        case ZeroPageX:
            AND_ZeroPageX(value);
            break;

        case Absolute:
            AND_Absolute(value);
            break;

        case AbsoluteX:
            AND_AbsoluteX(value);
            break;

        case AbsoluteY:
            AND_AbsoluteY(value);
            break;

        case IndirectX:
            AND_IndirectX(value);
            break;

        case IndirectY:
            AND_IndirectY(value);
            break;

        default:
            cerr << "Invalid addressing mode for AND" << endl;
    }
}

void CPU::AND_Immediate(uint8_t value) {
    accumulator = accumulator & value;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::AND_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);

}

void CPU::AND_ZeroPageX(uint8_t address) {
    uint8_t val = memory[address + xRegister];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::AND_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::AND_AbsoluteX(uint16_t address) {
    uint8_t val = memory[address + xRegister];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::AND_AbsoluteY(uint16_t address) {
    uint8_t val = memory[address + yRegister];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::AND_IndirectX(uint8_t address) {
    uint8_t indirectAddress = address + xRegister;
    uint8_t lowByte = memory[indirectAddress];
    uint8_t highByte = memory[indirectAddress + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;

    uint8_t val = memory[targetAddress];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::AND_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;
    targetAddress += yRegister;

    uint8_t val = memory[targetAddress];
    accumulator = accumulator & val;
    setZeroAndNegativeFlag(accumulator);
}

// FIXME: Potential Issues
// 1. Not sure if N and Z flags should be set when changing memory, only accumulator
template<typename T>
void CPU::executeASL(AddressingMode mode, T value) {
    switch (mode) {
        case Accumulator:
            ASL_Accumulator();
            break;

        case ZeroPage:
            ASL_ZeroPage(value);
            break;

        case ZeroPageX:
            ASL_ZeroPageX(value);
            break;

        case Absolute:
            ASL_Absolute(value);
            break;

        case AbsoluteX:
            ASL_AbsoluteX(value);
            break;

        default:
            cerr << "Invalid addressing mode for ASL" << endl;
    }
}

void CPU::ASL_Accumulator() {
    // Capture bit 7 of the accumulator before the shift
    uint8_t bit7 = GET_BIT(accumulator, 7);
    accumulator = accumulator << 1;

    // bit 7 of original accumulator is the new value of the carry flag
    bit7 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::ASL_ZeroPage(uint8_t address) {
    // Capture bit 7 of the accumulator before the shift
    uint8_t bit7 = GET_BIT(memory[address], 7);
    memory[address] = memory[address] << 1;

    // bit 7 of original memory value is the new value of the carry flag
    bit7 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::ASL_ZeroPageX(uint8_t address) {
    // Capture bit 7 of the accumulator before the shift
    uint8_t adjustedAddress = address + xRegister;
    uint8_t bit7 = GET_BIT(memory[adjustedAddress], 7);
    memory[adjustedAddress] = memory[adjustedAddress] << 1;

    // bit 7 of original memory value is the new value of the carry flag
    bit7 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[adjustedAddress]);
}

void CPU::ASL_Absolute(uint16_t address) {
    // Capture bit 7 of the accumulator before the shift
    uint8_t bit7 = GET_BIT(memory[address], 7);
    memory[address] = memory[address] << 1;

    // bit 7 of original memory value is the new value of the carry flag
    bit7 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::ASL_AbsoluteX(uint16_t address) {
    // Capture bit 7 of the accumulator before the shift
    uint16_t adjustedAddress = address + xRegister;
    uint8_t bit7 = GET_BIT(memory[adjustedAddress], 7);
    memory[adjustedAddress] = memory[adjustedAddress] << 1;

    // bit 7 of original memory value is the new value of the carry flag
    bit7 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[adjustedAddress]);
}

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

template<typename T>
void CPU::executeBIT(T address) {
    // Set Zero Flag on result of A & memory
    uint8_t val = memory[address];
    (accumulator & val) == 0 ? setFlag(Zero) : clearFlag(Zero);

    uint8_t bit6 = GET_BIT(val, 6);
    uint8_t bit7 = GET_BIT(val, 7);

    bit6 != 0 ? setFlag(StatusFlag::Overflow) : clearFlag(StatusFlag::Overflow);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
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

template<typename T>
void CPU::executeCMP(AddressingMode mode, T val) {
    switch (mode) {
        case Immediate:
            CMP_Immediate(val);
            break;

        case ZeroPage:
            CMP_ZeroPage(val);
            break;

        case ZeroPageX:
            CMP_ZeroPageX(val);
            break;

        case Absolute:
            CMP_Absolute(val);
            break;

        case AbsoluteX:
            CMP_AbsoluteX(val);
            break;

        case AbsoluteY:
            CMP_AbsoluteY(val);
            break;

        case IndirectX:
            CMP_IndirectX(val);
            break;

        case IndirectY:
            CMP_IndirectY(val);
            break;

        default:
            cerr << "Invalid addressing mode for CMP" << endl;
    }
}

void CPU::CMP_Immediate(uint8_t val) {
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_ZeroPageX(uint8_t address) {
    uint8_t val = memory[address + xRegister];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_AbsoluteX(uint16_t address) {
    uint8_t val = memory[address + xRegister];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_AbsoluteY(uint16_t address) {
    uint8_t val = memory[address + yRegister];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_IndirectX(uint8_t address) {
    uint8_t indirectAddress = address + xRegister;
    uint8_t lowByte = memory[indirectAddress];
    uint8_t highByte = memory[indirectAddress + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;

    uint8_t val = memory[targetAddress];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CMP_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;
    targetAddress += yRegister;

    uint8_t val = memory[targetAddress];
    uint8_t result = accumulator - val;
    uint8_t bit7 = GET_BIT(result, 7);

    accumulator >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    accumulator == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

template<typename T>
void CPU::executeCPX(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            CPX_Immediate(value);
            break;

        case ZeroPage:
            CPX_ZeroPage(value);
            break;

        case Absolute:
            CPX_Absolute(value);
            break;

        default:
            cout << "Invalid addressing mode for CPX" << endl;
    }
}

void CPU::CPX_Immediate(uint8_t val) {
    uint8_t result = xRegister - val;
    uint8_t bit7 = GET_BIT(result, 7);

    xRegister >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    xRegister == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CPX_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    uint8_t result = xRegister - val;
    uint8_t bit7 = GET_BIT(result, 7);

    xRegister >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    xRegister == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CPX_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    uint8_t result = xRegister - val;
    uint8_t bit7 = GET_BIT(result, 7);

    xRegister >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    xRegister == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

template<typename T>
void CPU::executeCPY(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            CPY_Immediate(value);
        break;

        case ZeroPage:
            CPY_ZeroPage(value);
        break;

        case Absolute:
            CPY_Absolute(value);
        break;

        default:
            cout << "Invalid addressing mode for CPX" << endl;
    }
}

void CPU::CPY_Immediate(uint8_t val) {
    uint8_t result = yRegister - val;
    uint8_t bit7 = GET_BIT(result, 7);

    yRegister >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    yRegister == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CPY_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    uint8_t result = yRegister - val;
    uint8_t bit7 = GET_BIT(result, 7);

    yRegister >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    yRegister == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

void CPU::CPY_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    uint8_t result = yRegister - val;
    uint8_t bit7 = GET_BIT(result, 7);

    yRegister >= val ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    yRegister == val ? setFlag(StatusFlag::Zero) : clearFlag(StatusFlag::Zero);
    bit7 != 0 ? setFlag(StatusFlag::Negative) : clearFlag(StatusFlag::Negative);
}

template<typename T>
void CPU::executeDEC(AddressingMode mode, T value) {
    switch (mode) {
        case ZeroPage:
            DEC_ZeroPage(value);
            break;

        case ZeroPageX:
            DEC_ZeroPageX(value);
            break;

        case Absolute:
            DEC_Absolute(value);
            break;

        case AbsoluteX:
            DEC_AbsoluteX(value);
            break;

        default:
            cout << "Invalid addressing mode for DEC" << endl;
    }
}

void CPU::DEC_ZeroPage(uint8_t address) {
    memory[address] -= 1;
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::DEC_ZeroPageX(uint8_t address) {
    memory[address + xRegister] -= 1;
    setZeroAndNegativeFlag(memory[address + xRegister]);
}

void CPU::DEC_Absolute(uint16_t address) {
    memory[address] -= 1;
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::DEC_AbsoluteX(uint16_t address) {
    memory[address + xRegister] -= 1;
    setZeroAndNegativeFlag(memory[address + xRegister]);
}

void CPU::executeDEY() {
    yRegister -= 1;
    setZeroAndNegativeFlag(yRegister);
}

void CPU::executeDEX() {
    xRegister -= 1;
    setZeroAndNegativeFlag(xRegister);
}

template<typename T>
void CPU::executeEOR(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            EOR_Immediate(value);
            break;

        case ZeroPage:
            EOR_ZeroPage(value);
            break;

        case ZeroPageX:
            EOR_ZeroPageX(value);
            break;

        case Absolute:
            EOR_Absolute(value);
            break;

        case AbsoluteX:
            EOR_AbsoluteX(value);
            break;

        case AbsoluteY:
            EOR_AbsoluteY(value);
            break;

        case IndirectX:
            EOR_IndirectX(value);
            break;

        case IndirectY:
            EOR_IndirectY(value);
            break;

        default:
            cout << "Invalid addressing mode for EOR" << endl;
    }
}

void CPU::EOR_Immediate(uint8_t val) {
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_ZeroPage(uint8_t address) {
    uint8_t val = memory[address];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_ZeroPageX(uint8_t address) {
    uint8_t val = memory[address + xRegister];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_Absolute(uint16_t address) {
    uint8_t val = memory[address];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_AbsoluteX(uint16_t address) {
    uint8_t val = memory[address + xRegister];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_AbsoluteY(uint16_t address) {
    uint8_t val = memory[address + yRegister];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_IndirectX(uint8_t address) {
    uint8_t indirectAddress = address + xRegister;
    uint8_t lowByte = memory[indirectAddress];
    uint8_t highByte = memory[indirectAddress + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;

    uint8_t val = memory[targetAddress];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::EOR_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;
    targetAddress += yRegister;

    uint8_t val = memory[targetAddress];
    accumulator ^= val;
    setZeroAndNegativeFlag(accumulator);
}

template<typename T>
void CPU::executeINC(AddressingMode mode, T value) {
    switch (mode) {
        case ZeroPage:
            INC_ZeroPage(value);
        break;

        case ZeroPageX:
            INC_ZeroPageX(value);
        break;

        case Absolute:
            INC_Absolute(value);
        break;

        case AbsoluteX:
            INC_AbsoluteX(value);
        break;

        default:
            cout << "Invalid addressing mode for DEC" << endl;
    }
}

void CPU::INC_ZeroPage(uint8_t address) {
    memory[address] += 1;
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::INC_ZeroPageX(uint8_t address) {
    memory[address + xRegister] += 1;
    setZeroAndNegativeFlag(memory[address + xRegister]);
}

void CPU::INC_Absolute(uint16_t address) {
    memory[address] += 1;
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::INC_AbsoluteX(uint16_t address) {
    memory[address + xRegister] += 1;
    setZeroAndNegativeFlag(memory[address + xRegister]);
}

void CPU::executeINX() {
    xRegister += 1;
    setZeroAndNegativeFlag(xRegister);
}

void CPU::executeINY() {
    yRegister += 1;
    setZeroAndNegativeFlag(yRegister);
}

template<typename T>
void CPU::executeJMP(AddressingMode mode, T value) {
    switch (mode) {
        case Absolute:
            JMP_Absolute(value);
            break;

        case Indirect:
            JMP_Indirect(value);
            break;

        default:
            cout << "Invalid addressing mode for JMP" << endl;
    }
}

void CPU::JMP_Absolute(uint16_t address) {
    programCounter = memory[address];
}

/*
    Unfortunately, because of a CPU bug, if this 2-byte variable has an address ending in $FF and thus crosses a page,
    then the CPU fails to increment the page when reading the second byte and thus reads the wrong address.
    For example, JMP ($03FF) reads $03FF and $0300 instead of $0400.
    Care should be taken to ensure this variable does not cross a page.
*/
void CPU::JMP_Indirect(uint16_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    uint16_t targetAddress = highByte << 8 | lowByte;

    programCounter = memory[targetAddress];
}

/*
    Notably, the return address on the stack points 1 byte before the start of the next instruction,
    rather than directly at the instruction.
    This is because RTS increments the program counter before the next instruction is fetched.
*/
void CPU::executeJSR(uint16_t address) {
    // This is the return address that we will be pushing to the stack, 1 byte LESS than the start
    // of the next instruction
    uint16_t returnAddress = programCounter - 1;

    // Break PC into high and low bytes
    uint8_t highByte = (returnAddress >> 8) & 0xFF;
    uint8_t lowByte = returnAddress & 0xFF;

    // Push high byte first (due to 6502 being little-endian)
    pushToStack(highByte);
    pushToStack(lowByte);

    programCounter = address;
}

template<typename T>
void CPU::executeLDA(AddressingMode mode, T value) {
    // Switch based on the addressing mode
    switch (mode) {
        case Immediate:
            LDA_Immediate(static_cast<uint8_t>(value));
            break;
        case ZeroPage:
            LDA_ZeroPage(static_cast<uint8_t>(value));
            break;
        case ZeroPageX:
            LDA_ZeroPageX(static_cast<uint8_t>(value));
            break;
        case IndirectX:
            LDA_IndirectX(static_cast<uint8_t>(value));
            break;
        case IndirectY:
            LDA_IndirectY(static_cast<uint8_t>(value));
            break;
        case Absolute:
            LDA_Absolute(static_cast<uint16_t>(value));
            break;
        case AbsoluteX:
            LDA_AbsoluteX(static_cast<uint16_t>(value));
            break;
        case AbsoluteY:
            LDA_AbsoluteY(static_cast<uint16_t>(value));
            break;
        default:
            cout << "Error with LDA type" << endl;
    }

    setZeroAndNegativeFlag(accumulator);
}

void CPU::LDA_Immediate(uint8_t value) {
    // Load value at memory address into the accumulator
    accumulator = value;
}

void CPU::LDA_ZeroPage(uint8_t address) {
    accumulator = memory[address];
}

void CPU::LDA_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xRegister;
    accumulator = memory[newAddress];
}

void CPU::LDA_Absolute(uint16_t address) {
    accumulator = memory[address];
}

void CPU::LDA_AbsoluteX(uint16_t address) {
    uint16_t newAddress = address + xRegister;
    accumulator = memory[newAddress];
}

void CPU::LDA_AbsoluteY(uint16_t address) {
    uint16_t newAddress = address + yRegister;
    accumulator = memory[newAddress];
}

void CPU::LDA_IndirectX(uint8_t address) {
    uint8_t val = address + xRegister;
    uint8_t lowByte = memory[val];
    uint8_t highByte = memory[val + 1];

    // Combine the low and high bytes to form a 16-bit target address
    uint16_t targetAddress = (highByte << 8) | lowByte;

    accumulator = memory[targetAddress];
}

void CPU::LDA_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    uint16_t targetAddress = (highByte << 8) | lowByte;
    targetAddress += yRegister;

    accumulator = memory[targetAddress];
}

template<typename T>
void CPU::executeLDX(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            LDX_Immediate(static_cast<uint8_t>(value));
            break;
        case ZeroPage:
            LDX_ZeroPage(static_cast<uint8_t>(value));
            break;
        case ZeroPageY:
            LDX_ZeroPageY(static_cast<uint8_t>(value));
            break;
        case Absolute:
            LDX_Absolute(static_cast<uint16_t>(value));
            break;
        case AbsoluteY:
            LDX_AbsoluteY(static_cast<uint16_t>(value));
            break;
        default:
            cout << "Error with LDX type" << endl;
    }

    setZeroAndNegativeFlag(xRegister);
}

void CPU::LDX_Immediate(uint8_t value) {
    xRegister = value;
}

void CPU::LDX_ZeroPage(uint8_t address) {
    xRegister = memory[address];
}

void CPU::LDX_ZeroPageY(uint8_t address) {
    uint8_t newAddress = address + yRegister;
    xRegister = memory[newAddress];
}

void CPU::LDX_Absolute(uint16_t address) {
    xRegister = memory[address];
}

void CPU::LDX_AbsoluteY(uint16_t address) {
    uint16_t newAddress = address + yRegister;
    xRegister = memory[newAddress];
}

template<typename T>
void CPU::executeLDY(AddressingMode mode, T value) {
    switch (mode) {
        case Immediate:
            LDY_Immediate(static_cast<uint8_t>(value));
            break;
        case ZeroPage:
            LDY_ZeroPage(static_cast<uint8_t>(value));
            break;
        case ZeroPageX:
            LDY_ZeroPageX(static_cast<uint8_t>(value));
            break;
        case Absolute:
            LDY_Absolute(static_cast<uint16_t>(value));
            break;
        case AbsoluteX:
            LDY_AbsoluteX(static_cast<uint16_t>(value));
            break;
        default:
            cout << "Error with LDY type" << endl;
    }

    setZeroAndNegativeFlag(yRegister);
}


void CPU::LDY_Immediate(uint8_t value) {
    yRegister = value;
}

void CPU::LDY_ZeroPage(uint8_t address) {
    yRegister = memory[address];
}

void CPU::LDY_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xRegister;
    yRegister = memory[newAddress];
}

void CPU::LDY_Absolute(uint16_t address) {
    yRegister = memory[address];
}

void CPU::LDY_AbsoluteX(uint16_t address) {
    uint16_t newAddress = address + xRegister;
    yRegister = memory[newAddress];
}


// FIXME: Potential Issues
// 1. Not sure if N and Z flags should be set when changing memory, only accumulator
template<typename T>
void CPU::executeLSR(AddressingMode mode, T value) {
    switch (mode) {
        case Accumulator:
            LSR_Accumulator();
            break;

        case ZeroPage:
            LSR_ZeroPage(value);
            break;

        case ZeroPageX:
            LSR_ZeroPageX(value);
            break;

        case Absolute:
            LSR_Absolute(value);
            break;

        case AbsoluteX:
            LSR_AbsoluteX(value);
            break;

        default:
            cerr << "Invalid addressing mode for ASL" << endl;
    }
}

void CPU::LSR_Accumulator() {
    // Capture bit 0 of the accumulator before the shift
    uint8_t bit0 = GET_BIT(accumulator, 0);
    accumulator = accumulator >> 1;

    // bit 0 of original accumulator is the new value of the carry flag
    bit0 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(accumulator);
}

void CPU::LSR_ZeroPage(uint8_t address) {
    // Capture bit 0 of the accumulator before the shift
    uint8_t bit0 = GET_BIT(memory[address], 0);
    memory[address] = memory[address] >> 1;

    // bit 0 of original memory value is the new value of the carry flag
    bit0 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::LSR_ZeroPageX(uint8_t address) {
    // Capture bit 0 of the accumulator before the shift
    uint8_t adjustedAddress = address + xRegister;
    uint8_t bit0 = GET_BIT(memory[adjustedAddress], 0);
    memory[adjustedAddress] = memory[adjustedAddress] >> 1;

    // bit 0 of original memory value is the new value of the carry flag
    bit0 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[adjustedAddress]);
}

void CPU::LSR_Absolute(uint16_t address) {
    // Capture bit 0 of the accumulator before the shift
    uint8_t bit0 = GET_BIT(memory[address], 0);
    memory[address] = memory[address] >> 1;

    // bit 0 of original memory value is the new value of the carry flag
    bit0 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[address]);
}

void CPU::LSR_AbsoluteX(uint16_t address) {
    // Capture bit 0 of the accumulator before the shift
    uint16_t adjustedAddress = address + xRegister;
    uint8_t bit0 = GET_BIT(memory[adjustedAddress], 0);
    memory[adjustedAddress] = memory[adjustedAddress] >> 1;

    // bit 0 of original memory value is the new value of the carry flag
    bit0 != 0 ? setFlag(StatusFlag::Carry) : clearFlag(StatusFlag::Carry);
    setZeroAndNegativeFlag(memory[adjustedAddress]);
}

template<typename T>
void CPU::executeSTA(AddressingMode mode, T value) {
    switch (mode) {
        case ZeroPage:
            STA_ZeroPage(static_cast<uint8_t>(value));
            break;
        case ZeroPageX:
            STA_ZeroPageX(static_cast<uint8_t>(value));
            break;
        case Absolute:
            STA_Absolute(static_cast<uint16_t>(value));
            break;
        case AbsoluteX:
            STA_AbsoluteX(static_cast<uint16_t>(value));
            break;
        case AbsoluteY:
            STA_AbsoluteY(static_cast<uint16_t>(value));
            break;
        case IndirectX:
            STA_IndirectX(static_cast<uint8_t>(value));
            break;
        case IndirectY:
            STA_IndirectY(static_cast<uint8_t>(value));
            break;
        default:
            cout << "Error with STA type" << endl;
    }
}

void CPU::STA_ZeroPage(uint8_t address) {
    memory[address] = accumulator;
}

void CPU::STA_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xRegister;
    memory[newAddress] = accumulator;
}

void CPU::STA_Absolute(uint16_t address) {
    memory[address] = accumulator;
}

void CPU::STA_AbsoluteX(uint16_t address) {
    uint16_t newAddress = address + xRegister;
    memory[newAddress] = accumulator;
}

void CPU::STA_AbsoluteY(uint16_t address) {
    uint16_t newAddress = address + yRegister;
    memory[newAddress] = accumulator;
}

void CPU::STA_IndirectX(uint8_t address) {
    uint8_t val = address + xRegister;
    uint8_t lowByte = memory[val];
    uint8_t highByte = memory[val + 1];

    // Combine the low and high bytes to form a 16-bit target address
    uint16_t targetAddress = (highByte << 8) | lowByte;

    memory[targetAddress] = accumulator;
}

void CPU::STA_IndirectY(uint8_t address) {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];

    uint16_t targetAddress = (highByte << 8) | lowByte;

    targetAddress += yRegister;

    memory[targetAddress] = accumulator;
}


template<typename T>
void CPU::executeSTX(AddressingMode mode, T value) {
    switch (mode) {
        case ZeroPage:
            STX_ZeroPage(static_cast<uint8_t>(value));
            break;
        case ZeroPageY:
            STX_ZeroPageY(static_cast<uint8_t>(value));
            break;
        case Absolute:
            STX_Absolute(static_cast<uint16_t>(value));
            break;
        default:
            cout << "Error with STX type" << endl;
    }
}

void CPU::STX_ZeroPage(uint8_t address) {
    memory.setMemory(address, xRegister);
}

void CPU::STX_ZeroPageY(uint8_t address) {
    uint8_t newAddress = address + yRegister;
    memory.setMemory(newAddress, xRegister);
}

void CPU::STX_Absolute(uint16_t address) {
    memory.setMemory(address, xRegister);
}


template<typename T>
void CPU::executeSTY(AddressingMode mode, T value) {
    switch (mode) {
        case ZeroPage:
            STY_ZeroPage(static_cast<uint8_t>(value));
            break;
        case ZeroPageX:
            STY_ZeroPageX(static_cast<uint8_t>(value));
            break;
        case Absolute:
            STY_Absolute(static_cast<uint16_t>(value));
            break;
        default:
            cout << "Error with STY type" << endl;
    }
}


void CPU::STY_ZeroPage(uint8_t address) {
    memory.setMemory(address, yRegister);
}

void CPU::STY_ZeroPageX(uint8_t address) {
    uint8_t newAddress = address + xRegister;
    memory.setMemory(newAddress, yRegister);
}

void CPU::STY_Absolute(uint16_t address) {
    memory.setMemory(address, yRegister);
}

void CPU::executePHA() {
    pushToStack(accumulator);
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

void CPU::executeTAX() {
    xRegister = accumulator;
    setZeroAndNegativeFlag(xRegister);
}

void CPU::executeTAY() {
    yRegister = accumulator;
    setZeroAndNegativeFlag(yRegister);
}

void CPU::executeTSX() {
    xRegister = stackPointer;
    setZeroAndNegativeFlag(xRegister);
}

void CPU::executeTXA() {
    accumulator = xRegister;
    setZeroAndNegativeFlag(accumulator);
}

void CPU::executeTXS() {
    stackPointer = xRegister;
}

void CPU::executeTYA() {
    accumulator = yRegister;
    setZeroAndNegativeFlag(accumulator);
}






