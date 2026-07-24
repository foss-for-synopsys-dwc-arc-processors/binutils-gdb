#name: RISC-V decompress RVC instructions to satisfy alignment
#source: relax-align-decompress.s
#as: -march=rv64ic -mrelax
#ld: -m[riscv_choose_lp64_emul] --relax --relax-align-decompress
#objdump: -d -Mno-aliases

.*:[ 	]+file format .*


Disassembly of section \.text:

0+[0-9a-f]+ <_start>:
.*:[ 	]+00100513[ 	]+addi[ 	]+a0,zero,1
.*:[ 	]+00200593[ 	]+addi[ 	]+a1,zero,2

0+[0-9a-f]+ <aligned>:
.*:[ 	]+[0-9a-f]+[ 	]+add[ 	]+a2,a0,a1
.*:[ 	]+[0-9a-f]+[ 	]+c\.beqz[ 	]+a0,[0-9a-f]+ <tail>
.*:[ 	]+0001[ 	]+c\.addi[ 	]+zero,0

0+[0-9a-f]+ <tail>:
.*:[ 	]+8082[ 	]+c\.jr[ 	]+ra
