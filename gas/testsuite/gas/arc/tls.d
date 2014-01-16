#as: -mARC700 -EL
#objdump: -dr -EL -mARC700

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	c7 70 00 00 00 00       	add_s      r0,r0,0
			2: R_ARC_TLS_LE_32	i
   6:	00 22 82 3f 00 00 00 00 	add        r2,gp,0
			a: R_ARC_TLS_LE_32	i
   e:	00 12 01 36             	ld.as      r1,\[gp,0\]
			e: R_ARC_TLS_LE_S9	i
  12:	00 12 00 36             	ld.as      r0,\[gp,0\]
			12: R_ARC_TLS_LE_S9	i
  16:	00 c8                   	ld_s       r0,\[gp,0\]
			16: R_ARC_TLS_LE_S9	i
  18:	00 1a 58 30             	st.as      r1,\[gp\]
			18: R_ARC_TLS_LE_S9	i
  1c:	00 1a 18 30             	st.as      r0,\[gp\]
			1c: R_ARC_TLS_LE_S9	i
  20:	30 27 82 7f 00 00 00 00 	ld         r2,\[pcl,0\]
			24: R_ARC_TLS_IE_GOT	i
  28:	30 27 80 7f 00 00 00 00 	ld         r0,\[pcl,0\]
			2c: R_ARC_TLS_GD_GOT	i
