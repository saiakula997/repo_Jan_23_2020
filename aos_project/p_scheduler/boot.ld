ENTRY(_MyApp) 
SECTIONS
{
 . = 0x100;
 .startup : { startup.o(.text) }
 .text : { *(.text) }
 .data : { *(.data) }
 .bss : { *(.bss COMMON) }
 . = ALIGN(0x4000);
 ttb_address = .;
 . = . + 0x10000; /* 64KB of heap memory */
 heap_start = .; 
 . = . + 0x10000; /* 64KB of heap memory */
 . = ALIGN(8);
 . = . + 0x1000; /* 4KB of stack memory */
 stack_top = .;
}