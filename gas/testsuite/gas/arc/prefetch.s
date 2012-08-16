# Test for the general arc700 instruction additions
.cpu ARC700
	prefetch [r0,-1]
	prefetch [0xdeadbeef]
	prefetch [r0,r1]
	prefetch [r0,0xdeadbeef]
	prefetch [0xdeadbeef,r1]
