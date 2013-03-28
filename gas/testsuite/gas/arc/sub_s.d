#as: -mARC700
#objdump: -dr
#name: sub_s

# Test the @OC@ insn.

.*: +file format elf32-.*arc

Disassembly of section .text:
00000000 <.text>:
   0:	08 69                   	sub_s      r0,r1,0
   2:	0f 69                   	sub_s      r0,r1,7
   4:	22 78                   	sub_s      r0,r0,r1
   6:	22 78                   	sub_s      r0,r0,r1
   8:	08 68                   	sub_s      r0,r0,0
   a:	7f b8                   	sub_s      r0,r0,31
   c:	c0 78                   	sub_s.ne   r0,r0,r0
   e:	a0 c1                   	sub_s      sp,sp,0
  10:	bf c1                   	sub_s      sp,sp,124
