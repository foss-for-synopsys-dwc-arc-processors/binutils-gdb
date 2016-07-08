#as:
#objdump: -Dr

.*: +file format .*


Disassembly of section .group:

00000000 <jli_group>:
   0:	0[10] 00 00 0[01]             	.word	0x00000001
   4:	0[70] 00 00 0[07]             	.word	0x00000007

Disassembly of section .text:

00000000 <.text>:
   0:	2095 0000           	add2	r0,r0,0
			0: R_ARC_JLI_SECTOFF_SIMM12	foo
   4:	5800                	jli_s	0
			4: R_ARC_JLI_SECTOFF	__jli.foo

Disassembly of section .data:

00000000 <.data>:
   0:	00 00 00 00             	.word	0x00000000
			0: R_ARC_JLI_32	foo

Disassembly of section .jlitab.foo:

00000000 <__jli.foo>:
   0:	0001 0000           	b	0 <foo>
			0: R_ARC_S25H_PCREL	foo

#...
