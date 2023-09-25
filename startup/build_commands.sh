arm-none-eabi-as -mcpu=cortex-a15 startup.s -o startup.o
arm-none-eabi-gcc -c -mcpu=cortex-a15 entry.c -o entry.o
arm-none-eabi-ld -T boot.ld entry.o startup.o -o output.elf
