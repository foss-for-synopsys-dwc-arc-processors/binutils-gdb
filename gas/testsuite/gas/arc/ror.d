#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	2f 20 43 00             	ror        r0,r1
   4:	2f 23 03 37             	ror        fp,sp
   8:	6f 20 03 00             	ror        r0,0
   c:	2f 21 83 0f ff ff ff ff 	ror        r1,-1
  14:	2f 26 83 70             	ror        0,r2
  18:	2f 24 83 0f 00 00 ff 00 	ror        r4,255
  20:	2f 26 83 0f ff ff 00 ff 	ror        r6,-256
  28:	2f 20 83 1f 00 00 00 01 	ror        r8,0x100
  30:	2f 21 83 1f ff ff ff fe 	ror        r9,0xfffffeff
  38:	2f 23 83 1f 42 42 42 42 	ror        r11,0x42424242
  40:	2f 20 83 0f 00 00 00 00 	ror        r0,0
			44: R_ARC_32_ME	foo
  48:	2f 20 43 80             	ror.f      r0,r1
  4c:	6f 22 43 80             	ror.f      r2,1
  50:	2f 26 03 f1             	ror.f      0,r4
  54:	2f 25 83 8f 00 00 00 02 	ror.f      r5,0x200
