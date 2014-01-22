#as: -mARC700 -EL
#objdump: -dr -EL -mARC700

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <bar>:
   0:	e0 78                   	nop_s      
   2:	c0 11 00 30             	ld         r0,\[r25,192\]
			2: R_ARC_TLS_LE_S9	a\+0x30
   6:	e0 7e                   	j_s        \[blink\]
00000008 <foo>:
   8:	00 21 80 3f 00 00 00 00 	add        r0,r25,0
			c: R_ARC_TLS_LE_32	a\+0x30
  10:	e0 78                   	nop_s      
  12:	e0 7e                   	j_s        \[blink\]
