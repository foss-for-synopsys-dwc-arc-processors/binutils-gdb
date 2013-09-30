	.file	"h30fun.c"
	.cpu ARC700
	.section .text
	.align 4
	.global	f
	.type	f, @function
f:
.LFB0:
	push_s blink
.LCFI0:
	st.a fp,[sp,-4]       ;17
.LCFI1:
	mov fp,sp		;3
.LCFI2:
	bl @h30@plt
	ld.ab fp,[sp,4]	;16
	pop_s blink
	j_s [blink]
.LFE0:
	.size	f, .-f
	.section	.debug_frame,"",@progbits
.Lframe0:
	.4byte	@.LECIE0-@.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x1
	.string	""
	.uleb128 0x1
	.sleb128 -4
	.byte	0x1f
	.byte	0xc
	.uleb128 0x1c
	.uleb128 0x0
	.align 4
.LECIE0:
.LSFDE0:
	.4byte	@.LEFDE0-@.LASFDE0
.LASFDE0:
	.4byte	@.Lframe0
	.4byte	@.LFB0
	.4byte	@.LFE0-@.LFB0
	.byte	0x4
	.4byte	@.LCFI0-@.LFB0
	.byte	0xe
	.uleb128 0x4
	.byte	0x4
	.4byte	@.LCFI1-@.LCFI0
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0x1b
	.sleb128 2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 1
	.byte	0x4
	.4byte	@.LCFI2-@.LCFI1
	.byte	0xd
	.uleb128 0x1b
	.align 4
.LEFDE0:
	.ident	"GCC: (ARCompact elf32 toolchain (built 20120911)) 4.4.7"
