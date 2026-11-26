// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Leah

#ifndef __3GS_H
#define __3GS_H

/* Here we define platform-specific constants */

#define FRAMEBUFFER_ADDRESS 0x4FE3A000
#define FRAMEBUFFER_X       320
#define FRAMEBUFFER_Y       480

/* These are stolen from openIBoot's plat-s5l8920/includes/hardware/s5l8920.h */

#define MemoryStart 0x00000000
#define MemoryEnd 0xFFFFFFFF
#define LargeMemoryStart 0x50000000

#define RAMStart 	0x40000000
#define RAMSize		(0x100*(MMU_SECTION_SIZE))
#define RAMEnd		(RAMStart + RAMSize)
#define HiMemStart 	0xC0000000
#define HiMemEnd	(HiMemStart + (0x400*(MMU_SECTION_SIZE)))

#define PageTable (RAMEnd - 0x8000)
#define GeneralStack (PageTable - 4)
#define HeapStart (LargeMemoryStart + 0x02000000)

#endif /* __3GS_H */
