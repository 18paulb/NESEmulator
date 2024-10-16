//
// Created by Brandon Paul on 5/1/24.
//

#include "ROMReader.h"

void ROMReader::loadROMFile(string &filePath, CPU *cpu) {
    ifstream romFile(filePath, std::ios::binary);

    if (!romFile.is_open()) {
        return;
    }

    vector<uint8_t> tmpRomData{istreambuf_iterator<char>{romFile}, {}};

    this->romData = tmpRomData;

    parseROMHeader();
    loadROMIntoCPU(cpu);
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

void ROMReader::loadROMIntoCPU(CPU *cpu) {
    loadPRGIntoCPU(cpu);
    loadCHRIntoCPU(cpu);
    loadTrainerIntoCPU(cpu);
}

void ROMReader::loadPRGIntoCPU(CPU *cpu) {

    const uint16_t FIRST_BANK_ADDR = 0x8000;
    const uint16_t SECOND_BANK_ADDR = 0xC000;

    for (int i = 0; i < SIZE_PRG_BANK; ++i) {

        uint16_t startingOffset = i + SIZE_HEADER;
        if (trainerPresence) startingOffset += SIZE_TRAINER;

        // Games with only one 16 KB bank of PRG-ROM will load it into both $8000 and $C000.
        if (numPRG_ROM == 1) {
            uint8_t val = romData.at(startingOffset);

            cpu->setMemory(FIRST_BANK_ADDR + i, val);
            cpu->setMemory(SECOND_BANK_ADDR + i, val);
        }

        // Games with two 16 KB banks of PRG-ROM will load first into $8000 and second into $C000
        if (numPRG_ROM == 2) {
            uint8_t val = romData.at(startingOffset);
            cpu->setMemory(FIRST_BANK_ADDR + i, val);

            // Set the CPU memory starting at $C000
            uint8_t val2 = romData.at(startingOffset + SIZE_PRG_BANK);
            cpu->setMemory(SECOND_BANK_ADDR + i, val2);
        }
    }
}

void ROMReader::loadCHRIntoCPU(CPU *cpu) {
}

void ROMReader::loadTrainerIntoCPU(CPU *cpu) {
}
