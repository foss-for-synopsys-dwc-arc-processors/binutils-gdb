#as: -EL -mARC700 -mlock
#objdump: -dr -EL -mARC700

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	2f 20 50 00             	llock      r0,\[r1\]
   4:	2f 20 90 0f 34 12 cd ab 	llock      r0,\[0x1234abcd\]
   c:	2f 26 10 70             	llock      0,\[r0\]
  10:	2f 26 90 7f 34 12 cd ab 	llock      0,\[0x1234abcd\]
  18:	2f 20 50 80             	llock.di   r0,\[r1\]
  1c:	2f 20 90 8f 34 12 cd ab 	llock.di   r0,\[0x1234abcd\]
  24:	2f 26 50 f0             	llock.di   0,\[r1\]
  28:	2f 26 90 ff 34 12 cd ab 	llock.di   0,\[0x1234abcd\]
