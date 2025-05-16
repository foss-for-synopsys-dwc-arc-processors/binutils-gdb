#as: -mcpu=hs5x
#source: fmvs2i.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e060 0031\s{2,}\tfmvs2i\tr0,f0
0x[0-9a-f]+ e160 0071\s{2,}\tfmvs2i\tr1,f1
0x[0-9a-f]+ e260 00b1\s{2,}\tfmvs2i\tr2,f2
0x[0-9a-f]+ e360 00f1\s{2,}\tfmvs2i\tr3,f3
0x[0-9a-f]+ e460 0131\s{2,}\tfmvs2i\tr4,f4
0x[0-9a-f]+ e560 0171\s{2,}\tfmvs2i\tr5,f5
0x[0-9a-f]+ e660 01b1\s{2,}\tfmvs2i\tr6,f6
0x[0-9a-f]+ e760 01f1\s{2,}\tfmvs2i\tr7,f7
0x[0-9a-f]+ e060 1231\s{2,}\tfmvs2i\tr8,f8
0x[0-9a-f]+ e160 1271\s{2,}\tfmvs2i\tr9,f9
0x[0-9a-f]+ e260 12b1\s{2,}\tfmvs2i\tr10,f10
0x[0-9a-f]+ e360 12f1\s{2,}\tfmvs2i\tr11,f11
0x[0-9a-f]+ e460 1331\s{2,}\tfmvs2i\tr12,f12
0x[0-9a-f]+ e560 1371\s{2,}\tfmvs2i\tr13,f13
0x[0-9a-f]+ e660 13b1\s{2,}\tfmvs2i\tr14,f14
0x[0-9a-f]+ e760 13f1\s{2,}\tfmvs2i\tr15,f15
0x[0-9a-f]+ e060 2431\s{2,}\tfmvs2i\tr16,f16
0x[0-9a-f]+ e160 2471\s{2,}\tfmvs2i\tr17,f17
0x[0-9a-f]+ e260 24b1\s{2,}\tfmvs2i\tr18,f18
0x[0-9a-f]+ e360 24f1\s{2,}\tfmvs2i\tr19,f19
0x[0-9a-f]+ e460 2531\s{2,}\tfmvs2i\tr20,f20
0x[0-9a-f]+ e560 2571\s{2,}\tfmvs2i\tr21,f21
0x[0-9a-f]+ e660 25b1\s{2,}\tfmvs2i\tr22,f22
0x[0-9a-f]+ e760 25f1\s{2,}\tfmvs2i\tr23,f23
0x[0-9a-f]+ e060 3631\s{2,}\tfmvs2i\tr24,f24
0x[0-9a-f]+ e160 3671\s{2,}\tfmvs2i\tr25,f25
0x[0-9a-f]+ e260 36b1\s{2,}\tfmvs2i\tr26,f26
0x[0-9a-f]+ e360 36f1\s{2,}\tfmvs2i\tfp,f27
0x[0-9a-f]+ e460 3731\s{2,}\tfmvs2i\tsp,f28
0x[0-9a-f]+ e560 3771\s{2,}\tfmvs2i\tilink,f29
0x[0-9a-f]+ e660 37b1\s{2,}\tfmvs2i\tr30,f30
0x[0-9a-f]+ e760 37f1\s{2,}\tfmvs2i\tblink,f31
