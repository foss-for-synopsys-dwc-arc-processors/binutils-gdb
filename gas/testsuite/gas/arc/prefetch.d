#as: -mARC700
#objdump: -dr
#name: prefetch

# Test the @OC@ insn.

.*: +file format elf32-.*arc

Disassembly of section .text:
00000000 <.text>:
   0:	ff 10 3e 80             	prefetch   \[r0,-1\]
   4:	00 16 3e 70 ad de ef be 	prefetch   \[0xdeadbeef\]
   c:	30 20 7e 00             	prefetch   \[r0,r1\]
  10:	30 20 be 0f ad de ef be 	prefetch   \[r0,0xdeadbeef\]
  18:	30 26 7e 70 ad de ef be 	prefetch   \[0xdeadbeef,r1\]
