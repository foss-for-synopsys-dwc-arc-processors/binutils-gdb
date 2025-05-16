#as: -mcpu=hs5x
#source: fs2int-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e060 0023[ 	]+fs2int[ 	]+r0,f0
0x[0-9a-f]+ e160 0063[ 	]+fs2int[ 	]+r1,f1
0x[0-9a-f]+ e260 00a3[ 	]+fs2int[ 	]+r2,f2
0x[0-9a-f]+ e360 00e3[ 	]+fs2int[ 	]+r3,f3
0x[0-9a-f]+ e460 0123[ 	]+fs2int[ 	]+r4,f4
0x[0-9a-f]+ e560 0163[ 	]+fs2int[ 	]+r5,f5
0x[0-9a-f]+ e660 01a3[ 	]+fs2int[ 	]+r6,f6
0x[0-9a-f]+ e760 01e3[ 	]+fs2int[ 	]+r7,f7
0x[0-9a-f]+ e060 1223[ 	]+fs2int[ 	]+r8,f8
0x[0-9a-f]+ e160 1263[ 	]+fs2int[ 	]+r9,f9
0x[0-9a-f]+ e260 12a3[ 	]+fs2int[ 	]+r10,f10
0x[0-9a-f]+ e360 12e3[ 	]+fs2int[ 	]+r11,f11
0x[0-9a-f]+ e460 1323[ 	]+fs2int[ 	]+r12,f12
0x[0-9a-f]+ e560 1363[ 	]+fs2int[ 	]+r13,f13
0x[0-9a-f]+ e660 13a3[ 	]+fs2int[ 	]+r14,f14
0x[0-9a-f]+ e760 13e3[ 	]+fs2int[ 	]+r15,f15
0x[0-9a-f]+ e060 2423[ 	]+fs2int[ 	]+r16,f16
0x[0-9a-f]+ e160 2463[ 	]+fs2int[ 	]+r17,f17
0x[0-9a-f]+ e260 24a3[ 	]+fs2int[ 	]+r18,f18
0x[0-9a-f]+ e360 24e3[ 	]+fs2int[ 	]+r19,f19
0x[0-9a-f]+ e460 2523[ 	]+fs2int[ 	]+r20,f20
0x[0-9a-f]+ e560 2563[ 	]+fs2int[ 	]+r21,f21
0x[0-9a-f]+ e660 25a3[ 	]+fs2int[ 	]+r22,f22
0x[0-9a-f]+ e760 25e3[ 	]+fs2int[ 	]+r23,f23
0x[0-9a-f]+ e060 3623[ 	]+fs2int[ 	]+r24,f24
0x[0-9a-f]+ e160 3663[ 	]+fs2int[ 	]+r25,f25
0x[0-9a-f]+ e260 36a3[ 	]+fs2int[ 	]+r26,f26
0x[0-9a-f]+ e360 36e3[ 	]+fs2int[ 	]+fp,f27
0x[0-9a-f]+ e460 3723[ 	]+fs2int[ 	]+sp,f28
0x[0-9a-f]+ e560 3763[ 	]+fs2int[ 	]+ilink,f29
0x[0-9a-f]+ e660 37a3[ 	]+fs2int[ 	]+r30,f30
0x[0-9a-f]+ e760 37e3[ 	]+fs2int[ 	]+blink,f31

