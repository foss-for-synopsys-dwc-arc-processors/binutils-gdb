#as: -mARC700 -mEA
#objdump: -dr
#name: @OC@

# Test the @OC@ insn.

.*: +file format elf32-.*arc

Disassembly of section .text:

00000000 <.text>:
   0:	2f 28 @DSP1IC+1@ 00             	@OC@      @sp+5@r0,r1
   4:	6f 28 @DSP1IC+2@ 00             	@OC@      @sp+5@r0,2
   8:	2f 28 @DSP1IC+2@ 0f ad de ef be 	@OC@      @sp+5@r0,0xdeadbeef
  10:	2f 2e @DSP1IC+1@ 70             	@OC@      @sp+5@0,r1
  14:	6f 2e @DSP1IC+2@ 70             	@OC@      @sp+5@0,2
  18:	2f 2e @DSP1IC+2@ 7f ad de ef be 	@OC@      @sp+5@0,0xdeadbeef
  20:	2f 28 @DSP1IC+1@ 80             	@OC@.f    @sp+5@r0,r1
  24:	6f 28 @DSP1IC+2@ 80             	@OC@.f    @sp+5@r0,2
  28:	2f 28 @DSP1IC+2@ 8f ad de ef be 	@OC@.f    @sp+5@r0,0xdeadbeef
  30:	2f 2e @DSP1IC+1@ f0             	@OC@.f    @sp+5@0,r1
  34:	6f 2e @DSP1IC+2@ f0             	@OC@.f    @sp+5@0,2
  38:	2f 2e @DSP1IC+2@ ff ad de ef be 	@OC@.f    @sp+5@0,0xdeadbeef

