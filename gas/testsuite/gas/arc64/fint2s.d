#as: -mcpu=hs5x
#source: fint2s.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ e0e0 0022\s{2,}fint2s\tf0,r0
0x[0-9a-f]+ e1e0 0062\s{2,}fint2s\tf1,r1
0x[0-9a-f]+ e2e0 00a2\s{2,}fint2s\tf2,r2
0x[0-9a-f]+ e3e0 00e2\s{2,}fint2s\tf3,r3
0x[0-9a-f]+ e4e0 0122\s{2,}fint2s\tf4,r4
0x[0-9a-f]+ e5e0 0162\s{2,}fint2s\tf5,r5
0x[0-9a-f]+ e6e0 01a2\s{2,}fint2s\tf6,r6
0x[0-9a-f]+ e7e0 01e2\s{2,}fint2s\tf7,r7
0x[0-9a-f]+ e0e0 1222\s{2,}fint2s\tf8,r8
0x[0-9a-f]+ e1e0 1262\s{2,}fint2s\tf9,r9
0x[0-9a-f]+ e2e0 12a2\s{2,}fint2s\tf10,r10
0x[0-9a-f]+ e3e0 12e2\s{2,}fint2s\tf11,r11
0x[0-9a-f]+ e4e0 1322\s{2,}fint2s\tf12,r12
0x[0-9a-f]+ e5e0 1362\s{2,}fint2s\tf13,r13
0x[0-9a-f]+ e6e0 13a2\s{2,}fint2s\tf14,r14
0x[0-9a-f]+ e7e0 13e2\s{2,}fint2s\tf15,r15
0x[0-9a-f]+ e0e0 2422\s{2,}fint2s\tf16,r16
0x[0-9a-f]+ e1e0 2462\s{2,}fint2s\tf17,r17
0x[0-9a-f]+ e2e0 24a2\s{2,}fint2s\tf18,r18
0x[0-9a-f]+ e3e0 24e2\s{2,}fint2s\tf19,r19
0x[0-9a-f]+ e4e0 2522\s{2,}fint2s\tf20,r20
0x[0-9a-f]+ e5e0 2562\s{2,}fint2s\tf21,r21
0x[0-9a-f]+ e6e0 25a2\s{2,}fint2s\tf22,r22
0x[0-9a-f]+ e7e0 25e2\s{2,}fint2s\tf23,r23
0x[0-9a-f]+ e0e0 3622\s{2,}fint2s\tf24,r24
0x[0-9a-f]+ e1e0 3662\s{2,}fint2s\tf25,r25
0x[0-9a-f]+ e2e0 36a2\s{2,}fint2s\tf26,r26
0x[0-9a-f]+ e3e0 36e2\s{2,}fint2s\tf27,fp
0x[0-9a-f]+ e4e0 3722\s{2,}fint2s\tf28,sp
0x[0-9a-f]+ e5e0 3762\s{2,}fint2s\tf29,ilink
0x[0-9a-f]+ e6e0 37a2\s{2,}fint2s\tf30,r30
0x[0-9a-f]+ e7e0 37e2\s{2,}fint2s\tf31,blink

