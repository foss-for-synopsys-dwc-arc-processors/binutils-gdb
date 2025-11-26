#as: -march=rv32i_xarcvbitstream
#objdump: -d

.*:[    ]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+484e12db[ 	]+arcv.bspeek[ 	]+t0,t3
[ 	]+[0-9a-f]+:[ 	]+484f9e5b[ 	]+arcv.bspeek[ 	]+t3,t6
[ 	]+[0-9a-f]+:[ 	]+485e12db[ 	]+arcv.bspop[ 	]+t0,t3
[ 	]+[0-9a-f]+:[ 	]+485f9e5b[ 	]+arcv.bspop[ 	]+t3,t6
[ 	]+[0-9a-f]+:[ 	]+01fe12db[ 	]+arcv.bspush[ 	]+t0,t3,t6
[ 	]+[0-9a-f]+:[ 	]+005f9e5b[ 	]+arcv.bspush[ 	]+t3,t6,t0
[ 	]+[0-9a-f]+:[ 	]+01c29fdb[ 	]+arcv.bspush[ 	]+t6,t0,t3
