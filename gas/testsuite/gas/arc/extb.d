#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	2f 20 47 00             	extb       r0,r1
   4:	2f 23 07 37             	extb       fp,sp
   8:	6f 20 07 00             	extb       r0,0
   c:	2f 21 87 0f ff ff ff ff 	extb       r1,-1
  14:	2f 26 87 70             	extb       0,r2
  18:	2f 24 87 0f 00 00 ff 00 	extb       r4,255
  20:	2f 26 87 0f ff ff 00 ff 	extb       r6,-256
  28:	2f 20 87 1f 00 00 00 01 	extb       r8,0x100
  30:	2f 21 87 1f ff ff ff fe 	extb       r9,0xfffffeff
  38:	2f 23 87 1f 42 42 42 42 	extb       r11,0x42424242
  40:	2f 20 87 0f 00 00 00 00 	extb       r0,0
			44: R_ARC_32_ME	foo
  48:	2f 20 47 80             	extb.f     r0,r1
  4c:	6f 22 47 80             	extb.f     r2,1
  50:	2f 26 07 f1             	extb.f     0,r4
  54:	2f 25 87 8f 00 00 00 02 	extb.f     r5,0x200
