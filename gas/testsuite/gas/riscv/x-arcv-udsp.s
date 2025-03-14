	arcv.xvadd.vv t0,t3,t6,e16,m1
	arcv.xvadd.vv t3,t6,t0,e16,m1
	arcv.xvadd.vv t6,t0,t3,e16,m1

	arcv.xvsub.vv t0,t3,t6,e16,m1
	arcv.xvsub.vv t3,t6,t0,e16,m1
	arcv.xvsub.vv t6,t0,t3,e16,m1

	arcv.xvsadd.vv t0,t3,t6,e16,m1
	arcv.xvsadd.vv t3,t6,t0,e16,m1
	arcv.xvsadd.vv t6,t0,t3,e16,m1

	arcv.xvsadd.vv t0,t3,t6,e32,m1
	arcv.xvsadd.vv t3,t6,t0,e32,m1
	arcv.xvsadd.vv t6,t0,t3,e32,m1

	arcv.xvssub.vv t0,t3,t6,e16,m1
	arcv.xvssub.vv t3,t6,t0,e16,m1
	arcv.xvssub.vv t6,t0,t3,e16,m1

	arcv.xvssub.vv t0,t3,t6,e32,m1
	arcv.xvssub.vv t3,t6,t0,e32,m1
	arcv.xvssub.vv t6,t0,t3,e32,m1

	arcv.xvsll.vx t0,t3,t6,e16,m1
	arcv.xvsll.vx t3,t6,t0,e16,m1
	arcv.xvsll.vx t6,t0,t3,e16,m1

	arcv.xvsra.vx t0,t3,t6,e16,m1
	arcv.xvsra.vx t3,t6,t0,e16,m1
	arcv.xvsra.vx t6,t0,t3,e16,m1

	arcv.xvnclip.wx t0,t3,t6,e16,m1
	arcv.xvnclip.wx t3,t6,t0,e16,m1
	arcv.xvnclip.wx t6,t0,t3,e16,m1

	arcv.xvnclip.wx t0,t3,t6,e16,mf2
	arcv.xvnclip.wx t3,t6,t0,e16,mf2
	arcv.xvnclip.wx t6,t0,t3,e16,mf2

	arcv.xvwmul.vv t0,t3,t6,e16,m1
	arcv.xvwmul.vv t3,t6,t0,e16,m1
	arcv.xvwmul.vv t6,t0,t3,e16,m1

	arcv.xvwmul.vv t0,t3,t6,e16,mf2
	arcv.xvwmul.vv t3,t6,t0,e16,mf2
	arcv.xvwmul.vv t6,t0,t3,e16,mf2

	arcv.xvwsrdot.vv t0,t3,t6,e16,m1
	arcv.xvwsrdot.vv t3,t6,t0,e16,m1
	arcv.xvwsrdot.vv t6,t0,t3,e16,m1

	arcv.xvscmul.vv t0,t3,t6,e16,m1
	arcv.xvscmul.vv t3,t6,t0,e16,m1
	arcv.xvscmul.vv t6,t0,t3,e16,m1

	arcv.xvscjmul.vv t0,t3,t6,e16,m1
	arcv.xvscjmul.vv t3,t6,t0,e16,m1
	arcv.xvscjmul.vv t6,t0,t3,e16,m1

	arcv.xvwscmul.vv t0,t3,t6,e16,m1
	arcv.xvwscmul.vv t3,t6,t0,e16,m1
	arcv.xvwscmul.vv t6,t0,t3,e16,m1

	arcv.xvwscjmul.vv t0,t3,t6,e16,m1
	arcv.xvwscjmul.vv t3,t6,t0,e16,m1
	arcv.xvwscjmul.vv t6,t0,t3,e16,m1

	arcv.xvwscrdot.vv t0,t3,t6,e16,m1
	arcv.xvwscrdot.vv t3,t6,t0,e16,m1
	arcv.xvwscrdot.vv t6,t0,t3,e16,m1

	arcv.xvwscjrdot.vv t0,t3,t6,e16,m1
	arcv.xvwscjrdot.vv t3,t6,t0,e16,m1
	arcv.xvwscjrdot.vv t6,t0,t3,e16,m1

	arcv.bitrev t0,t3,t6
	arcv.bitrev t3,t6,t0
	arcv.bitrev t6,t0,t3



