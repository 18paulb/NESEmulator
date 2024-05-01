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


    uint8_t romControlByteOne = romData.at(6);

    bool horizontal_mirroring = (romControlByteOne & 0b00000001) != 0;
    bool battery_backed_ram = (romControlByteOne & 0b00000010) != 0;
    bool trainer_presence = (romControlByteOne & 0b00000100) != 0;

//    cout << "Reset Vector: " << romData.at(0xFFFC);

//    for (int i = 0; i < romData.size(); ++i) {
//        if (romData[i] != '\0') {
//            cout << i << ": ";
//            cout << romData[i] << endl;
//        }
//    }

    return 0;
}
