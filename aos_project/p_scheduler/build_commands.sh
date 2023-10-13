arm-none-eabi-gcc -g -c -O0 -mcpu=cortex-a15 *.c 
arm-none-eabi-as -g -mcpu=cortex-a15 startup.s -o startup.o 
arm-none-eabi-ld -T boot.ld *.o -o qemuboot.elf  -v
arm-none-eabi-objcopy -O binary qemuboot.elf qemuboot.bin
# qemu-system-arm -M versatilepb -nographic -kernel qemuboot.bin 