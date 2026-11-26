// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Leah

/*
 *	Platform specific code for iPhone 3GS
 */

#include <plat/3gs/3gs.h>
#include <testing/image.h>

#include <lib/framebuffer.h>

void draw_boot_image(void) {
    volatile unsigned int *fb = (volatile unsigned int *)FRAMEBUFFER_ADDRESS;
    const char *data = header_data;
    unsigned char pixel[3];
    unsigned int total_pixels = width * height;

    for (unsigned int i = 0; i < total_pixels; i++) {
        HEADER_PIXEL(data, pixel);
        fb[i] = (0xFFU << 24)
              | ((unsigned int)pixel[0] << 16)
              | ((unsigned int)pixel[1] << 8)
              |  (unsigned int)pixel[2];
    }
}


void plat_init(void) {
	volatile unsigned int *framebuffer = (volatile unsigned int *)FRAMEBUFFER_ADDRESS;
	
    draw_boot_image();

    for(int i = 0; i < 50; i++) {
        fb_puts(0, i * fb_get_char_height(), "Hello, World!!", 0xFFFFFFFF);
    }

	return;
}

void plat_exit(void) {
	return;
}

