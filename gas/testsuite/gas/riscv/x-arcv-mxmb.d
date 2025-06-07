#as: -march=rv32i_xarcvmxmb
#objdump: -d

.*:[    ]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+0633205b[ 	]+arcv.vqmxm4.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+066021db[ 	]+arcv.vqmxm4.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0601a35b[ 	]+arcv.vqmxm4.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+0633605b[ 	]+arcv.vqmxm4u.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+066061db[ 	]+arcv.vqmxm4u.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0601e35b[ 	]+arcv.vqmxm4u.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+0633105b[ 	]+arcv.vqmxm4su.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+066011db[ 	]+arcv.vqmxm4su.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0601935b[ 	]+arcv.vqmxm4su.vv[ 	]+v6,v0,v3
