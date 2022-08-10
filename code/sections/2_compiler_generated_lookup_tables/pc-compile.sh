#!/bin/bash

CXX=$(find /usr/bin /opt/arm -name g++ -print -quit)
[[ -z $CXX ]] && { echo "Compiler not found!"; exit -1; }

$CXX --version

CXXFLAGS="-g0 -Os -std=c++20 \
-Wall -Wextra -Wpedantic -Wno-psabi \
-fno-rtti -fno-exceptions -ffunction-sections -Wl,--gc-sections"


$CXX $CXXFLAGS main.cpp -o main.elf


readelf --sections --wide main.elf 
readelf --symbols --wide --demangle main.elf


