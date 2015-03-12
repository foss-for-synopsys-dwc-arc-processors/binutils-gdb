#source: gotpc1.s
#as: -mARC700 -mEA
#ld: -q -T gotpc2.ld
#ld_after_inputfiles: tmpdir/libdummy.so.0
#objdump: -rd

.*:     file format elf32-littlearc


Disassembly of section \.text:

0001016c <__start>:
   1016c:	00 27 84 7f ff ff 88 ff 	add        r4,pcl,-120
			10170: R_ARC_GOTPC32	a_in_other_thread
   10174:	00 1c 80 0f 00 00 01 00 	st         1,\[r4\]
