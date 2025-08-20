
  .extern func_1
  .extern func_2
  .globl _start

_start:
  call func_1
  call func_2
  ret
