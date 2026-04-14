#source: x-arcv-apex-02.s
#objdump: -d

.*:[ 	]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+0020e50b[ 	]+foo[ 	]+a0,a0,(0x2|2)
[ 	]+[0-9a-f]+:[ 	]+0205b50b[ 	]+foo[ 	]+a0,a1,(0x2|2)
[ 	]+[0-9a-f]+:[ 	]+1000e50b[ 	]+foo[ 	]+a0,a0,(0x100|256)
[ 	]+[0-9a-f]+:[ 	]+0ff0e50b[ 	]+foo[ 	]+a0,a0,(0xff|255)
