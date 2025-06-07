	# xarcvbitrev - architecture set
	.option push
	.option arch, rv32i
	.include "x-arcv-bitrev.s"
	.option pop

	# xarcvbitrev - wrong number of operands

	arcv.bitrev t0,t3
	arcv.bitrev t3,t6
	arcv.bitrev t6,t0
	arcv.bitrev t0,t3,t6,t0
	arcv.bitrev t3,t6,t0,t0
	arcv.bitrev t6,t0,t3,t0

	# xarcvbitrev - wrong operand types

	arcv.bitrev 0,t3,t6
	arcv.bitrev t0,3,t6
	arcv.bitrev t0,t3,6
