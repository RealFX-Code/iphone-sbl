
/*
 *	Platform specific code for iPhone 3GS
 *
 */


#define FRAMEBUFFER_ADDRESS 0x4FD00000;

// Framebuffer in memory
volatile unsigned int *framebuffer = (volatile unsigned int *)FRAMEBUFFER_ADDRESS;

void plat_init(void) {
	int i;

	// Fill first 4k of the framebuffer to see what happens.
	// Fills 1024 blocks of 4-byte words
	for (i = 0; i < 1024; i++ ){
		framebuffer[i] = 0xFFFFFFFF;
	}

	return;
}

void plat_exit(void) {
	return;
}

