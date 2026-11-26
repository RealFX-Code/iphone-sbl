// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Leah

#ifndef __LIB_H
#define __LIB_H

int fb_printf(const char* fmt, ...);

void hang(void);
void panic(const char *msg);

#endif /* __LIB_H */
