ENTRY(_MyApp) 
SECTIONS
{
 . = 0x00;
 .startup : { startup.o(.text) }
 .text : { *(.text) }
 .data : { *(.data) }
 .bss : { *(.bss COMMON) }
 . = ALIGN(8);
 heap_start = .; 
 . = . + 0x10000; /* 64KB of heap memory */
 . = ALIGN(8);
 . = . + 0x1000; /* 4KB of stack memory */
 stack_top = .;
}