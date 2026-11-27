/*
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * SPDX-FileCopyrightText: 2026 Shomy, R0rt1z2, Leah
 */

#ifndef __MEM_H
#define __MEM_H

#include <stdint.h>

#define dsb(option) __asm__ __volatile__ ("dsb " #option : : : "memory")
#define dmb(option) __asm__ __volatile__ ("dmb " #option : : : "memory")
#define isb()       __asm__ volatile("isb" ::: "memory")

#define mb()        dsb(sy)
#define rmb()       dsb(sy)
#define wmb()       dsb(sy)

#define __raw_readb(addr) \
    ({ uint8_t __v = (*(volatile uint8_t *)(uintptr_t)(addr)); __v; })

#define __raw_readw(addr) \
    ({ uint16_t __v = (*(volatile uint16_t *)(uintptr_t)(addr)); __v; })

#define __raw_readl(addr) \
    ({ uint32_t __v = (*(volatile uint32_t *)(uintptr_t)(addr)); __v; })

#define __raw_writeb(val, addr) \
    ({ (*(volatile uint8_t *)(uintptr_t)(addr)) = (val); })

#define __raw_writew(val, addr) \
    ({ (*(volatile uint16_t *)(uintptr_t)(addr)) = (val); })

#define __raw_writel(val, addr) \
    ({ (*(volatile uint32_t *)(uintptr_t)(addr)) = (val); })

#define readb_relaxed(addr) \
    ({ uint8_t __v = __raw_readb(addr); __asm__ volatile("" ::: "memory"); __v; })

#define readw_relaxed(addr) \
    ({ uint16_t __v = __raw_readw(addr); __asm__ volatile("" ::: "memory"); __v; })

#define readl_relaxed(addr) \
    ({ uint32_t __v = __raw_readl(addr); __asm__ volatile("" ::: "memory"); __v; })

#define writeb_relaxed(val, addr) \
    ({ __asm__ volatile("" ::: "memory"); __raw_writeb(val, addr); })

#define writew_relaxed(val, addr) \
    ({ __asm__ volatile("" ::: "memory"); __raw_writew(val, addr); })

#define writel_relaxed(val, addr) \
    ({ __asm__ volatile("" ::: "memory"); __raw_writel(val, addr); })

#define readb(addr) \
    ({ uint8_t __v = __raw_readb(addr); rmb(); __v; })

#define readw(addr) \
    ({ uint16_t __v = __raw_readw(addr); rmb(); __v; })

#define readl(addr) \
    ({ uint32_t __v = __raw_readl(addr); rmb(); __v; })

#define writeb(val, addr) \
    ({ wmb(); __raw_writeb(val, addr); })

#define writew(val, addr) \
    ({ wmb(); __raw_writew(val, addr); })

#define writel(val, addr) \
    ({ wmb(); __raw_writel(val, addr); })

#endif /* __MEM_H */