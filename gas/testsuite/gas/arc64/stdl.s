; 128-bit double stores

  stdl r4, [r1]                    ; stdl c,    [b]
  stdl r2, [0x1338]                ; stdl c,    [ximm]      ximm: default
  stdl r6, [0x7fffffff]            ; stdl c,    [ximm]      ximm: big
  stdl r2, [0x80000000]            ; stdl c,    [limm]      limm: positive
  stdl r0, [-1234]                 ; stdl c,    [ximm]      ximm: negative
  stdl 0x80000000, [r3]            ; stdl limm, [b]         limm: smallest
  stdl 0x7fffffff, [r3]            ; stdl ximm, [b]         ximm: biggest
  stdl     0x1234, [0x1234]        ; stdl ximm, [ximm]      ximm: equal
  stdl 0xf0f0f0f0, [0xf0f0f0f0]    ; stdl limm, [limm]      limm: equal

  stdl r0, [r1, 255]               ; stdl c,    [b, s9]     s9: biggest
  stdl r2, [r4,-256]               ; stdl c,    [b, s9]     s9: smallest
  stdl r4, [0x0       ,12]         ; stdl c,    [ximm,s9]   ximm: smallest
  stdl r6, [0x7fffffff,13]         ; stdl c,    [ximm,s9]   ximm: positive
  stdl r0, [0x80000000,14]         ; stdl c,    [limm,s9]   limm: smallest
  stdl     -42000, [r1,  255]      ; stdl ximm, [b, s9]     ximm: negative
  stdl 0x82345678, [r2, -256]      ; stdl limm, [b, s9]     limm: positive
  stdl     0x4321, [0x4321,13]     ; stdl ximm, [ximm,s9]   ximm: equal
  stdl 0xf0000000, [0xf0000000,31] ; stdl limm, [limm,s9]   limm: equal

  ; Now, repetition of instructions above with suffices (*.a/aw/ab/as)
 
  stdl.a r0, [r1,255]
  stdl.a r4, [r4,-256]
  stdl.a 0x82345678, [r2, -256]
  stdl.a     -42000, [r1, 255]
  
  stdl.aw r0, [r1,255]
  stdl.aw r2, [r4,-256]
  stdl.aw 0x82345678, [r2, -256]
  stdl.aw     -42000, [r1, 255]
  
  stdl.ab r0, [r1,255]
  stdl.ab r6, [r4,-256]
  stdl.ab 0x82345678, [r2, -256]
  stdl.ab     -42000, [r1, 255]
  
  stdl.as r0, [r1,255]
  stdl.as r4, [r4,-256]
  stdl.as r2, [-1024, 11]
  stdl.as 0x82345678, [r2, -256]
  stdl.as     -42000, [r1, 255]
  stdl.as 0x82345678, [r2, -256]
  stdl.as     0x4321, [0x4321,13]
  stdl.as 0xf0000000, [0xf0000000,31]
