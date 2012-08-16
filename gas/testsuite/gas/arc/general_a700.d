#as: -mARC700
#objdump: -dr  --prefix-addresses
#name: general_a700

# Test the @OC@ insn.

.*: +file format elf32-.*arc

Disassembly of section .text:
0x00000000 236f003f     sync       
0x00000004 242f003f     rtie       
0x00000008 256f003f     brk        
0x0000000c 216f003f     sleep      
0x00000010         0000783e     trap_s     1
0x00000012 226f003f     swi        
0x00000016 216f003f     sleep      
0x0000001a 216f003f     sleep      
0x0000001e 216f007f     sleep      1
0x00000022 216f00bf     sleep      2
0x00000026 216f00ff     sleep      3
0x0000002a 216f013f     sleep      4
0x0000002e         000079e0     unimp_s    
0x00000030 202f004c     ex         r0,\[r1\]
0x00000034 202f804c     ex.di      r0,\[r1\]
0x00000038 202f0f8c     ex         r0,\[0xdeadbeef\]
0x00000040 202f8f8c     ex.di      r0,\[0xdeadbeef\]



