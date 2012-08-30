# scond test - ARC700 4.10 extension instruction

	scond r0, [r1]
	scond r0, [0x1234abcd]
	scond r0, [0xcf]

	; cache bypass
	scond.di r0, [r1]
	scond.di r0, [0x1234abcd]
	scond.di r0, [0xcf]
