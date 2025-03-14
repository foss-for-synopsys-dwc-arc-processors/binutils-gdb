#as: -march=rv32i_xarcvudsp
#objdump: -d

.*:[ 	]+file format .*


Disassembly of section .text:

0+[0-9a-f]+ <.text>:
[ 	]+[0-9a-f]+:[ 	]+01fe22d7[ 	]+arcv.xvadd.vv[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+005fae57[ 	]+arcv.xvadd.vv[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+01c2afd7[ 	]+arcv.xvadd.vv[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+09fe22d7[ 	]+arcv.xvsub.vv[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+085fae57[ 	]+arcv.xvsub.vv[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+09c2afd7[ 	]+arcv.xvsub.vv[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+85fe22d7[ 	]+arcv.xvsadd.vv[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+845fae57[ 	]+arcv.xvsadd.vv[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+85c2afd7[ 	]+arcv.xvsadd.vv[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+85fe42d7[ 	]+arcv.xvsadd.vv[ 	]+t0,t3,t6,e32,m1
[ 	]+[0-9a-f]+:[ 	]+845fce57[ 	]+arcv.xvsadd.vv[ 	]+t3,t6,t0,e32,m1
[ 	]+[0-9a-f]+:[ 	]+85c2cfd7[ 	]+arcv.xvsadd.vv[ 	]+t6,t0,t3,e32,m1
[ 	]+[0-9a-f]+:[ 	]+8dfe22d7[ 	]+arcv.xvssub.vv[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+8c5fae57[ 	]+arcv.xvssub.vv[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+8dc2afd7[ 	]+arcv.xvssub.vv[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+8dfe42d7[ 	]+arcv.xvssub.vv[ 	]+t0,t3,t6,e32,m1
[ 	]+[0-9a-f]+:[ 	]+8c5fce57[ 	]+arcv.xvssub.vv[ 	]+t3,t6,t0,e32,m1
[ 	]+[0-9a-f]+:[ 	]+8dc2cfd7[ 	]+arcv.xvssub.vv[ 	]+t6,t0,t3,e32,m1
[ 	]+[0-9a-f]+:[ 	]+97fe22d7[ 	]+arcv.xvsll.vx[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+965fae57[ 	]+arcv.xvsll.vx[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+97c2afd7[ 	]+arcv.xvsll.vx[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+a7fe22d7[ 	]+arcv.xvsra.vx[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+a65fae57[ 	]+arcv.xvsra.vx[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+a7c2afd7[ 	]+arcv.xvsra.vx[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+bffe22d7[ 	]+arcv.xvnclip.wx[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+be5fae57[ 	]+arcv.xvnclip.wx[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+bfc2afd7[ 	]+arcv.xvnclip.wx[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+bffe12d7[ 	]+arcv.xvnclip.wx[ 	]+t0,t3,t6,e16,mf2
[ 	]+[0-9a-f]+:[ 	]+be5f9e57[ 	]+arcv.xvnclip.wx[ 	]+t3,t6,t0,e16,mf2
[ 	]+[0-9a-f]+:[ 	]+bfc29fd7[ 	]+arcv.xvnclip.wx[ 	]+t6,t0,t3,e16,mf2
[ 	]+[0-9a-f]+:[ 	]+edfe22d7[ 	]+arcv.xvwmul.vv[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+ec5fae57[ 	]+arcv.xvwmul.vv[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+edc2afd7[ 	]+arcv.xvwmul.vv[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+edfe12d7[ 	]+arcv.xvwmul.vv[ 	]+t0,t3,t6,e16,mf2
[ 	]+[0-9a-f]+:[ 	]+ec5f9e57[ 	]+arcv.xvwmul.vv[ 	]+t3,t6,t0,e16,mf2
[ 	]+[0-9a-f]+:[ 	]+edc29fd7[ 	]+arcv.xvwmul.vv[ 	]+t6,t0,t3,e16,mf2
[ 	]+[0-9a-f]+:[ 	]+95fe22db[ 	]+arcv.xvwsrdot.vv[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+945fae5b[ 	]+arcv.xvwsrdot.vv[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+95c2afdb[ 	]+arcv.xvwsrdot.vv[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+21fe22db[ 	]+arcv.xvscmul.vv[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+205fae5b[ 	]+arcv.xvscmul.vv[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+21c2afdb[ 	]+arcv.xvscmul.vv[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+31fe22db[ 	]+arcv.xvscjmul.vv[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+305fae5b[ 	]+arcv.xvscjmul.vv[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+31c2afdb[ 	]+arcv.xvscjmul.vv[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+25fe22db[ 	]+arcv.xvwscmul.vv[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+245fae5b[ 	]+arcv.xvwscmul.vv[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+25c2afdb[ 	]+arcv.xvwscmul.vv[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+35fe22db[ 	]+arcv.xvwscjmul.vv[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+345fae5b[ 	]+arcv.xvwscjmul.vv[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+35c2afdb[ 	]+arcv.xvwscjmul.vv[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+65fe22db[ 	]+arcv.xvwscrdot.vv[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+645fae5b[ 	]+arcv.xvwscrdot.vv[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+65c2afdb[ 	]+arcv.xvwscrdot.vv[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+75fe22db[ 	]+arcv.xvwscjrdot.vv[ 	]+t0,t3,t6,e16,m1
[ 	]+[0-9a-f]+:[ 	]+745fae5b[ 	]+arcv.xvwscjrdot.vv[ 	]+t3,t6,t0,e16,m1
[ 	]+[0-9a-f]+:[ 	]+75c2afdb[ 	]+arcv.xvwscjrdot.vv[ 	]+t6,t0,t3,e16,m1
[ 	]+[0-9a-f]+:[ 	]+01fe22db[ 	]+arcv.bitrev[ 	]+t0,t3,t6
[ 	]+[0-9a-f]+:[ 	]+005fae5b[ 	]+arcv.bitrev[ 	]+t3,t6,t0
[ 	]+[0-9a-f]+:[ 	]+01c2afdb[ 	]+arcv.bitrev[ 	]+t6,t0,t3
