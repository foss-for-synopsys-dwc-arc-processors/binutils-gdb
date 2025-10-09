#as: -march=rv32i_xarcvmxmc
#objdump: -d

.*:[    ]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+0a61a05b[ 	]+arcv.vqmxm8.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+0a0321db[ 	]+arcv.vqmxm8.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0a30235b[ 	]+arcv.vqmxm8.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+0a61e05b[ 	]+arcv.vqmxm8u.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+0a0361db[ 	]+arcv.vqmxm8u.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0a30635b[ 	]+arcv.vqmxm8u.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+0a61905b[ 	]+arcv.vqmxm8su.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+0a0311db[ 	]+arcv.vqmxm8su.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0a30135b[ 	]+arcv.vqmxm8su.vv[ 	]+v6,v0,v3
