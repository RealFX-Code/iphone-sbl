# iphone-sbl

```
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Leah
```

A small, wip secondary bootloader for older iphones.

My only device that I can test / develop for is the iPhone 3GS

## Building

First you need an ARM toolchain, Archlinux's `arm-none-eabi-gcc` is what I use.

Then select your platform. E.G. `3gs`.

Make it:

```
$ make CROSS_COMPILE=arm-none-eabi- PLAT=3gs
```

That will make you `iphone-sbl.elf`, `iphone-sbl.bin`, and `iphone-sbl.img3` . The img3 is the one you want to send to the device.

## Booting

Booting it is quite convoluted at the moment.

Prerequisites:
 - Alloc8 instealled

First, enter recovery mode:

```

$ idevice_id
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx (USB)

$ ideviceenterrecovery xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

# The device now boots into recovery mode

```

Now we enter the Alloc8 patched DFU mode:

```

$ irecovery -c "reboot"
# Now we start holding the DFU mode combo.
# Hold POWER and HOME until you see the phone enumerate in DFU mode.

```

Now we can boot a patched recovery mode to boot our custom binaries.

To patch these, Use these decryption keys to decrypt the firmware to get the iBSS and iBEC files: https://theapplewiki.com/wiki/Keys:BrightonMaps_10B500_(iPhone2,1)
You can then use iboot32patcher to patch them, and then use xpwntool to repackage them as img3 images, which is what i'm sending to the device.

```

$ irecovery -f iBSS.n88ap.pwned.dfu
[==================================================] 100.0%

$ irecovery -f iBEC.n88ap.pwned.dfu
[==================================================] 100.0%

```

You should now see a powered LCD, but black.
You're now ready to load the iphone-sbl binary.

```
$ irecovery -f iphone-sbl.img3
[==================================================] 100.0%

$ irecovery -c "go"

# You should now see the device disconnect from USB and show a plain white screen!

```

## Current status

- [x] Booting on device
- [x] Drawing to framebuffer
- [ ] A text console on the framebuffer
- [ ] Hand off execution to Linux

