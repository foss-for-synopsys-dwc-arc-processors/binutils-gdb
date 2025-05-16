#as: -mcpu=hs5x
#source: fst32-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ 6900 0101[ 	]+fst32[ 	]+f4,\[r1,0\]
0x[0-9a-f]+ 6e00 7101 0000 1338[ 	]+fst32[ 	]+f4,\[0x1338\]
0x[0-9a-f]+ 6e00 7181 7fff ffff[ 	]+fst32[ 	]+f6,\[0x7fffffff\]
0x[0-9a-f]+ 6e00 7201 ffff fc00[ 	]+fst32[ 	]+f8,\[0xfffffc00\]
0x[0-9a-f]+ 69ff 0001[ 	]+fst32[ 	]+f0,\[r1,255\]
0x[0-9a-f]+ 6c00 8081[ 	]+fst32[ 	]+f2,\[r4,-256\]
0x[0-9a-f]+ 6a14 8281[ 	]+fst32[ 	]+f10,\[r2,-236\]
0x[0-9a-f]+ 697f 0301[ 	]+fst32[ 	]+f12,\[r1,127\]
0x[0-9a-f]+ 69ff 0009[ 	]+fst32.aw[ 	]+f0,\[r1,255\]
0x[0-9a-f]+ 6b00 8089[ 	]+fst32.aw[ 	]+f2,\[r3,-256\]
0x[0-9a-f]+ 6d00 0109[ 	]+fst32.aw[ 	]+f4,\[r5,0\]
0x[0-9a-f]+ 69ff 0009[ 	]+fst32.aw[ 	]+f0,\[r1,255\]
0x[0-9a-f]+ 6b00 8089[ 	]+fst32.aw[ 	]+f2,\[r3,-256\]
0x[0-9a-f]+ 6d00 0109[ 	]+fst32.aw[ 	]+f4,\[r5,0\]
0x[0-9a-f]+ 699c 8011[ 	]+fst32.ab[ 	]+f0,\[r1,-100\]
0x[0-9a-f]+ 6bff 0091[ 	]+fst32.ab[ 	]+f2,\[r3,255\]
0x[0-9a-f]+ 69ff 0019[ 	]+fst32.as[ 	]+f0,\[r1,255\]
0x[0-9a-f]+ 6b00 8099[ 	]+fst32.as[ 	]+f2,\[r3,-256\]
0x[0-9a-f]+ 6dff 0119[ 	]+fst32.as[ 	]+f4,\[r5,255\]
