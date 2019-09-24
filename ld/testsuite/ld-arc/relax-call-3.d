#source: relax-call-3.s
#as: -mlinker-relax
#ld: -q -A elf32-arclittle -relax
#objdump: -dr

[^:]+:     file format elf.*arc


Disassembly of section \.text:

[0-9]+ <__start>:
\s+[01]+:	f803                	bl_s	12	;[0-9a-f]+ <foo>
\s+[0-9]+: R_ARC_S13_PCREL	foo
\s+[0-9]+: R_ARC_NONE	\*ABS\*\+0x4

[0-9]+ <.L1>:
\s+[0-9]+:	0002 0000.*
\s+[0-9]+: R_ARC_32	\.L1
\s+[0-9]+: R_ARC_SUB32	\.L0
\s+[0-9]+:	0002 0002.*
\s+[0-9]+: R_ARC_ADD16	\.L1
\s+[0-9]+: R_ARC_SUB16	\.L0
\s+[0-9]+: R_ARC_ADD8	\.L1
\s+[0-9]+: R_ARC_SUB8	\.L0
\s+[0-9a-f]+:	78e0\s+nop_s
\s+[0-9a-f]+: R_ARC_NONE	\*ABS\*\+0x4

[0-9c]+ <foo>:
\s+[0-9a-f]+:	2000 0000           	add	r0,r0,r0
\s+[0-9a-f]+:	fffc                	bl_s	-16	;[0-9a-f]+ <__start>
\s+[0-9a-f]+: R_ARC_S13_PCREL	__start
\s+[0-9a-f]+:	78e0\s+nop_s
\s+[0-9a-f]+: R_ARC_NONE	\*ABS\*\+0x6

[0-9a-f]+ <goo>:
\s+[0-9a-f]+:	2000 0000           	add	r0,r0,r0
