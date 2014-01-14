; Test ARC specific assembler warnings
;
; { dg-do assemble { target arc*-*-* } }

	b.d foo
	mov r0,4096	; { dg-warning "Instruction with long immediate data in delay slot" "Instruction with long immediate data in delay slot" }

	j.d foo		; { dg-warning "bad instruction" "8 byte jump instruction with delay slot" }
	mov r0,r1

foo:
.extCoreRegister roscreg,45,r,can_shortcut
.extCoreRegister woscreg,46,w,can_shortcut
        .section .text
         add    r0,woscreg,r1   ; { dg-warning "Error: attempt to read writeonly register" }
         add    roscreg,r1,r2   ; { dg-warning "Error: attempt to set readonly register" }
