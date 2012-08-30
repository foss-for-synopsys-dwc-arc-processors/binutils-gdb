#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	2f 20 46 00             	sexw       r0,r1
   4:	2f 23 06 37             	sexw       fp,sp
   8:	6f 20 06 00             	sexw       r0,0
   c:	2f 21 86 0f ff ff ff ff 	sexw       r1,-1
  14:	2f 26 86 70             	sexw       0,r2
  18:	2f 24 86 0f 00 00 ff 00 	sexw       r4,255
  20:	2f 26 86 0f ff ff 00 ff 	sexw       r6,-256
  28:	2f 20 86 1f 00 00 00 01 	sexw       r8,0x100
  30:	2f 21 86 1f ff ff ff fe 	sexw       r9,0xfffffeff
  38:	2f 23 86 1f 42 42 42 42 	sexw       r11,0x42424242
  40:	2f 20 86 0f 00 00 00 00 	sexw       r0,0
			44: R_ARC_32_ME	foo
  48:	2f 20 46 80             	sexw.f     r0,r1
  4c:	6f 22 46 80             	sexw.f     r2,1
  50:	2f 26 06 f1             	sexw.f     0,r4
  54:	2f 25 86 8f 00 00 00 02 	sexw.f     r5,0x200
