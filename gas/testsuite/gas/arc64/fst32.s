; Validate fst32: Stores a 32-bit value from the lower 32 bits of the designated
; floating-point source register to specified memory address.

; basic variants
  fst32  f4, [r1]                   # base register only
  fst32  f4, [0x1338]               # small limm, s9 = 0
  fst32  f6, [0x7fffffff]           # large limm, s9 = 0
  fst32  f8, [-1024]                # negative limm, s9 = 0

  fst32  f0, [r1,255]               # max positive s9
  fst32  f2, [r4,-256]              # min negative s9
  fst32  f10, [r2,-236]             # valid negative offset
  fst32  f12, [r1,127]              # valid mid positive offset

; .a/.aw - pre-increment with write-back
  fst32.a  f0, [r1,255]
  fst32.a  f2, [r3,-256]
  fst32.a  f4, [r5,0]
  fst32.aw  f0, [r1,255]
  fst32.aw  f2, [r3,-256]
  fst32.aw  f4, [r5,0]

; .ab - post-increment with write-back
  fst32.ab  f0, [r1,-100]
  fst32.ab  f2, [r3,255]

; .as - scaled offset, no write-back
  fst32.as  f0, [r1,255]
  fst32.as  f2, [r3,-256]
  fst32.as  f4, [r5,255]

