arm-none-eabi-gcc -g -c -O0 -mcpu=arm926ej-s *.c
arm-none-eabi-as -g -mcpu=arm926ej-s startup.s -o startup.o 
arm-none-eabi-ld -T boot.ld *.o -o np_scheduler.elf 
arm-none-eabi-objcopy -O binary np_scheduler.elf np_scheduler.bin

# Run np_scheduler.bin using QEMU 
# qemu-system-arm -M versatilepb -nographic -kernel np_scheduler.bin 