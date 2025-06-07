	# xarcvmxmc - architecture set
	.option push
	.option arch, rv32i
	.include "x-arcv-mxmc.s"
	.option pop

	# xarcvmxmc - wrong number of operands

	arcv.vqmxm8.vv v0,v3
	arcv.vqmxm8.vv v3,v6
	arcv.vqmxm8.vv v6,v0

	arcv.vqmxm8u.vv v0,v3
	arcv.vqmxm8u.vv v3,v6
	arcv.vqmxm8u.vv v6,v0

	arcv.vqmxm8su.vv v0,v3
	arcv.vqmxm8su.vv v3,v6
	arcv.vqmxm8su.vv v6,v0

	arcv.vqmxm8.vv v0,v3,v6,t0
	arcv.vqmxm8.vv v3,v6,v0,t0
	arcv.vqmxm8.vv v6,v0,v3,t0

	arcv.vqmxm8u.vv v0,v3,v6,t0
	arcv.vqmxm8u.vv v3,v6,v0,t0
	arcv.vqmxm8u.vv v6,v0,v3,t0

	arcv.vqmxm8su.vv v0,v3,v6,t0
	arcv.vqmxm8su.vv v3,v6,v0,t0
	arcv.vqmxm8su.vv v6,v0,v3,t0

	# xarcvmxmc - wrong operand types

	arcv.vqmxm8.vv 0,v3,v6
	arcv.vqmxm8.vv v0,3,v6
	arcv.vqmxm8.vv v0,v3,6

	arcv.vqmxm8u.vv 0,v3,v6
	arcv.vqmxm8u.vv v0,3,v6
	arcv.vqmxm8u.vv v0,v3,6

	arcv.vqmxm8su.vv 0,v3,v6
	arcv.vqmxm8su.vv v0,3,v6
	arcv.vqmxm8su.vv v0,v3,6
