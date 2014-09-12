#source: gotpc1.s
#as: -mARC700 -mEA
#ld: -q -T gotpc1.ld
#ld_after_inputfiles: tmpdir/libdummy.so.0
#objdump: -rd

.*:     file format elf32-littlearc


Disassembly of section \.text:

000100d4 <__start>:
   100d4:	00 27 84 7f 00 00 80 00 	add        r4,pcl,128
			100d8: R_ARC_GOTPC32	a_in_other_thread
   100dc:	00 1c 80 0f 00 00 01 00 	st         1,\[r4\]
