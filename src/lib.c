
#include "lib.h"
#include <stdint.h>

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
