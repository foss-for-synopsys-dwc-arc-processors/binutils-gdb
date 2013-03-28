#as: -mARC700
#objdump: -dr
#name: general_a700

# Test the @OC@ insn.

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	6f 23 3f 00             	sync       
   4:	2f 24 3f 00             	rtie       
   8:	6f 25 3f 00             	brk        
   c:	6f 21 3f 00             	sleep      
  10:	3e 78                   	trap_s     1
  12:	6f 22 3f 00             	swi        
  16:	6f 21 3f 00             	sleep      
  1a:	6f 21 3f 00             	sleep      
  1e:	6f 21 7f 00             	sleep      1
  22:	6f 21 bf 00             	sleep      2
  26:	6f 21 ff 00             	sleep      3
  2a:	6f 21 3f 01             	sleep      4
  2e:	e0 79                   	unimp_s    
  30:	2f 20 4c 00             	ex         r0,\[r1\]
  34:	2f 20 4c 80             	ex.di      r0,\[r1\]
  38:	2f 20 8c 0f ad de ef be 	ex         r0,\[0xdeadbeef\]
  40:	2f 20 8c 8f ad de ef be 	ex.di      r0,\[0xdeadbeef\]



