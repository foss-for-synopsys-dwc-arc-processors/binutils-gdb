#source: relax-call-1.s
#as: -mlinker-relax
#ld: -q -A elf32-arclittle -relax
#objdump: -dr

[^:]+:     file format elf.*arc


Disassembly of section \.text:

[01]+ <__start>:
\s+[0-9]+:	f801                	bl_s	4	;[0-9]+ <foo>
			[0-9]+: R_ARC_S13_PCREL	foo
			[0-9]+: R_ARC_NONE	\*ABS\*\+0x4
\s+[0-9]+:	f801                	bl_s	4	;[0-9]+ <foo>
			[0-9]+: R_ARC_S13_PCREL	foo

[0-9]+ <foo>:
\s+[0-9]+:	2000 0000           	add	r0,r0,r0
			[0-9]+: R_ARC_NONE	\*ABS\*\+0x6
