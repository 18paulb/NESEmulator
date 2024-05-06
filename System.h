//
// Created by Brandon Paul on 4/26/24.
//

#ifndef NESEMULATOR_SYSTEM_H
#define NESEMULATOR_SYSTEM_H

#include "CPU/CPU.h"
#include "ROM/ROMReader.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

class System {
private:
    CPU* cpu;
    ROMReader* romReader;
    int cycleCount;

public:

    System() {
        cpu = new CPU();
        romReader = new ROMReader();
        cycleCount = 0;
    }

    CPU* getCPU() {
        return cpu;
    }

    ROMReader* getRomReader() {
        return romReader;
    }

    void step(int count) {
        cycleCount += count;
    }


};


#endif //NESEMULATOR_SYSTEM_H
