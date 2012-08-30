# lp test
	
; note ARCompact cannot reference labels with negative offsets, only
; labels ahead of them.
text_label:

	lp	.L0
	; Note ARCompact need an actual instructin to execute
	add r0, r0, r0
	nop ; required in this instance
.L0:
	lpal	.L1
	add r0, r0, r0
.L1:
	lpra	.L2
	add r0, r0, r0
.L2:
	lpeq	.L3
	add r0, r0, r0
.L3:
	lpz	.L4
	add r0, r0, r0
.L4:
	lpne	.L5
	add r0, r0, r0
.L5:
	lpnz	.L6
	add r0, r0, r0
.L6:
	lppl	.L7
	add r0, r0, r0
.L7:
	lpp	.L8
	add r0, r0, r0
.L8:
	lpmi	.L9
	add r0, r0, r0
.L9:
	lpn	.L10
	add r0, r0, r0
.L10:
	lpcs	.L11
	add r0, r0, r0
.L11:
	lpc	.L12
	add r0, r0, r0
.L12:
	lplo	.L13
	add r0, r0, r0
.L13:
	lpcc	.L14
	add r0, r0, r0
.L14:
	lpnc	.L15
	add r0, r0, r0
.L15:
	lphs	.L16
	add r0, r0, r0
.L16:
	lpvs	.L17
	add r0, r0, r0
.L17:
	lpv	.L18
	add r0, r0, r0
.L18:
	lpvc	.L19
	add r0, r0, r0
.L19:
	lpnv	.L20
	add r0, r0, r0
.L20:
	lpgt	.L21
	add r0, r0, r0
.L21:
	lpge	.L22
	add r0, r0, r0
.L22:
	lplt	.L23
	add r0, r0, r0
.L23:
	lple	.L24
	add r0, r0, r0
.L24:
	lphi	.L25
	add r0, r0, r0
.L25:
	lpls	.L26
	add r0, r0, r0
.L26:
	lppnz	.L27
	add r0, r0, r0
.L27:

; Note ARCompact does not have a delay slot to LP
;	lp.d	.L
;	lp.nd	.L
; No such ARCxxx 'j':
;	lp.jd	.L

;	lpeq.d	.L
;	lpne.nd	.L
; No such ARCxxx 'j':
;	lpcc.jd	.L
	
