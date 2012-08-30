_foo:
	mov_s r0,0

.section .data
_abc:
	.global _abc
	.4byte _foo

