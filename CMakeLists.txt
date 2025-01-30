cmake_minimum_required(VERSION 3.26)
project(NESEmulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

set(COMMON_SOURCES
        CPU/CPU.cpp
        CPU/CPU.h
        CPU/Opcode/AddressingMode.h
        CPU/StatusFlag.h
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

# Main executable
add_executable(NESEmulator
        ${COMMON_SOURCES}
        main.cpp
)

# Test executable
add_executable(NESEmulatorTests
        ${COMMON_SOURCES}
        tests/tests_main.cpp
        tests/utils/JsonTestReader.h
)

target_link_libraries(NESEmulator PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(NESEmulatorTests PRIVATE nlohmann_json::nlohmann_json)