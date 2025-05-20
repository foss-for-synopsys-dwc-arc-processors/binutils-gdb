#as: -mcpu=hs5x
#source: fsrnd.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e060 0026[ 	]+fsrnd[ 	]+f0,f0
0x[0-9a-f]+ e160 0066[ 	]+fsrnd[ 	]+f1,f1
0x[0-9a-f]+ e260 00a6[ 	]+fsrnd[ 	]+f2,f2
0x[0-9a-f]+ e360 00e6[ 	]+fsrnd[ 	]+f3,f3
0x[0-9a-f]+ e460 0126[ 	]+fsrnd[ 	]+f4,f4
0x[0-9a-f]+ e560 0166[ 	]+fsrnd[ 	]+f5,f5
0x[0-9a-f]+ e660 01a6[ 	]+fsrnd[ 	]+f6,f6
0x[0-9a-f]+ e760 01e6[ 	]+fsrnd[ 	]+f7,f7
0x[0-9a-f]+ e060 1226[ 	]+fsrnd[ 	]+f8,f8
0x[0-9a-f]+ e160 1266[ 	]+fsrnd[ 	]+f9,f9
0x[0-9a-f]+ e260 12a6[ 	]+fsrnd[ 	]+f10,f10
0x[0-9a-f]+ e360 12e6[ 	]+fsrnd[ 	]+f11,f11
0x[0-9a-f]+ e460 1326[ 	]+fsrnd[ 	]+f12,f12
0x[0-9a-f]+ e560 1366[ 	]+fsrnd[ 	]+f13,f13
0x[0-9a-f]+ e660 13a6[ 	]+fsrnd[ 	]+f14,f14
0x[0-9a-f]+ e760 13e6[ 	]+fsrnd[ 	]+f15,f15
0x[0-9a-f]+ e060 2426[ 	]+fsrnd[ 	]+f16,f16
0x[0-9a-f]+ e160 2466[ 	]+fsrnd[ 	]+f17,f17
0x[0-9a-f]+ e260 24a6[ 	]+fsrnd[ 	]+f18,f18
0x[0-9a-f]+ e360 24e6[ 	]+fsrnd[ 	]+f19,f19
0x[0-9a-f]+ e460 2526[ 	]+fsrnd[ 	]+f20,f20
0x[0-9a-f]+ e560 2566[ 	]+fsrnd[ 	]+f21,f21
0x[0-9a-f]+ e660 25a6[ 	]+fsrnd[ 	]+f22,f22
0x[0-9a-f]+ e760 25e6[ 	]+fsrnd[ 	]+f23,f23
0x[0-9a-f]+ e060 3626[ 	]+fsrnd[ 	]+f24,f24
0x[0-9a-f]+ e160 3666[ 	]+fsrnd[ 	]+f25,f25
0x[0-9a-f]+ e260 36a6[ 	]+fsrnd[ 	]+f26,f26
0x[0-9a-f]+ e360 36e6[ 	]+fsrnd[ 	]+f27,f27
0x[0-9a-f]+ e460 3726[ 	]+fsrnd[ 	]+f28,f28
0x[0-9a-f]+ e560 3766[ 	]+fsrnd[ 	]+f29,f29
0x[0-9a-f]+ e660 37a6[ 	]+fsrnd[ 	]+f30,f30
0x[0-9a-f]+ e760 37e6[ 	]+fsrnd[ 	]+f31,f31
