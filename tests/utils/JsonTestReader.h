//
// Created by Brandon Paul on 1/30/25.
//

#ifndef JSONTESTREADER_H
#define JSONTESTREADER_H

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using json = nlohmann::json;

struct State {
    uint16_t pc{};
    uint8_t stackPointer{};
    uint8_t accumulator{};
    uint8_t xRegister{};
    uint8_t yRegister{};
    uint8_t pStatus{};
    std::vector<std::vector<int>> ram;
};

struct Cycle {
    int address{};
    int value{};
    std::string action;
};

struct Element {
    std::string name;
    State initial;
    State final;
    std::vector<Cycle> cycles;
};

class JsonTestReader {
public:
    explicit JsonTestReader(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Could not open file: " << filename << std::endl;
            return;
        }

        try {
            json jsonData;
            file >> jsonData;  // Read JSON data from file
            parse(jsonData);   // Parse into test cases
        } catch (const json::parse_error& e) {
            std::cerr << "JSON parse error: " << e.what() << std::endl;
        }
    }

    void parse(const json& jsonData) {
        for (const auto& item : jsonData) {
            Element element;
            element.name = item["name"];

            // Parse initial state
            element.initial.pc = item["initial"]["pc"];
            element.initial.stackPointer = item["initial"]["s"];
            element.initial.accumulator = item["initial"]["a"];
            element.initial.xRegister = item["initial"]["x"];
            element.initial.yRegister = item["initial"]["y"];
            element.initial.pStatus = item["initial"]["p"];
            element.initial.ram = item["initial"]["ram"].get<std::vector<std::vector<int>>>();

            // Parse final state
            element.final.pc = item["final"]["pc"];
            element.final.stackPointer = item["final"]["s"];
            element.final.accumulator = item["final"]["a"];
            element.final.xRegister = item["final"]["x"];
            element.final.yRegister = item["final"]["y"];
            element.final.pStatus = item["final"]["p"];
            element.final.ram = item["final"]["ram"].get<std::vector<std::vector<int>>>();

            // Parse cycles
            for (const auto& cycle : item["cycles"]) {
                Cycle c;
                c.address = cycle[0];
                c.value = cycle[1];
                c.action = cycle[2];
                element.cycles.push_back(c);
            }

            // Store the parsed test case
            tests.push_back(element);
        }
    }

    void printTests() const {
        for (const auto& test : tests) {
            std::cout << "Test Name: " << test.name << "\n";
            printState("Initial", test.initial);
            printState("Final", test.final);
            printCycles(test.cycles);
            std::cout << "----------------------------------\n";
        }
    }

    const std::vector<Element>& getTests() const {
        return tests;
    }

private:
    std::vector<Element> tests;  // Store all test cases

    static void printState(const std::string& label, const State& state) {
        std::cout << label << " State:\n";
        std::cout << "  PC: " << state.pc << ", S: " << state.stackPointer << ", A: " << state.accumulator
                  << ", X: " << state.xRegister << ", Y: " << state.yRegister << ", P: " << state.pStatus << "\n";
        std::cout << "  RAM:\n";
        for (const auto& pair : state.ram) {
            std::cout << "    [" << pair[0] << ", " << pair[1] << "]\n";
        }
    }

    static void printCycles(const std::vector<Cycle>& cycles) {
        std::cout << "Cycles:\n";
        for (const auto& cycle : cycles) {
            std::cout << "  Address: " << cycle.address << ", Value: " << cycle.value
                      << ", Action: " << cycle.action << "\n";
        }
    }
};

#endif //JSONTESTREADER_H
