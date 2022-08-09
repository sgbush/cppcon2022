#!/bin/bash

CXX=$(find /usr/bin /opt/arm -name arm-none-eabi-g++ -print -quit)
[[ -z $CXX ]] && { echo "Compiler not found!"; exit -1; }

$CXX --version

CXXFLAGS="-g0 -Os -std=c++20 \
-march=armv7e-m+fp -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mtune=cortex-m4 \
-Wall -Wextra -Wpedantic -Wno-psabi \
-fno-rtti -fno-exceptions -ffunction-sections \
--specs=nosys.specs -Wl,--gc-sections"

OBJCOPY=$(find /usr/bin /opt/arm -name arm-none-eabi-objcopy)
[[ -z $OBJCOPY ]] && { echo "Object copy not found!"; exit -1; }


$CXX $CXXFLAGS main-conventional.cpp -o main-conventional.elf
$OBJCOPY --output-format binary main-conventional.elf main-conventional.bin
SIZE1=$(du --bytes main-conventional.bin | sed --regexp-extended --expression 's/([0-9]+)[ \t]+[.a-z\-]+/\1/')
echo "Reference size = " $SIZE1

$CXX $CXXFLAGS main-better.cpp -o main-better.elf
$OBJCOPY --output-format binary main-better.elf main-better.bin
SIZE2=$(du --bytes main-better.bin | sed --regexp-extended --expression 's/([0-9]+)[ \t]+[.a-z\-]+/\1/')
echo "Improved size = " $SIZE2

echo "Difference = " $(expr $SIZE1 - $SIZE2)




