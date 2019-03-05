	.arc_attribute Tag_ARC_PCS_config, 2
	.section	.text
	.align 4
	.global __start
	.type __start, @function
__start:
	bl	@foo
	bl_s	@foo
	.size __start, .-__start

	.align 4
foo:
	add	r0,r0,r0
	.size foo, .-foo
