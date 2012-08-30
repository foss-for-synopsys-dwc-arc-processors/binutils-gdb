# Test for the general arc700 instruction additions
.cpu ARC700


	sync

	rtie
	
	brk
	
	sleep


	trap_s 1

	trap0

# All the sleep variants
# ~~~~~~~~~~~~~~~~~~~~~~
	sleep
	sleep 0
	sleep 1
	sleep 2
	sleep 3
	sleep 4

	unimp_s

	ex r0,[r1]
	ex.di r0,[r1]
	ex r0,[0xdeadbeef]
	ex.di r0,[0xdeadbeef]
