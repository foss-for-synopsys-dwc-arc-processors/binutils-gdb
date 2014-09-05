	.cpu ARC700

# subsdw test

# Stay away from operands with duplicate arguments (eg:	add r0,r1,r1).
# They will be disassembled as they're macro counterparts (eg: asl r0,r1).

# reg,reg,reg
	subsdw r0,r1,r2
	subsdw.f r0,r1,r2

	subsdw r0,r1,1
	subsdw.f r0,r1,1

	subsdw r1,r1,-1
	subsdw.f r1,r1,-1

	subsdw r1,r1,r2
	subsdw.f r1,r1,r2
	subsdw.z r1,r1,r2
	subsdw.z.f r1,r1,r2

	subsdw r1,r1,2
	subsdw.f r1,r1,2
	subsdw.z r1,r1,2
	subsdw.z.f r1,r1,2

	subsdw r1,0xdeadbeef,r2
	subsdw.f r1,0xdeadbeef,r2

	subsdw r1,r2,0xdeadbeef
	subsdw.f r1,r2,0xdeadbeef

	subsdw r1,r1,0xdeadbeef
	subsdw.f r1,r1,0xdeadbeef
	subsdw.z r1,r1,0xdeadbeef
	subsdw.z.f r1,r1,0xdeadbeef

	subsdw 0,r1,r2
	subsdw.f 0,r1,r2

	subsdw 0,r1,2
	subsdw.f 0,r1,2

	subsdw 0,0xdeadbeef,r1
	subsdw.f 0,0xdeadbeef,r1
	subsdw.z 0,0xdeadbeef,r1
	subsdw.z.f 0,0xdeadbeef,r1

	subsdw 0,0xdeadbeef,-56
