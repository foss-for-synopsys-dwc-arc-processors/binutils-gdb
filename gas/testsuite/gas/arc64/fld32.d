#as: -mcpu=hs5x
#source: fld32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ 6900 0100\s{2,}\tfld32\tf4,\[r1,0\]
0x[0-9a-f]+ 6e00 7100 0000 1338\s\tfld32\tf4,\[0x1338\]
0x[0-9a-f]+ 6e00 7180 7fff ffff\s\tfld32\tf6,\[0x7fffffff\]
0x[0-9a-f]+ 6e00 7200 ffff fc00\s\tfld32\tf8,\[0xfffffc00\]
0x[0-9a-f]+ 69ff 0000\s{2,}\tfld32\tf0,\[r1,255\]
0x[0-9a-f]+ 6c00 8080\s{2,}\tfld32\tf2,\[r4,-256\]
0x[0-9a-f]+ 6a14 8280\s{2,}\tfld32\tf10,\[r2,-236\]
0x[0-9a-f]+ 697f 0300\s{2,}\tfld32\tf12,\[r1,127\]
0x[0-9a-f]+ 6900 0008\s{2,}\tfld32.aw\tf0,\[r1,0\]
0x[0-9a-f]+ 6bff 0088\s{2,}\tfld32.aw\tf2,\[r3,255\]
0x[0-9a-f]+ 6d00 8108\s{2,}\tfld32.aw\tf4,\[r5,-256\]
0x[0-9a-f]+ 6f00 0188\s{2,}\tfld32.aw\tf6,\[r7,0\]
0x[0-9a-f]+ 6900 0008\s{2,}\tfld32.aw\tf0,\[r1,0\]
0x[0-9a-f]+ 6bff 0088\s{2,}\tfld32.aw\tf2,\[r3,255\]
0x[0-9a-f]+ 6d00 8108\s{2,}\tfld32.aw\tf4,\[r5,-256\]
0x[0-9a-f]+ 6f00 0188\s{2,}\tfld32.aw\tf6,\[r7,0\]
0x[0-9a-f]+ 6900 0010\s{2,}\tfld32.ab\tf0,\[r1,0\]
0x[0-9a-f]+ 6b9c 8090\s{2,}\tfld32.ab\tf2,\[r3,-100\]
0x[0-9a-f]+ 6dff 0110\s{2,}\tfld32.ab\tf4,\[r5,255\]
0x[0-9a-f]+ 6900 0018\s{2,}\tfld32.as\tf0,\[r1,0\]
0x[0-9a-f]+ 6bff 0098\s{2,}\tfld32.as\tf2,\[r3,255\]
0x[0-9a-f]+ 6d00 8118\s{2,}\tfld32.as\tf4,\[r5,-256\]
0x[0-9a-f]+ 6fff 0198\s{2,}\tfld32.as\tf6,\[r7,255\]

