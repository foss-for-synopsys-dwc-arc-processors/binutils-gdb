	.text

	.global	lib_func1
	.type	lib_func1, @function
lib_func1:
	push_s 	blink
	bl	@app_func2	;add @plt to pass
	pop_s 	blink
	j_s 	[blink]
	.size	lib_func1, .-lib_func1
	.align 	4

	.global	lib_func2
	.type	lib_func2, @function
lib_func2:
	j_s 	[blink]
	.size	lib_func2, .-lib_func2


	.data
	.global	data_obj
	.align	4
	.type	data_obj, @object
data_obj:
	.long	0
	.size	data_obj, .-data_obj
