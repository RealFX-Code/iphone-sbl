// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Leah

#include <lib/framebuffer.h>
#include <plat/plat.h>
#include <lib/string.h>
#include <stdint.h>

#ifdef FONT_8x8
    #include "fonts/font_8x8.h"
#elif FONT_calstone
    #include "fonts/font_calstone.h"
#elif FONT_comicsans
    #include "fonts/font_comicsans.h"
#else
    #error Invalid font!
#endif

#define FONT_SIZE 1

static int cursor_x = 0;
static int cursor_y = 0;

void fb_pixel(int x, int y, int  color) {
    int location = y*FRAMEBUFFER_X+x;
    if (location > FRAMEBUFFER_X*FRAMEBUFFER_Y) {
        // We're drawing outside of the framebuffer!
        return;
    }
    volatile unsigned int *fb = (volatile unsigned int *)FRAMEBUFFER_ADDRESS;
    fb[location] = color;
}

void fb_puts(int x, int y, char *str, int color) {
	size_t len = strlen(str);
	int i;
	for(i = 0; i < len; i++) {
		fb_putc(0, 0, str[i], color);
	}
}

// The 8x8 font is defined differently, and so needs a different putc implementation.
#ifdef FONT_8x8
void fb_putc(int x, int y, char c, int color) {
    if (c < 0 || c >= 128) return;
    
    int scale = FONT_SIZE;
    
    for (int row = 0; row < 8; row++) {
        int line = font_data[(unsigned char)c][row];
        for (int col = 0; col < 8; col++) {
            if (line & (1 << col)) {
                for (int sy = 0; sy < scale; sy++) {
                    for (int sx = 0; sx < scale; sx++) {
                        fb_pixel(cursor_x + (col * scale) + sx, cursor_y + (row * scale) + sy, color);
                    }
                }
            } else {
                for (int sy = 0; sy < scale; sy++) {
                    for (int sx = 0; sx < scale; sx++) {
                        fb_pixel(cursor_x + (col * scale) + sx, cursor_y + (row * scale) + sy, 0x00000000);
                    }
                }
            }
        }
    }

    cursor_x += fb_get_char_width()
    if (cursor_x + fb_get_char_width() > FRAMEBUFFER_X) {
        cursor_x = 0;
        cursor_y += fb_get_char_height() + 4;
    }

}
#else /* FONT_8x8 */
void fb_putc(int x, int y, char c, int color) {
    int index = c - 32;
    
    if (index < 0 || index >= 96) return;
    
    int scale = FONT_SIZE;
    
    for (int row = 0; row < 8; row++) {
        int line = font_data[index][row];
        for (int col = 0; col < 8; col++) {
            if (line & (1 << (7 - col))) {
                for (int sy = 0; sy < scale; sy++) {
                    for (int sx = 0; sx < scale; sx++) {
                        fb_pixel(cursor_x + (col * scale) + sx, cursor_y + (row * scale) + sy, color);
                    }
                }
            } else {
                for (int sy = 0; sy < scale; sy++) {
                    for (int sx = 0; sx < scale; sx++) {
                        fb_pixel(cursor_x + (col * scale) + sx, cursor_y + (row * scale) + sy, 0x00000000);
                    }
                }
            }
        }
    }
    cursor_x += fb_get_char_width();
    if (cursor_x + fb_get_char_width() > FRAMEBUFFER_X) {
        cursor_x = 0;
        cursor_y += fb_get_char_height() + 4;
    }
}
#endif /* FONT_8x8 */

int fb_get_char_width(void) {
    return 8 * FONT_SIZE;
}

int fb_get_char_height(void) {
    return 8 * FONT_SIZE;
}
