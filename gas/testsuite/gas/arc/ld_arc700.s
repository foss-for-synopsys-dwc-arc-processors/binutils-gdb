; Test ARC specific assembler errors
;
; { dg-do assemble { target arc-*-* } }

	ld	lp_count,[sp,4]	; { dg-error "ld operand error" }
	
	ld	ilink1,[sp,4]	; { dg-error "ld operand error" }

	ld	ilink2,[sp,4]	; { dg-error "ld operand error" }


		

