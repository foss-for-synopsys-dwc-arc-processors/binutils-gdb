# @OC@ test

# Stay away from operands with duplicate arguments (eg:	add r0,r1,r1).
# They will be disassembled as they're macro counterparts (eg: asl r0,r1).

# reg,reg,reg
	@OC@ r0,r1,r2	
	@OC@.f r0,r1,r2

	@OC@ r0,r1,1
	@OC@.f r0,r1,1

	@OC@ r1,r1,-1
	@OC@.f r1,r1,-1

	@OC@ r1,r1,r2
	@OC@.f r1,r1,r2	
	@OC@.z r1,r1,r2
	@OC@.z.f r1,r1,r2

	@OC@ r1,r1,2
	@OC@.f r1,r1,2	
	@OC@.z r1,r1,2
	@OC@.z.f r1,r1,2

	@OC@ r1,0xdeadbeef,r2
	@OC@.f r1,0xdeadbeef,r2	

	@OC@ r1,r2,0xdeadbeef
	@OC@.f r1,r2,0xdeadbeef
	
	@OC@ r1,r1,0xdeadbeef
	@OC@.f r1,r1,0xdeadbeef
	@OC@.z r1,r1,0xdeadbeef
	@OC@.z.f r1,r1,0xdeadbeef

	@OC@ 0,r1,r2
	@OC@.f 0,r1,r2

	@OC@ 0,r1,2
	@OC@.f 0,r1,2

	@OC@ 0,0xdeadbeef,r1
	@OC@.f 0,0xdeadbeef,r1
	@OC@.z 0,0xdeadbeef,r1
	@OC@.z.f 0,0xdeadbeef,r1
