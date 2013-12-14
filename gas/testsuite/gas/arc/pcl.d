#as: -mARC700 -EL
#objdump: -dr -EL -mARC700

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	00 27 82 7f 00 00 30 00 	add        r2,pcl,48
   8:	00 27 82 7f 00 00 2a 00 	add        r2,pcl,42
  10:	00 27 82 7f 00 00 00 00 	add        r2,pcl,0
			14: R_ARC_PC32	foo\+0x4
  18:	30 27 80 7f 00 00 18 00 	ld         r0,\[pcl,24\]
  20:	30 27 80 7f 00 00 12 00 	ld         r0,\[pcl,18\]
  28:	30 27 80 7f 00 00 00 00 	ld         r0,\[pcl,0\]
			2c: R_ARC_PC32	foo\+0x4
  30:	e0 78                   	nop_s      
  32:	00 27 82 7f 00 00 00 00 	add        r2,pcl,0
  3a:	00 27 82 7f ff ff fa ff 	add        r2,pcl,-6
  42:	00 27 82 7f 00 00 00 00 	add        r2,pcl,0
			46: R_ARC_PC32	foo\+0x4
  4a:	30 27 80 7f ff ff e8 ff 	ld         r0,\[pcl,-24\]
  52:	30 27 80 7f ff ff e2 ff 	ld         r0,\[pcl,-30\]
  5a:	30 27 80 7f 00 00 00 00 	ld         r0,\[pcl,0\]
			5e: R_ARC_PC32	foo\+0x4
  62:	e0 78                   	nop_s      
