       .global  foo
foo:
        bl     @foo@plt

        .data
        .word   foo-.
        .word   foo-.+0x100
