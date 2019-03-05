        .section        .text
        .align 4
        .global __start
        .type __start, @function
__start:
        add	r0,r0,r0
        bl	@foo
        .size __start, .-__start

        .align 4
        .global foo
        .type foo, @function
foo:
        add	r0,r0,r0
        bl_s	@__start
        .size foo, .-foo

        .align 4
        .global goo
        .type goo, @function
goo:
        add	r0,r0,r0
        .size goo, .-goo
