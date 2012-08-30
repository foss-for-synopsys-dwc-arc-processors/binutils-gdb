#as: -mARC700 -mEA
#objdump: -dr  --prefix-addresses
#name: @OC@

# Test the @OC@ insn.

.*: +file format elf32-.*arc

Disassembly of section .text:
0x00000000 282f00@DSP1IC+1@     @OC@      @sp+5@r0,r1
0x00000004 286f00@DSP1IC+2@     @OC@      @sp+5@r0,2
0x00000008 282f0f@DSP1IC+2@     @OC@      @sp+5@r0,0xdeadbeef
0x00000010 2e2f70@DSP1IC+1@     @OC@      @sp+5@0,r1
0x00000014 2e6f70@DSP1IC+2@     @OC@      @sp+5@0,2
0x00000018 2e2f7f@DSP1IC+2@     @OC@      @sp+5@0,0xdeadbeef
0x00000020 282f80@DSP1IC+1@     @OC@.f    @sp+5@r0,r1
0x00000024 286f80@DSP1IC+2@     @OC@.f    @sp+5@r0,2
0x00000028 282f8f@DSP1IC+2@     @OC@.f    @sp+5@r0,0xdeadbeef
0x00000030 2e2ff0@DSP1IC+1@     @OC@.f    @sp+5@0,r1
0x00000034 2e6ff0@DSP1IC+2@     @OC@.f    @sp+5@0,2
0x00000038 2e2fff@DSP1IC+2@     @OC@.f    @sp+5@0,0xdeadbeef

