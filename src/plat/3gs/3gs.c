// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Leah

/*
 *	Platform specific code for iPhone 3GS
 */

#include <3gs.h>

// Framebuffer in memory
volatile unsigned int *framebuffer = (volatile unsigned int *)FRAMEBUFFER_ADDRESS;

void plat_init(void) {
    volatile unsigned int *fb = (volatile unsigned int *)0x4fe3a000;
    for (int i = 0; i < 320 * 480; i++) {
        fb[i] = 0xFFFFFFFF;
    }
    while (1) { __asm__("wfi"); }
	return;
}


void plat_exit(void) {
	return;
}

