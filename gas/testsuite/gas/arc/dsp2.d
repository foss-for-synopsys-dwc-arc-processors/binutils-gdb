#as: -mARC700 -mEA
#objdump: -dr  --prefix-addresses
#name: @OC@

# Test the @OC@ insn.

.*: +file format elf32-.*arc

Disassembly of section .text:
0x00000000 29@DSP2IC+0@0080     @OC@     @sp+6@r0,r1,r2
0x00000004 29@DSP2IC+0@8080     @OC@.f   @sp+6@r0,r1,r2
0x00000008 29@DSP2IC+1@0040     @OC@     @sp+6@r0,r1,1
0x0000000c 29@DSP2IC+1@8040     @OC@.f   @sp+6@r0,r1,1
0x00000010 29@DSP2IC+2@0fff     @OC@     @sp+6@r1,r1,-1
0x00000014 29@DSP2IC+2@8fff     @OC@.f   @sp+6@r1,r1,-1
0x00000018 29@DSP2IC+0@0081     @OC@     @sp+6@r1,r1,r2
0x0000001c 29@DSP2IC+0@8081     @OC@.f   @sp+6@r1,r1,r2
0x00000020 29@DSP2IC+3@0081     @OC@.z   @sp+6@r1,r1,r2
0x00000024 29@DSP2IC+3@8081     @OC@.z.f @sp+6@r1,r1,r2
0x00000028 29@DSP2IC+1@0081     @OC@     @sp+6@r1,r1,2
0x0000002c 29@DSP2IC+1@8081     @OC@.f   @sp+6@r1,r1,2
0x00000030 29@DSP2IC+3@00a1     @OC@.z   @sp+6@r1,r1,2
0x00000034 29@DSP2IC+3@80a1     @OC@.z.f @sp+6@r1,r1,2
0x00000038 2e@DSP2IC+0@7081     @OC@     @sp+6@r1,0xdeadbeef,r2
0x00000040 2e@DSP2IC+0@f081     @OC@.f   @sp+6@r1,0xdeadbeef,r2
0x00000048 2a@DSP2IC+0@0f81     @OC@     @sp+6@r1,r2,0xdeadbeef
0x00000050 2a@DSP2IC+0@8f81     @OC@.f   @sp+6@r1,r2,0xdeadbeef
0x00000058 29@DSP2IC+0@0f81     @OC@     @sp+6@r1,r1,0xdeadbeef
0x00000060 29@DSP2IC+0@8f81     @OC@.f   @sp+6@r1,r1,0xdeadbeef
0x00000068 29@DSP2IC+3@0f81     @OC@.z   @sp+6@r1,r1,0xdeadbeef
0x00000070 29@DSP2IC+3@8f81     @OC@.z.f @sp+6@r1,r1,0xdeadbeef
0x00000078 29@DSP2IC+0@00be     @OC@     @sp+6@0,r1,r2
0x0000007c 29@DSP2IC+0@80be     @OC@.f   @sp+6@0,r1,r2
0x00000080 29@DSP2IC+1@00be     @OC@     @sp+6@0,r1,2
0x00000084 29@DSP2IC+1@80be     @OC@.f   @sp+6@0,r1,2
0x00000088 2e@DSP2IC+0@707e     @OC@     @sp+6@0,0xdeadbeef,r1
0x00000090 2e@DSP2IC+0@f07e     @OC@.f   @sp+6@0,0xdeadbeef,r1
0x00000098 2e@DSP2IC+3@7041     @OC@.z   @sp+6@0,0xdeadbeef,r1
0x000000a0 2e@DSP2IC+3@f041     @OC@.z.f @sp+6@0,0xdeadbeef,r1
