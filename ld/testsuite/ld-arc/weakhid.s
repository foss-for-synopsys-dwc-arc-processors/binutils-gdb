 .weak xweakobj
 .weak xweakhidobj
 .hidden xweakhidobj

 .data
 .global x
 .type	x,@object
x:
 .word xweakhidobj
 .word xweakobj
 .word xregobj
.Lfe1:
 .size	x,.Lfe1-x
