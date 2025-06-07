#as: -march=rv32i_xarcvbitrev
#objdump: -d

.*:[    ]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+01fe22db[ 	]+arcv.bitrev[ 	]+t0,t3,t6
[ 	]+[0-9a-f]+:[ 	]+005fae5b[ 	]+arcv.bitrev[ 	]+t3,t6,t0
[ 	]+[0-9a-f]+:[ 	]+01c2afdb[ 	]+arcv.bitrev[ 	]+t6,t0,t3
