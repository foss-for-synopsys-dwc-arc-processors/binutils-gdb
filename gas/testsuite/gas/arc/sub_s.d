#as: -mARC700
#objdump: -dr  --prefix-addresses
#name: prefetch

# Test the @OC@ insn.

.*: +file format elf32-.*arc

Disassembly of section .text:
0x00000000         00006908     sub_s      r0,r1,0
0x00000002         0000690f     sub_s      r0,r1,7
0x00000004         00007822     sub_s      r0,r0,r1
0x00000006         00007822     sub_s      r0,r0,r1
0x00000008         00006808     sub_s      r0,r0,0
0x0000000a         0000b87f     sub_s      r0,r0,31
0x0000000c         000078c0     sub_s.ne   r0,r0,r0
0x0000000e         0000c1a0     sub_s      sp,sp,0
0x00000010         0000c1bf     sub_s      sp,sp,124
