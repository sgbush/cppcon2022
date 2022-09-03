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

ASRCS="boot.asm"
CSRCS="chrono.cpp clock.cpp system_init.cpp usart.cpp syscalls.cpp filestream.cpp main.cpp"
INCLUDES="."


ELF="main.elf"
HEX="main.hex"

echo "Compiling..."
$CXX $CXXFLAGS -I $INCLUDES -x assembler $ASRCS -x c++ $CSRCS -o $ELF -T $LDSCRIPT
RETVAL=$?

if [ $RETVAL -eq 0 ]
then
    echo "Compilation successful..."
else
    exit -1
fi

echo "Using objcopy $OBJCOPY"
echo "Converting..."

$OBJCOPY -O ihex $ELF $HEX

echo "Using JLink $JLINK"
echo "Flashing..."

$JLINK -nogui 1 -device stm32h743zi -if SWD -speed 4000 -autoconnect 1 -CommandFile commandfile.jlink > /dev/null
RETVAL=$?

if [ $RETVAL -eq 0 ]
then
    echo "Flashing successful..."
else
    exit -1
fi

stty --file=/dev/ttyACM0 115200
cat /dev/ttyACM0




