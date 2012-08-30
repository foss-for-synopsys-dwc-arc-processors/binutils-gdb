# @OC@ test

# Stay away from operands with duplicate arguments (eg:	add r0,r1,r1).
# They will be disassembled as they're macro counterparts (eg: asl r0,r1).

# reg,reg,reg
	@OC@ r0,r1
	@OC@ r0,2
	@OC@ r0,0xdeadbeef

	@OC@ 0,r1
	@OC@ 0,2
	@OC@ 0,0xdeadbeef

	@OC@.f r0,r1
	@OC@.f r0,2
	@OC@.f r0,0xdeadbeef

	@OC@.f 0,r1
	@OC@.f 0,2
	@OC@.f 0,0xdeadbeef
