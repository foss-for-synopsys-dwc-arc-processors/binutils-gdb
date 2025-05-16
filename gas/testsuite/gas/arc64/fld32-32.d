#as: -mcpu=hs5x
#source: fld32-32.s
#objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format elf32-.*arc64

Disassembly of section .text:
0x[0-9a-f]+ 6900 0100[ 	]+fld32[ 	]+f4,\[r1,0\]
0x[0-9a-f]+ 6e00 7100 0000 1338[ 	]+fld32[ 	]+f4,\[0x1338\]
0x[0-9a-f]+ 6e00 7180 7fff ffff[ 	]+fld32[ 	]+f6,\[0x7fffffff\]
0x[0-9a-f]+ 6e00 7200 ffff fc00[ 	]+fld32[ 	]+f8,\[0xfffffc00\]
0x[0-9a-f]+ 69ff 0000[ 	]+fld32[ 	]+f0,\[r1,255\]
0x[0-9a-f]+ 6c00 8080[ 	]+fld32[ 	]+f2,\[r4,-256\]
0x[0-9a-f]+ 6a14 8280[ 	]+fld32[ 	]+f10,\[r2,-236\]
0x[0-9a-f]+ 697f 0300[ 	]+fld32[ 	]+f12,\[r1,127\]
0x[0-9a-f]+ 6900 0008[ 	]+fld32.aw[ 	]+f0,\[r1,0\]
0x[0-9a-f]+ 6bff 0088[ 	]+fld32.aw[ 	]+f2,\[r3,255\]
0x[0-9a-f]+ 6d00 8108[ 	]+fld32.aw[ 	]+f4,\[r5,-256\]
0x[0-9a-f]+ 6f00 0188[ 	]+fld32.aw[ 	]+f6,\[r7,0\]
0x[0-9a-f]+ 6900 0008[ 	]+fld32.aw[ 	]+f0,\[r1,0\]
0x[0-9a-f]+ 6bff 0088[ 	]+fld32.aw[ 	]+f2,\[r3,255\]
0x[0-9a-f]+ 6d00 8108[ 	]+fld32.aw[ 	]+f4,\[r5,-256\]
0x[0-9a-f]+ 6f00 0188[ 	]+fld32.aw[ 	]+f6,\[r7,0\]
0x[0-9a-f]+ 6900 0010[ 	]+fld32.ab[ 	]+f0,\[r1,0\]
0x[0-9a-f]+ 6b9c 8090[ 	]+fld32.ab[ 	]+f2,\[r3,-100\]
0x[0-9a-f]+ 6dff 0110[ 	]+fld32.ab[ 	]+f4,\[r5,255\]
0x[0-9a-f]+ 6900 0018[ 	]+fld32.as[ 	]+f0,\[r1,0\]
0x[0-9a-f]+ 6bff 0098[ 	]+fld32.as[ 	]+f2,\[r3,255\]
0x[0-9a-f]+ 6d00 8118[ 	]+fld32.as[ 	]+f4,\[r5,-256\]
0x[0-9a-f]+ 6fff 0198[ 	]+fld32.as[ 	]+f6,\[r7,255\]

