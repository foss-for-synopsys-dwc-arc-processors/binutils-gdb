#source: gc-sections1.s
#as: -mARC700 -mEA
#ld: -shared --gc-sections --version-script=gc-sections1.ver
#objdump: -rd

.*:     file format elf32-littlearc


Disassembly of section \.text:

00000290 <bar>:
 290:	4a 26 00 70             	nop        
