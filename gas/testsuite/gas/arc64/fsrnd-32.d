#as: -mcpu=hs5x
#source: fsrnd-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e160 0026[ 	]+fsrnd[ 	]+f0,f1
0x[0-9a-f]+ e360 00a6[ 	]+fsrnd[ 	]+f2,f3
0x[0-9a-f]+ e560 0126[ 	]+fsrnd[ 	]+f4,f5
0x[0-9a-f]+ e760 01a6[ 	]+fsrnd[ 	]+f6,f7
0x[0-9a-f]+ e160 1226[ 	]+fsrnd[ 	]+f8,f9
0x[0-9a-f]+ e360 12a6[ 	]+fsrnd[ 	]+f10,f11
0x[0-9a-f]+ e560 1326[ 	]+fsrnd[ 	]+f12,f13
0x[0-9a-f]+ e760 13a6[ 	]+fsrnd[ 	]+f14,f15
0x[0-9a-f]+ e160 2426[ 	]+fsrnd[ 	]+f16,f17
0x[0-9a-f]+ e360 24a6[ 	]+fsrnd[ 	]+f18,f19
0x[0-9a-f]+ e560 2526[ 	]+fsrnd[ 	]+f20,f21
0x[0-9a-f]+ e760 25a6[ 	]+fsrnd[ 	]+f22,f23
0x[0-9a-f]+ e160 3626[ 	]+fsrnd[ 	]+f24,f25
0x[0-9a-f]+ e360 36a6[ 	]+fsrnd[ 	]+f26,f27
0x[0-9a-f]+ e560 3726[ 	]+fsrnd[ 	]+f28,f29
0x[0-9a-f]+ e760 37a6[ 	]+fsrnd[ 	]+f30,f31
