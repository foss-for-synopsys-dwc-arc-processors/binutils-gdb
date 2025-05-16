#as: -mcpu=hs5x
#source: fs2h-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e060 0034[ 	]+fs2h[ 	]+f0,f0
0x[0-9a-f]+ e160 0074[ 	]+fs2h[ 	]+f1,f1
0x[0-9a-f]+ e260 00b4[ 	]+fs2h[ 	]+f2,f2
0x[0-9a-f]+ e360 00f4[ 	]+fs2h[ 	]+f3,f3
0x[0-9a-f]+ e460 0134[ 	]+fs2h[ 	]+f4,f4
0x[0-9a-f]+ e560 0174[ 	]+fs2h[ 	]+f5,f5
0x[0-9a-f]+ e660 01b4[ 	]+fs2h[ 	]+f6,f6
0x[0-9a-f]+ e760 01f4[ 	]+fs2h[ 	]+f7,f7
0x[0-9a-f]+ e060 1234[ 	]+fs2h[ 	]+f8,f8
0x[0-9a-f]+ e160 1274[ 	]+fs2h[ 	]+f9,f9
0x[0-9a-f]+ e260 12b4[ 	]+fs2h[ 	]+f10,f10
0x[0-9a-f]+ e360 12f4[ 	]+fs2h[ 	]+f11,f11
0x[0-9a-f]+ e460 1334[ 	]+fs2h[ 	]+f12,f12
0x[0-9a-f]+ e560 1374[ 	]+fs2h[ 	]+f13,f13
0x[0-9a-f]+ e660 13b4[ 	]+fs2h[ 	]+f14,f14
0x[0-9a-f]+ e760 13f4[ 	]+fs2h[ 	]+f15,f15
0x[0-9a-f]+ e060 2434[ 	]+fs2h[ 	]+f16,f16
0x[0-9a-f]+ e160 2474[ 	]+fs2h[ 	]+f17,f17
0x[0-9a-f]+ e260 24b4[ 	]+fs2h[ 	]+f18,f18
0x[0-9a-f]+ e360 24f4[ 	]+fs2h[ 	]+f19,f19
0x[0-9a-f]+ e460 2534[ 	]+fs2h[ 	]+f20,f20
0x[0-9a-f]+ e560 2574[ 	]+fs2h[ 	]+f21,f21
0x[0-9a-f]+ e660 25b4[ 	]+fs2h[ 	]+f22,f22
0x[0-9a-f]+ e760 25f4[ 	]+fs2h[ 	]+f23,f23
0x[0-9a-f]+ e060 3634[ 	]+fs2h[ 	]+f24,f24
0x[0-9a-f]+ e160 3674[ 	]+fs2h[ 	]+f25,f25
0x[0-9a-f]+ e260 36b4[ 	]+fs2h[ 	]+f26,f26
0x[0-9a-f]+ e360 36f4[ 	]+fs2h[ 	]+f27,f27
0x[0-9a-f]+ e460 3734[ 	]+fs2h[ 	]+f28,f28
0x[0-9a-f]+ e560 3774[ 	]+fs2h[ 	]+f29,f29
0x[0-9a-f]+ e660 37b4[ 	]+fs2h[ 	]+f30,f30
0x[0-9a-f]+ e760 37f4[ 	]+fs2h[ 	]+f31,f31
