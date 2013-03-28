#as: -mARC700 -mEA
#objdump: -dr 
#name: @OC@

# Test the @OC@ insn.

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	@DSP2IC+0@ 29 80 00             	@OC@     @sp+6@r0,r1,r2
   4:	@DSP2IC+0@ 29 80 80             	@OC@.f   @sp+6@r0,r1,r2
   8:	@DSP2IC+1@ 29 40 00             	@OC@     @sp+6@r0,r1,1
   c:	@DSP2IC+1@ 29 40 80             	@OC@.f   @sp+6@r0,r1,1
  10:	@DSP2IC+2@ 29 ff 0f             	@OC@     @sp+6@r1,r1,-1
  14:	@DSP2IC+2@ 29 ff 8f             	@OC@.f   @sp+6@r1,r1,-1
  18:	@DSP2IC+0@ 29 81 00             	@OC@     @sp+6@r1,r1,r2
  1c:	@DSP2IC+0@ 29 81 80             	@OC@.f   @sp+6@r1,r1,r2
  20:	@DSP2IC+3@ 29 81 00             	@OC@.z   @sp+6@r1,r1,r2
  24:	@DSP2IC+3@ 29 81 80             	@OC@.z.f @sp+6@r1,r1,r2
  28:	@DSP2IC+1@ 29 81 00             	@OC@     @sp+6@r1,r1,2
  2c:	@DSP2IC+1@ 29 81 80             	@OC@.f   @sp+6@r1,r1,2
  30:	@DSP2IC+3@ 29 a1 00             	@OC@.z   @sp+6@r1,r1,2
  34:	@DSP2IC+3@ 29 a1 80             	@OC@.z.f @sp+6@r1,r1,2
  38:	@DSP2IC+0@ 2e 81 70 ad de ef be 	@OC@     @sp+6@r1,0xdeadbeef,r2
  40:	@DSP2IC+0@ 2e 81 f0 ad de ef be 	@OC@.f   @sp+6@r1,0xdeadbeef,r2
  48:	@DSP2IC+0@ 2a 81 0f ad de ef be 	@OC@     @sp+6@r1,r2,0xdeadbeef
  50:	@DSP2IC+0@ 2a 81 8f ad de ef be 	@OC@.f   @sp+6@r1,r2,0xdeadbeef
  58:	@DSP2IC+0@ 29 81 0f ad de ef be 	@OC@     @sp+6@r1,r1,0xdeadbeef
  60:	@DSP2IC+0@ 29 81 8f ad de ef be 	@OC@.f   @sp+6@r1,r1,0xdeadbeef
  68:	@DSP2IC+3@ 29 81 0f ad de ef be 	@OC@.z   @sp+6@r1,r1,0xdeadbeef
  70:	@DSP2IC+3@ 29 81 8f ad de ef be 	@OC@.z.f @sp+6@r1,r1,0xdeadbeef
  78:	@DSP2IC+0@ 29 be 00             	@OC@     @sp+6@0,r1,r2
  7c:	@DSP2IC+0@ 29 be 80             	@OC@.f   @sp+6@0,r1,r2
  80:	@DSP2IC+1@ 29 be 00             	@OC@     @sp+6@0,r1,2
  84:	@DSP2IC+1@ 29 be 80             	@OC@.f   @sp+6@0,r1,2
  88:	@DSP2IC+0@ 2e 7e 70 ad de ef be 	@OC@     @sp+6@0,0xdeadbeef,r1
  90:	@DSP2IC+0@ 2e 7e f0 ad de ef be 	@OC@.f   @sp+6@0,0xdeadbeef,r1
  98:	@DSP2IC+3@ 2e 41 70 ad de ef be 	@OC@.z   @sp+6@0,0xdeadbeef,r1
  a0:	@DSP2IC+3@ 2e 41 f0 ad de ef be 	@OC@.z.f @sp+6@0,0xdeadbeef,r1
