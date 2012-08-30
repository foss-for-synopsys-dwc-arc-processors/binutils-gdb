#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	2f 20 45 00             	sexb       r0,r1
   4:	2f 23 05 37             	sexb       fp,sp
   8:	6f 20 05 00             	sexb       r0,0
   c:	2f 21 85 0f ff ff ff ff 	sexb       r1,-1
  14:	2f 26 85 70             	sexb       0,r2
  18:	2f 24 85 0f 00 00 ff 00 	sexb       r4,255
  20:	2f 26 85 0f ff ff 00 ff 	sexb       r6,-256
  28:	2f 20 85 1f 00 00 00 01 	sexb       r8,0x100
  30:	2f 21 85 1f ff ff ff fe 	sexb       r9,0xfffffeff
  38:	2f 23 85 1f 42 42 42 42 	sexb       r11,0x42424242
  40:	2f 20 85 0f 00 00 00 00 	sexb       r0,0
			44: R_ARC_32_ME	foo
  48:	2f 20 45 80             	sexb.f     r0,r1
  4c:	6f 22 45 80             	sexb.f     r2,1
  50:	2f 26 05 f1             	sexb.f     0,r4
  54:	2f 25 85 8f 00 00 00 02 	sexb.f     r5,0x200
