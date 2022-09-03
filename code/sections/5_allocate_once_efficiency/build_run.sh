#!/bin/bash

CXX=$(which g++)

OBJCOPY=$(which objcopy)

echo "Using compiler $CXX"

ARCHFLAGS="-march=native"
ERRORFLAGS="-Wall -Wextra -Wpedantic -Wno-psabi -Wno-volatile"
RUNFLAGS="-fno-rtti -fno-exceptions -std=c++20"
OPTFLAGS="-ggdb -Og"
LINKFLAGS="-ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,-Map=output.map"
CXXFLAGS="$ARCHFLAGS $ERRORFLAGS $RUNFLAGS $OPTFLAGS $LINKFLAGS"


CSRCS="main.cpp"
INCLUDES="."


ELF="main.elf"

echo "Compiling..."
$CXX $CXXFLAGS -I $INCLUDES -x c++ $CSRCS -o $ELF
RETVAL=$?

if [ $RETVAL -eq 0 ]
then
    echo "Compilation successful..."
else
    exit -1
fi

./main.elf


