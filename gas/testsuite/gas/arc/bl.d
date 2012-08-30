#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <text_label>:
   0:	02 08 00 00             	bl         0 <text_label>

   4:	fc 0f c0 ff             	bl         0 <text_label>

   8:	f8 0f c0 ff             	bl         0 <text_label>

   c:	f4 0f c1 ff             	blz        0 <text_label>

  10:	f0 0f c1 ff             	blz        0 <text_label>

  14:	ec 0f c2 ff             	blnz       0 <text_label>

  18:	e8 0f c2 ff             	blnz       0 <text_label>

  1c:	e4 0f c3 ff             	blp        0 <text_label>

  20:	e0 0f c3 ff             	blp        0 <text_label>

  24:	dc 0f c4 ff             	bln        0 <text_label>

  28:	d8 0f c4 ff             	bln        0 <text_label>

  2c:	d4 0f c5 ff             	blc        0 <text_label>

  30:	d0 0f c5 ff             	blc        0 <text_label>

  34:	cc 0f c5 ff             	blc        0 <text_label>

  38:	c8 0f c6 ff             	blnc       0 <text_label>

  3c:	c4 0f c6 ff             	blnc       0 <text_label>

  40:	c0 0f c6 ff             	blnc       0 <text_label>

  44:	bc 0f c7 ff             	blv        0 <text_label>

  48:	b8 0f c7 ff             	blv        0 <text_label>

  4c:	b4 0f c8 ff             	blnv       0 <text_label>

  50:	b0 0f c8 ff             	blnv       0 <text_label>

  54:	ac 0f c9 ff             	blgt       0 <text_label>

  58:	a8 0f ca ff             	blge       0 <text_label>

  5c:	a4 0f cb ff             	bllt       0 <text_label>

  60:	a0 0f cc ff             	blle       0 <text_label>

  64:	9c 0f cd ff             	blhi       0 <text_label>

  68:	98 0f ce ff             	blls       0 <text_label>

  6c:	94 0f cf ff             	blpnz      0 <text_label>

  70:	92 0f ef ff             	bl.d       0 <text_label>

  74:	4a 26 00 70             	nop        
  78:	8a 0f cf ff             	bl         0 <text_label>

  7c:	4a 26 00 70             	nop        
  80:	80 0f e1 ff             	blz.d      0 <text_label>

  84:	4a 26 00 70             	nop        
  88:	78 0f c2 ff             	blnz       0 <text_label>

  8c:	4a 26 00 70             	nop        
