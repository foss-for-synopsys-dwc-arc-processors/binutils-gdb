	.extInstruction foo0,1,XD
	.extInstruction foo1,2,XD,void
	.extInstruction foo2,3,XD,void,no_src1
	.extInstruction foo3,4,XD,void,no_src0,no_src1
	.extInstruction foo4,5,XS
	.extInstruction foo5,6,XS,void
	.extInstruction foo6,7,XI
	.extInstruction foo7,8,XI,void
	.extInstruction foo8,9,XC

	.globl func_1
	func_1:
	  foo0	a0,a1,a2
	  foo1	a1,a2
	  foo2	a1
	  foo3
	  foo4	a0,a1,11
	  foo5	a1,11
	  foo6	a0,22
	  foo7	22
	  foo8	a0,a0,33
