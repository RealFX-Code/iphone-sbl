#include <stdio.h>

#include <plat/plat.h>

int _start() {	
	plat_init();
	plat_exit();
	do {
		// nothing!
		plat_exit();
	} while(1);
	return 0;
}

