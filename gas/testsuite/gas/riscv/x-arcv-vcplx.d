#as: -march=rv32i_xarcvvcplx
#objdump: -d

.*:[    ]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+4a34205b[ 	]+arcv.vconj.v[ 	]+v0,v3
[ 	]+[0-9a-f]+:[ 	]+4a6421db[ 	]+arcv.vconj.v[ 	]+v3,v6
[ 	]+[0-9a-f]+:[ 	]+4a35205b[ 	]+arcv.vcmuli.v[ 	]+v0,v3
[ 	]+[0-9a-f]+:[ 	]+4a6521db[ 	]+arcv.vcmuli.v[ 	]+v3,v6
[ 	]+[0-9a-f]+:[ 	]+4a35a05b[ 	]+arcv.vcmulni.v[ 	]+v0,v3
[ 	]+[0-9a-f]+:[ 	]+4a65a1db[ 	]+arcv.vcmulni.v[ 	]+v3,v6
[ 	]+[0-9a-f]+:[ 	]+4a36205b[ 	]+arcv.veven.v[ 	]+v0,v3
[ 	]+[0-9a-f]+:[ 	]+4a6621db[ 	]+arcv.veven.v[ 	]+v3,v6
[ 	]+[0-9a-f]+:[ 	]+4a36a05b[ 	]+arcv.vodd.v[ 	]+v0,v3
[ 	]+[0-9a-f]+:[ 	]+4a66a1db[ 	]+arcv.vodd.v[ 	]+v3,v6
[ 	]+[0-9a-f]+:[ 	]+c233105b[ 	]+arcv.vinterleave.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+c26011db[ 	]+arcv.vinterleave.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+c201935b[ 	]+arcv.vinterleave.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+f233105b[ 	]+arcv.vscredsum.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+f26011db[ 	]+arcv.vscredsum.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+f201935b[ 	]+arcv.vscredsum.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+f233605b[ 	]+arcv.vwcredsum.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+f26061db[ 	]+arcv.vwcredsum.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+f201e35b[ 	]+arcv.vwcredsum.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+2233205b[ 	]+arcv.vscmul.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+226021db[ 	]+arcv.vscmul.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+2201a35b[ 	]+arcv.vscmul.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+223fe05b[ 	]+arcv.vscmul.vx[ 	]+v0,v3,t6
[ 	]+[0-9a-f]+:[ 	]+2262e1db[ 	]+arcv.vscmul.vx[ 	]+v3,v6,t0
[ 	]+[0-9a-f]+:[ 	]+220e635b[ 	]+arcv.vscmul.vx[ 	]+v6,v0,t3
[ 	]+[0-9a-f]+:[ 	]+3233205b[ 	]+arcv.vscjmul.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+326021db[ 	]+arcv.vscjmul.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+3201a35b[ 	]+arcv.vscjmul.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+323fe05b[ 	]+arcv.vscjmul.vx[ 	]+v0,v3,t6
[ 	]+[0-9a-f]+:[ 	]+3262e1db[ 	]+arcv.vscjmul.vx[ 	]+v3,v6,t0
[ 	]+[0-9a-f]+:[ 	]+320e635b[ 	]+arcv.vscjmul.vx[ 	]+v6,v0,t3
[ 	]+[0-9a-f]+:[ 	]+2633205b[ 	]+arcv.vwscmul.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+266021db[ 	]+arcv.vwscmul.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+2601a35b[ 	]+arcv.vwscmul.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+263fe05b[ 	]+arcv.vwscmul.vx[ 	]+v0,v3,t6
[ 	]+[0-9a-f]+:[ 	]+2662e1db[ 	]+arcv.vwscmul.vx[ 	]+v3,v6,t0
[ 	]+[0-9a-f]+:[ 	]+260e635b[ 	]+arcv.vwscmul.vx[ 	]+v6,v0,t3
[ 	]+[0-9a-f]+:[ 	]+3633205b[ 	]+arcv.vwscjmul.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+366021db[ 	]+arcv.vwscjmul.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+3601a35b[ 	]+arcv.vwscjmul.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+363fe05b[ 	]+arcv.vwscjmul.vx[ 	]+v0,v3,t6
[ 	]+[0-9a-f]+:[ 	]+3662e1db[ 	]+arcv.vwscjmul.vx[ 	]+v3,v6,t0
[ 	]+[0-9a-f]+:[ 	]+360e635b[ 	]+arcv.vwscjmul.vx[ 	]+v6,v0,t3
[ 	]+[0-9a-f]+:[ 	]+2e61a05b[ 	]+arcv.vwscmac.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+2e0321db[ 	]+arcv.vwscmac.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+2e30235b[ 	]+arcv.vwscmac.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+2e6e605b[ 	]+arcv.vwscmac.vx[ 	]+v0,t3,v6
[ 	]+[0-9a-f]+:[ 	]+2e0fe1db[ 	]+arcv.vwscmac.vx[ 	]+v3,t6,v0
[ 	]+[0-9a-f]+:[ 	]+2e32e35b[ 	]+arcv.vwscmac.vx[ 	]+v6,t0,v3
[ 	]+[0-9a-f]+:[ 	]+2a61a05b[ 	]+arcv.vwscnmsac.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+2a0321db[ 	]+arcv.vwscnmsac.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+2a30235b[ 	]+arcv.vwscnmsac.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+2a6e605b[ 	]+arcv.vwscnmsac.vx[ 	]+v0,t3,v6
[ 	]+[0-9a-f]+:[ 	]+2a0fe1db[ 	]+arcv.vwscnmsac.vx[ 	]+v3,t6,v0
[ 	]+[0-9a-f]+:[ 	]+2a32e35b[ 	]+arcv.vwscnmsac.vx[ 	]+v6,t0,v3
[ 	]+[0-9a-f]+:[ 	]+3e61a05b[ 	]+arcv.vwscjmac.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+3e0321db[ 	]+arcv.vwscjmac.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+3e30235b[ 	]+arcv.vwscjmac.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+3e6e605b[ 	]+arcv.vwscjmac.vx[ 	]+v0,t3,v6
[ 	]+[0-9a-f]+:[ 	]+3e0fe1db[ 	]+arcv.vwscjmac.vx[ 	]+v3,t6,v0
[ 	]+[0-9a-f]+:[ 	]+3e32e35b[ 	]+arcv.vwscjmac.vx[ 	]+v6,t0,v3
[ 	]+[0-9a-f]+:[ 	]+3a61a05b[ 	]+arcv.vwscjnmsac.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+3a0321db[ 	]+arcv.vwscjnmsac.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+3a30235b[ 	]+arcv.vwscjnmsac.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+3a6e605b[ 	]+arcv.vwscjnmsac.vx[ 	]+v0,t3,v6
[ 	]+[0-9a-f]+:[ 	]+3a0fe1db[ 	]+arcv.vwscjnmsac.vx[ 	]+v3,t6,v0
[ 	]+[0-9a-f]+:[ 	]+3a32e35b[ 	]+arcv.vwscjnmsac.vx[ 	]+v6,t0,v3
[ 	]+[0-9a-f]+:[ 	]+6661a05b[ 	]+arcv.vwscrdot.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+660321db[ 	]+arcv.vwscrdot.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+6630235b[ 	]+arcv.vwscrdot.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+7661a05b[ 	]+arcv.vwscjrdot.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+760321db[ 	]+arcv.vwscjrdot.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+7630235b[ 	]+arcv.vwscjrdot.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+6261a05b[ 	]+arcv.vqcrdot.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+620321db[ 	]+arcv.vqcrdot.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+6230235b[ 	]+arcv.vqcrdot.vv[ 	]+v6,v0,v3
[ 	]+[0-9a-f]+:[ 	]+7261a05b[ 	]+arcv.vqcjrdot.vv[ 	]+v0,v3,v6
[ 	]+[0-9a-f]+:[ 	]+720321db[ 	]+arcv.vqcjrdot.vv[ 	]+v3,v6,v0
[ 	]+[0-9a-f]+:[ 	]+7230235b[ 	]+arcv.vqcjrdot.vv[ 	]+v6,v0,v3
