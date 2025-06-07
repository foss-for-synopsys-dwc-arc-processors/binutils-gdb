#as: -march=rv32i_xarcvmxmc
#objdump: -d

.*:[    ]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+0a33205b[ 	]+arcv.vqmxm8.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+0a6021db[ 	]+arcv.vqmxm8.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0a01a35b[ 	]+arcv.vqmxm8.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+0a33605b[ 	]+arcv.vqmxm8u.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+0a6061db[ 	]+arcv.vqmxm8u.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0a01e35b[ 	]+arcv.vqmxm8u.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+0a33105b[ 	]+arcv.vqmxm8su.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+0a6011db[ 	]+arcv.vqmxm8su.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0a01935b[ 	]+arcv.vqmxm8su.vv[ 	]+v6,v0,v3
