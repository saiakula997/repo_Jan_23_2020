#!/bin/bash

# -M indicates Machine to be emulated (ARMVersatile Express is an ARM platform intended for prototyping and testing)
# vexpress-a9 variant has the Cortex A9 CPU use ARMv7 Arc

# -m indicates RAM size here 32 Mega Bytes
# -no-reboot indicates no need to reboot if qemu crashes
# -nographic indicates to redirect all the o/p to terminal
# -monitor QEMU comes with an intergface that is useful to examine the emulated machine
# using telnet protocol for communication with ip 127.0.0.1(localhost) port 1234
# server,nowait indicates keep running telnet server even if none connects.  

# this command dosent execute any binary but crashes internally
# qemu-system-arm -M vexpress-a9 -m 32M -no-reboot -nographic -monitor telnet:127.0.0.1:1234,server,nowait

# -kernel fisrt_hang.bin indicates that we want to load binary into emulated machine.
qemu-system-arm -M vexpress-a9 -m 32M -no-reboot -nographic -monitor telnet:127.0.0.1:1234,server,nowait -kernel ${PWD}/build/first_hang.bin




# To connect as client to the server
#(qemu) telnet localhost 1234

# Basic Qemu commands 
# info registers - to inspect registers
# xp /4w 0x1000  - to inspect 4 words  at 0x1000 physical address 
# x /4w 0x1000   - to inspect 4 words  at 0x1000  virtual address
# help           - to print help

# (qemu) xp /4w 0x60010000
# 0000000060010000: 0xe59f2004 0xe3a01005 0xeafffffe 0xbabeface
# we can find our code in physical address 0x60010000 because for ths vexpress-a9 device DDR2 RAM starts from 0x60000000 that is how it is memory mapped
# where the addition offset 0x10000 is 64KB which is qemu boot code for this device, after execting this boot code only qemu will jump to kernel code 
# begining from 0x0060010000.

