#as: -mARC700 -EL
#objdump: -dr -EL -mARC700

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <bar>:
   0:	00 27 80 7f 00 00 00 00 	add        r0,pcl,0
			4: R_ARC_TLS_GD_GOT	a
   8:	80 80                   	ld_s       r12,\[r0,0\]
			8: R_ARC_TLS_GD_LD	a\+0x8
   a:	f1 c0                   	push_s     blink
   c:	4a 26 00 70             	nop        
  10:	40 7c                   	jl_s       \[r12\]
  12:	d1 c0                   	pop_s      blink
  14:	e0 7f                   	j_s.d      \[blink\]
  16:	00 80                   	ld_s       r0,\[r0,0\]

00000018 <foo>:
  18:	00 27 80 7f 00 00 00 00 	add        r0,pcl,0
			1c: R_ARC_TLS_GD_GOT	a
  20:	80 80                   	ld_s       r12,\[r0,0\]
			20: R_ARC_TLS_GD_LD	a
  22:	f1 c0                   	push_s     blink
  24:	4a 26 00 70             	nop        
  28:	40 7c                   	jl_s       \[r12\]
			28: R_ARC_TLS_GD_CALL	a
  2a:	d1 c0                   	pop_s      blink
  2c:	e0 7f                   	j_s.d      \[blink\]
  2e:	00 80                   	ld_s       r0,\[r0,0\]

