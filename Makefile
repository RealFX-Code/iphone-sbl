# SPDX-License-Identifier: GPL-3.0-or-later
# Copyright (C) 2026 Leah

ifndef PLAT
  $(error set PLAT to your platform. e.g. 3gs)
endif

ifndef FONT
	FONT := 8x8
endif

CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
READELF		= $(CROSS_COMPILE)readelf
STRIP		= $(CROSS_COMPILE)strip

CFLAGS := -mlittle-endian -mfpu=vfp -mthumb \
		-mthumb-interwork -fPIC -Wno-error \
		-Wno-array-bounds -Wno-unused-value -Wno-unused-but-set-variable \
		-Wno-misleading-indentation -Wno-address-of-packed-member \
		-Wno-unused-const-variable -Wno-unused-function \
		-Wno-unused-variable -Wno-maybe-uninitialized \
		-Wno-address -Wno-bool-compare -Wno-logical-not-parentheses \
		-Wno-format-overflow -nostdlib -ffreestanding -fno-builtin

ifeq ($(PLAT), 3gs)
    CFLAGS   += -mcpu=cortex-a8
    LOAD_ADDR := 0x40000000
else ifeq ($(PLAT), 4)
    CFLAGS   += -mcpu=cortex-a8
    LOAD_ADDR := 0x41000000
else ifneq ($(filter $(PLAT), 2g 3g),)
    CFLAGS   += -mcpu=arm1176jzf-s
    LOAD_ADDR := 0x09000000
else
    $(error Unknown PLAT '$(PLAT)'. Use 2g, 3g, 3gs, or 4)
endif


LDFLAGS := $(PLAT_FLAGS) -nostdlib -Wl,-Ttext=$(LOAD_ADDR) -Wl,-e,_start -Wl,-T,src/linker.ld

# Set up includes
CFLAGS += -Isrc/include

# path macros
SRC_PATH	:= src
# compile macros
TARGET_NAME 	:= iphone-sbl
TARGET_ELF	:= $(TARGET_NAME).elf
TARGET_BIN	:= $(TARGET_NAME).bin
TARGET_IMG3	:= $(TARGET_NAME).img3

# src files & obj files
#SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
SRC := start.S lib/arm/memchr.S lib/arm/memset.S main.c lib.c lib/framebuffer/framebuffer.c lib/libc/string.c

CFLAGS += -DFONT_$(FONT)

# Add platform-specific code
SRC += plat/$(PLAT)/$(PLAT).c
CFLAGS += -DPLAT_$(PLAT)

OBJ := $(patsubst %.c,src/%.o,$(SRC))
OBJ := $(patsubst %.S,src/%.o,$(OBJ))

# clean files list
DISTCLEAN_LIST 	:= $(OBJ)
CLEAN_LIST 	:= $(TARGET_ELF) \
		$(TARGET_BIN) \
		$(TARGET_IMG3) \
		$(DISTCLEAN_LIST)

COBJFLAGS       := $(CFLAGS) -c

# default rule
default: all

# non-phony targets
$(TARGET_ELF): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LDFLAGS)

$(TARGET_BIN): $(TARGET_ELF)
	$(OBJCOPY) -O binary $< $@

$(TARGET_IMG3): $(TARGET_BIN)
	python3 mkimg3.py $< $@

%.o: %.S*
	$(CC) $(COBJFLAGS) -o $@ $<

%.o: %.c*
	$(CC) $(COBJFLAGS) -o $@ $<

# phony rules
.PHONY: all
all: $(TARGET_ELF) $(TARGET_BIN) $(TARGET_IMG3)

.PHONY: clean
clean:
	rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	rm -f $(DISTCLEAN_LIST)

