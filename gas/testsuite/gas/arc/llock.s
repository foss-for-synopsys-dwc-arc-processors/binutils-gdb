# llock test - ARC700 4.10 extension instruction

	llock r0, [r1]
	llock r0, [0x1234abcd]

	llock  0, [r0]
	llock  0, [0x1234abcd]

	; cache bypass
	llock.di r0, [r1]
	llock.di r0, [0x1234abcd]
	llock.di  0, [r1]
	llock.di  0, [0x1234abcd]
