	# xmipstrig - architecture set
	.option push
	.option arch, rv32if
	.include "x-mips-trig.s"
	.option pop

	# xmipstrig - wrong number of operands

	mips.fsinhz.s	 ft0,ft1,ft2
	mips.fcoshz.s	 ft2,ft3,ft1
	mips.ftanhz.s	 ft4,ft5,ft0
	mips.fversinhz.s	 ft6,ft7,ft1
	mips.fatanhz.s	 ft8,ft9,ft0
	mips.flti.s	 fa0,0,9
	mips.fftanh.s	 fs0,fs1,fs2
	mips.fflog2.s	 fs2,fs3,fs0
	mips.ffexp2.s	 fs4,fs5,fs1
	mips.ffrecip.s	 fs6,fs7,fs6
	mips.ffsqrt.s	 fs8,fs9,fs0
	mips.ffrsqrt.s	 fs10,fs11,fs0

	# xmipstrig - wrong operand types

	mips.flti.s	 fa1,32
