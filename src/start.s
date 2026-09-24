@ Startup for iphone-sbl

.global _start
_start:
    @ Set up our processor.
    @ This disables interrupts, (except for aborts), and sets our CPU to hypervisor mode.
    cpsid if, #0x13
    
    @ Set our stack pointer
    ldr sp, =0x4101F000 
    
    @ Jump 2 main
    bl main
    
    @ Hang if we're here. Something went wrong!
1:  wfi
    b 1b