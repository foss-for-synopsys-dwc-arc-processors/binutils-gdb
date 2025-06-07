#as: -march=rv32i_xarcvvsad
#objdump: -d

.*:[    ]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+c233205b[ 	]+arcv.vwsad.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+c26021db[ 	]+arcv.vwsad.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+c201a35b[ 	]+arcv.vwsad.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+c233605b[ 	]+arcv.vwsadu.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+c26061db[ 	]+arcv.vwsadu.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+c201e35b[ 	]+arcv.vwsadu.vv[ 	]+v6,v0,v3
