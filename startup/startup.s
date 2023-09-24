.section	INTERRUPT_VECTOR,	"x"
.global	_Reset
_Reset:
	B	Reset_Handler	/* Reset */
	B	.	            /* Undefined */
	B	SVC_Handler     /* Supervisor Mode */
	B	.	            /* Prefetch Abort */
	B	.	            /* Data Abort */
	B	.	            /* reserved	*/
	B	.	            /* IRQ	*/
	B	.	            /* FIQ	*/
Reset_Handler:
	LDR	sp,	=stack_top
	BL	entry
    CPS #0x10
    MOV R2, #0xBABA
    BKPT
    NOP
    CPS #0x13
	SVC	0
    CPS #0x10
    BL my_fun
	B	.

SVC_Handler:
    MOV R0, #0xABCD
    MOV R1, #0xDEAD
    BX LR

my_fun:
    MOV R0, #0xBEEF
    MSR CPSR_c, #0x11
    NOP
    NOP
    BX LR


	