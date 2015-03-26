#source: sda_relocs.s
#as: -mHS
#ld: -q -T sda_relocs.ld
#objdump: -rd

.*:     file format elf32-littlearc


Disassembly of section .text:

00010054 <__SDATA_BEGIN__>:
   10054:	09 c8                   	ld_s       r0,\[gp,36\]
			10054: R_ARC_SDA16_LD2	a
   10056:	12 cc                   	ldh_s      r0,\[gp,36\]
			10056: R_ARC_SDA16_LD1	a
   10058:	24 ca                   	ldb_s      r0,\[gp,36\]
			10058: R_ARC_SDA16_LD	a
   1005a:	09 12 00 36             	ld.as      r0,\[gp,9\]
			1005a: R_ARC_SDA_LDST2	a
   1005e:	09 1a 18 30             	st.as      r0,\[gp,9\]
			1005e: R_ARC_SDA_LDST2	a
   10062:	09 12 00 36             	ld.as      r0,\[gp,9\]
			10062: R_ARC_SDA_LDST2	a
   10066:	24 12 80 30             	ldb        r0,\[gp,36\]
			10066: R_ARC_SDA_LDST	a
   1006a:	12 12 00 37             	ldh.as     r0,\[gp,18\]
			1006a: R_ARC_SDA_LDST1	a
   1006e:	12 1a 1c 30             	sth.as     r0,\[gp,18\]
			1006e: R_ARC_SDA_LDST1	a
   10072:	21 50                   	ld_s r1,\[gp ,36\]
			10072: R_ARC_SDA16_ST2	a
   10074:	31 50                   	st_s r0,\[gp ,36\]
			10074: R_ARC_SDA16_ST2	a
   10076:	e0 78                   	nop_s      
