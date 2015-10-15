	.text
	.global foo
	.type foo, @function
foo:
	nop
.L2:
	nop
	push_s	blink

.Lpool:
	add     r0,r25,@a@tpoff + (. - .L2 - 8)
#	.word	@lib_gd@tpoff + (. - .L2 - 8)
#	.word	lib_ld(tlsldm) + (. - .L2 - 8)
#	.word	lib_ld(tlsldo)

	.section .tdata,"awT"
	.global lib_gd
lib_gd:
	.space	4

	.global lib_ld
lib_ld:
	.space	4
