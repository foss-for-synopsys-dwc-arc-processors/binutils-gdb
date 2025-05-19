; Validate fld32: Loads a 32-bit value from the memory address and
; places it into the lower 32 bits of the destination floating-poing register.

; basic variants
  fld32  f4, [r1]                  ; base register only
  fld32  f4, [0x1338]              ; small limm, s9 = 0
  fld32  f6, [0x7fffffff]          ; large limm, s9 = 0
  fld32  f8, [-1024]               ; negative limm, s9 = 0

  fld32  f0, [r1,255]              ; max positive s9
  fld32  f2, [r4,-256]             ; min negative s9
  fld32  f10, [r2, -236]           ; valid negative offset
  fld32  f12, [r1, 127]            ; valid mid positive offset

; .a/.aw - pre-increment with write-back
  fld32.a     f0, [r1]
  fld32.a     f2, [r3,255]
  fld32.a     f4, [r5,-256]
  fld32.a     f6, [r7, 0]
  fld32.aw    f0, [r1]
  fld32.aw    f2, [r3,255]
  fld32.aw    f4, [r5,-256]
  fld32.aw    f6, [r7,0]

; .ab - post-increment with write-back
  fld32.ab    f0, [r1]
  fld32.ab    f2, [r3,-100]
  fld32.ab    f4, [r5,255]

; .as - scaled offset, no write-back
  fld32.as    f0, [r1]
  fld32.as    f2, [r3, 255]
  fld32.as    f4, [r5, -256]
  fld32.as    f6, [r7, 255]

