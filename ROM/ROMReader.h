//
// Created by Brandon Paul on 5/1/24.
//

#ifndef NESEMULATOR_ROMREADER_H
#define NESEMULATOR_ROMREADER_H

using namespace std;

#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

#include "CPU/CPU.h"

class ROMReader {
private:
    bool batteryBackedRam;
    bool trainerPresence;
    int mapperNumber;
    bool horizontalMirroring;
    int numPRG_ROM;
    int numCHR_ROM;

    const int SIZE_PRG_BANK = 16384;
    const int SIZE_HEADER = 16;
    const int SIZE_CRH_BANK = 8192;
    const int SIZE_TRAINER = 512;

    vector<uint8_t> romData;

public:
    void loadROMFile(string& filePath, CPU* cpu);

    void parseROMHeader();

    void loadROMIntoCPU(CPU* cpu);

    void loadPRGIntoCPU(CPU* cpu);

    void loadCHRIntoCPU(CPU* cpu);

    void loadTrainerIntoCPU(CPU* cpu);
};


#endif //NESEMULATOR_ROMREADER_H
