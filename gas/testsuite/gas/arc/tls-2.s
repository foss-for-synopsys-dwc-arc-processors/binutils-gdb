	.balign 4
bar:
	nop_s
	ld.as	r0,[r25,@a@tpoff9+48]
	j_s	[blink]

foo:
	add	r0,r25,@a@tpoff9+48
	nop_s
	j_s	[blink]

