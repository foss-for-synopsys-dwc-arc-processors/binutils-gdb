# b test
	
text_label:

	b	text_label
	bal	text_label
	bra	text_label
	beq	text_label
	bz	text_label
	bne	text_label
	bnz	text_label
	bpl	text_label
	bp	text_label
	bmi	text_label
	bn	text_label
	bcs	text_label
	bc	text_label
	blo	text_label
	bcc	text_label
	bnc	text_label
	bhs	text_label
	bvs	text_label
	bv	text_label
	bvc	text_label
	bnv	text_label
	bgt	text_label
	bge	text_label
	blt	text_label
	ble	text_label
	bhi	text_label
	bls	text_label
	bpnz	text_label

	; note each delay slot cannot be a branch or jump
	b.d	text_label
	nop
	b.nd	text_label
	nop
; No such ARCxxx 'j':
;	b.jd	text_label

	beq.d	text_label
	nop
	bne.nd	text_label
	nop
; No such ARCxxx 'j':
;	bcc.jd	text_label
