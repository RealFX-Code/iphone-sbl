/*
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *  SPDX-FileCopyrightText: 2026 Leah <leah@realfx.rocks>
 */

#ifndef __LIB_H
#define __LIB_H

#include <stdarg.h>

int fb_vprintf(const char *fmt, va_list args);
int fb_printf(const char *fmt, ...);
int fb_print(const char *str);

void hang(void);
void panic(const char *msg);

#endif /* __LIB_H */
