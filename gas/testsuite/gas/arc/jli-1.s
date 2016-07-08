;;; Test basic JLI relocs and constructs.

	.cpu em4

	add2    r0,r0,@foo@jli	; Generates R_ARC_JLI_SECTOFF_SIMM12
	jli_s	__jli.foo	; Generates R_ARC_JLI_SECTOFF

	.data
	.word	@foo@jli	; Generates R_ARC_JLI_32

	.section	.jlitab.foo,"axG",%progbits,jli_group,comdat
        .align  4
__jli.foo:
        .weak   __jli.foo
        b       @foo
