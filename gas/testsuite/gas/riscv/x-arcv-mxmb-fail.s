	# xarcvmxmb - architecture set
	.option push
	.option arch, rv32i
	.include "x-arcv-mxmb.s"
	.option pop

	# xarcvmxmb - wrong number of operands

	arcv.vqmxm4.vv v0,v3
	arcv.vqmxm4.vv v3,v6
	arcv.vqmxm4.vv v6,v0

	arcv.vqmxm4u.vv v0,v3
	arcv.vqmxm4u.vv v3,v6
	arcv.vqmxm4u.vv v6,v0

	arcv.vqmxm4su.vv v0,v3
	arcv.vqmxm4su.vv v3,v6
	arcv.vqmxm4su.vv v6,v0

	arcv.vqmxm4.vv v0,v3,v6,t0
	arcv.vqmxm4.vv v3,v6,v0,t0
	arcv.vqmxm4.vv v6,v0,v3,t0

	arcv.vqmxm4u.vv v0,v3,v6,t0
	arcv.vqmxm4u.vv v3,v6,v0,t0
	arcv.vqmxm4u.vv v6,v0,v3,t0

	arcv.vqmxm4su.vv v0,v3,v6,t0
	arcv.vqmxm4su.vv v3,v6,v0,t0
	arcv.vqmxm4su.vv v6,v0,v3,t0

	# xarcvmxmb - wrong operand types

	arcv.vqmxm4.vv 0,v3,v6
	arcv.vqmxm4.vv v0,3,v6
	arcv.vqmxm4.vv v0,v3,6

	arcv.vqmxm4u.vv 0,v3,v6
	arcv.vqmxm4u.vv v0,3,v6
	arcv.vqmxm4u.vv v0,v3,6

	arcv.vqmxm4su.vv 0,v3,v6
	arcv.vqmxm4su.vv v0,3,v6
	arcv.vqmxm4su.vv v0,v3,6
