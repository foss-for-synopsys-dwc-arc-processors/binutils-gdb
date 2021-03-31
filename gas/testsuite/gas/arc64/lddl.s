# 128-bit loads

  ; Sometimes, there are "odd" numbered registers as the destination.
  ; They are intended to be that way, because such encoding is valid.
  ; However, the processor may raise an exception encountering them.
  ; Moreover, the assembler allows using writebacks (a/aw/ab) for
  ; immediates, which in practice has no effect.

  lddl r0, [r1,r2]               ; lddl a, [b, c]
  lddl r3, [r2,256]              ; lddl a, [b, limm]  (limm > s9)
  lddl r2, [r2,-257]             ; lddl a, [b, ximm]
  lddl r4, [0x80000000,r5]       ; lddl a, [limm, c]
  lddl r4, [-100,r5]             ; lddl a, [ximm, c]

  lddl r2, [r0]                  ; lddl a, [b, s9=0]
  lddl r6, [r7,255]              ; lddl a, [b, s9]    biggest s9
  lddl r6, [r7,-256]             ; lddl a, [b, s9]    smallest s9
  lddl r1, [0x13371338]          ; lddl a, [limm,s9=0]
  lddl r2, [0x80000000]          ; lddl a, [limm,s9=0]
  lddl r2, [-2147483648]         ; lddl a, [ximm,s9=0]
  
  ; Now, repetition of instructions above with suffices (*.a/aw/ab/as)

  lddl.a r0, [r1,r2]
  lddl.a r3, [r2,256]
  lddl.a r2, [r2,-257]
  lddl.a r4, [0x80000000,r5]
  lddl.a r4, [-100,r5]

  lddl.a r2, [r0]
  lddl.a r6, [r7,255]
  lddl.a r6, [r7,-256]
  lddl.a r4, [-256,r5]
  lddl.a r1, [0x13371338]
  lddl.a r2, [0x80000000]
  lddl.a r2, [-2147483648]

  lddl.aw r0, [r1,r2]
  lddl.aw r3, [r2,256]
  lddl.aw r2, [r2,-257]
  lddl.aw r4, [0x80000000,r5]
  lddl.aw r4, [-100,r5]

  lddl.aw r2, [r0]
  lddl.aw r6, [r7,255]
  lddl.aw r6, [r7,-256]
  lddl.aw r4, [-256,r5]
  lddl.aw r1, [0x13371338]
  lddl.aw r2, [0x80000000]
  lddl.aw r2, [-2147483648]
  
  lddl.ab r0, [r1,r2]
  lddl.ab r3, [r2,256]
  lddl.ab r2, [r2,-257]
  lddl.ab r4, [0x80000000,r5]
  lddl.ab r4, [-100,r5]

  lddl.ab r2, [r0]
  lddl.ab r6, [r7,255]
  lddl.ab r6, [r7,-256]
  lddl.ab r4, [-256,r5]
  lddl.ab r1, [0x13371338]
  lddl.ab r2, [0x80000000]
  lddl.ab r2, [-2147483648]

  lddl.as r0, [r1,r2]
  lddl.as r3, [r2,256]
  lddl.as r2, [r2,-257]
  lddl.as r4, [0x80000000,r5]
  lddl.as r4, [-100,r5]

  lddl.as r2, [r0]
  lddl.as r6, [r7,255]
  lddl.as r6, [r7,-256]
  lddl.as r4, [-256,r5]
  lddl.as r1, [0x13371338]
  lddl.as r2, [0x80000000]
  lddl.as r2, [-2147483648]
