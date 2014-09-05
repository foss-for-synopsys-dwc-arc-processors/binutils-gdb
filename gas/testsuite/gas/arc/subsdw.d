#as: -mARC700 -mEA
#objdump: -dr 
#name: subsdw

# Test the subsdw insn.

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	29 29 80 00             	subsdw     r0,r1,r2
   4:	29 29 80 80             	subsdw.f   r0,r1,r2
   8:	69 29 40 00             	subsdw     r0,r1,1
   c:	69 29 40 80             	subsdw.f   r0,r1,1
  10:	a9 29 ff 0f             	subsdw     r1,r1,-1
  14:	a9 29 ff 8f             	subsdw.f   r1,r1,-1
  18:	29 29 81 00             	subsdw     r1,r1,r2
  1c:	29 29 81 80             	subsdw.f   r1,r1,r2
  20:	e9 29 81 00             	subsdw.z   r1,r1,r2
  24:	e9 29 81 80             	subsdw.z.f r1,r1,r2
  28:	69 29 81 00             	subsdw     r1,r1,2
  2c:	69 29 81 80             	subsdw.f   r1,r1,2
  30:	e9 29 a1 00             	subsdw.z   r1,r1,2
  34:	e9 29 a1 80             	subsdw.z.f r1,r1,2
  38:	29 2e 81 70 ad de ef be 	subsdw     r1,0xdeadbeef,r2
  40:	29 2e 81 f0 ad de ef be 	subsdw.f   r1,0xdeadbeef,r2
  48:	29 2a 81 0f ad de ef be 	subsdw     r1,r2,0xdeadbeef
  50:	29 2a 81 8f ad de ef be 	subsdw.f   r1,r2,0xdeadbeef
  58:	29 29 81 0f ad de ef be 	subsdw     r1,r1,0xdeadbeef
  60:	29 29 81 8f ad de ef be 	subsdw.f   r1,r1,0xdeadbeef
  68:	e9 29 81 0f ad de ef be 	subsdw.z   r1,r1,0xdeadbeef
  70:	e9 29 81 8f ad de ef be 	subsdw.z.f r1,r1,0xdeadbeef
  78:	29 29 be 00             	subsdw     0,r1,r2
  7c:	29 29 be 80             	subsdw.f   0,r1,r2
  80:	69 29 be 00             	subsdw     0,r1,2
  84:	69 29 be 80             	subsdw.f   0,r1,2
  88:	29 2e 7e 70 ad de ef be 	subsdw     0,0xdeadbeef,r1
  90:	29 2e 7e f0 ad de ef be 	subsdw.f   0,0xdeadbeef,r1
  98:	e9 2e 41 70 ad de ef be 	subsdw.z   0,0xdeadbeef,r1
  a0:	e9 2e 41 f0 ad de ef be 	subsdw.z.f 0,0xdeadbeef,r1
  a8:	a9 2e 3f 72 ad de ef be 	subsdw     0,0xdeadbeef,-56
