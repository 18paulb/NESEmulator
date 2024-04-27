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

    std::vector<uint8_t> romData = nes.loadROM("/Users/brandonpaul/CS/PersonalProjects/NESEmulator/tests/testROM/02-immediate.nes");

    for (int i = 0; i < romData.size(); ++i) {
        if (romData[i] != '\0') {
            cout << i << ": ";
            cout << romData[i] << endl;
        }
    }

    return 0;
}
