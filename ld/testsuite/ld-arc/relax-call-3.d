#source: relax-call-3.s
#as: -mlinker-relax
#ld: -q -A elf32-arclittle -relax
#objdump: -dr

[^:]+:     file format elf32-.*arc


Disassembly of section \.text:

00000100 <__start>:
 [01]+:	f803                	bl_s	12	;10c <foo>
\s+100: R_ARC_S13_PCREL	foo
\s+100: R_ARC_NONE	\*ABS\*\+0x4

00000102 <.L1>:
 102:	0002 0000.*
\s+102: R_ARC_32	\.L1
\s+102: R_ARC_SUB32	\.L0
 106:	0002 0002.*
\s+106: R_ARC_ADD16	\.L1
\s+106: R_ARC_SUB16	\.L0
\s+108: R_ARC_ADD8	\.L1
\s+108: R_ARC_SUB8	\.L0
 10a:	78e0\s+nop_s
\s+10a: R_ARC_NONE	\*ABS\*\+0x4

0000010c <foo>:
 10c:	2000 0000           	add	r0,r0,r0
 110:	fffc                	bl_s	-16	;100 <__start>
\s+110: R_ARC_S13_PCREL	__start
 112:	78e0\s+nop_s
\s+112: R_ARC_NONE	\*ABS\*\+0x6

00000114 <goo>:
 114:	2000 0000           	add	r0,r0,r0
