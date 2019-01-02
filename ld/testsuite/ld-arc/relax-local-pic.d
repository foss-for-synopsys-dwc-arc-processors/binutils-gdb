#source: relax-local-pic.s
#as:
#ld: -q -A elf32-arclittle -relax
#objdump: -dr

[^:]+:     file format elf32-.*arc


Disassembly of section \.text:

00000100 <__start>:
 100:	2700 7f84 0000 200c 	add	r4,pcl,0x200c	;210c <a_in_other_thread>
			104: R_ARC_PC32	a_in_other_thread
 108:	1c00 0041           	st	1,\[r4\]
