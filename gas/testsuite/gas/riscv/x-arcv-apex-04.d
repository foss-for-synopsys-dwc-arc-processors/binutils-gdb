#source x-arcv-apex-04.s
#objdump: -d

.*:[ 	]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+8005b50b[ 	]+foo0[ 	]a0,a1,(-0x80|-128)
[ 	]+[0-9a-f]+:[ 	]+7f05b50b[ 	]+foo0[ 	]a0,a1,(0x7f|127)
[ 	]+[0-9a-f]+:[ 	]+8000a50b[ 	]+foo1[ 	]a0,(-0x800|-2048)
[ 	]+[0-9a-f]+:[ 	]+7ff0a50b[ 	]+foo1[ 	]a0,(0x7ff|2047)
[ 	]+[0-9a-f]+:[ 	]+8000e50b[ 	]+foo2[ 	]a0,a0,(-0x800|-2048)
[ 	]+[0-9a-f]+:[ 	]+7ff0e50b[ 	]+foo2[ 	]a0,a0,(0x7ff|2047)

