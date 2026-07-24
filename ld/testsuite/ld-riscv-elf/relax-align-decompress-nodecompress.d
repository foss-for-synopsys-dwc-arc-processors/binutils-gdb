#name: RISC-V alignment NOP fill without --relax-align-decompress
#source: relax-align-decompress.s
#as: -march=rv64ic -mrelax
#ld: -m[riscv_choose_lp64_emul] --relax
#objdump: -d -Mno-aliases

.*:[ 	]+file format .*


Disassembly of section \.text:

0+[0-9a-f]+ <_start>:
.*:[ 	]+4505[ 	]+c\.li[ 	]+a0,1
.*:[ 	]+4589[ 	]+c\.li[ 	]+a1,2
.*:[ 	]+00000013[ 	]+addi[ 	]+zero,zero,0

0+[0-9a-f]+ <aligned>:
.*:[ 	]+[0-9a-f]+[ 	]+add[ 	]+a2,a0,a1
.*:[ 	]+[0-9a-f]+[ 	]+c\.beqz[ 	]+a0,[0-9a-f]+ <tail>
.*:[ 	]+0001[ 	]+c\.addi[ 	]+zero,0

0+[0-9a-f]+ <tail>:
.*:[ 	]+8082[ 	]+c\.jr[ 	]+ra
