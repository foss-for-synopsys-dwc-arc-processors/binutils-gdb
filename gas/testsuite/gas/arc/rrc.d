#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	2f 20 44 00             	rrc        r0,r1
   4:	2f 23 04 37             	rrc        fp,sp
   8:	6f 20 04 00             	rrc        r0,0
   c:	2f 21 84 0f ff ff ff ff 	rrc        r1,-1
  14:	2f 26 84 70             	rrc        0,r2
  18:	2f 24 84 0f 00 00 ff 00 	rrc        r4,255
  20:	2f 26 84 0f ff ff 00 ff 	rrc        r6,-256
  28:	2f 20 84 1f 00 00 00 01 	rrc        r8,0x100
  30:	2f 21 84 1f ff ff ff fe 	rrc        r9,0xfffffeff
  38:	2f 23 84 1f 42 42 42 42 	rrc        r11,0x42424242
  40:	2f 20 84 0f 00 00 00 00 	rrc        r0,0
			44: R_ARC_32_ME	foo
  48:	2f 20 44 80             	rrc.f      r0,r1
  4c:	6f 22 44 80             	rrc.f      r2,1
  50:	2f 26 04 f1             	rrc.f      0,r4
  54:	2f 25 84 8f 00 00 00 02 	rrc.f      r5,0x200
