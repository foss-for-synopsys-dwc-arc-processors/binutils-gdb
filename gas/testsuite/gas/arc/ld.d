#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	30 21 80 00             	ld         r0,\[r1,r2\]
   4:	32 21 80 00             	ldb        r0,\[r1,r2\]
   8:	70 23 01 01             	ld.a       r1,\[r3,r4\]
   c:	35 22 c1 00             	ldw.x      r1,\[r2,r3\]
  10:	75 23 02 01             	ldw.x.a    r2,\[r3,r4\]
  14:	00 16 00 70 00 00 00 00 	ld         r0,\[0\]
  1c:	1e 11 00 00             	ld         r0,\[r1,30\]
  20:	ec 12 01 80             	ld         r1,\[r2,-20\]
