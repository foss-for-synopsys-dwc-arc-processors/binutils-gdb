	.text
	.globl _start
_start:
	# Two compressed instructions before the alignment.  With
	# --relax-align-decompress they are expanded to their 32-bit forms so
	# that no NOP is needed to reach the 8-byte boundary.
	c.li	a0, 1
	c.li	a1, 2
	.align	3
aligned:
	add	a2, a0, a1
	# The instruction before this alignment (a compressed branch carrying a
	# relocation) cannot be decompressed, so the linker must fall back to
	# inserting a NOP.
	c.beqz	a0, tail
	.align	3
tail:
	ret
