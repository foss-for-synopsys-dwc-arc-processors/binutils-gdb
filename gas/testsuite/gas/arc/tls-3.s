	.balign 4
bar:
	add	r0,pcl,a@tlsgd
	.tls_gd_ld a,.L_tls_gd_0`ld_s	r12,[r0]
	push_s	blink
	nop
	.L_tls_gd_0:jl_s	[r12]
	pop_s	blink
	j_s.d	[blink]
	ld_s	r0,[r0]
	.balign 4
foo:
	add	r0,pcl,a@tlsgd
	.tls_gd_ld a`ld_s	r12,[r0]
	push_s	blink
	nop
	.tls_gd_call a`jl_s	[r12]
	pop_s	blink
	j_s.d	[blink]
	ld_s	r0,[r0]
