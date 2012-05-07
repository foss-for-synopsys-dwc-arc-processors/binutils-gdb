; Test ARC specific assembler errors
;
; { dg-do assemble { target arc-*-* } }

	ex	lp_count,[sp]	; { dg-error "ex operand error" }
	
	ex	ilink1,[sp]	; { dg-error "ex operand error" }

	ex	ilink2,[sp]	; { dg-error "ex operand error" }

