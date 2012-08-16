#as: -EL -mARC700 -mswape
#objdump: -dr -EL -mARC700

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	2f 28 49 00             	swape      r0,r1
   4:	2f 28 89 0f 00 00 cf 00 	swape      r0,207
   c:	2f 28 89 0f 34 12 cd ab 	swape      r0,0x1234abcd
  14:	2f 2e 49 70             	swape      0,r1
  18:	2f 2e 89 7f 00 00 cf 00 	swape      0,207
  20:	2f 2e 89 7f 34 12 cd ab 	swape      0,0x1234abcd
  28:	2f 28 49 80             	swape.f    r0,r1
  2c:	2f 28 89 8f 00 00 cf 00 	swape.f    r0,207
  34:	2f 28 89 8f 34 12 cd ab 	swape.f    r0,0x1234abcd
  3c:	2f 2e 49 f0             	swape.f    0,r1
  40:	2f 2e 89 ff 00 00 cf 00 	swape.f    0,207
  48:	2f 2e 89 ff 34 12 cd ab 	swape.f    0,0x1234abcd
