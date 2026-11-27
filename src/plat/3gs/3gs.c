// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Leah

/*
 *	Platform specific code for iPhone 3GS
 */

#include <plat/3gs/3gs.h>
#include <testing/image.h>
#include <lib/framebuffer.h>
#include <lib/mem.h>
#include <lib.h>
#include <stdint.h>

int buttons_is_pushed(int which) {
    uint8_t pin = which & 0x7;
	which = which >> 8;

	if (which == 0x2e) {
		return 0;
	}
	
    // GPIO bank for 3gs is 0x83000000
    uint32_t reg_val = readl(0x83000000 + (8 * which + pin) * sizeof(uint32_t));
    return !(reg_val & 1);
}



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
    draw_boot_image();

    fb_init(
        (uint32_t *)FRAMEBUFFER_ADDRESS,
        FRAMEBUFFER_X,
        FRAMEBUFFER_Y,
        4, 32
    );

    fb_printf("Hello, World! From printf!\n");

    for(;;) {
        if (!buttons_is_pushed(BUTTONS_HOME))
            fb_print(".");

        if (!buttons_is_pushed(BUTTONS_HOLD))
            break;
    }

	return;
}

void plat_exit(void) {
	return;
}

