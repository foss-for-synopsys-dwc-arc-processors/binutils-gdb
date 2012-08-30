#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <text_label>:
   0:	01 00 00 00             	b          0 <text_label>

   4:	fc 07 c0 ff             	b          0 <text_label>

   8:	f8 07 c0 ff             	b          0 <text_label>

   c:	f4 07 c1 ff             	bz         0 <text_label>

  10:	f0 07 c1 ff             	bz         0 <text_label>

  14:	ec 07 c2 ff             	bnz        0 <text_label>

  18:	e8 07 c2 ff             	bnz        0 <text_label>

  1c:	e4 07 c3 ff             	bp         0 <text_label>

  20:	e0 07 c3 ff             	bp         0 <text_label>

  24:	dc 07 c4 ff             	bn         0 <text_label>

  28:	d8 07 c4 ff             	bn         0 <text_label>

  2c:	d4 07 c5 ff             	bc         0 <text_label>

  30:	d0 07 c5 ff             	bc         0 <text_label>

  34:	cc 07 c5 ff             	bc         0 <text_label>

  38:	c8 07 c6 ff             	bnc        0 <text_label>

  3c:	c4 07 c6 ff             	bnc        0 <text_label>

  40:	c0 07 c6 ff             	bnc        0 <text_label>

  44:	bc 07 c7 ff             	bv         0 <text_label>

  48:	b8 07 c7 ff             	bv         0 <text_label>

  4c:	b4 07 c8 ff             	bnv        0 <text_label>

  50:	b0 07 c8 ff             	bnv        0 <text_label>

  54:	ac 07 c9 ff             	bgt        0 <text_label>

  58:	a8 07 ca ff             	bge        0 <text_label>

  5c:	a4 07 cb ff             	blt        0 <text_label>

  60:	a0 07 cc ff             	ble        0 <text_label>

  64:	9c 07 cd ff             	bhi        0 <text_label>

  68:	98 07 ce ff             	bls        0 <text_label>

  6c:	94 07 cf ff             	bpnz       0 <text_label>

  70:	91 07 ef ff             	b.d        0 <text_label>

  74:	4a 26 00 70             	nop        
  78:	89 07 cf ff             	b          0 <text_label>

  7c:	4a 26 00 70             	nop        
  80:	80 07 e1 ff             	bz.d       0 <text_label>

  84:	4a 26 00 70             	nop        
  88:	78 07 c2 ff             	bnz        0 <text_label>

  8c:	4a 26 00 70             	nop        
