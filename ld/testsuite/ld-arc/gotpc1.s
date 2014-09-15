        .section        .text
        .align 4
        .global __start
        .type   __start, @function
__start:
        ld r4,[pcl,@a_in_other_thread@gotpc]    ;19
        st 1,[r4]	;21
        .size   __start, .-__start

        .global a_in_other_thread
        .section        .data
        .align 4
        .type   a_in_other_thread, @object
        .size   a_in_other_thread, 4
a_in_other_thread:
        .word   -559038737
