#as: -mcpu=hs5x
#source: fs2int_rz-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e060 002b[ 	]+fs2int_rz[ 	]+r0,f0
0x[0-9a-f]+ e160 006b[ 	]+fs2int_rz[ 	]+r1,f1
0x[0-9a-f]+ e260 00ab[ 	]+fs2int_rz[ 	]+r2,f2
0x[0-9a-f]+ e360 00eb[ 	]+fs2int_rz[ 	]+r3,f3
0x[0-9a-f]+ e460 012b[ 	]+fs2int_rz[ 	]+r4,f4
0x[0-9a-f]+ e560 016b[ 	]+fs2int_rz[ 	]+r5,f5
0x[0-9a-f]+ e660 01ab[ 	]+fs2int_rz[ 	]+r6,f6
0x[0-9a-f]+ e760 01eb[ 	]+fs2int_rz[ 	]+r7,f7
0x[0-9a-f]+ e060 122b[ 	]+fs2int_rz[ 	]+r8,f8
0x[0-9a-f]+ e160 126b[ 	]+fs2int_rz[ 	]+r9,f9
0x[0-9a-f]+ e260 12ab[ 	]+fs2int_rz[ 	]+r10,f10
0x[0-9a-f]+ e360 12eb[ 	]+fs2int_rz[ 	]+r11,f11
0x[0-9a-f]+ e460 132b[ 	]+fs2int_rz[ 	]+r12,f12
0x[0-9a-f]+ e560 136b[ 	]+fs2int_rz[ 	]+r13,f13
0x[0-9a-f]+ e660 13ab[ 	]+fs2int_rz[ 	]+r14,f14
0x[0-9a-f]+ e760 13eb[ 	]+fs2int_rz[ 	]+r15,f15
0x[0-9a-f]+ e060 242b[ 	]+fs2int_rz[ 	]+r16,f16
0x[0-9a-f]+ e160 246b[ 	]+fs2int_rz[ 	]+r17,f17
0x[0-9a-f]+ e260 24ab[ 	]+fs2int_rz[ 	]+r18,f18
0x[0-9a-f]+ e360 24eb[ 	]+fs2int_rz[ 	]+r19,f19
0x[0-9a-f]+ e460 252b[ 	]+fs2int_rz[ 	]+r20,f20
0x[0-9a-f]+ e560 256b[ 	]+fs2int_rz[ 	]+r21,f21
0x[0-9a-f]+ e660 25ab[ 	]+fs2int_rz[ 	]+r22,f22
0x[0-9a-f]+ e760 25eb[ 	]+fs2int_rz[ 	]+r23,f23
0x[0-9a-f]+ e060 362b[ 	]+fs2int_rz[ 	]+r24,f24
0x[0-9a-f]+ e160 366b[ 	]+fs2int_rz[ 	]+r25,f25
0x[0-9a-f]+ e260 36ab[ 	]+fs2int_rz[ 	]+r26,f26
0x[0-9a-f]+ e360 36eb[ 	]+fs2int_rz[ 	]+fp,f27
0x[0-9a-f]+ e460 372b[ 	]+fs2int_rz[ 	]+sp,f28
0x[0-9a-f]+ e560 376b[ 	]+fs2int_rz[ 	]+ilink,f29
0x[0-9a-f]+ e660 37ab[ 	]+fs2int_rz[ 	]+r30,f30
0x[0-9a-f]+ e760 37eb[ 	]+fs2int_rz[ 	]+blink,f31

