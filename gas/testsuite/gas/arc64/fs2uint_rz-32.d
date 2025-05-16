#as: -mcpu=hs5x
#source: fs2uint_rz-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e060 0029[ 	]+fs2uint_rz[ 	]+r0,f0
0x[0-9a-f]+ e160 0069[ 	]+fs2uint_rz[ 	]+r1,f1
0x[0-9a-f]+ e260 00a9[ 	]+fs2uint_rz[ 	]+r2,f2
0x[0-9a-f]+ e360 00e9[ 	]+fs2uint_rz[ 	]+r3,f3
0x[0-9a-f]+ e460 0129[ 	]+fs2uint_rz[ 	]+r4,f4
0x[0-9a-f]+ e560 0169[ 	]+fs2uint_rz[ 	]+r5,f5
0x[0-9a-f]+ e660 01a9[ 	]+fs2uint_rz[ 	]+r6,f6
0x[0-9a-f]+ e760 01e9[ 	]+fs2uint_rz[ 	]+r7,f7
0x[0-9a-f]+ e060 1229[ 	]+fs2uint_rz[ 	]+r8,f8
0x[0-9a-f]+ e160 1269[ 	]+fs2uint_rz[ 	]+r9,f9
0x[0-9a-f]+ e260 12a9[ 	]+fs2uint_rz[ 	]+r10,f10
0x[0-9a-f]+ e360 12e9[ 	]+fs2uint_rz[ 	]+r11,f11
0x[0-9a-f]+ e460 1329[ 	]+fs2uint_rz[ 	]+r12,f12
0x[0-9a-f]+ e560 1369[ 	]+fs2uint_rz[ 	]+r13,f13
0x[0-9a-f]+ e660 13a9[ 	]+fs2uint_rz[ 	]+r14,f14
0x[0-9a-f]+ e760 13e9[ 	]+fs2uint_rz[ 	]+r15,f15
0x[0-9a-f]+ e060 2429[ 	]+fs2uint_rz[ 	]+r16,f16
0x[0-9a-f]+ e160 2469[ 	]+fs2uint_rz[ 	]+r17,f17
0x[0-9a-f]+ e260 24a9[ 	]+fs2uint_rz[ 	]+r18,f18
0x[0-9a-f]+ e360 24e9[ 	]+fs2uint_rz[ 	]+r19,f19
0x[0-9a-f]+ e460 2529[ 	]+fs2uint_rz[ 	]+r20,f20
0x[0-9a-f]+ e560 2569[ 	]+fs2uint_rz[ 	]+r21,f21
0x[0-9a-f]+ e660 25a9[ 	]+fs2uint_rz[ 	]+r22,f22
0x[0-9a-f]+ e760 25e9[ 	]+fs2uint_rz[ 	]+r23,f23
0x[0-9a-f]+ e060 3629[ 	]+fs2uint_rz[ 	]+r24,f24
0x[0-9a-f]+ e160 3669[ 	]+fs2uint_rz[ 	]+r25,f25
0x[0-9a-f]+ e260 36a9[ 	]+fs2uint_rz[ 	]+r26,f26
0x[0-9a-f]+ e360 36e9[ 	]+fs2uint_rz[ 	]+fp,f27
0x[0-9a-f]+ e460 3729[ 	]+fs2uint_rz[ 	]+sp,f28
0x[0-9a-f]+ e560 3769[ 	]+fs2uint_rz[ 	]+ilink,f29
0x[0-9a-f]+ e660 37a9[ 	]+fs2uint_rz[ 	]+r30,f30
0x[0-9a-f]+ e760 37e9[ 	]+fs2uint_rz[ 	]+blink,f31
