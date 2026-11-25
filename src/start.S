@ SPDX-License-Identifier: GPL-3.0-or-later
@ Copyright (C) 2026 Leah
@ Startup for iphone-sbl

@ General startup stuff
.arm
.global _start
_start:
    @ The apple bootloader will ALWAYS load our binary at an 8-byte aligned offset.
    @ So the program counter will always be 8-byte aligned and at a valid ram offset at boot.
    @ So we repurpose it to derive a valid stack pointer location.
    mov     sp, pc
    add     sp, sp, #0x100000

    @ This disables all interrups, except for aborts. We want those.
    @ Also sets the CPU into Supervisor mode.
    cpsid   if, #0b10011

    @ Jump 2 main
    bl      main

    @ Should never reach here.
    adr     r0, panic_str
    bl      panic
    
_hang: wfi
    b       _hang

panic_str:
    .asciz "main() somehow returned!"
    .align 2
