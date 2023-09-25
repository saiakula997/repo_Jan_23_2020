.section INTERRUPT_VECTOR, "x"
.global _Reset
_Reset:
    B   Reset_Handler   /* Reset */
    B   .               /* Undefined */
    B   SVC_Handler     /* Supervisor Mode */
    B   .               /* Prefetch Abort */
    B   .               /* Data Abort */
    B   .               /* reserved */
    B   .               /* IRQ */
    B   .               /* FIQ */

Reset_Handler:
    LDR x0, =stack_top
    MSR SP_EL0, x0
    BL  entry
    MSR ELR_el1, x30   // Set ELR to the address of 'entry'
    MRS x0, CurrentEL  // Get Current Exception Level (EL)
    CMP x0, #0x4       // Check if we're in EL0
    BNE 1f             // If not, branch to '1'
    MSR DAIFSet, #0x3  // Clear DAIF (Disable All Interrupts and Exceptions)
    ERET               // Exception Return to EL0
1:
    // Code that runs in EL1 (Supervisor Mode)
    MOV x2, #0xBABA
    BRK #0
    NOP
    ERET

SVC_Handler:
    // Code for the Supervisor Call (SVC) handler
    MOV x0, #0xABCD
    MOV x1, #0xDEAD
    RET

my_fun:
    // Code for the custom function 'my_fun'
    MOV x0, #0xBEEF
    MOV x1, #0x13   // Set SPSR to EL1 with desired flags (Supervisor Mode)
    MSR SPSR_el1, x1
    NOP
    NOP
    RET

.global main
