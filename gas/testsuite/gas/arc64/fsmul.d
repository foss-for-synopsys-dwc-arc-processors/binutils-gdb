#as: -mcpu=hs5x
#source: fsmul.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e202 4021\s{2,}\tfsmul\tf0,f1,f2
0x[0-9a-f]+ e502 40e4\s{2,}\tfsmul\tf3,f4,f5
0x[0-9a-f]+ e002 51a7\s{2,}\tfsmul\tf6,f7,f8
0x[0-9a-f]+ e302 526a\s{2,}\tfsmul\tf9,f10,f11
0x[0-9a-f]+ e602 532d\s{2,}\tfsmul\tf12,f13,f14
0x[0-9a-f]+ e102 63f0\s{2,}\tfsmul\tf15,f16,f17
0x[0-9a-f]+ e402 64b3\s{2,}\tfsmul\tf18,f19,f20
0x[0-9a-f]+ e702 6576\s{2,}\tfsmul\tf21,f22,f23
0x[0-9a-f]+ e202 7639\s{2,}\tfsmul\tf24,f25,f26
0x[0-9a-f]+ e502 76fc\s{2,}\tfsmul\tf27,f28,f29
0x[0-9a-f]+ e002 47bf\s{2,}\tfsmul\tf30,f31,f0

