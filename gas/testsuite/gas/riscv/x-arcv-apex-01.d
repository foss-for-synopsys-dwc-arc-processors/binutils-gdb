#source x-arcv-apex-01.s
#objdump: -d

.*:[ 	]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+00c5c50b[ 	]+foo0[ 	]+a0,a1,a2
[ 	]+[0-9a-f]+:[ 	]+02c5800b[ 	]+foo1[ 	]+a1,a2
[ 	]+[0-9a-f]+:[ 	]+0205c00b[ 	]+foo2[ 	]+a1
[ 	]+[0-9a-f]+:[ 	]+0400000b[ 	]+foo3
[ 	]+[0-9a-f]+:[ 	]+0b15b50b[ 	]+foo4[ 	]+a0,a1,(0xb|11)
[ 	]+[0-9a-f]+:[ 	]+0b15d00b[ 	]+foo5[ 	]+a1,(0xb|11)
[ 	]+[0-9a-f]+:[ 	]+0163a50b[ 	]+foo6[ 	]+a0,(0x16|22)
[ 	]+[0-9a-f]+:[ 	]+0164200b[ 	]+foo7[ 	]+(0x16|22)
[ 	]+[0-9a-f]+:[ 	]+0214e50b[ 	]+foo8[ 	]+a0,a0,(0x21|33)

