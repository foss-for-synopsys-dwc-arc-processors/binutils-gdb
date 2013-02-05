;; Test ARC-EM ADD_S extensions for ARC700
;;
; { dg-do assemble { target arc-*-* } }

	;; The following insns are accepted by ARCv2 only
	add_s r4,r4,-1		; { dg-error "bad instruction `add_s r4,r4,-1'" }
	add_s 0,0xAAAA5555,-1   ; { dg-error "bad instruction `add_s 0,0xAAAA5555,-1'" }
	add_s r0,r15,0x20	; { dg-error "bad instruction `add_s r0,r15,0x20'" }
	add_s r1,r15,0x20	; { dg-error "bad instruction `add_s r1,r15,0x20'" }
