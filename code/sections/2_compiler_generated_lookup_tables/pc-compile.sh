#!/bin/bash

CXX=$(find /usr/bin -name g++ -print -quit)
[[ -z $CXX ]] && { echo "Compiler not found!"; exit -1; }

$CXX --version

CXXFLAGS="-g0 -Os -std=c++20 \
-Wall -Wextra -Wpedantic -Wno-psabi \
-fno-rtti -fno-exceptions -ffunction-sections -Wl,--gc-sections"


$CXX $CXXFLAGS main.cpp -o main.elf


echo 'Note the section number:'
readelf --sections --wide main.elf | grep --color rodata
echo "Note that the lookup table is in the rodata section:"
readelf --symbols --wide --demangle main.elf | grep --color ThermistorLookup


