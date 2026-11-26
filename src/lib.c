// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Leah

#include <lib.h>
#include <lib/framebuffer.h>
#include <plat/plat.h>
#include <stdint.h>
#include <stdarg.h>

#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_SMALL_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_ALT_FORM_FLAG 1
#define NANOPRINTF_IMPLEMENTATION

#include <lib/nanoprintf.h>

int fb_printf(const char* fmt, ...) {
    char buf[256];
    va_list args;
    va_start(args, fmt);

    // We can't hand our va_list to LK, so format here and only pass
    // it the result. Forwarding fmt alone loses every argument past
    // the second one.
    int ret = npf_vsnprintf(buf, sizeof(buf), fmt, args);

    va_end(args);

    fb_puts(0, 0, buf, 0x00ffffff);
    return ret;
}

void hang(void) {
    // Disable interrups, we don't want to wake after this!
    __asm__ __volatile__("cpsid if"); 

    do {
        // Forever wait for an interrupt, which we disabled.
        __asm__ __volatile__("wfi");
    } while (1);
}

void panic(const char *msg) {
    register uint32_t current_sp __asm__("sp");
    register uint32_t current_lr __asm__("lr");
    
    // Keep this address in mind!
    uint32_t *crash_log = (uint32_t *)0x4101F000; 
    crash_log[0] = 0xBADDBABE; // bad babe :drooling:
    crash_log[1] = current_sp;
    crash_log[2] = current_lr;

    hang(); 
}
