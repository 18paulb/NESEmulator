//
// Created by Brandon Paul on 4/26/24.
//

#include "System.h"

void System::runROM(string romFile) {

}

vector<uint8_t> System::loadROM(string filePath) {
    // Open the ROM file
    ifstream romFile(filePath, std::ios::binary);

    if (!romFile.is_open()) {
        return {};
    }
    vector<uint8_t> romData{istreambuf_iterator<char>{romFile}, {}};

    return romData;
}
