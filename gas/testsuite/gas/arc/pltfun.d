#as: -EL -mARC700
#objdump: -dr -EL

.*: +file format elf32-.*arc


Disassembly of section .text:

00000000 <f>:
   0:	f1 c0                   	push_s     blink
   2:	fc 1c c8 b6             	st.a       fp,\[sp,-4\]
   6:	0a 23 00 37             	mov        fp,sp
   a:	02 08 00 00             	bl         8 <f\+0x8>

			a: R_ARC_S25W_PCREL	plt
   e:	04 14 1b 34             	ld.ab      fp,\[sp,4\]
  12:	d1 c0                   	pop_s      blink
  14:	e0 7e                   	j_s        \[blink\]
  16:	e0 78                   	nop_s      
