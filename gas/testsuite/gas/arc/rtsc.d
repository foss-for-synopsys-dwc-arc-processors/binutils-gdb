#as: -EL -mARC700 -mrtsc
#objdump: -dr -EL -mARC700

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	6f 30 1a 00             	rtsc       r0,0
