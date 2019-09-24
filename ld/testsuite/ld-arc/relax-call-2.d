#source: relax-call-2.s
#as: -mlinker-relax
#ld: -q -A elf32-arclittle -relax
#objdump: -dr

[^:]+:     file format elf.*arc


Disassembly of section \.text:

[0-9]+ <__start>:
\s+[0-9a-f]+:\s+2000 0000\s+add.*
\s+[0-9]+: R_ARC_NONE\s+\*ABS\*\+0x4
\s+[0-9a-f]+:\s+f801\s+bl_s\s+4\s+;[0-9a-f]+ <foo>
\s+[0-9]+: R_ARC_S13_PCREL\s+foo
\s+[0-9a-f]+:\s+78e0\s.*
\s+[0-9]+: R_ARC_NONE\s+\*ABS\*\+0x4

[0-9]+ <foo>:
\s+[0-9a-f]+:\s+2000 0000\s+add.*
\s+[0-9a-f]+:\s+fffd\s+bl_s\s+-12\s+;[0-9a-f]+ <__start>
\s+[0-9c]+: R_ARC_S13_PCREL\s+__start
\s+[0-9a-f]+:\s+78e0\s.*
\s+[0-9e]+: R_ARC_NONE\s+\*ABS\*\+0x6

[0-9]+ <goo>:
\s+[0-9a-f]+:\s+2000 0000\s+add.*
