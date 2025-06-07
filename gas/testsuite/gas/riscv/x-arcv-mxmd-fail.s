	# xarcvmxmd - architecture set
	.option push
	.option arch, rv32i
	.include "x-arcv-mxmd.s"
	.option pop

	# xarcvmxmd - wrong number of operands

	arcv.vqmxm16.vv v0,v3
	arcv.vqmxm16.vv v3,v6
	arcv.vqmxm16.vv v6,v0

	arcv.vqmxm16u.vv v0,v3
	arcv.vqmxm16u.vv v3,v6
	arcv.vqmxm16u.vv v6,v0

	arcv.vqmxm16su.vv v0,v3
	arcv.vqmxm16su.vv v3,v6
	arcv.vqmxm16su.vv v6,v0

	arcv.vqmxm16.vv v0,v3,v6,t0
	arcv.vqmxm16.vv v3,v6,v0,t0
	arcv.vqmxm16.vv v6,v0,v3,t0

	arcv.vqmxm16u.vv v0,v3,v6,t0
	arcv.vqmxm16u.vv v3,v6,v0,t0
	arcv.vqmxm16u.vv v6,v0,v3,t0

	arcv.vqmxm16su.vv v0,v3,v6,t0
	arcv.vqmxm16su.vv v3,v6,v0,t0
	arcv.vqmxm16su.vv v6,v0,v3,t0

	# xarcvmxmd - wrong operand types

	arcv.vqmxm16.vv 0,v3,v6
	arcv.vqmxm16.vv v0,3,v6
	arcv.vqmxm16.vv v0,v3,6

	arcv.vqmxm16u.vv 0,v3,v6
	arcv.vqmxm16u.vv v0,3,v6
	arcv.vqmxm16u.vv v0,v3,6

	arcv.vqmxm16su.vv 0,v3,v6
	arcv.vqmxm16su.vv v0,3,v6
	arcv.vqmxm16su.vv v0,v3,6
