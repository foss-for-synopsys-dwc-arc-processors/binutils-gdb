#as: -march=rv32i
#source: zc-zca-option-march.s
#objdump: -d -Mno-aliases

.*:[ 	]+file format .*


Disassembly of section .text:

0+000 <testcase>:
[ 	]+0:[ 	]+0001[ 	]+c.addi[ 	]+zero,0
#...
