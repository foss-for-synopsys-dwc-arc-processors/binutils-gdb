	# xarcvbitstream - architecture set
	.option push
	.option arch, rv32i
	.include "x-arcv-bitstream.s"
	.option pop

	# xarcvbitstream - wrong number of operands

	arcv.bspeek t0
	arcv.bspeek t3

	arcv.bspop t0
	arcv.bspop t3

	arcv.bspush t0,t3
	arcv.bspush t3,t6
	arcv.bspush t6,t0

	arcv.bspeek t0,t3,t0
	arcv.bspeek t3,t6,t0

	arcv.bspop t0,t3,t0
	arcv.bspop t3,t6,t0

	arcv.bspush t0,t3,t6,t0
	arcv.bspush t3,t6,t0,t0
	arcv.bspush t6,t0,t3,t0

	# xarcvbitstream - wrong operand types

	arcv.bspeek 0,t3
	arcv.bspeek t0,3

	arcv.bspop 0,t3
	arcv.bspop t0,3

	arcv.bspush 0,t3,t6
	arcv.bspush t0,3,t6
	arcv.bspush t0,t3,6
