//
// Created by Brandon Paul on 5/1/24.
//

#ifndef NESEMULATOR_MEMORY_H
#define NESEMULATOR_MEMORY_H

#include <cstdint>

class Memory {

private:
    uint8_t memory[65536];

public:

    void setMemory(uint16_t address, uint8_t value) {
        memory[address] = value;
    }

    uint8_t getMemory(uint16_t address) {
        return memory[address];
    }

};




#endif //NESEMULATOR_MEMORY_H
