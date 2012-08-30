#as: -EL -mARC600
#objdump: -dr -EL
#.*: +file format elf32-.*arc

.*:     file format elf32-littlearc

Disassembly of section .text:

00000000 <.text>:
   0:	78 78 	        00007878     asl_s      r0,r0,r3
   2:	b8 7c 	        00007cb8     asl_s      r12,r12,r13
   4:	b7 6c 	        00006cb7     asl_s      r13,r12,7
   6:	14 69 	        00006914     asl_s      r0,r1,4
   8:	1f bd 	        0000bd1f     asl_s      r13,r13,31
   a:	1f ba 	        0000ba1f     asl_s      r2,r2,31
   c:	7b 7a 	        00007a7b     asl_s      r2,r3
   e:	3b 78 	        0000783b     asl_s      r0,r1
