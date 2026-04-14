	.extInstruction foo0,1,XS
	.extInstruction foo1,2,XI
	.extInstruction foo2,3,XC

	foo0 a0,a1,-129
	foo0 a0,a1,128

	foo1 a0,-2049
	foo1 a0,2048

	foo2 a0,a0,-2049
	foo2 a0,a0,2048
