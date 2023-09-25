arm-none-eabi-as -mcpu=cortex-a15 startup.s -o startup.o
arm-none-eabi-gcc -c -mcpu=cortex-a15 entry.c -o entry.o
arm-none-eabi-ld -T boot.ld entry.o startup.o -o output.elf

aarch64-none-elf-as -mcpu=cortex-a53 startup_arm64.s -o startup.o
aarch64-none-elf-gcc -mcpu=cortex-a53 -c entry.c -o entry.o
aarch64-none-elf-ld -T boot.ld startup.o entry.o -o output.elf