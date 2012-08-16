test:
	llock r0, [r1]
	scond r0, [r1]
	swape r0, r1

	llock r0, [0xdeadbeef]
	scond r0, [0xabcd1234]
	swape r0, 0xccddeeff
	swape r0, 0x12

	llock 0, [r1]
	swape 0, r1
	llock 0, [0xdeadbeef]
	swape 0, 0xccddeeff

	rtsc r0, 0

withdi:
	llock.di r0, [r1]
	scond.di r0, [r1]

	llock.di r0, [0xdeadbeef]
	scond.di r0, [0xabcd1234]

	llock.di 0, [r1]
	llock.di 0, [0xdeadbeef]

withf:
	swape.f r0, r1

	swape.f r0, 0xccddeeff
	swape.f r0, 0x12

	swape.f 0, r1
	swape.f 0, 0xccddeeff
