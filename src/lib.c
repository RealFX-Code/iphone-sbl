/*
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *  SPDX-FileCopyrightText: 2026 Leah <leah@realfx.rocks>
 */

#include <lib.h>
#include <plat/plat.h>
#include <stdint.h>
#include <lib/framebuffer.h>
#include <lib/string.h>
#include <lib/npf_config.h>
#include <stdarg.h>

static void fb_putc_callback(int c, void *ctx) {
    (void)ctx;
    fb_putc(c);
}

int fb_vprintf(const char *fmt, va_list args) {
    return npf_vpprintf(&fb_putc_callback, NULL, fmt, args);
}

int fb_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = fb_vprintf(fmt, args);
    va_end(args);
    return ret;
}

int fb_print(const char *str) {
    size_t len = strlen(str);
	int i;
	for(i = 0; i < len; i++) {
		fb_putc(str[i]);
	}
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

    fb_printf("\n%s: %s\n", __func__, msg);

    hang(); 
}
