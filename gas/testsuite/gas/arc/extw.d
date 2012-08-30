#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	2f 20 48 00             	extw       r0,r1
   4:	2f 23 08 37             	extw       fp,sp
   8:	6f 20 08 00             	extw       r0,0
   c:	2f 21 88 0f ff ff ff ff 	extw       r1,-1
  14:	2f 26 88 70             	extw       0,r2
  18:	2f 24 88 0f 00 00 ff 00 	extw       r4,255
  20:	2f 26 88 0f ff ff 00 ff 	extw       r6,-256
  28:	2f 20 88 1f 00 00 00 01 	extw       r8,0x100
  30:	2f 21 88 1f ff ff ff fe 	extw       r9,0xfffffeff
  38:	2f 23 88 1f 42 42 42 42 	extw       r11,0x42424242
  40:	2f 20 88 0f 00 00 00 00 	extw       r0,0
			44: R_ARC_32_ME	foo
  48:	2f 20 48 80             	extw.f     r0,r1
  4c:	6f 22 48 80             	extw.f     r2,1
  50:	2f 26 08 f1             	extw.f     0,r4
  54:	2f 25 88 8f 00 00 00 02 	extw.f     r5,0x200
