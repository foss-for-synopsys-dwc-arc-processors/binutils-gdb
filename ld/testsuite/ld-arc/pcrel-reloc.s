	.text
	.align 4
.L1:
	.4byte	@.L2-.

	.data
	.align 4
.L2:
	.4byte	@.L1-.
