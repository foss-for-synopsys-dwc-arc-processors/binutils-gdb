#as: -mcpu=hs5x
#source: fmvi2s.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e0e0 0030\s{2,}fmvi2s\tf0,r0
0x[0-9a-f]+ e1e0 0070\s{2,}fmvi2s\tf1,r1
0x[0-9a-f]+ e2e0 00b0\s{2,}fmvi2s\tf2,r2
0x[0-9a-f]+ e3e0 00f0\s{2,}fmvi2s\tf3,r3
0x[0-9a-f]+ e4e0 0130\s{2,}fmvi2s\tf4,r4
0x[0-9a-f]+ e5e0 0170\s{2,}fmvi2s\tf5,r5
0x[0-9a-f]+ e6e0 01b0\s{2,}fmvi2s\tf6,r6
0x[0-9a-f]+ e7e0 01f0\s{2,}fmvi2s\tf7,r7
0x[0-9a-f]+ e0e0 1230\s{2,}fmvi2s\tf8,r8
0x[0-9a-f]+ e1e0 1270\s{2,}fmvi2s\tf9,r9
0x[0-9a-f]+ e2e0 12b0\s{2,}fmvi2s\tf10,r10
0x[0-9a-f]+ e3e0 12f0\s{2,}fmvi2s\tf11,r11
0x[0-9a-f]+ e4e0 1330\s{2,}fmvi2s\tf12,r12
0x[0-9a-f]+ e5e0 1370\s{2,}fmvi2s\tf13,r13
0x[0-9a-f]+ e6e0 13b0\s{2,}fmvi2s\tf14,r14
0x[0-9a-f]+ e7e0 13f0\s{2,}fmvi2s\tf15,r15
0x[0-9a-f]+ e0e0 2430\s{2,}fmvi2s\tf16,r16
0x[0-9a-f]+ e1e0 2470\s{2,}fmvi2s\tf17,r17
0x[0-9a-f]+ e2e0 24b0\s{2,}fmvi2s\tf18,r18
0x[0-9a-f]+ e3e0 24f0\s{2,}fmvi2s\tf19,r19
0x[0-9a-f]+ e4e0 2530\s{2,}fmvi2s\tf20,r20
0x[0-9a-f]+ e5e0 2570\s{2,}fmvi2s\tf21,r21
0x[0-9a-f]+ e6e0 25b0\s{2,}fmvi2s\tf22,r22
0x[0-9a-f]+ e7e0 25f0\s{2,}fmvi2s\tf23,r23
0x[0-9a-f]+ e0e0 3630\s{2,}fmvi2s\tf24,r24
0x[0-9a-f]+ e1e0 3670\s{2,}fmvi2s\tf25,r25
0x[0-9a-f]+ e2e0 36b0\s{2,}fmvi2s\tf26,r26
0x[0-9a-f]+ e3e0 36f0\s{2,}fmvi2s\tf27,fp
0x[0-9a-f]+ e4e0 3730\s{2,}fmvi2s\tf28,sp
0x[0-9a-f]+ e5e0 3770\s{2,}fmvi2s\tf29,ilink
0x[0-9a-f]+ e6e0 37b0\s{2,}fmvi2s\tf30,r30
0x[0-9a-f]+ e7e0 37f0\s{2,}fmvi2s\tf31,blink
