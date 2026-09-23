
ifndef PLAT
  $(error set PLAT to your platform. e.g. 3gs)
endif

CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
READELF		= $(CROSS_COMPILE)readelf
STRIP		= $(CROSS_COMPILE)strip
CFLAGS 		:= -Wall -nostdlib -static \
				-Os -std=gnu99 -Ttext=0x0 -mlittle-endian \
				-mfpu=vfp -mthumb -mthumb-interwork -fPIC \
				-mcpu=cortex-a8 -Wno-error -Wno-array-bounds \
				-Wno-unused-value -Wno-unused-but-set-variable \
				-Wno-misleading-indentation -Wno-address-of-packed-member \
				-Wno-unused-const-variable -Wno-unused-function \
				-Wno-unused-variable -Wno-maybe-uninitialized \
				-Wno-address -Wno-bool-compare -Wno-logical-not-parentheses \
				-Wno-format-overflow \

# path macros
SRC_PATH	:= src
# compile macros
TARGET_NAME 	:= iphone-sbl
TARGET_ELF	:= $(TARGET_NAME).elf
TARGET_BIN	:= $(TARGET_NAME).bin

# src files & obj files
#SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
SRC := main.c

# Add platform-specific code
SRC += plat/$(PLAT).c
CFLAGS += -DPLAT_$(PLAT)
CFLAGS += -Isrc
CFLAGS += -Isrc/plat

OBJ := $(patsubst %.c,src/%.o,$(SRC))

# clean files list
DISTCLEAN_LIST 	:= $(OBJ)
CLEAN_LIST 	:= $(TARGET_ELF) \
		$(TARGET_BIN) \
		$(DISTCLEAN_LIST)

COBJFLAGS       := $(CFLAGS) -c

# default rule
default: all

# non-phony targets
$(TARGET_ELF): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

$(TARGET_BIN): $(TARGET_ELF)
	$(OBJCOPY) -O binary $< $@

%.o: %.s*
	$(CC) $(COBJFLAGS) -o $@ $<

%.o: %.c*
	$(CC) $(COBJFLAGS) -o $@ $<

# phony rules
.PHONY: all
all: $(TARGET_ELF) $(TARGET_BIN)

.PHONY: clean
clean:
	rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	rm -f $(DISTCLEAN_LIST)

