#as: -EL -mARC700 -mlock
#objdump: -dr -EL -mARC700

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	2f 20 51 00             	scond      r0,\[r1\]
   4:	2f 20 91 0f 34 12 cd ab 	scond      r0,\[0x1234abcd\]
   c:	2f 20 91 0f 00 00 cf 00 	scond      r0,\[207\]
  14:	2f 20 51 80             	scond.di   r0,\[r1\]
  18:	2f 20 91 8f 34 12 cd ab 	scond.di   r0,\[0x1234abcd\]
  20:	2f 20 91 8f 00 00 cf 00 	scond.di   r0,\[207\]
