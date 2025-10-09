#as: -march=rv32i_xarcvmxmd
#objdump: -d

.*:[    ]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+0e61a05b[ 	]+arcv.vqmxm16.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+0e0321db[ 	]+arcv.vqmxm16.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0e30235b[ 	]+arcv.vqmxm16.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+0e61e05b[ 	]+arcv.vqmxm16u.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+0e0361db[ 	]+arcv.vqmxm16u.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0e30635b[ 	]+arcv.vqmxm16u.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+0e61905b[ 	]+arcv.vqmxm16su.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+0e0311db[ 	]+arcv.vqmxm16su.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+0e30135b[ 	]+arcv.vqmxm16su.vv[ 	]+v6,v0,v3
