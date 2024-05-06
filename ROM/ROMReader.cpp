//
// Created by Brandon Paul on 5/1/24.
//

#include "ROMReader.h"

void ROMReader::loadROM(string& filePath) {
    ifstream romFile(filePath, std::ios::binary);

    if (!romFile.is_open()) {
        return;
    }
    vector<uint8_t> romData{istreambuf_iterator<char>{romFile}, {}};

    this->romData = romData;

    parseROMHeader();
}

void ROMReader::parseROMHeader() {
    uint8_t controlByteOne = romData.at(6);
    uint8_t controlByteTwo = romData.at(7);

    this->numPRG_ROM = romData.at(4);
    this->numCHR_ROM = romData.at(5);

    this->horizontalMirroring = (controlByteOne & 0b00000001) != 0;
    this->batteryBackedRam = (controlByteOne & 0b00000010) != 0;
    this->trainerPresence = (controlByteOne & 0b00000100) != 0;

    // Extracting bits 4-7 from control byte 2 and shifting them to the left by 4 bits
    int mapperNumberPart1 = ((controlByteTwo >> 4) & 0x0F) << 4;
    // Extracting bits 4-7 from control byte 1
    int mapperNumberPart2 = (controlByteOne >> 4) & 0x0F;
    // Combining the two parts to get the mapper number
    this->mapperNumber = mapperNumberPart1 + mapperNumberPart2;
}

void ROMReader::loadROMIntoCPU(CPU* cpu) {
    loadPRGIntoCPU(cpu);
}

// TODO: This does not account for different offsets if there is a trainer present, fix eventually
void ROMReader::loadPRGIntoCPU(CPU* cpu) {

    const int PRG_BANK_SIZE = 16384;
    const int HEADER_SIZE = 16;

    const uint16_t firstBankAddr = 0x8000;
    const uint16_t secondBankAddr = 0xC000;

    // Games with only one 16 KB bank of PRG-ROM will load it into both $8000 and $C000.
    if (numPRG_ROM == 1) {
        for (int i = 0; i < PRG_BANK_SIZE; ++i) {

            uint8_t val = romData.at(i + HEADER_SIZE);

            cpu->getMemory()->setMemory(firstBankAddr+i, val);

            cpu->getMemory()->setMemory(secondBankAddr+i, val);

        }
    }

    if (numPRG_ROM == 2) {
        for (int i = 0; i < PRG_BANK_SIZE; ++i) {

            uint8_t val = romData.at(i + HEADER_SIZE);

            cpu->getMemory()->setMemory(firstBankAddr+i, val);

            uint8_t val2 = romData.at(i + HEADER_SIZE + PRG_BANK_SIZE);

            cpu->getMemory()->setMemory(secondBankAddr+i, val2);

        }
    }
}