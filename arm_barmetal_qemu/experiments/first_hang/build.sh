#!/bin/bash

SOURCE_DIR="${PWD}/src"
BUILD_DIR="${PWD}/build"

arm-none-eabi-as -o ${BUILD_DIR}/startup.o ${SOURCE_DIR}/startup.s
arm-none-eabi-ld -o ${BUILD_DIR}/first_hang.elf ${BUILD_DIR}/startup.o
arm-none-eabi-objcopy -O binary ${BUILD_DIR}/first_hang.elf ${BUILD_DIR}/first_hang.bin


echo "******************************* SiZE ***************************************"
arm-none-eabi-size ${BUILD_DIR}/first_hang.elf
echo "\n\n\n"

echo "***************************** SECTIONS *************************************"
arm-none-eabi-objdump -h ${BUILD_DIR}/first_hang.elf
echo "\n\n\n"

echo "**************************** DISASSEMBLY ***********************************"
arm-none-eabi-objdump -d ${BUILD_DIR}/first_hang.elf
echo "\n\n\n"