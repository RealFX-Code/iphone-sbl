// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Leah

#ifndef __FRAMEBUFFER_H
#define __FRAMEBUFFER_H

void fb_pixel(int x, int y, int  color);

void fb_puts(int x, int y, char *str, int color);

void fb_putc(int x, int y, char c, int color);

int fb_get_char_width(void);

int fb_get_char_height(void);

#endif