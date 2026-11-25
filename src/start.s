@ Startup for iphone-sbl

@ Include hardware constants!
#include "plat.h"

@ General startup stuff
.global _start
_start:
    @ This disables all interrups, except for aborts. We want those.
    @ Also sets the CPU into Supervisor mode.
    @ cpsid if, #0x13
    ORR	R1, R0,	#0x13
	MSR	CPSR_c,	R1
    
    @ Set our stack pointer
    LDR SP, =#0x27ffc
    
    @ Jump 2 main
    BL main
    
    @ Hang if we're here. Something went wrong!
HangLoop:  WFI
    B HangLoop
