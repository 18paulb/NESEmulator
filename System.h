//
// Created by Brandon Paul on 4/26/24.
//

#ifndef NESEMULATOR_SYSTEM_H
#define NESEMULATOR_SYSTEM_H

using namespace std;

#include "CPU/CPU.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::__fs::filesystem;



class System {
private:
    CPU cpu;
    int cycleCount;

public:

    void step(int count) {
        cycleCount += count;
    }

    vector<uint8_t> loadROM(string filePath);

    void runROM(string romFile);

};


#endif //NESEMULATOR_SYSTEM_H
