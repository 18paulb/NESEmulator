cmake_minimum_required(VERSION 3.26)
project(NESEmulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(NESEmulator
        CPU.cpp
        CPU.h
        AddressingMode.h
        StatusFlag.h
        main.cpp)
