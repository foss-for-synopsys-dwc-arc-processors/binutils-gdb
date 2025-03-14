	# xarcvudsp - architecture set
	.option push
	.option arch, rv32i
	.include "x-arcv-udsp.s"
	.option pop

	# xarcvudsp - incompatible with V
	.option arch, rv32gcv_xarcvudsp

	# xarcvudsp - bad operand types
	arcv.xvadd.vv t0,t3,5,e16,m1
	arcv.xvadd.vv t3,5,t0,e16,m1
	arcv.xvadd.vv 5,t0,t3,e16,m1

	arcv.xvsub.vv t0,t3,5,e16,m1
	arcv.xvsub.vv t3,5,t0,e16,m1
	arcv.xvsub.vv 5,t0,t3,e16,m1

	arcv.xvsadd.vv t0,t3,5,e16,m1
	arcv.xvsadd.vv t3,5,t0,e16,m1
	arcv.xvsadd.vv 5,t0,t3,e16,m1

	arcv.xvsadd.vv t0,t3,5,e32,m1
	arcv.xvsadd.vv t3,5,t0,e32,m1
	arcv.xvsadd.vv 5,t0,t3,e32,m1

	arcv.xvssub.vv t0,t3,5,e16,m1
	arcv.xvssub.vv t3,5,t0,e16,m1
	arcv.xvssub.vv 5,t0,t3,e16,m1

	arcv.xvssub.vv t0,t3,5,e32,m1
	arcv.xvssub.vv t3,5,t0,e32,m1
	arcv.xvssub.vv 5,t0,t3,e32,m1

	arcv.xvsll.vx t0,t3,5,e16,m1
	arcv.xvsll.vx t3,5,t0,e16,m1
	arcv.xvsll.vx 5,t0,t3,e16,m1

	arcv.xvsra.vx t0,t3,5,e16,m1
	arcv.xvsra.vx t3,5,t0,e16,m1
	arcv.xvsra.vx 5,t0,t3,e16,m1

	arcv.xvnclip.wx t0,t3,5,e16,m1
	arcv.xvnclip.wx t3,5,t0,e16,m1
	arcv.xvnclip.wx 5,t0,t3,e16,m1

	arcv.xvnclip.wx t0,t3,5,e16,mf2
	arcv.xvnclip.wx t3,5,t0,e16,mf2
	arcv.xvnclip.wx 5,t0,t3,e16,mf2

	arcv.xvwmul.vv t0,t3,5,e16,m1
	arcv.xvwmul.vv t3,5,t0,e16,m1
	arcv.xvwmul.vv 5,t0,t3,e16,m1

	arcv.xvwmul.vv t0,t3,5,e16,mf2
	arcv.xvwmul.vv t3,5,t0,e16,mf2
	arcv.xvwmul.vv 5,t0,t3,e16,mf2

	arcv.xvwsrdot.vv t0,t3,5,e16,m1
	arcv.xvwsrdot.vv t3,5,t0,e16,m1
	arcv.xvwsrdot.vv 5,t0,t3,e16,m1

	arcv.xvscmul.vv t0,t3,5,e16,m1
	arcv.xvscmul.vv t3,5,t0,e16,m1
	arcv.xvscmul.vv 5,t0,t3,e16,m1

	arcv.xvscjmul.vv t0,t3,5,e16,m1
	arcv.xvscjmul.vv t3,5,t0,e16,m1
	arcv.xvscjmul.vv 5,t0,t3,e16,m1

	arcv.xvwscmul.vv t0,t3,5,e16,m1
	arcv.xvwscmul.vv t3,5,t0,e16,m1
	arcv.xvwscmul.vv 5,t0,t3,e16,m1

	arcv.xvwscjmul.vv t0,t3,5,e16,m1
	arcv.xvwscjmul.vv t3,5,t0,e16,m1
	arcv.xvwscjmul.vv 5,t0,t3,e16,m1

	arcv.xvwscrdot.vv t0,t3,5,e16,m1
	arcv.xvwscrdot.vv t3,5,t0,e16,m1
	arcv.xvwscrdot.vv 5,t0,t3,e16,m1

	arcv.xvwscjrdot.vv t0,t3,5,e16,m1
	arcv.xvwscjrdot.vv t3,5,t0,e16,m1
	arcv.xvwscjrdot.vv 5,t0,t3,e16,m1

	arcv.bitrev t0,t3,5
	arcv.bitrev t3,5,t0
	arcv.bitrev 5,t0,t3

	# xarcvudsp - no SEW
	arcv.xvadd.vv t0,t3,t6,m1

	arcv.xvsub.vv t0,t3,t6,m1

	arcv.xvsadd.vv t0,t3,t6,m1

	arcv.xvssub.vv t0,t3,t6,m1

	arcv.xvsll.vx t0,t3,t6,m1

	arcv.xvsra.vx t0,t3,t6,m1

	arcv.xvnclip.wx t0,t3,t6,m1
	arcv.xvnclip.wx t0,t3,t6,mf2

	arcv.xvwmul.vv t0,t3,t6,m1
	arcv.xvwmul.vv t0,t3,t6,mf2

	arcv.xvwsrdot.vv t0,t3,t6,m1

	arcv.xvscmul.vv t0,t3,t6,m1

	arcv.xvscjmul.vv t0,t3,t6,m1

	arcv.xvwscmul.vv t0,t3,t6,m1

	arcv.xvwscjmul.vv t0,t3,t6,m1

	arcv.xvwscrdot.vv t0,t3,t6,m1

	arcv.xvwscjrdot.vv t0,t3,t6,m1

	# xarcvudsp - no LMUL
	arcv.xvadd.vv t0,t3,t6,e16

	arcv.xvsub.vv t0,t3,t6,e16

	arcv.xvsadd.vv t0,t3,t6,e16
	arcv.xvsadd.vv t0,t3,t6,e32

	arcv.xvssub.vv t0,t3,t6,e16
	arcv.xvssub.vv t0,t3,t6,e32

	arcv.xvsll.vx t0,t3,t6,e16

	arcv.xvsra.vx t0,t3,t6,e16

	arcv.xvnclip.wx t0,t3,t6,e16

	arcv.xvwmul.vv t0,t3,t6,e16

	arcv.xvwsrdot.vv t0,t3,t6,e16

	arcv.xvscmul.vv t0,t3,t6,e16

	arcv.xvscjmul.vv t0,t3,t6,e16

	arcv.xvwscmul.vv t0,t3,t6,e16

	arcv.xvwscjmul.vv t0,t3,t6,e16

	arcv.xvwscrdot.vv t0,t3,t6,e16

	arcv.xvwscjrdot.vv t0,t3,t6,e16


	# xarcvudsp - bad combinations of SEW+LMUL
	arcv.xvadd.vv t0,t3,t6,e8,m1
	arcv.xvadd.vv t0,t3,t6,e32,m1
	arcv.xvadd.vv t0,t3,t6,e16,mf2
	arcv.xvadd.vv t0,t3,t6,e16,m2

	arcv.xvsub.vv t0,t3,t6,e8,m1
	arcv.xvsub.vv t0,t3,t6,e32,m1
	arcv.xvsub.vv t0,t3,t6,e16,mf2
	arcv.xvsub.vv t0,t3,t6,e16,m2

	arcv.xvsadd.vv t0,t3,t6,e8,m1
	arcv.xvsadd.vv t0,t3,t6,e16,mf2
	arcv.xvsadd.vv t0,t3,t6,e16,m2

	arcv.xvssub.vv t0,t3,t6,e8,m1
	arcv.xvssub.vv t0,t3,t6,e16,mf2
	arcv.xvssub.vv t0,t3,t6,e16,m2

	arcv.xvsll.vx t0,t3,t6,e8,m1
	arcv.xvsll.vx t0,t3,t6,e32,m1
	arcv.xvsll.vx t0,t3,t6,e16,mf2
	arcv.xvsll.vx t0,t3,t6,e16,m2

	arcv.xvsra.vx t0,t3,t6,e8,m1
	arcv.xvsra.vx t0,t3,t6,e32,m1
	arcv.xvsra.vx t0,t3,t6,e16,mf2
	arcv.xvsra.vx t0,t3,t6,e16,m2

	arcv.xvnclip.wx t0,t3,t6,e8,m1
	arcv.xvnclip.wx t0,t3,t6,e32,m1
	arcv.xvnclip.wx t0,t3,t6,e16,m2

	arcv.xvwmul.vv t0,t3,t6,e8,m1
	arcv.xvwmul.vv t0,t3,t6,e32,m1
	arcv.xvwmul.vv t0,t3,t6,e16,m2

	arcv.xvwsrdot.vv t0,t3,t6,e8,m1
	arcv.xvwsrdot.vv t0,t3,t6,e32,m1
	arcv.xvwsrdot.vv t0,t3,t6,e16,mf2
	arcv.xvwsrdot.vv t0,t3,t6,e16,m2

	arcv.xvscmul.vv t0,t3,t6,e8,m1
	arcv.xvscmul.vv t0,t3,t6,e32,m1
	arcv.xvscmul.vv t0,t3,t6,e16,mf2
	arcv.xvscmul.vv t0,t3,t6,e16,m2

	arcv.xvscjmul.vv t0,t3,t6,e8,m1
	arcv.xvscjmul.vv t0,t3,t6,e32,m1
	arcv.xvscjmul.vv t0,t3,t6,e16,mf2
	arcv.xvscjmul.vv t0,t3,t6,e16,m2

	arcv.xvwscmul.vv t0,t3,t6,e8,m1
	arcv.xvwscmul.vv t0,t3,t6,e32,m1
	arcv.xvwscmul.vv t0,t3,t6,e16,mf2
	arcv.xvwscmul.vv t0,t3,t6,e16,m2

	arcv.xvwscjmul.vv t0,t3,t6,e8,m1
	arcv.xvwscjmul.vv t0,t3,t6,e32,m1
	arcv.xvwscjmul.vv t0,t3,t6,e16,mf2
	arcv.xvwscjmul.vv t0,t3,t6,e16,m2

	arcv.xvwscrdot.vv t0,t3,t6,e8,m1
	arcv.xvwscrdot.vv t0,t3,t6,e32,m1
	arcv.xvwscrdot.vv t0,t3,t6,e16,mf2
	arcv.xvwscrdot.vv t0,t3,t6,e16,m2

	arcv.xvwscjrdot.vv t0,t3,t6,e8,m1
	arcv.xvwscjrdot.vv t0,t3,t6,e32,m1
	arcv.xvwscjrdot.vv t0,t3,t6,e16,mf2
	arcv.xvwscjrdot.vv t0,t3,t6,e16,m2


	# xarcvudsp - junk at end of insn
	arcv.xvadd.vv t0,t3,t6,e16,m1,tu
	arcv.xvadd.vv t3,t6,t0,e16,m1,tu
	arcv.xvadd.vv t6,t0,t3,e16,m1,tu

	arcv.xvsub.vv t0,t3,t6,e16,m1,tu
	arcv.xvsub.vv t3,t6,t0,e16,m1,tu
	arcv.xvsub.vv t6,t0,t3,e16,m1,tu

	arcv.xvsadd.vv t0,t3,t6,e16,m1,tu
	arcv.xvsadd.vv t3,t6,t0,e16,m1,tu
	arcv.xvsadd.vv t6,t0,t3,e16,m1,tu

	arcv.xvsadd.vv t0,t3,t6,e32,m1,tu
	arcv.xvsadd.vv t3,t6,t0,e32,m1,tu
	arcv.xvsadd.vv t6,t0,t3,e32,m1,tu

	arcv.xvssub.vv t0,t3,t6,e16,m1,tu
	arcv.xvssub.vv t3,t6,t0,e16,m1,tu
	arcv.xvssub.vv t6,t0,t3,e16,m1,tu

	arcv.xvssub.vv t0,t3,t6,e32,m1,tu
	arcv.xvssub.vv t3,t6,t0,e32,m1,tu
	arcv.xvssub.vv t6,t0,t3,e32,m1,tu

	arcv.xvsll.vx t0,t3,t6,e16,m1,tu
	arcv.xvsll.vx t3,t6,t0,e16,m1,tu
	arcv.xvsll.vx t6,t0,t3,e16,m1,tu

	arcv.xvsra.vx t0,t3,t6,e16,m1,tu
	arcv.xvsra.vx t3,t6,t0,e16,m1,tu
	arcv.xvsra.vx t6,t0,t3,e16,m1,tu

	arcv.xvnclip.wx t0,t3,t6,e16,m1,tu
	arcv.xvnclip.wx t3,t6,t0,e16,m1,tu
	arcv.xvnclip.wx t6,t0,t3,e16,m1,tu

	arcv.xvnclip.wx t0,t3,t6,e16,mf2,tu
	arcv.xvnclip.wx t3,t6,t0,e16,mf2,tu
	arcv.xvnclip.wx t6,t0,t3,e16,mf2,tu

	arcv.xvwmul.vv t0,t3,t6,e16,m1,tu
	arcv.xvwmul.vv t3,t6,t0,e16,m1,tu
	arcv.xvwmul.vv t6,t0,t3,e16,m1,tu

	arcv.xvwmul.vv t0,t3,t6,e16,mf2,tu
	arcv.xvwmul.vv t3,t6,t0,e16,mf2,tu
	arcv.xvwmul.vv t6,t0,t3,e16,mf2,tu

	arcv.xvwsrdot.vv t0,t3,t6,e16,m1,tu
	arcv.xvwsrdot.vv t3,t6,t0,e16,m1,tu
	arcv.xvwsrdot.vv t6,t0,t3,e16,m1,tu

	arcv.xvscmul.vv t0,t3,t6,e16,m1,tu
	arcv.xvscmul.vv t3,t6,t0,e16,m1,tu
	arcv.xvscmul.vv t6,t0,t3,e16,m1,tu

	arcv.xvscjmul.vv t0,t3,t6,e16,m1,tu
	arcv.xvscjmul.vv t3,t6,t0,e16,m1,tu
	arcv.xvscjmul.vv t6,t0,t3,e16,m1,tu

	arcv.xvwscmul.vv t0,t3,t6,e16,m1,tu
	arcv.xvwscmul.vv t3,t6,t0,e16,m1,tu
	arcv.xvwscmul.vv t6,t0,t3,e16,m1,tu

	arcv.xvwscjmul.vv t0,t3,t6,e16,m1,tu
	arcv.xvwscjmul.vv t3,t6,t0,e16,m1,tu
	arcv.xvwscjmul.vv t6,t0,t3,e16,m1,tu

	arcv.xvwscrdot.vv t0,t3,t6,e16,m1,tu
	arcv.xvwscrdot.vv t3,t6,t0,e16,m1,tu
	arcv.xvwscrdot.vv t6,t0,t3,e16,m1,tu

	arcv.xvwscjrdot.vv t0,t3,t6,e16,m1,tu
	arcv.xvwscjrdot.vv t3,t6,t0,e16,m1,tu
	arcv.xvwscjrdot.vv t6,t0,t3,e16,m1,tu


