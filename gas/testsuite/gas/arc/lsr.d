#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	2f 20 42 00             	lsr        r0,r1
   4:	2f 23 02 37             	lsr        fp,sp
   8:	6f 20 02 00             	lsr        r0,0
   c:	2f 21 82 0f ff ff ff ff 	lsr        r1,-1
  14:	2f 26 82 70             	lsr        0,r2
  18:	2f 24 82 0f 00 00 ff 00 	lsr        r4,255
  20:	2f 26 82 0f ff ff 00 ff 	lsr        r6,-256
  28:	2f 20 82 1f 00 00 00 01 	lsr        r8,0x100
  30:	2f 21 82 1f ff ff ff fe 	lsr        r9,0xfffffeff
  38:	2f 23 82 1f 42 42 42 42 	lsr        r11,0x42424242
  40:	2f 20 82 0f 00 00 00 00 	lsr        r0,0
			44: R_ARC_32_ME	foo
  48:	2f 20 42 80             	lsr.f      r0,r1
  4c:	6f 22 42 80             	lsr.f      r2,1
  50:	2f 26 02 f1             	lsr.f      0,r4
  54:	2f 25 82 8f 00 00 00 02 	lsr.f      r5,0x200
