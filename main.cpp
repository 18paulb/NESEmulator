//
// Created by Brandon Paul on 4/24/24.
//
#include<iostream>

using namespace std;

#include <vector>
#include "System.h"

int main() {
    // Load ROM file
    System nes = System();

    nes.getRomReader().loadROM(
            (string &) "/Users/brandonpaul/CS/PersonalProjects/NESEmulator/tests/testROM/02-immediate.nes");

    nes.getRomReader().loadROMIntoCPU(nes.getCPU());

    return 0;
}
