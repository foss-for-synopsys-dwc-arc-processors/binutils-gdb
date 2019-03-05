#source: relax-call-1.s
#as: -mlinker-relax
#ld: -q -A elf32-arclittle -relax
#objdump: -dr

[^:]+:     file format elf32-.*arc


Disassembly of section \.text:

00000100 <__start>:
 100:	f801                	bl_s	4	;104 <foo>
			100: R_ARC_S13_PCREL	foo
			100: R_ARC_NONE	\*ABS\*\+0x4
 102:	f801                	bl_s	4	;104 <foo>
			102: R_ARC_S13_PCREL	foo

00000104 <foo>:
 104:	2000 0000           	add	r0,r0,r0
			104: R_ARC_NONE	\*ABS\*\+0x6
