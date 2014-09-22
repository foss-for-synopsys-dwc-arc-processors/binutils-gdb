        .section        .debug_info,"",@progbits
        .word   foo
        .word   bar

        .section ".text.1", "ax"
        .global foo
foo:
        nop
        .type foo, @function
        .size foo, . - foo

        .section ".text.2", "ax"
        .global bar
bar:
        nop
        .type bar, @function
        .size bar, . - bar
