#as: -mcpu=hs5x
#source: fsmul-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e202 4021[ 	]+fsmul[ 	]+f0,f1,f2
0x[0-9a-f]+ e502 40e4[ 	]+fsmul[ 	]+f3,f4,f5
0x[0-9a-f]+ e002 51a7[ 	]+fsmul[ 	]+f6,f7,f8
0x[0-9a-f]+ e302 526a[ 	]+fsmul[ 	]+f9,f10,f11
0x[0-9a-f]+ e602 532d[ 	]+fsmul[ 	]+f12,f13,f14
0x[0-9a-f]+ e102 63f0[ 	]+fsmul[ 	]+f15,f16,f17
0x[0-9a-f]+ e402 64b3[ 	]+fsmul[ 	]+f18,f19,f20
0x[0-9a-f]+ e702 6576[ 	]+fsmul[ 	]+f21,f22,f23
0x[0-9a-f]+ e202 7639[ 	]+fsmul[ 	]+f24,f25,f26
0x[0-9a-f]+ e502 76fc[ 	]+fsmul[ 	]+f27,f28,f29
0x[0-9a-f]+ e002 47bf[ 	]+fsmul[ 	]+f30,f31,f0

