#source: relax-call-2.s
#as: -mlinker-relax
#ld: -q -A elf32-arclittle -relax
#objdump: -dr

[^:]+:     file format elf32-.*arc


Disassembly of section \.text:

00000100 <__start>:
 [0-9a-f]+:\s+2000 0000\s+add.*
\s+100: R_ARC_NONE\s+\*ABS\*\+0x4
 [0-9a-f]+:\s+f801\s+bl_s\s+4\s+;[0-9a-f]+ <foo>
\s+104: R_ARC_S13_PCREL\s+foo
 [0-9a-f]+:\s+78e0\s.*
\s+106: R_ARC_NONE\s+\*ABS\*\+0x4

00000108 <foo>:
 [0-9a-f]+:\s+2000 0000\s+add.*
 [0-9a-f]+:\s+fffd\s+bl_s\s+-12\s+;[0-9a-f]+ <__start>
\s+10c: R_ARC_S13_PCREL\s+__start
 [0-9a-f]+:\s+78e0\s.*
\s+10e: R_ARC_NONE\s+\*ABS\*\+0x6

00000110 <goo>:
 [0-9a-f]+:\s+2000 0000\s+add.*
