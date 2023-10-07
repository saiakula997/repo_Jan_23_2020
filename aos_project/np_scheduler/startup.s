.global _MyApp
.global delay
.global panic 

_MyApp:
    LDR sp, =stack_top
    BL entry
    B .

panic:
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

