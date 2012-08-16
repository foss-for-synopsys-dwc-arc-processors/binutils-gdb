# bl test
	
text_label:

	bl	text_label
	blal	text_label
	blra	text_label
	bleq	text_label
	blz	text_label
	blne	text_label
	blnz	text_label
	blpl	text_label
	blp	text_label
	blmi	text_label
	bln	text_label
	blcs	text_label
	blc	text_label
	bllo	text_label
	blcc	text_label
	blnc	text_label
	blhs	text_label
	blvs	text_label
	blv	text_label
	blvc	text_label
	blnv	text_label
	blgt	text_label
	blge	text_label
	bllt	text_label
	blle	text_label
	blhi	text_label
	blls	text_label
	blpnz	text_label

	; note each delay slot cannot be a branch or jump
	bl.d	text_label
	nop
	bl.nd	text_label
	nop
; No such ARCxxx 'j':
;	bl.jd	text_label

	bleq.d	text_label
	nop
	blne.nd	text_label
	nop
; No such ARCxxx 'j':
;	blcc.jd	text_label
