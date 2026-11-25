// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Leah

#ifndef __PLAT_H
#define __PLAT_H

// Include platform-dependant stuff
#ifdef PLAT_3GS
    #include "3gs/3gs.h"
#endif

void plat_init(void);
void plat_exit(void);

#endif /* __PLAT_H */

