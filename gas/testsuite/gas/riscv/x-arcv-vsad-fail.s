	# xarcvvsad - architecture set
	.option push
	.option arch, rv32i
	.include "x-arcv-vsad.s"
	.option pop

	# xarcvvsad - wrong number of operands

	arcv.vwsad.vv v0,v3
	arcv.vwsad.vv v3,v6
	arcv.vwsad.vv v6,v0

	arcv.vwsadu.vv v0,v3
	arcv.vwsadu.vv v3,v6
	arcv.vwsadu.vv v6,v0

	arcv.vwsad.vv v0,v3,v6,t0
	arcv.vwsad.vv v3,v6,v0,t0
	arcv.vwsad.vv v6,v0,v3,t0

	arcv.vwsadu.vv v0,v3,v6,t0
	arcv.vwsadu.vv v3,v6,v0,t0
	arcv.vwsadu.vv v6,v0,v3,t0

	# xarcvvsad - wrong operand types

	arcv.vwsad.vv 0,v3,v6
	arcv.vwsad.vv v0,3,v6
	arcv.vwsad.vv v0,v3,6

	arcv.vwsadu.vv 0,v3,v6
	arcv.vwsadu.vv v0,3,v6
	arcv.vwsadu.vv v0,v3,6
