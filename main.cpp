//
// Created by Brandon Paul on 4/24/24.
//

#include "System/System.h"
#include<iostream>


using namespace std;

int main(const int argc, char *argv[]) {

    // Default ROM file path
     const string defaultRomFilePath = "/Users/brandonpaul/CS/PersonalProjects/NESEmulator/tests/other/balloonfight.nes";

    // Use command line argument if provided, otherwise use default
     string romFilePath = (argc > 1) ? argv[1] : defaultRomFilePath;

    System nes = System();

    // Load ROM file
    nes.getRomReader().loadROMFile(
            (string &) romFilePath,
            nes.getCPU());

    nes.getCPU().initializeProgramCounter();

    nes.step(1);

    return 0;
}
