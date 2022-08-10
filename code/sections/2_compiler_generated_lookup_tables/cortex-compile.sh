#!/bin/bash

CXX=$(find /usr/bin /opt/arm -name arm-none-eabi-g++ -print -quit)
[[ -z $CXX ]] && { echo "Compiler not found!"; exit -1; }

OBJCOPY=$(find /usr/bin /opt/arm -name arm-none-eabi-objcopy)
[[ -z $OBJCOPY ]] && { echo "Object copy not found!"; exit -1; }

$CXX --version

CXXFLAGS="-g0 -Os -std=c++20 \
-march=armv7e-m+fp -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mtune=cortex-m4 \
-Wall -Wextra -Wpedantic -Wno-psabi \
-fno-rtti -fno-exceptions -ffunction-sections \
--specs=nosys.specs -Wl,--gc-sections"


$CXX $CXXFLAGS main.cpp -o main.elf
$OBJCOPY --output-format binary main.elf main.bin





