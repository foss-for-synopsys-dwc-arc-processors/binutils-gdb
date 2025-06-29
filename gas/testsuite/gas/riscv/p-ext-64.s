target:
	pli.b	a0, 1
	pli.h	a0, 5
	pli.w	a0, 31
	pslli.b	a0, a1, 1
	pslli.h	a0, a1, 5
	pslli.w	a0, a1, 31
	psslai.h	a0, a1, 5
	psslai.w	a0, a1, 31
