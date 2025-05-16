#as: -mcpu=hs5x
#source: fh2s-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e060 0035[ 	]+fh2s[ 	]+f0,f0
0x[0-9a-f]+ e160 0075[ 	]+fh2s[ 	]+f1,f1
0x[0-9a-f]+ e260 00b5[ 	]+fh2s[ 	]+f2,f2
0x[0-9a-f]+ e360 00f5[ 	]+fh2s[ 	]+f3,f3
0x[0-9a-f]+ e460 0135[ 	]+fh2s[ 	]+f4,f4
0x[0-9a-f]+ e560 0175[ 	]+fh2s[ 	]+f5,f5
0x[0-9a-f]+ e660 01b5[ 	]+fh2s[ 	]+f6,f6
0x[0-9a-f]+ e760 01f5[ 	]+fh2s[ 	]+f7,f7
0x[0-9a-f]+ e060 1235[ 	]+fh2s[ 	]+f8,f8
0x[0-9a-f]+ e160 1275[ 	]+fh2s[ 	]+f9,f9
0x[0-9a-f]+ e260 12b5[ 	]+fh2s[ 	]+f10,f10
0x[0-9a-f]+ e360 12f5[ 	]+fh2s[ 	]+f11,f11
0x[0-9a-f]+ e460 1335[ 	]+fh2s[ 	]+f12,f12
0x[0-9a-f]+ e560 1375[ 	]+fh2s[ 	]+f13,f13
0x[0-9a-f]+ e660 13b5[ 	]+fh2s[ 	]+f14,f14
0x[0-9a-f]+ e760 13f5[ 	]+fh2s[ 	]+f15,f15
0x[0-9a-f]+ e060 2435[ 	]+fh2s[ 	]+f16,f16
0x[0-9a-f]+ e160 2475[ 	]+fh2s[ 	]+f17,f17
0x[0-9a-f]+ e260 24b5[ 	]+fh2s[ 	]+f18,f18
0x[0-9a-f]+ e360 24f5[ 	]+fh2s[ 	]+f19,f19
0x[0-9a-f]+ e460 2535[ 	]+fh2s[ 	]+f20,f20
0x[0-9a-f]+ e560 2575[ 	]+fh2s[ 	]+f21,f21
0x[0-9a-f]+ e660 25b5[ 	]+fh2s[ 	]+f22,f22
0x[0-9a-f]+ e760 25f5[ 	]+fh2s[ 	]+f23,f23
0x[0-9a-f]+ e060 3635[ 	]+fh2s[ 	]+f24,f24
0x[0-9a-f]+ e160 3675[ 	]+fh2s[ 	]+f25,f25
0x[0-9a-f]+ e260 36b5[ 	]+fh2s[ 	]+f26,f26
0x[0-9a-f]+ e360 36f5[ 	]+fh2s[ 	]+f27,f27
0x[0-9a-f]+ e460 3735[ 	]+fh2s[ 	]+f28,f28
0x[0-9a-f]+ e560 3775[ 	]+fh2s[ 	]+f29,f29
0x[0-9a-f]+ e660 37b5[ 	]+fh2s[ 	]+f30,f30
0x[0-9a-f]+ e760 37f5[ 	]+fh2s[ 	]+f31,f31

