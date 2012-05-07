#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	2f 20 41 00             	asr        r0,r1
   4:	2f 23 01 37             	asr        fp,sp
   8:	6f 20 01 00             	asr        r0,0
   c:	2f 21 81 0f ff ff ff ff 	asr        r1,-1
  14:	2f 26 81 70             	asr        0,r2
  18:	2f 24 81 0f 00 00 ff 00 	asr        r4,255
  20:	2f 26 81 0f ff ff 00 ff 	asr        r6,-256
  28:	2f 20 81 1f 00 00 00 01 	asr        r8,0x100
  30:	2f 21 81 1f ff ff ff fe 	asr        r9,0xfffffeff
  38:	2f 23 81 1f 42 42 42 42 	asr        r11,0x42424242
  40:	2f 20 81 0f 00 00 00 00 	asr        r0,0
			44: R_ARC_32_ME	foo
  48:	2f 20 41 80             	asr.f      r0,r1
  4c:	6f 22 41 80             	asr.f      r2,1
  50:	2f 26 01 f1             	asr.f      0,r4
  54:	2f 25 81 8f 00 00 00 02 	asr.f      r5,0x200
