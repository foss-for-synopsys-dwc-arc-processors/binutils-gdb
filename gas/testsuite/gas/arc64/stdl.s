# 128-bit stores

  stdl r0, [r1,255]               ; stdl c, [b, s9]      s9: biggest
  stdl r2, [r4,-256]              ; stdl c, [b, s9]      s9: smallest
  stdl r4, [0x1338]               ; stdl c, [limm]     limm: small positive
  stdl r6, [0x80000000]           ; stdl c, [limm]     limm: positive
  stdl r8, [-1024]                ; stdl c, [ximm]     ximm: negative
  stdl 0x12345678, [r2, -256]     ; stdl limm, [b, s9] limm: positive
  stdl     -42000, [r1, 255]      ; stdl ximm, [b, s9] ximm: negative

  ; Now, repetition of instructions above with suffices (*.a/aw/ab/as)
  
  stdl.a r0, [r1,255]
  stdl.a r2, [r4,-256]
  stdl.a 0x12345678, [r2, -256]
  stdl.a     -42000, [r1, 255]
  
  stdl.aw r0, [r1,255]
  stdl.aw r2, [r4,-256]
  stdl.aw 0x12345678, [r2, -256]
  stdl.aw     -42000, [r1, 255]
  
  stdl.ab r0, [r1,255]
  stdl.ab r2, [r4,-256]
  stdl.ab 0x12345678, [r2, -256]
  stdl.ab     -42000, [r1, 255]
  
  stdl.as r0, [r1,255]
  stdl.as r2, [r4,-256]
  stdl.as r4, [0x1338]
  stdl.as r6, [0x80000000]
  stdl.as r8, [-1024]
  stdl.as 0x12345678, [r2, -256]
  stdl.as     -42000, [r1, 255]
