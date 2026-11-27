/*
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *  SPDX-FileCopyrightText: 2026 Leah <leah@realfx.rocks>
 */

/*
 *	Platform specific code for iPhone 3GS
 */

#include <plat/3gs/3gs.h>
#include <testing/hellokitty.h>
#include <lib/framebuffer.h>
#include <lib/mem.h>
#include <lib.h>
#include <stdint.h>

#if 0
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
#endif


void plat_init(void) {

    fb_init(
        (uint32_t *)FRAMEBUFFER_ADDRESS,
        FRAMEBUFFER_X,
        FRAMEBUFFER_Y,
        4, 32
    );

    fb_clear(0x00000000);
    fb_printf("Framebuffer initialized.\n");

	return;
}

void plat_exit(void) {
	return;
}

