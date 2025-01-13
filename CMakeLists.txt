cmake_minimum_required(VERSION 3.26)
project(NESEmulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

# Main executable
add_executable(NESEmulator
        CPU/CPU.cpp
        CPU/CPU.h
        CPU/Opcode/AddressingMode.h
        CPU/StatusFlag.h
        main.cpp
        tests/tests.cpp
        System/System.h
        System/System.cpp
        CPU/Memory/Memory.h
        CPU/Memory/Memory.cpp
        CPU/Instruction/TransferInstruction.cpp
        CPU/Instruction/StackInstruction.cpp
        CPU/Instruction/DecrementIncrementInstruction.cpp
        CPU/Instruction/ArithmeticInstruction.cpp
        CPU/Instruction/LogicalInstruction.cpp
        CPU/Instruction/ShiftRotateInstruction.cpp
        CPU/Instruction/FlagInstruction.cpp
        CPU/Instruction/ComparisonInstruction.cpp
        CPU/Instruction/BranchInstruction.cpp
        CPU/Instruction/JumpInstruction.cpp
        CPU/Instruction/InterruptInstruction.cpp
        CPU/Instruction/OtherInstruction.cpp
        ROM/ROMReader.cpp
        ROM/ROMReader.h
        CPU/Opcode/OpcodeHelper.h
        System/SystemPart.h
        CPU/Opcode/Instruction.h
        HelperClasses/InstructionMetadata.h
)

# Test executable
#add_executable(NESEmulatorTests
#        CPU.cpp
#        CPU.h
#        AddressingMode.h
#        StatusFlag.h
#        tests/tests.cpp
#)
#
## Optionally, you can use target_include_directories to include directories for specific targets
#target_include_directories(NESEmulatorTests PRIVATE tests)
#
## Optionally, you can use target_link_libraries if your test executable depends on external libraries
## For example:
## target_link_libraries(NESEmulatorTests some_external_library)
