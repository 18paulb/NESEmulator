//
// Created by Brandon Paul on 10/16/24.
//

#include<string>

#include "System/System.h"
#include "utils/JsonTestReader.h"

using namespace std;

void assertEqual(const std::string& name, int expected, int actual);

int main(const int argc, char *argv[]) {

    string file = "/Users/brandonpaul/CS/PersonalProjects/NESEmulator/tests/JSONTests/00.json";

    // Read in the JSON file and parse all the data
    JsonTestReader testReader = JsonTestReader(file);

    // Because these are tests, we are going to skip all the ROM/PC initializing

    // Go through every single test parsed from that file
    for (int i = 0; i < testReader.getTests().size(); i++) {
        // Set CPU values
        Element test = testReader.getTests()[i];
        State initial = test.initial;
        State final = test.initial;

        auto testCPU = CPU(initial.pc, initial.stackPointer, initial.accumulator, initial.xRegister,
            initial.yRegister, initial.pStatus);

        // Sets the memory for the inital CPU state
        for (int j = 0; j < initial.ram.size(); j++) {
            vector<int> memoryVal = initial.ram[j];
            testCPU.setMemory(memoryVal[0], memoryVal[1]);
        }

        // Run Instructions
        for (int j = 0; j < test.cycles.size(); j++) {
            testCPU.executeInstruction();
        }

        // Verify that CPU matches final state
        assertEqual("PC", final.pc, testCPU.getProgramCounter());
        assertEqual("Accumulator", final.accumulator, testCPU.getAccumulator());
        assertEqual("X Register", final.xRegister, testCPU.getXRegister());
        assertEqual("Y Register", final.yRegister, testCPU.getYRegister());
        assertEqual("P Status", final.pStatus, testCPU.getPStatus());
    }

    return 0;
}

void assertEqual(const std::string& name, int expected, int actual) {
    if (expected == actual) {
        std::cout << name << " matches expected final state\n";
    } else {
        std::cout << name << " Expected: " << expected << " does not match CPU Result: " << actual << "\n";
    }
}