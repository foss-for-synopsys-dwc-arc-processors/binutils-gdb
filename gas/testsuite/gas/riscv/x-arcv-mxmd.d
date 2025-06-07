#as: -march=rv32i_xarcvmxmd
#objdump: -d

.*:[    ]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+0e33205b[ 	]+arcv.vqmxm16.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+0e6021db[ 	]+arcv.vqmxm16.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0e01a35b[ 	]+arcv.vqmxm16.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+0e33605b[ 	]+arcv.vqmxm16u.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+0e6061db[ 	]+arcv.vqmxm16u.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0e01e35b[ 	]+arcv.vqmxm16u.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+0e33105b[ 	]+arcv.vqmxm16su.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+0e6011db[ 	]+arcv.vqmxm16su.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0e01935b[ 	]+arcv.vqmxm16su.vv[ 	]+v6,v0,v3
