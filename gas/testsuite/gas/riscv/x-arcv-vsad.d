#as: -march=rv32i_xarcvvsad
#objdump: -d

.*:[    ]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+c261a05b[ 	]+arcv.vwsad.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+c20321db[ 	]+arcv.vwsad.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+c230235b[ 	]+arcv.vwsad.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+c261e05b[ 	]+arcv.vwsadu.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+c20361db[ 	]+arcv.vwsadu.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+c230635b[ 	]+arcv.vwsadu.vv[ 	]+v6,v0,v3
