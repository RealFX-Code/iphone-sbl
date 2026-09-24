# iphone-sbl

A small, wip secondary bootloader for older iphones.

My only device that I can test / develop for is the iPhone 3GS

## Building

First you need an ARM toolchain, Archlinux's `arm-none-eabi-gcc` is what I use.

Then select your platform. E.G. `3gs`.

Make it:

```
$ make CROSS_COMPILE=arm-none-eabi- PLAT=3gs
```

That will make you `iphone-sbl.elf` and `iphone-sbl.bin`. The bin file is the raw binary you should send to the device.

## Current status

- [ ] Booting on device
- [ ] Drawing to framebuffer
- [ ] A text console on the framebuffer
- [ ] Hand off execution to Linux

