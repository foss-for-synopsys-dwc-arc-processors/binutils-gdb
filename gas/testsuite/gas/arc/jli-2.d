#as:
#objdump: -dr

.*: +file format .*


Disassembly of section .text:

00000000 <.text>:
   0:	2015 0f80 0000 0000 	add2	r0,r0,0
			4: R_ARC_PC32	foo
   8:	2095 0000           	add2	r0,r0,0
			8: R_ARC_JLI_SECTOFF_SIMM12	foo
   c:	2015 0f80 0000 0000 	add2	r0,r0,0
			10: R_ARC_32_ME	foo
  14:	2095 0fc7           	add2	r0,r0,511
