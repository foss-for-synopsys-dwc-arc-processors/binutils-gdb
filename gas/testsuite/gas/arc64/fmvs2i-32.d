#as: -mcpu=hs5x
#source: fmvs2i-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e060 0031[ 	]+fmvs2i[ 	]+r0,f0
0x[0-9a-f]+ e160 0071[ 	]+fmvs2i[ 	]+r1,f1
0x[0-9a-f]+ e260 00b1[ 	]+fmvs2i[ 	]+r2,f2
0x[0-9a-f]+ e360 00f1[ 	]+fmvs2i[ 	]+r3,f3
0x[0-9a-f]+ e460 0131[ 	]+fmvs2i[ 	]+r4,f4
0x[0-9a-f]+ e560 0171[ 	]+fmvs2i[ 	]+r5,f5
0x[0-9a-f]+ e660 01b1[ 	]+fmvs2i[ 	]+r6,f6
0x[0-9a-f]+ e760 01f1[ 	]+fmvs2i[ 	]+r7,f7
0x[0-9a-f]+ e060 1231[ 	]+fmvs2i[ 	]+r8,f8
0x[0-9a-f]+ e160 1271[ 	]+fmvs2i[ 	]+r9,f9
0x[0-9a-f]+ e260 12b1[ 	]+fmvs2i[ 	]+r10,f10
0x[0-9a-f]+ e360 12f1[ 	]+fmvs2i[ 	]+r11,f11
0x[0-9a-f]+ e460 1331[ 	]+fmvs2i[ 	]+r12,f12
0x[0-9a-f]+ e560 1371[ 	]+fmvs2i[ 	]+r13,f13
0x[0-9a-f]+ e660 13b1[ 	]+fmvs2i[ 	]+r14,f14
0x[0-9a-f]+ e760 13f1[ 	]+fmvs2i[ 	]+r15,f15
0x[0-9a-f]+ e060 2431[ 	]+fmvs2i[ 	]+r16,f16
0x[0-9a-f]+ e160 2471[ 	]+fmvs2i[ 	]+r17,f17
0x[0-9a-f]+ e260 24b1[ 	]+fmvs2i[ 	]+r18,f18
0x[0-9a-f]+ e360 24f1[ 	]+fmvs2i[ 	]+r19,f19
0x[0-9a-f]+ e460 2531[ 	]+fmvs2i[ 	]+r20,f20
0x[0-9a-f]+ e560 2571[ 	]+fmvs2i[ 	]+r21,f21
0x[0-9a-f]+ e660 25b1[ 	]+fmvs2i[ 	]+r22,f22
0x[0-9a-f]+ e760 25f1[ 	]+fmvs2i[ 	]+r23,f23
0x[0-9a-f]+ e060 3631[ 	]+fmvs2i[ 	]+r24,f24
0x[0-9a-f]+ e160 3671[ 	]+fmvs2i[ 	]+r25,f25
0x[0-9a-f]+ e260 36b1[ 	]+fmvs2i[ 	]+r26,f26
0x[0-9a-f]+ e360 36f1[ 	]+fmvs2i[ 	]+fp,f27
0x[0-9a-f]+ e460 3731[ 	]+fmvs2i[ 	]+sp,f28
0x[0-9a-f]+ e560 3771[ 	]+fmvs2i[ 	]+ilink,f29
0x[0-9a-f]+ e660 37b1[ 	]+fmvs2i[ 	]+r30,f30
0x[0-9a-f]+ e760 37f1[ 	]+fmvs2i[ 	]+blink,f31
