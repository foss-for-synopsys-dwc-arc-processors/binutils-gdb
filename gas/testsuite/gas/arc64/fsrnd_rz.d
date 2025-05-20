#as: -mcpu=hs5x
#source: fsrnd_rz.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e060 002e[ 	]+fsrnd_rz[ 	]+f0,f0
0x[0-9a-f]+ e160 006e[ 	]+fsrnd_rz[ 	]+f1,f1
0x[0-9a-f]+ e260 00ae[ 	]+fsrnd_rz[ 	]+f2,f2
0x[0-9a-f]+ e360 00ee[ 	]+fsrnd_rz[ 	]+f3,f3
0x[0-9a-f]+ e460 012e[ 	]+fsrnd_rz[ 	]+f4,f4
0x[0-9a-f]+ e560 016e[ 	]+fsrnd_rz[ 	]+f5,f5
0x[0-9a-f]+ e660 01ae[ 	]+fsrnd_rz[ 	]+f6,f6
0x[0-9a-f]+ e760 01ee[ 	]+fsrnd_rz[ 	]+f7,f7
0x[0-9a-f]+ e060 122e[ 	]+fsrnd_rz[ 	]+f8,f8
0x[0-9a-f]+ e160 126e[ 	]+fsrnd_rz[ 	]+f9,f9
0x[0-9a-f]+ e260 12ae[ 	]+fsrnd_rz[ 	]+f10,f10
0x[0-9a-f]+ e360 12ee[ 	]+fsrnd_rz[ 	]+f11,f11
0x[0-9a-f]+ e460 132e[ 	]+fsrnd_rz[ 	]+f12,f12
0x[0-9a-f]+ e560 136e[ 	]+fsrnd_rz[ 	]+f13,f13
0x[0-9a-f]+ e660 13ae[ 	]+fsrnd_rz[ 	]+f14,f14
0x[0-9a-f]+ e760 13ee[ 	]+fsrnd_rz[ 	]+f15,f15
0x[0-9a-f]+ e060 242e[ 	]+fsrnd_rz[ 	]+f16,f16
0x[0-9a-f]+ e160 246e[ 	]+fsrnd_rz[ 	]+f17,f17
0x[0-9a-f]+ e260 24ae[ 	]+fsrnd_rz[ 	]+f18,f18
0x[0-9a-f]+ e360 24ee[ 	]+fsrnd_rz[ 	]+f19,f19
0x[0-9a-f]+ e460 252e[ 	]+fsrnd_rz[ 	]+f20,f20
0x[0-9a-f]+ e560 256e[ 	]+fsrnd_rz[ 	]+f21,f21
0x[0-9a-f]+ e660 25ae[ 	]+fsrnd_rz[ 	]+f22,f22
0x[0-9a-f]+ e760 25ee[ 	]+fsrnd_rz[ 	]+f23,f23
0x[0-9a-f]+ e060 362e[ 	]+fsrnd_rz[ 	]+f24,f24
0x[0-9a-f]+ e160 366e[ 	]+fsrnd_rz[ 	]+f25,f25
0x[0-9a-f]+ e260 36ae[ 	]+fsrnd_rz[ 	]+f26,f26
0x[0-9a-f]+ e360 36ee[ 	]+fsrnd_rz[ 	]+f27,f27
0x[0-9a-f]+ e460 372e[ 	]+fsrnd_rz[ 	]+f28,f28
0x[0-9a-f]+ e560 376e[ 	]+fsrnd_rz[ 	]+f29,f29
0x[0-9a-f]+ e660 37ae[ 	]+fsrnd_rz[ 	]+f30,f30
0x[0-9a-f]+ e760 37ee[ 	]+fsrnd_rz[ 	]+f31,f31

