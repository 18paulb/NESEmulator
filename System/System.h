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
    CPU cpu;
    ROMReader romReader;
    int masterCycle;

public:

    System() {
        cpu = CPU();
        romReader = ROMReader();
        masterCycle = 0;
    }

    CPU& getCPU() {
        return cpu;
    }

    void step(int count) {
        masterCycle += count;
        cpu.step_to(masterCycle);
    }

    ROMReader getRomReader() {
        return romReader;
    }

};


#endif //NESEMULATOR_SYSTEM_H
