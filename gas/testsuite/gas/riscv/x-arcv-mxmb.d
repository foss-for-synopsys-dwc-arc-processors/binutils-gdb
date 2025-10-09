#as: -march=rv32i_xarcvmxmb
#objdump: -d

.*:[    ]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+0661a05b[ 	]+arcv.vqmxm4.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+060321db[ 	]+arcv.vqmxm4.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0630235b[ 	]+arcv.vqmxm4.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+0661e05b[ 	]+arcv.vqmxm4u.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+060361db[ 	]+arcv.vqmxm4u.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0630635b[ 	]+arcv.vqmxm4u.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+0661905b[ 	]+arcv.vqmxm4su.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+060311db[ 	]+arcv.vqmxm4su.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0630135b[ 	]+arcv.vqmxm4su.vv[ 	]+v6,v0,v3
