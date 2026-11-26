

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
    int fb_x = x;
    int fb_y = y;
	for(i = 0; i < len; i++) {
		fb_putc(fb_x, fb_y, str[i], color);
        fb_x += fb_get_char_width() + 1;
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
                        fb_pixel(x + (col * scale) + sx, y + (row * scale) + sy, color);
                    }
                }
            } else {
                for (int sy = 0; sy < scale; sy++) {
                    for (int sx = 0; sx < scale; sx++) {
                        fb_pixel(x + (col * scale) + sx, y + (row * scale) + sy, 0x00000000);
                    }
                }
            }
        }
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
                        fb_pixel(x + (col * scale) + sx, y + (row * scale) + sy, color);
                    }
                }
            } else {
                for (int sy = 0; sy < scale; sy++) {
                    for (int sx = 0; sx < scale; sx++) {
                        fb_pixel(x + (col * scale) + sx, y + (row * scale) + sy, 0x00000000);
                    }
                }
            }
        }
    }
}
#endif /* FONT_8x8 */

int fb_get_char_width(void) {
    return 8 * FONT_SIZE;
}

int fb_get_char_height(void) {
    return 8 * FONT_SIZE;
}
