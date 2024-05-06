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
    int masterCycle;

public:

    System() {
        cpu = new CPU();
        romReader = new ROMReader();
        masterCycle = 0;
    }

    ~System() {
        delete cpu;
    }

    CPU* getCPU() {
        return cpu;
    }

    void step(int count) {
        masterCycle += count;
        cpu->step_to(masterCycle);
    }

    ROMReader* getRomReader() {
        return romReader;
    }

};


#endif //NESEMULATOR_SYSTEM_H
