#as: -mcpu=hs5x
#source: fs2uint-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e060 0021[ 	]+fs2uint[ 	]+r0,f0
0x[0-9a-f]+ e160 0061[ 	]+fs2uint[ 	]+r1,f1
0x[0-9a-f]+ e260 00a1[ 	]+fs2uint[ 	]+r2,f2
0x[0-9a-f]+ e360 00e1[ 	]+fs2uint[ 	]+r3,f3
0x[0-9a-f]+ e460 0121[ 	]+fs2uint[ 	]+r4,f4
0x[0-9a-f]+ e560 0161[ 	]+fs2uint[ 	]+r5,f5
0x[0-9a-f]+ e660 01a1[ 	]+fs2uint[ 	]+r6,f6
0x[0-9a-f]+ e760 01e1[ 	]+fs2uint[ 	]+r7,f7
0x[0-9a-f]+ e060 1221[ 	]+fs2uint[ 	]+r8,f8
0x[0-9a-f]+ e160 1261[ 	]+fs2uint[ 	]+r9,f9
0x[0-9a-f]+ e260 12a1[ 	]+fs2uint[ 	]+r10,f10
0x[0-9a-f]+ e360 12e1[ 	]+fs2uint[ 	]+r11,f11
0x[0-9a-f]+ e460 1321[ 	]+fs2uint[ 	]+r12,f12
0x[0-9a-f]+ e560 1361[ 	]+fs2uint[ 	]+r13,f13
0x[0-9a-f]+ e660 13a1[ 	]+fs2uint[ 	]+r14,f14
0x[0-9a-f]+ e760 13e1[ 	]+fs2uint[ 	]+r15,f15
0x[0-9a-f]+ e060 2421[ 	]+fs2uint[ 	]+r16,f16
0x[0-9a-f]+ e160 2461[ 	]+fs2uint[ 	]+r17,f17
0x[0-9a-f]+ e260 24a1[ 	]+fs2uint[ 	]+r18,f18
0x[0-9a-f]+ e360 24e1[ 	]+fs2uint[ 	]+r19,f19
0x[0-9a-f]+ e460 2521[ 	]+fs2uint[ 	]+r20,f20
0x[0-9a-f]+ e560 2561[ 	]+fs2uint[ 	]+r21,f21
0x[0-9a-f]+ e660 25a1[ 	]+fs2uint[ 	]+r22,f22
0x[0-9a-f]+ e760 25e1[ 	]+fs2uint[ 	]+r23,f23
0x[0-9a-f]+ e060 3621[ 	]+fs2uint[ 	]+r24,f24
0x[0-9a-f]+ e160 3661[ 	]+fs2uint[ 	]+r25,f25
0x[0-9a-f]+ e260 36a1[ 	]+fs2uint[ 	]+r26,f26
0x[0-9a-f]+ e360 36e1[ 	]+fs2uint[ 	]+fp,f27
0x[0-9a-f]+ e460 3721[ 	]+fs2uint[ 	]+sp,f28
0x[0-9a-f]+ e560 3761[ 	]+fs2uint[ 	]+ilink,f29
0x[0-9a-f]+ e660 37a1[ 	]+fs2uint[ 	]+r30,f30
0x[0-9a-f]+ e760 37e1[ 	]+fs2uint[ 	]+blink,f31

