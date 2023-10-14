.global _MyApp
.global delay
.global panic 
.global heap_start

.text
.align 2
_MyApp:
    B   Reset_Handler
    B   NMI_Handler
    B   SVC_Handler
    B   HardFault_Handler
    B   panic

Reset_Handler:
    MOV R2, #0x100
    MRC p15, 0, R0, c12, c0, 0
    MCR p15, 0, R2, c12, c0, 0
    MRC p15, 0, R0, c12, c0, 0
    MOV R0, #0x01
    SVC 0
    MOV R1, #0x01
    B entry
    B .
    
NMI_Handler:
    B panic
    B .

HardFault_Handler:
    B panic
    B .

SVC_Handler:
    B .

panic:
    SVC 0
    BAL .

delay:
    MOV R1, R0
_ploop:
    MOV R0, #0xFFFFFF
_delay_loop:
    NOP
    SUBS R0, #1
    CMP R0, #0
    BNE _delay_loop
    SUBS R1, #1
    CMP R1, #0
    BNE _ploop
    BX LR
