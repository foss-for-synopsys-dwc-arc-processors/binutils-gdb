.extInstruction foo0,1,XS
.extInstruction foo1,2,XI
.extInstruction foo2,3,XC

#XS
#pass 
  foo0	a0,a1,-128
  foo0	a0,a1,127
  foo0	a0,a1,-127
  foo0	a0,a1,126

#XI
#pass 
  foo1	a0,-2048
  foo1	a0,2047
  foo1	a0,-2048
  foo1	a0,2047

#XC
#pass 
  foo2	a1,a1,-2048
  foo2	a1,a1,2047
  foo2	a1,a1,-2048
  foo2	a1,a1,2047
