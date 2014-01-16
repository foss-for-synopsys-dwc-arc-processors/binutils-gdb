# To look at compiler output, compile this:
#
# extern __thread int i;
# int f (void) { return i; }
# void g (int j) { i = j; }
#
# with -fpic and a choice of
# --tls-model=[global-dynamic|initial-exec|local-exec]

	.balign 4
	add_s r0,r0,@i@tpoff
	add r2,gp,@i@tpoff
	ld r1,[gp,@i@tpoff9]
	ld r0,[gp,@i@tpoff9]
	ld_s r0,[gp,@i@tpoff9]
	st r1,[gp,@i@tpoff9]
	st r0,[gp,@i@tpoff9]
        ld r2,[pcl,@i@tlsie]    ;16
        ld r0,[pcl,@i@tlsgd]    ;16
