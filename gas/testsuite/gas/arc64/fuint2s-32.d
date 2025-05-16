#as: -mcpu=hs5x
#source: fuint2s-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e0e0 0020[ 	]+fuint2s[ 	]+f0,r0
0x[0-9a-f]+ e1e0 0060[ 	]+fuint2s[ 	]+f1,r1
0x[0-9a-f]+ e2e0 00a0[ 	]+fuint2s[ 	]+f2,r2
0x[0-9a-f]+ e3e0 00e0[ 	]+fuint2s[ 	]+f3,r3
0x[0-9a-f]+ e4e0 0120[ 	]+fuint2s[ 	]+f4,r4
0x[0-9a-f]+ e5e0 0160[ 	]+fuint2s[ 	]+f5,r5
0x[0-9a-f]+ e6e0 01a0[ 	]+fuint2s[ 	]+f6,r6
0x[0-9a-f]+ e7e0 01e0[ 	]+fuint2s[ 	]+f7,r7
0x[0-9a-f]+ e0e0 1220[ 	]+fuint2s[ 	]+f8,r8
0x[0-9a-f]+ e1e0 1260[ 	]+fuint2s[ 	]+f9,r9
0x[0-9a-f]+ e2e0 12a0[ 	]+fuint2s[ 	]+f10,r10
0x[0-9a-f]+ e3e0 12e0[ 	]+fuint2s[ 	]+f11,r11
0x[0-9a-f]+ e4e0 1320[ 	]+fuint2s[ 	]+f12,r12
0x[0-9a-f]+ e5e0 1360[ 	]+fuint2s[ 	]+f13,r13
0x[0-9a-f]+ e6e0 13a0[ 	]+fuint2s[ 	]+f14,r14
0x[0-9a-f]+ e7e0 13e0[ 	]+fuint2s[ 	]+f15,r15
0x[0-9a-f]+ e0e0 2420[ 	]+fuint2s[ 	]+f16,r16
0x[0-9a-f]+ e1e0 2460[ 	]+fuint2s[ 	]+f17,r17
0x[0-9a-f]+ e2e0 24a0[ 	]+fuint2s[ 	]+f18,r18
0x[0-9a-f]+ e3e0 24e0[ 	]+fuint2s[ 	]+f19,r19
0x[0-9a-f]+ e4e0 2520[ 	]+fuint2s[ 	]+f20,r20
0x[0-9a-f]+ e5e0 2560[ 	]+fuint2s[ 	]+f21,r21
0x[0-9a-f]+ e6e0 25a0[ 	]+fuint2s[ 	]+f22,r22
0x[0-9a-f]+ e7e0 25e0[ 	]+fuint2s[ 	]+f23,r23
0x[0-9a-f]+ e0e0 3620[ 	]+fuint2s[ 	]+f24,r24
0x[0-9a-f]+ e1e0 3660[ 	]+fuint2s[ 	]+f25,r25
0x[0-9a-f]+ e2e0 36a0[ 	]+fuint2s[ 	]+f26,r26
0x[0-9a-f]+ e3e0 36e0[ 	]+fuint2s[ 	]+f27,fp
0x[0-9a-f]+ e4e0 3720[ 	]+fuint2s[ 	]+f28,sp
0x[0-9a-f]+ e5e0 3760[ 	]+fuint2s[ 	]+f29,ilink
0x[0-9a-f]+ e6e0 37a0[ 	]+fuint2s[ 	]+f30,r30
0x[0-9a-f]+ e7e0 37e0[ 	]+fuint2s[ 	]+f31,blink

