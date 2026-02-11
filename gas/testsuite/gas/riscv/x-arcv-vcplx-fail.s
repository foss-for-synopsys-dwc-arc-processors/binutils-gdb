	# xarcvvcplx - architecture set
	.option push
	.option arch, rv32i
	.include "x-arcv-vcplx.s"
	.option pop

	# xarcvvcplx - wrong number of operands

	arcv.vconj.v v0
	arcv.vconj.v v3

	arcv.vcmuli.v v0
	arcv.vcmuli.v v3

	arcv.vcmulni.v v0
	arcv.vcmulni.v v3

	arcv.veven.v v0
	arcv.veven.v v3

	arcv.vodd.v v0
	arcv.vodd.v v3

	arcv.vinterleave.vv v0,v3
	arcv.vinterleave.vv v3,v6
	arcv.vinterleave.vv v6,v0

	arcv.vscredsum.vv v0,v3
	arcv.vscredsum.vv v3,v6
	arcv.vscredsum.vv v6,v0

	arcv.vwcredsum.vv v0,v3
	arcv.vwcredsum.vv v3,v6
	arcv.vwcredsum.vv v6,v0

	arcv.vscmul.vv v0,v3
	arcv.vscmul.vv v3,v6
	arcv.vscmul.vv v6,v0

	arcv.vscmul.vs v0,v3
	arcv.vscmul.vs v3,v6
	arcv.vscmul.vs v6,v0

	arcv.vscjmul.vv v0,v3
	arcv.vscjmul.vv v3,v6
	arcv.vscjmul.vv v6,v0

	arcv.vscjmul.vs v0,v3
	arcv.vscjmul.vs v3,v6
	arcv.vscjmul.vs v6,v0

	arcv.vwscmul.vv v0,v3
	arcv.vwscmul.vv v3,v6
	arcv.vwscmul.vv v6,v0

	arcv.vwscmul.vs v0,v3
	arcv.vwscmul.vs v3,v6
	arcv.vwscmul.vs v6,v0

	arcv.vwscjmul.vv v0,v3
	arcv.vwscjmul.vv v3,v6
	arcv.vwscjmul.vv v6,v0

	arcv.vwscjmul.vs v0,v3
	arcv.vwscjmul.vs v3,v6
	arcv.vwscjmul.vs v6,v0

	arcv.vwscmac.vv v0,v3
	arcv.vwscmac.vv v3,v6
	arcv.vwscmac.vv v6,v0

	arcv.vwscmac.vs v0,v3
	arcv.vwscmac.vs v3,v6
	arcv.vwscmac.vs v6,v0

	arcv.vwscnmsac.vv v0,v3
	arcv.vwscnmsac.vv v3,v6
	arcv.vwscnmsac.vv v6,v0

	arcv.vwscnmsac.vs v0,v3
	arcv.vwscnmsac.vs v3,v6
	arcv.vwscnmsac.vs v6,v0

	arcv.vwscjmac.vv v0,v3
	arcv.vwscjmac.vv v3,v6
	arcv.vwscjmac.vv v6,v0

	arcv.vwscjmac.vs v0,v3
	arcv.vwscjmac.vs v3,v6
	arcv.vwscjmac.vs v6,v0

	arcv.vwscjnmsac.vv v0,v3
	arcv.vwscjnmsac.vv v3,v6
	arcv.vwscjnmsac.vv v6,v0

	arcv.vwscjnmsac.vs v0,v3
	arcv.vwscjnmsac.vs v3,v6
	arcv.vwscjnmsac.vs v6,v0

	arcv.vwscrdot.vv v0,v3
	arcv.vwscrdot.vv v3,v6
	arcv.vwscrdot.vv v6,v0

	arcv.vwscjrdot.vv v0,v3
	arcv.vwscjrdot.vv v3,v6
	arcv.vwscjrdot.vv v6,v0

	arcv.vqcrdot.vv v0,v3
	arcv.vqcrdot.vv v3,v6
	arcv.vqcrdot.vv v6,v0

	arcv.vqcjrdot.vv v0,v3
	arcv.vqcjrdot.vv v3,v6
	arcv.vqcjrdot.vv v6,v0

	arcv.vconj.v v0,v3,t0
	arcv.vconj.v v3,v6,t0

	arcv.vcmuli.v v0,v3,t0
	arcv.vcmuli.v v3,v6,t0

	arcv.vcmulni.v v0,v3,t0
	arcv.vcmulni.v v3,v6,t0

	arcv.veven.v v0,v3,t0
	arcv.veven.v v3,v6,t0

	arcv.vodd.v v0,v3,t0
	arcv.vodd.v v3,v6,t0

	arcv.vinterleave.vv v0,v3,v6,t0
	arcv.vinterleave.vv v3,v6,v0,t0
	arcv.vinterleave.vv v6,v0,v3,t0

	arcv.vscredsum.vv v0,v3,v6,t0
	arcv.vscredsum.vv v3,v6,v0,t0
	arcv.vscredsum.vv v6,v0,v3,t0

	arcv.vwcredsum.vv v0,v3,v6,t0
	arcv.vwcredsum.vv v3,v6,v0,t0
	arcv.vwcredsum.vv v6,v0,v3,t0

	arcv.vscmul.vv v0,v3,v6,t0
	arcv.vscmul.vv v3,v6,v0,t0
	arcv.vscmul.vv v6,v0,v3,t0

	arcv.vscmul.vs v0,v3,v6,t0
	arcv.vscmul.vs v3,v6,v0,t0
	arcv.vscmul.vs v6,v0,v3,t0

	arcv.vscjmul.vv v0,v3,v6,t0
	arcv.vscjmul.vv v3,v6,v0,t0
	arcv.vscjmul.vv v6,v0,v3,t0

	arcv.vscjmul.vs v0,v3,v6,t0
	arcv.vscjmul.vs v3,v6,v0,t0
	arcv.vscjmul.vs v6,v0,v3,t0

	arcv.vwscmul.vv v0,v3,v6,t0
	arcv.vwscmul.vv v3,v6,v0,t0
	arcv.vwscmul.vv v6,v0,v3,t0

	arcv.vwscmul.vs v0,v3,v6,t0
	arcv.vwscmul.vs v3,v6,v0,t0
	arcv.vwscmul.vs v6,v0,v3,t0

	arcv.vwscjmul.vv v0,v3,v6,t0
	arcv.vwscjmul.vv v3,v6,v0,t0
	arcv.vwscjmul.vv v6,v0,v3,t0

	arcv.vwscjmul.vs v0,v3,v6,t0
	arcv.vwscjmul.vs v3,v6,v0,t0
	arcv.vwscjmul.vs v6,v0,v3,t0

	arcv.vwscmac.vv v0,v3,v6,t0
	arcv.vwscmac.vv v3,v6,v0,t0
	arcv.vwscmac.vv v6,v0,v3,t0

	arcv.vwscmac.vs v0,v3,v6,t0
	arcv.vwscmac.vs v3,v6,v0,t0
	arcv.vwscmac.vs v6,v0,v3,t0

	arcv.vwscnmsac.vv v0,v3,v6,t0
	arcv.vwscnmsac.vv v3,v6,v0,t0
	arcv.vwscnmsac.vv v6,v0,v3,t0

	arcv.vwscnmsac.vs v0,v3,v6,t0
	arcv.vwscnmsac.vs v3,v6,v0,t0
	arcv.vwscnmsac.vs v6,v0,v3,t0

	arcv.vwscjmac.vv v0,v3,v6,t0
	arcv.vwscjmac.vv v3,v6,v0,t0
	arcv.vwscjmac.vv v6,v0,v3,t0

	arcv.vwscjmac.vs v0,v3,v6,t0
	arcv.vwscjmac.vs v3,v6,v0,t0
	arcv.vwscjmac.vs v6,v0,v3,t0

	arcv.vwscjnmsac.vv v0,v3,v6,t0
	arcv.vwscjnmsac.vv v3,v6,v0,t0
	arcv.vwscjnmsac.vv v6,v0,v3,t0

	arcv.vwscjnmsac.vs v0,v3,v6,t0
	arcv.vwscjnmsac.vs v3,v6,v0,t0
	arcv.vwscjnmsac.vs v6,v0,v3,t0

	arcv.vwscrdot.vv v0,v3,v6,t0
	arcv.vwscrdot.vv v3,v6,v0,t0
	arcv.vwscrdot.vv v6,v0,v3,t0

	arcv.vwscjrdot.vv v0,v3,v6,t0
	arcv.vwscjrdot.vv v3,v6,v0,t0
	arcv.vwscjrdot.vv v6,v0,v3,t0

	arcv.vqcrdot.vv v0,v3,v6,t0
	arcv.vqcrdot.vv v3,v6,v0,t0
	arcv.vqcrdot.vv v6,v0,v3,t0

	arcv.vqcjrdot.vv v0,v3,v6,t0
	arcv.vqcjrdot.vv v3,v6,v0,t0
	arcv.vqcjrdot.vv v6,v0,v3,t0

	# xarcvvcplx - wrong operand types

	arcv.vconj.v 0,v3
	arcv.vconj.v v0,3

	arcv.vcmuli.v 0,v3
	arcv.vcmuli.v v0,3

	arcv.vcmulni.v 0,v3
	arcv.vcmulni.v v0,3

	arcv.veven.v 0,v3
	arcv.veven.v v0,3

	arcv.vodd.v 0,v3
	arcv.vodd.v v0,3

	arcv.vinterleave.vv 0,v3,v6
	arcv.vinterleave.vv v0,3,v6
	arcv.vinterleave.vv v0,v3,6

	arcv.vscredsum.vv 0,v3,v6
	arcv.vscredsum.vv v0,3,v6
	arcv.vscredsum.vv v0,v3,6

	arcv.vwcredsum.vv 0,v3,v6
	arcv.vwcredsum.vv v0,3,v6
	arcv.vwcredsum.vv v0,v3,6

	arcv.vscmul.vv 0,v3,v6
	arcv.vscmul.vv v0,3,v6
	arcv.vscmul.vv v0,v3,6

	arcv.vscmul.vs 0,v3,t6
	arcv.vscmul.vs v0,3,t6
	arcv.vscmul.vs v0,v3,6

	arcv.vscjmul.vv 0,v3,v6
	arcv.vscjmul.vv v0,3,v6
	arcv.vscjmul.vv v0,v3,6

	arcv.vscjmul.vs 0,v3,t6
	arcv.vscjmul.vs v0,3,t6
	arcv.vscjmul.vs v0,v3,6

	arcv.vwscmul.vv 0,v3,v6
	arcv.vwscmul.vv v0,3,v6
	arcv.vwscmul.vv v0,v3,6

	arcv.vwscmul.vs 0,v3,t6
	arcv.vwscmul.vs v0,3,t6
	arcv.vwscmul.vs v0,v3,6

	arcv.vwscjmul.vv 0,v3,v6
	arcv.vwscjmul.vv v0,3,v6
	arcv.vwscjmul.vv v0,v3,6

	arcv.vwscjmul.vs 0,v3,t6
	arcv.vwscjmul.vs v0,3,t6
	arcv.vwscjmul.vs v0,v3,6

	arcv.vwscmac.vv 0,v3,v6
	arcv.vwscmac.vv v0,3,v6
	arcv.vwscmac.vv v0,v3,6

	arcv.vwscmac.vs 0,v3,t6
	arcv.vwscmac.vs v0,3,t6
	arcv.vwscmac.vs v0,v3,6

	arcv.vwscnmsac.vv 0,v3,v6
	arcv.vwscnmsac.vv v0,3,v6
	arcv.vwscnmsac.vv v0,v3,6

	arcv.vwscnmsac.vs 0,v3,t6
	arcv.vwscnmsac.vs v0,3,t6
	arcv.vwscnmsac.vs v0,v3,6

	arcv.vwscjmac.vv 0,v3,v6
	arcv.vwscjmac.vv v0,3,v6
	arcv.vwscjmac.vv v0,v3,6

	arcv.vwscjmac.vs 0,v3,t6
	arcv.vwscjmac.vs v0,3,t6
	arcv.vwscjmac.vs v0,v3,6

	arcv.vwscjnmsac.vv 0,v3,v6
	arcv.vwscjnmsac.vv v0,3,v6
	arcv.vwscjnmsac.vv v0,v3,6

	arcv.vwscjnmsac.vs 0,v3,t6
	arcv.vwscjnmsac.vs v0,3,t6
	arcv.vwscjnmsac.vs v0,v3,6

	arcv.vwscrdot.vv 0,v3,v6
	arcv.vwscrdot.vv v0,3,v6
	arcv.vwscrdot.vv v0,v3,6

	arcv.vwscjrdot.vv 0,v3,v6
	arcv.vwscjrdot.vv v0,3,v6
	arcv.vwscjrdot.vv v0,v3,6

	arcv.vqcrdot.vv 0,v3,v6
	arcv.vqcrdot.vv v0,3,v6
	arcv.vqcrdot.vv v0,v3,6

	arcv.vqcjrdot.vv 0,v3,v6
	arcv.vqcjrdot.vv v0,3,v6
	arcv.vqcjrdot.vv v0,v3,6
