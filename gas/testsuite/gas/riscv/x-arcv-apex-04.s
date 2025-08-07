  .extInstruction foo0,1,XS
  .extInstruction foo1,1,XI
  .extInstruction foo2,1,XC

  foo0	a0,a1,-128
  foo0	a0,a1,127
  foo1	a0,-2048
  foo1	a0,2047
  foo2	a0,a0,-2048
  foo2	a0,a0,2047
