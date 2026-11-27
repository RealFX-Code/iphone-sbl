/*
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *  SPDX-FileCopyrightText: 2026 Leah <leah@realfx.rocks>
 */

#include <plat/plat.h>
#include <lib.h>
#include <stdint.h>
#include <lib/mem.h>

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

int main() {	
	plat_init();

    fb_printf("Welcome to iphone-sbl for: %s!\n", PLATFORM_NAME);

	fb_printf("\n");
	fb_printf("d888888b        .d8888. d8888b. db     \n");
	fb_printf("  `88'          88'  YP 88  `8D 88     \n");
	fb_printf("   88           `8bo.   88oooY' 88     \n");
	fb_printf("   88    C8888D   `Y8b. 88~~~b. 88     \n");
	fb_printf("  .88.          db   8D 88   8D 88booo.\n");
	fb_printf("Y888888P        `8888Y' Y8888P' Y88888P\n");
	fb_printf("\n");
	
    for(;;) {
        if (!buttons_is_pushed(BUTTONS_HOME))
            fb_print(".");
        if (!buttons_is_pushed(BUTTONS_HOLD))
            break;
    }

	plat_exit();

	return 0;
}

