        /* This file is not intended to be real code, however, the
           contents of the main function is real code as generated as
           part of a local dynamic tls model access.  The purpose of
           this test is to check that such an access will link
           correctly.

           Notice that the relocation in main references '.tdata', and
           though we put content into '.tdata.pgsz.1362' we don't
           create a '.tdata' section.  This is intentional, this example
           was generated using -fdata-sections.

           The '.tdata' section will be created in the linker script,
           and we do expect to be able to reference it.  This should link.
        */

        .section ".text", "ax"
        .global main, _start
_start: 
        .type   main, @function
main:
        add r0,pcl,@.tdata@tlsgd                ;8
        .size   main, .-main

        .section        .tdata.pgsz.1362,"awT",@progbits
        .align 8
        .type   pgsz.1362, @object
        .size   pgsz.1362, 4

pgsz.1362:
        .word   1
