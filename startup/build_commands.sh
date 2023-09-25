arm-none-eabi-as -mcpu=cortex-a53 startup.s -o startup.o
arm-none-eabi-gcc -c -mcpu=cortex-a53 entry.c -o entry.o
arm-none-eabi-ld -T boot.ld entry.o startup.o -o output.elf
