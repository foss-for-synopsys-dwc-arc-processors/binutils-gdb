#as: -mcpu=hs5x
#source: fsrnd_rz-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e160 002e[ 	]+fsrnd_rz[ 	]+f0,f1
0x[0-9a-f]+ e360 00ae[ 	]+fsrnd_rz[ 	]+f2,f3
0x[0-9a-f]+ e560 012e[ 	]+fsrnd_rz[ 	]+f4,f5
0x[0-9a-f]+ e760 01ae[ 	]+fsrnd_rz[ 	]+f6,f7
0x[0-9a-f]+ e160 122e[ 	]+fsrnd_rz[ 	]+f8,f9
0x[0-9a-f]+ e360 12ae[ 	]+fsrnd_rz[ 	]+f10,f11
0x[0-9a-f]+ e560 132e[ 	]+fsrnd_rz[ 	]+f12,f13
0x[0-9a-f]+ e760 13ae[ 	]+fsrnd_rz[ 	]+f14,f15
0x[0-9a-f]+ e160 242e[ 	]+fsrnd_rz[ 	]+f16,f17
0x[0-9a-f]+ e360 24ae[ 	]+fsrnd_rz[ 	]+f18,f19
0x[0-9a-f]+ e560 252e[ 	]+fsrnd_rz[ 	]+f20,f21
0x[0-9a-f]+ e760 25ae[ 	]+fsrnd_rz[ 	]+f22,f23
0x[0-9a-f]+ e160 362e[ 	]+fsrnd_rz[ 	]+f24,f25
0x[0-9a-f]+ e360 36ae[ 	]+fsrnd_rz[ 	]+f26,f27
0x[0-9a-f]+ e560 372e[ 	]+fsrnd_rz[ 	]+f28,f29
0x[0-9a-f]+ e760 37ae[ 	]+fsrnd_rz[ 	]+f30,f31

