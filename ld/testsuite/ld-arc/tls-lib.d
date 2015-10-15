
.*:     file format .*
architecture: .*:
HAS_RELOC, HAS_SYMS, DYNAMIC, D_PAGED
start address 0x[0-9a-f]+


Disassembly of section .text:

[0-9a-f]+ <foo>:
 [0-9a-f]+:	4a 26 00 70             	nop        
 [0-9a-f]+:	4a 26 00 70             	nop        
 [0-9a-f]+:	f1 c0                   	push_s     blink
 [0-9a-f]+:	00 21 80 3f ff ff 46 dd 	add        r0,r25,0xffffdd46
