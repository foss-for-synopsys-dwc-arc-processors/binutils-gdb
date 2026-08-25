#as: -march=rv32if_xmipstrig
#objdump: -dr

.*:[   ]+file format .*


Disassembly of section .text:

0+000 <.text>:
[ 	]+[0-9a-f]+:[ 	]+e000800b[ 	]+mips.fsinhz.s[ 	]+ft0,ft1
[ 	]+[0-9a-f]+:[ 	]+e011810b[ 	]+mips.fcoshz.s[ 	]+ft2,ft3
[ 	]+[0-9a-f]+:[ 	]+e022820b[ 	]+mips.ftanhz.s[ 	]+ft4,ft5
[ 	]+[0-9a-f]+:[ 	]+e033830b[ 	]+mips.fversinhz.s[ 	]+ft6,ft7
[ 	]+[0-9a-f]+:[ 	]+e06e8e0b[ 	]+mips.fatanhz.s[ 	]+ft8,ft9
[ 	]+[0-9a-f]+:[ 	]+e070050b[ 	]+mips.flti.s[ 	]+fa0,0
[ 	]+[0-9a-f]+:[ 	]+e07f858b[ 	]+mips.flti.s[ 	]+fa1,31
[ 	]+[0-9a-f]+:[ 	]+e124840b[ 	]+mips.fftanh.s[ 	]+fs0,fs1
[ 	]+[0-9a-f]+:[ 	]+e189890b[ 	]+mips.fflog2.s[ 	]+fs2,fs3
[ 	]+[0-9a-f]+:[ 	]+e19a8a0b[ 	]+mips.ffexp2.s[ 	]+fs4,fs5
[ 	]+[0-9a-f]+:[ 	]+e1bb8b0b[ 	]+mips.ffrecip.s[ 	]+fs6,fs7
[ 	]+[0-9a-f]+:[ 	]+e1cc8c0b[ 	]+mips.ffsqrt.s[ 	]+fs8,fs9
[ 	]+[0-9a-f]+:[ 	]+e1dd8d0b[ 	]+mips.ffrsqrt.s[ 	]+fs10,fs11
