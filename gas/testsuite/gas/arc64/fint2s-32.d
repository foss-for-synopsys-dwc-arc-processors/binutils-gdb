#as: -mcpu=hs5x
#source: fint2s-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e0e0 0022[ 	]+fint2s[ 	]+f0,r0
0x[0-9a-f]+ e1e0 0062[ 	]+fint2s[ 	]+f1,r1
0x[0-9a-f]+ e2e0 00a2[ 	]+fint2s[ 	]+f2,r2
0x[0-9a-f]+ e3e0 00e2[ 	]+fint2s[ 	]+f3,r3
0x[0-9a-f]+ e4e0 0122[ 	]+fint2s[ 	]+f4,r4
0x[0-9a-f]+ e5e0 0162[ 	]+fint2s[ 	]+f5,r5
0x[0-9a-f]+ e6e0 01a2[ 	]+fint2s[ 	]+f6,r6
0x[0-9a-f]+ e7e0 01e2[ 	]+fint2s[ 	]+f7,r7
0x[0-9a-f]+ e0e0 1222[ 	]+fint2s[ 	]+f8,r8
0x[0-9a-f]+ e1e0 1262[ 	]+fint2s[ 	]+f9,r9
0x[0-9a-f]+ e2e0 12a2[ 	]+fint2s[ 	]+f10,r10
0x[0-9a-f]+ e3e0 12e2[ 	]+fint2s[ 	]+f11,r11
0x[0-9a-f]+ e4e0 1322[ 	]+fint2s[ 	]+f12,r12
0x[0-9a-f]+ e5e0 1362[ 	]+fint2s[ 	]+f13,r13
0x[0-9a-f]+ e6e0 13a2[ 	]+fint2s[ 	]+f14,r14
0x[0-9a-f]+ e7e0 13e2[ 	]+fint2s[ 	]+f15,r15
0x[0-9a-f]+ e0e0 2422[ 	]+fint2s[ 	]+f16,r16
0x[0-9a-f]+ e1e0 2462[ 	]+fint2s[ 	]+f17,r17
0x[0-9a-f]+ e2e0 24a2[ 	]+fint2s[ 	]+f18,r18
0x[0-9a-f]+ e3e0 24e2[ 	]+fint2s[ 	]+f19,r19
0x[0-9a-f]+ e4e0 2522[ 	]+fint2s[ 	]+f20,r20
0x[0-9a-f]+ e5e0 2562[ 	]+fint2s[ 	]+f21,r21
0x[0-9a-f]+ e6e0 25a2[ 	]+fint2s[ 	]+f22,r22
0x[0-9a-f]+ e7e0 25e2[ 	]+fint2s[ 	]+f23,r23
0x[0-9a-f]+ e0e0 3622[ 	]+fint2s[ 	]+f24,r24
0x[0-9a-f]+ e1e0 3662[ 	]+fint2s[ 	]+f25,r25
0x[0-9a-f]+ e2e0 36a2[ 	]+fint2s[ 	]+f26,r26
0x[0-9a-f]+ e3e0 36e2[ 	]+fint2s[ 	]+f27,fp
0x[0-9a-f]+ e4e0 3722[ 	]+fint2s[ 	]+f28,sp
0x[0-9a-f]+ e5e0 3762[ 	]+fint2s[ 	]+f29,ilink
0x[0-9a-f]+ e6e0 37a2[ 	]+fint2s[ 	]+f30,r30
0x[0-9a-f]+ e7e0 37e2[ 	]+fint2s[ 	]+f31,blink

