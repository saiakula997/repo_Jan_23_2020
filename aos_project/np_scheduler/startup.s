.global _MyApp
.global delay
.global panic 
.global heap_start

_MyApp:
    LDR sp, =stack_top
    LDR R0, =heap_start
    BL entry
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

