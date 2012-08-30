#as: -mARC700 -mmpy
#objdump: -dr  --prefix-addresses
#name: @OC@

# Test the @OC@ insn.

.*: +file format elf32-.*arc

Disassembly of section .text:
0x00000000 21@MUL_IC+0@0080     @OC@     @sp+6@r0,r1,r2
0x00000004 26@MUL_IC+0@7040     @OC@     @sp+6@r0,0xdeadbeef,r1
0x0000000c 21@MUL_IC+0@0f80     @OC@     @sp+6@r0,r1,0xdeadbeef
0x00000014 21@MUL_IC+0@00be     @OC@     @sp+6@0,r1,r2
0x00000018 26@MUL_IC+0@707e     @OC@     @sp+6@0,0xdeadbeef,r1
0x00000020 21@MUL_IC+0@0fbe     @OC@     @sp+6@0,r1,0xdeadbeef
0x00000028 26@MUL_IC+0@7f80     @OC@     @sp+6@r0,0xdeadbeef,0xdeadbeef
0x00000030 26@MUL_IC+0@7fbe     @OC@     @sp+6@0,0xdeadbeef,0xdeadbeef
0x00000038 21@MUL_IC+0@8080     @OC@.f   @sp+6@r0,r1,r2
0x0000003c 26@MUL_IC+0@f040     @OC@.f   @sp+6@r0,0xdeadbeef,r1
0x00000044 21@MUL_IC+0@8f80     @OC@.f   @sp+6@r0,r1,0xdeadbeef
0x0000004c 21@MUL_IC+0@80be     @OC@.f   @sp+6@0,r1,r2
0x00000050 26@MUL_IC+0@f07e     @OC@.f   @sp+6@0,0xdeadbeef,r1
0x00000058 21@MUL_IC+0@8fbe     @OC@.f   @sp+6@0,r1,0xdeadbeef
0x00000060 26@MUL_IC+0@ff80     @OC@.f   @sp+6@r0,0xdeadbeef,0xdeadbeef
0x00000068 26@MUL_IC+0@ffbe     @OC@.f   @sp+6@0,0xdeadbeef,0xdeadbeef
0x00000070 21@MUL_IC+1@0040     @OC@     @sp+6@r0,r1,1
0x00000074 21@MUL_IC+1@007e     @OC@     @sp+6@0,r1,1
0x00000078 26@MUL_IC+1@7040     @OC@     @sp+6@r0,0xdeadbeef,1
0x00000080 26@MUL_IC+1@707e     @OC@     @sp+6@0,0xdeadbeef,1
0x00000088 21@MUL_IC+1@8040     @OC@.f   @sp+6@r0,r1,1
0x0000008c 21@MUL_IC+1@807e     @OC@.f   @sp+6@0,r1,1
0x00000090 26@MUL_IC+1@f040     @OC@.f   @sp+6@r0,0xdeadbeef,1
0x00000098 26@MUL_IC+1@f07e     @OC@.f   @sp+6@0,0xdeadbeef,1
0x000000a0 20@MUL_IC+2@0fff     @OC@     @sp+6@r0,r0,-1
0x000000a4 26@MUL_IC+2@7fff     @OC@     @sp+6@0,0xdeadbeef,-1
0x000000ac 20@MUL_IC+2@8fff     @OC@.f   @sp+6@r0,r0,-1
0x000000b0 26@MUL_IC+2@ffff     @OC@.f   @sp+6@0,0xdeadbeef,-1
0x000000b8 21@MUL_IC+3@0081     @OC@.z   @sp+6@r1,r1,r2
0x000000bc 26@MUL_IC+3@7041     @OC@.z   @sp+6@0,0xdeadbeef,r1
0x000000c4 21@MUL_IC+3@0f81     @OC@.z   @sp+6@r1,r1,0xdeadbeef
0x000000cc 26@MUL_IC+3@7f81     @OC@.z   @sp+6@0,0xdeadbeef,0xdeadbeef
0x000000d4 21@MUL_IC+3@8081     @OC@.z.f @sp+6@r1,r1,r2
0x000000d8 26@MUL_IC+3@f041     @OC@.z.f @sp+6@0,0xdeadbeef,r1
0x000000e0 21@MUL_IC+3@8f81     @OC@.z.f @sp+6@r1,r1,0xdeadbeef
0x000000e8 26@MUL_IC+3@ff81     @OC@.z.f @sp+6@0,0xdeadbeef,0xdeadbeef
0x000000f0 21@MUL_IC+3@00a1     @OC@.z   @sp+6@r1,r1,2
0x000000f4 26@MUL_IC+3@70a1     @OC@.z   @sp+6@0,0xdeadbeef,2
0x000000fc 21@MUL_IC+3@80a1     @OC@.z.f @sp+6@r1,r1,2
0x00000100 26@MUL_IC+3@f0a1     @OC@.z.f @sp+6@0,0xdeadbeef,2
