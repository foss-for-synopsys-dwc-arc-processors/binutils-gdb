#as: -mcpu=hs5x
#source: fmvi2s-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e0e0 0030[ 	]+fmvi2s[ 	]+f0,r0
0x[0-9a-f]+ e1e0 0070[ 	]+fmvi2s[ 	]+f1,r1
0x[0-9a-f]+ e2e0 00b0[ 	]+fmvi2s[ 	]+f2,r2
0x[0-9a-f]+ e3e0 00f0[ 	]+fmvi2s[ 	]+f3,r3
0x[0-9a-f]+ e4e0 0130[ 	]+fmvi2s[ 	]+f4,r4
0x[0-9a-f]+ e5e0 0170[ 	]+fmvi2s[ 	]+f5,r5
0x[0-9a-f]+ e6e0 01b0[ 	]+fmvi2s[ 	]+f6,r6
0x[0-9a-f]+ e7e0 01f0[ 	]+fmvi2s[ 	]+f7,r7
0x[0-9a-f]+ e0e0 1230[ 	]+fmvi2s[ 	]+f8,r8
0x[0-9a-f]+ e1e0 1270[ 	]+fmvi2s[ 	]+f9,r9
0x[0-9a-f]+ e2e0 12b0[ 	]+fmvi2s[ 	]+f10,r10
0x[0-9a-f]+ e3e0 12f0[ 	]+fmvi2s[ 	]+f11,r11
0x[0-9a-f]+ e4e0 1330[ 	]+fmvi2s[ 	]+f12,r12
0x[0-9a-f]+ e5e0 1370[ 	]+fmvi2s[ 	]+f13,r13
0x[0-9a-f]+ e6e0 13b0[ 	]+fmvi2s[ 	]+f14,r14
0x[0-9a-f]+ e7e0 13f0[ 	]+fmvi2s[ 	]+f15,r15
0x[0-9a-f]+ e0e0 2430[ 	]+fmvi2s[ 	]+f16,r16
0x[0-9a-f]+ e1e0 2470[ 	]+fmvi2s[ 	]+f17,r17
0x[0-9a-f]+ e2e0 24b0[ 	]+fmvi2s[ 	]+f18,r18
0x[0-9a-f]+ e3e0 24f0[ 	]+fmvi2s[ 	]+f19,r19
0x[0-9a-f]+ e4e0 2530[ 	]+fmvi2s[ 	]+f20,r20
0x[0-9a-f]+ e5e0 2570[ 	]+fmvi2s[ 	]+f21,r21
0x[0-9a-f]+ e6e0 25b0[ 	]+fmvi2s[ 	]+f22,r22
0x[0-9a-f]+ e7e0 25f0[ 	]+fmvi2s[ 	]+f23,r23
0x[0-9a-f]+ e0e0 3630[ 	]+fmvi2s[ 	]+f24,r24
0x[0-9a-f]+ e1e0 3670[ 	]+fmvi2s[ 	]+f25,r25
0x[0-9a-f]+ e2e0 36b0[ 	]+fmvi2s[ 	]+f26,r26
0x[0-9a-f]+ e3e0 36f0[ 	]+fmvi2s[ 	]+f27,fp
0x[0-9a-f]+ e4e0 3730[ 	]+fmvi2s[ 	]+f28,sp
0x[0-9a-f]+ e5e0 3770[ 	]+fmvi2s[ 	]+f29,ilink
0x[0-9a-f]+ e6e0 37b0[ 	]+fmvi2s[ 	]+f30,r30
0x[0-9a-f]+ e7e0 37f0[ 	]+fmvi2s[ 	]+f31,blink

