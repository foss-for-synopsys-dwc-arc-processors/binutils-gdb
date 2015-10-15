	.global	__start
	.type	__start,@function
__start:
	mov	r1,1f
	mov	r1,2f
1:
	mov	r2,@foo@gotoff
2:
	mov	r2,@__start@gotoff
	.size	__start,.-__start
