#as: -mARC700
#objdump: -dr
#name: @OC@

# Test the @OC@ insn.

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	@MUL_IC+0@ 21 80 00             	@OC@     @sp+6@r0,r1,r2
   4:	@MUL_IC+0@ 26 40 70 ad de ef be 	@OC@     @sp+6@r0,0xdeadbeef,r1
   c:	@MUL_IC+0@ 21 80 0f ad de ef be 	@OC@     @sp+6@r0,r1,0xdeadbeef
  14:	@MUL_IC+0@ 21 be 00             	@OC@     @sp+6@0,r1,r2
  18:	@MUL_IC+0@ 26 7e 70 ad de ef be 	@OC@     @sp+6@0,0xdeadbeef,r1
  20:	@MUL_IC+0@ 21 be 0f ad de ef be 	@OC@     @sp+6@0,r1,0xdeadbeef
  28:	@MUL_IC+0@ 26 80 7f ad de ef be 	@OC@     @sp+6@r0,0xdeadbeef,0xdeadbeef
  30:	@MUL_IC+0@ 26 be 7f ad de ef be 	@OC@     @sp+6@0,0xdeadbeef,0xdeadbeef
  38:	@MUL_IC+0@ 21 80 80             	@OC@.f   @sp+6@r0,r1,r2
  3c:	@MUL_IC+0@ 26 40 f0 ad de ef be 	@OC@.f   @sp+6@r0,0xdeadbeef,r1
  44:	@MUL_IC+0@ 21 80 8f ad de ef be 	@OC@.f   @sp+6@r0,r1,0xdeadbeef
  4c:	@MUL_IC+0@ 21 be 80             	@OC@.f   @sp+6@0,r1,r2
  50:	@MUL_IC+0@ 26 7e f0 ad de ef be 	@OC@.f   @sp+6@0,0xdeadbeef,r1
  58:	@MUL_IC+0@ 21 be 8f ad de ef be 	@OC@.f   @sp+6@0,r1,0xdeadbeef
  60:	@MUL_IC+0@ 26 80 ff ad de ef be 	@OC@.f   @sp+6@r0,0xdeadbeef,0xdeadbeef
  68:	@MUL_IC+0@ 26 be ff ad de ef be 	@OC@.f   @sp+6@0,0xdeadbeef,0xdeadbeef
  70:	@MUL_IC+1@ 21 40 00             	@OC@     @sp+6@r0,r1,1
  74:	@MUL_IC+1@ 21 7e 00             	@OC@     @sp+6@0,r1,1
  78:	@MUL_IC+1@ 26 40 70 ad de ef be 	@OC@     @sp+6@r0,0xdeadbeef,1
  80:	@MUL_IC+1@ 26 7e 70 ad de ef be 	@OC@     @sp+6@0,0xdeadbeef,1
  88:	@MUL_IC+1@ 21 40 80             	@OC@.f   @sp+6@r0,r1,1
  8c:	@MUL_IC+1@ 21 7e 80             	@OC@.f   @sp+6@0,r1,1
  90:	@MUL_IC+1@ 26 40 f0 ad de ef be 	@OC@.f   @sp+6@r0,0xdeadbeef,1
  98:	@MUL_IC+1@ 26 7e f0 ad de ef be 	@OC@.f   @sp+6@0,0xdeadbeef,1
  a0:	@MUL_IC+2@ 20 ff 0f             	@OC@     @sp+6@r0,r0,-1
  a4:	@MUL_IC+2@ 26 ff 7f ad de ef be 	@OC@     @sp+6@0,0xdeadbeef,-1
  ac:	@MUL_IC+2@ 20 ff 8f             	@OC@.f   @sp+6@r0,r0,-1
  b0:	@MUL_IC+2@ 26 ff ff ad de ef be 	@OC@.f   @sp+6@0,0xdeadbeef,-1
  b8:	@MUL_IC+3@ 21 81 00             	@OC@.z   @sp+6@r1,r1,r2
  bc:	@MUL_IC+3@ 26 41 70 ad de ef be 	@OC@.z   @sp+6@0,0xdeadbeef,r1
  c4:	@MUL_IC+3@ 21 81 0f ad de ef be 	@OC@.z   @sp+6@r1,r1,0xdeadbeef
  cc:	@MUL_IC+3@ 26 81 7f ad de ef be 	@OC@.z   @sp+6@0,0xdeadbeef,0xdeadbeef
  d4:	@MUL_IC+3@ 21 81 80             	@OC@.z.f @sp+6@r1,r1,r2
  d8:	@MUL_IC+3@ 26 41 f0 ad de ef be 	@OC@.z.f @sp+6@0,0xdeadbeef,r1
  e0:	@MUL_IC+3@ 21 81 8f ad de ef be 	@OC@.z.f @sp+6@r1,r1,0xdeadbeef
  e8:	@MUL_IC+3@ 26 81 ff ad de ef be 	@OC@.z.f @sp+6@0,0xdeadbeef,0xdeadbeef
  f0:	@MUL_IC+3@ 21 a1 00             	@OC@.z   @sp+6@r1,r1,2
  f4:	@MUL_IC+3@ 26 a1 70 ad de ef be 	@OC@.z   @sp+6@0,0xdeadbeef,2
  fc:	@MUL_IC+3@ 21 a1 80             	@OC@.z.f @sp+6@r1,r1,2
 100:	@MUL_IC+3@ 26 a1 f0 ad de ef be 	@OC@.z.f @sp+6@0,0xdeadbeef,2
