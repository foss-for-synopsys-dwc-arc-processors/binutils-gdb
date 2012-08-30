#as: -mARC700
#objdump: -dr  --prefix-addresses
#name: prefetch

# Test the @OC@ insn.

.*: +file format elf32-.*arc

Disassembly of section .text:
0x00000000 10ff803e     prefetch   \[r0,-1\]
0x00000004 1600703e     prefetch   \[0xdeadbeef\]
0x0000000c 2030007e     prefetch   \[r0,r1\]
0x00000010 20300fbe     prefetch   \[r0,0xdeadbeef\]
0x00000018 2630707e     prefetch   \[0xdeadbeef,r1\]
