.global _MyApp
.global delay
.global panic 
.global heap_start
.global ttb_address

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
    BL creating_pt
    MOV R0, #0xABCD
    LDR R0, =heap_start
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

creating_pt:
    MRC p15, 0, r1, c1, c0, 1
    ORR r1, r1, #(0x1 <<2)
    MCR p15, 0, r1, c1, c0, 1 ;
    DSB
    ISB
descriptor:
    LDR r1, =ttb_address
    LDR r3, = 4095
write_pte:
    ORR r2, r0, r3, LSL #20
    STR r2, [r1, r3, LSL #2]
    SUBS r3, r3, #1
    BNE write_pte
    BIC r0, r0, #12 
    ORR r0, r0, #4 
    BIC r0, r0, #28672 
    ORR r0, r0, #20480 
    ORR r0, r0, #65536 
    STR r0, [r1]
    
    @ Initialize MMU
    MOV r1,#0x0
    MCR p15, 0, r1, c2, c0, 2 
    LDR r1, =ttb_address

    MCR p15, 0, r1, c2, c0, 0 
    @ Write Translation Table Base Register 0
    @ In this simple example, we don't use TRE or Normal Memory Remap Register. 
    @ Set all Domains to Client
    LDR r1, =0x55555555
    MCR p15, 0, r1, c3, c0, 0 
    
    @ Write Domain Access Control Register
    @ Enable MMU
    MRC p15, 0, r1, c1, c0, 0 @ Read Control Register configuration data 
    ORR r1, r1, #0x1 @ Bit 0 is the MMU enable
    MCR p15, 0, r1, c1, c0, 0
    BX LR
