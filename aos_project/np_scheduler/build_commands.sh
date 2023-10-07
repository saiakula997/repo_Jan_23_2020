arm-none-eabi-gcc -g -c -O0 -mcpu=arm926ej-s *.c
arm-none-eabi-as -g -mcpu=arm926ej-s startup.s -o startup.o 
arm-none-eabi-ld -T boot.ld *.o -o qemuboot.elf 
arm-none-eabi-objcopy -O binary qemuboot.elf qemuboot.bin
# qemu-system-arm -M versatilepb -nographic -kernel qemuboot.bin 