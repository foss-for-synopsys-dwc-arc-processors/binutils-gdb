#as: -EL -mARC600
#objdump: -dr -EL

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	29 20 00 00             	flag       r0
   4:	69 20 40 00             	flag       1
   8:	69 20 80 00             	flag       2
   c:	69 20 00 01             	flag       4
  10:	69 20 00 02             	flag       8
  14:	69 20 00 04             	flag       16
  18:	69 20 00 08             	flag       32
  1c:	a9 20 01 00             	flag       64
  20:	a9 20 02 00             	flag       128
  24:	29 20 80 0f 00 80 01 00 	flag       0x80000001
  2c:	e9 20 0b 00             	flag.lt    r0
  30:	e9 20 69 00             	flag.gt    1
  34:	e9 20 a9 00             	flag.gt    2
  38:	e9 20 29 01             	flag.gt    4
  3c:	e9 20 29 02             	flag.gt    8
  40:	e9 20 29 04             	flag.gt    16
  44:	e9 20 29 08             	flag.gt    32
  48:	e9 20 89 0f 00 00 40 00 	flag.gt    64
  50:	e9 20 89 0f 00 00 80 00 	flag.gt    128
  58:	e9 20 8a 0f 00 80 01 00 	flag.ge    0x80000001
