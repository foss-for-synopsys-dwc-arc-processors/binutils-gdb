#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	00 11 00 00             	ld         r0,\[r1,0\]
   4:	01 16 05 00             	ld         r5,\[r6,1\]
   8:	00 16 13 70 00 00 00 00 	ld         r19,\[0\]
			c: R_ARC_32_ME	foo
  10:	0a 12 04 02             	ld.a       r4,\[r2,10\]
  14:	00 16 01 70 00 00 84 03 	ld         r1,\[0x384\]
  1c:	0f 13 82 00             	ldb        r2,\[r3,15\]
  20:	fe 14 03 81             	ldw        r3,\[r4,-2\]
  24:	2a 21 80 00             	lr         r1,\[r2\]
  28:	aa 21 00 05             	lr         r1,\[0x14\]
  2c:	aa 20 00 00             	lr         r0,\[0x0\]
