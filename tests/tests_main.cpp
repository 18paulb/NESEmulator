//
// Created by Brandon Paul on 10/16/24.
//
// CPU tests driven by the per-opcode JSON files in tests/JSONTests (SingleStepTests format).
// Each JSON file becomes one GoogleTest test; every case inside it is checked, and failures
// are reported with the case name (e.g. "00 35 26").
//

#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

#include "System/System.h"
#include "utils/JsonTestReader.h"

namespace {

// After this many failing cases in one opcode file, stop printing details (still counted)
constexpr int kMaxReportedFailures = 10;

// Find every *.json file in the test data folder, e.g. {"00", "01", ...}
std::vector<std::string> findOpcodeFiles() {
    std::vector<std::string> names;
    for (const auto& entry : std::filesystem::directory_iterator(TEST_DATA_DIR)) {
        if (entry.path().extension() == ".json") {
            names.push_back(entry.path().stem().string());
        }
    }
    std::sort(names.begin(), names.end());
    return names;
}

// Compares one value and records a readable line if it differs
void check(std::ostringstream& mismatches, const std::string& field, int expected, int actual) {
    if (expected != actual) {
        mismatches << "  " << field << ": expected " << expected << ", got " << actual << "\n";
    }
}

}  // namespace

class OpcodeTest : public ::testing::TestWithParam<std::string> {};

TEST_P(OpcodeTest, MatchesJsonTests) {
    const std::string file = std::string(TEST_DATA_DIR) + "/" + GetParam() + ".json";
    JsonTestReader reader(file);
    const auto& tests = reader.getTests();
    ASSERT_FALSE(tests.empty()) << "No tests loaded from " << file;

    int failedCases = 0;

    for (const auto& test : tests) {
        const State& initial = test.initial;
        const State& final = test.final;

        CPU cpu(initial.pc, initial.stackPointer, initial.accumulator, initial.xRegister,
                initial.yRegister, initial.pStatus);

        for (const auto& memoryVal : initial.ram) {
            cpu.setMemory(memoryVal[0], memoryVal[1]);
        }

        // Each JSON case is exactly one instruction ("cycles" are its bus accesses, not instructions)
        cpu.executeInstruction();

        std::ostringstream mismatches;
        check(mismatches, "PC", final.pc, cpu.getProgramCounter());
        check(mismatches, "Accumulator", final.accumulator, cpu.getAccumulator());
        check(mismatches, "X Register", final.xRegister, cpu.getXRegister());
        check(mismatches, "Y Register", final.yRegister, cpu.getYRegister());
        check(mismatches, "P Status", final.pStatus, cpu.getPStatus());
        check(mismatches, "Stack Pointer", final.stackPointer, cpu.getStackPointer());

        for (const auto& memoryVal : final.ram) {
            check(mismatches, "Memory[" + std::to_string(memoryVal[0]) + "]",
                  memoryVal[1], cpu.getMemory(memoryVal[0]));
        }

        if (!mismatches.str().empty()) {
            failedCases++;
            if (failedCases <= kMaxReportedFailures) {
                ADD_FAILURE() << "Case [" << test.name << "]\n" << mismatches.str();
            }
        }
    }

    EXPECT_EQ(failedCases, 0) << failedCases << " of " << tests.size()
                              << " cases failed for opcode " << GetParam();
}

INSTANTIATE_TEST_SUITE_P(
    CPU, OpcodeTest, ::testing::ValuesIn(findOpcodeFiles()),
    [](const ::testing::TestParamInfo<std::string>& info) { return "op_" + info.param; });
