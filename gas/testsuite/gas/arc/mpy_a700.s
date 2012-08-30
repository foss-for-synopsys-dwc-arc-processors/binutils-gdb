# @OC@ test

# Stay away from operands with duplicate arguments (eg:	add r0,r1,r1).
# They will be disassembled as they're macro counterparts (eg: asl r0,r1).

# general operations reg-reg
	@OC@ r0,r1,r2
	@OC@ r0,0xdeadbeef,r1
	@OC@ r0,r1,0xdeadbeef
	@OC@ 0,r1,r2
	@OC@ 0,0xdeadbeef,r1
	@OC@ 0,r1,0xdeadbeef
	@OC@ r0,0xdeadbeef,0xdeadbeef
	@OC@ 0,0xdeadbeef,0xdeadbeef

	@OC@.f r0,r1,r2
	@OC@.f r0,0xdeadbeef,r1
	@OC@.f r0,r1,0xdeadbeef
	@OC@.f 0,r1,r2
	@OC@.f 0,0xdeadbeef,r1
	@OC@.f 0,r1,0xdeadbeef
	@OC@.f r0,0xdeadbeef,0xdeadbeef
	@OC@.f 0,0xdeadbeef,0xdeadbeef

# general operations reg - u6
	@OC@ r0,r1,1
	@OC@ 0,r1,1
	@OC@ r0,0xdeadbeef,1
	@OC@ 0,0xdeadbeef,1

	@OC@.f r0,r1,1
	@OC@.f 0,r1,1
	@OC@.f r0,0xdeadbeef,1
	@OC@.f 0,0xdeadbeef,1

# general operations reg-s12
	@OC@ r0,r0,-1
	@OC@ 0,0xdeadbeef,-1

	@OC@.f r0,r0,-1
	@OC@.f 0,0xdeadbeef,-1

# general operations conditional reg-reg
#	@OC@ r1,r1,r2
#	@OC@ 0,0xdeadbeef,r1
#	@OC@ r1,r1,0xdeadbeef
#	@OC@ 0,0xdeadbeef,0xdeadbeef

	@OC@.z r1,r1,r2
	@OC@.z 0,0xdeadbeef,r1
	@OC@.z r1,r1,0xdeadbeef
	@OC@.z 0,0xdeadbeef,0xdeadbeef

	@OC@.z.f r1,r1,r2
	@OC@.z.f 0,0xdeadbeef,r1
	@OC@.z.f r1,r1,0xdeadbeef
	@OC@.z.f 0,0xdeadbeef,0xdeadbeef

# general operations conditional reg-u6
#	@OC@ r1,r1,2
#	@OC@ 0,0xdeadbeef,2

	@OC@.z r1,r1,2
	@OC@.z 0,0xdeadbeef,2

	@OC@.z.f r1,r1,2
	@OC@.z.f 0,0xdeadbeef,2
