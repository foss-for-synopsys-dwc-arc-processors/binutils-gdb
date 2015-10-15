	.global	foo
	.type	foo,@function
foo:
	j_s	[blink]
	.size	foo,.-foo
