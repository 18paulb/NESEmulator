//
// Created by Brandon Paul on 4/24/24.
//
#include<iostream>

using namespace std;

#include <vector>
#include "System/System.h"

int main() {
    // Load ROM file
    System nes = System();

    nes.getRomReader()->loadROMFile(
            (string &) "/Users/brandonpaul/CS/PersonalProjects/NESEmulator/tests/testROM/cpu_dummy_reads.nes",
            nes.getCPU());

    nes.getCPU()->initializeProgramCounter();

    for (int i = 0; i < 65536; ++i) {
        if (nes.getCPU()->getMemory(i) != '\0') {
            cout << i << ": " << nes.getCPU()->getMemory(i) << endl;
        }
    }

    nes.step(1);

    return 0;
}
