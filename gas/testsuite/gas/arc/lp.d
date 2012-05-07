#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <text_label>:
   0:	a8 20 80 01             	lp         c <text_label\+0xc>

   4:	00 20 00 00             	add        r0,r0,r0
   8:	4a 26 00 70             	nop        
   c:	e8 20 20 01             	lp         14 <text_label\+0x14>

  10:	00 20 00 00             	add        r0,r0,r0
  14:	e8 20 20 01             	lp         1c <text_label\+0x1c>

  18:	00 20 00 00             	add        r0,r0,r0
  1c:	e8 20 21 01             	lpz        24 <text_label\+0x24>

  20:	00 20 00 00             	add        r0,r0,r0
  24:	e8 20 21 01             	lpz        2c <text_label\+0x2c>

  28:	00 20 00 00             	add        r0,r0,r0
  2c:	e8 20 22 01             	lpnz       34 <text_label\+0x34>

  30:	00 20 00 00             	add        r0,r0,r0
  34:	e8 20 22 01             	lpnz       3c <text_label\+0x3c>

  38:	00 20 00 00             	add        r0,r0,r0
  3c:	e8 20 23 01             	lpp        44 <text_label\+0x44>

  40:	00 20 00 00             	add        r0,r0,r0
  44:	e8 20 23 01             	lpp        4c <text_label\+0x4c>

  48:	00 20 00 00             	add        r0,r0,r0
  4c:	e8 20 24 01             	lpn        54 <text_label\+0x54>

  50:	00 20 00 00             	add        r0,r0,r0
  54:	e8 20 24 01             	lpn        5c <text_label\+0x5c>

  58:	00 20 00 00             	add        r0,r0,r0
  5c:	e8 20 25 01             	lpc        64 <text_label\+0x64>

  60:	00 20 00 00             	add        r0,r0,r0
  64:	e8 20 25 01             	lpc        6c <text_label\+0x6c>

  68:	00 20 00 00             	add        r0,r0,r0
  6c:	e8 20 25 01             	lpc        74 <text_label\+0x74>

  70:	00 20 00 00             	add        r0,r0,r0
  74:	e8 20 26 01             	lpnc       7c <text_label\+0x7c>

  78:	00 20 00 00             	add        r0,r0,r0
  7c:	e8 20 26 01             	lpnc       84 <text_label\+0x84>

  80:	00 20 00 00             	add        r0,r0,r0
  84:	e8 20 26 01             	lpnc       8c <text_label\+0x8c>

  88:	00 20 00 00             	add        r0,r0,r0
  8c:	e8 20 27 01             	lpv        94 <text_label\+0x94>

  90:	00 20 00 00             	add        r0,r0,r0
  94:	e8 20 27 01             	lpv        9c <text_label\+0x9c>

  98:	00 20 00 00             	add        r0,r0,r0
  9c:	e8 20 28 01             	lpnv       a4 <text_label\+0xa4>

  a0:	00 20 00 00             	add        r0,r0,r0
  a4:	e8 20 28 01             	lpnv       ac <text_label\+0xac>

  a8:	00 20 00 00             	add        r0,r0,r0
  ac:	e8 20 29 01             	lpgt       b4 <text_label\+0xb4>

  b0:	00 20 00 00             	add        r0,r0,r0
  b4:	e8 20 2a 01             	lpge       bc <text_label\+0xbc>

  b8:	00 20 00 00             	add        r0,r0,r0
  bc:	e8 20 2b 01             	lplt       c4 <text_label\+0xc4>

  c0:	00 20 00 00             	add        r0,r0,r0
  c4:	e8 20 2c 01             	lple       cc <text_label\+0xcc>

  c8:	00 20 00 00             	add        r0,r0,r0
  cc:	e8 20 2d 01             	lphi       d4 <text_label\+0xd4>

  d0:	00 20 00 00             	add        r0,r0,r0
  d4:	e8 20 2e 01             	lpls       dc <text_label\+0xdc>

  d8:	00 20 00 00             	add        r0,r0,r0
  dc:	e8 20 2f 01             	lppnz      e4 <text_label\+0xe4>

  e0:	00 20 00 00             	add        r0,r0,r0
