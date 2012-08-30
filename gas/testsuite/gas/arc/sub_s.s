; SUB_S    c,b,u3   01101bbbccc01uuu

	sub_s	  r0,r1,0
	sub_s	  r0,r1,7
		
; SUB_S    b,b,c    01111bbbccc00010

	sub_s	  r0,r0,r1
	sub_s	  r0,r0,r1

; SUB_S    b,b,u5   10111bbb011uuuuu

	sub_s	  r0,r0,0
	sub_s	  r0,r0,31
	
; SUB_S.NE b,b,b    01111bbb11000000

	sub_s.ne  r0,r0,r0
	
; SUB_S    sp,sp,u7 11000001101uuuuu

	sub_s	  sp,sp,0
	sub_s	  sp,sp,124	
