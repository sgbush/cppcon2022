#!/bin/bash

CXX=$(find -L /opt/arm/arm-none-eabi -name arm-none-eabi-g++ -print -quit)

OBJCOPY=$(find -L /opt/arm/arm-none-eabi -name arm-none-eabi-objcopy -print -quit)

JLINK=$(find -L /opt/segger/JLink -name JLinkExe -print -quit)

echo "Using compiler $CXX"

ARCHFLAGS="-march=armv7e-m+fp.dp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mtune=cortex-m7"
ERRORFLAGS="-Wall -Wextra -Wpedantic -Wno-psabi -Wno-volatile"
RUNFLAGS="-fno-rtti -fno-exceptions -std=c++20 -fcheck-new"
OPTFLAGS="-ggdb -O0"
LINKFLAGS="-ffunction-sections -fdata-sections --specs=nano.specs -Wl,--gc-sections -Wl,-Map=output.map"
CXXFLAGS="$ARCHFLAGS $ERRORFLAGS $RUNFLAGS $OPTFLAGS $LINKFLAGS"

LDSCRIPT="default.ld"


function compile
{

    ASRCS="boot.asm"
    CSRCS="$1.cpp syscalls.cpp"
    INCLUDES="."

    ELF="$1.elf"

    echo "Compiling..."
    $CXX $CXXFLAGS -I $INCLUDES -x assembler $ASRCS -x c++ $CSRCS -o $ELF -T $LDSCRIPT
    RETVAL=$?

    if [ $RETVAL -eq 0 ]
    then
        echo "Compilation successful..."
    else
        exit -1
    fi

    HEX="$1.hex"
    BIN="$1.bin"

    echo "Using objcopy $OBJCOPY"
    echo "Converting..."

    $OBJCOPY -O binary $ELF $BIN

}

compile "main-bare"
compile "main-conventional"
compile "main-better"



