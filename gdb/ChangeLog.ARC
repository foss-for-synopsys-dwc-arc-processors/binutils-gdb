2012-12-12  Mischa Jonker  <mischa.jonker@synopsys.com>
	* arc-tdep.c: Fix printf format %llx to work correctly for both 32
	and 64 bit architectures (by using PRIx64 from inttypes.h)

2012-12-12  Mischa Jonker  <mischa.jonker@synopsys.com>
	* arc-linux-tdep.c (next_pc): Fix regression for 32 bit architectures.
	regcache_cooked_read_unsigned writes a ULONGEST instead of CORE_ADDR.
	On 32 bit hosts, CORE_ADDR is 32 bit, but ULONGEST is not.

2012-12-11  Mischa Jonker  <mischa.jonker@synopsys.com>
	* arc-linux-tdep.c (next_pc): Let debug print output both jump targets

2012-12-10  Noam Camus  <noamc@ezchip.com>
	* arc-linux-tdep.c (next_pc): Use regcache_cooked_read_unsigned
	instead of regcache_cooked_read. This fixes endianness issues.

2012-12-10  Mischa Jonker  <mischa.jonker@synopsys.com>
	* arc-linux-tdep.c (arc_linux_software_single_step): Fix single
	stepping when jumping to next instruction

2012-04-14  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* arc-linux-tdep.c (arc_linux_init_abi): Swap over breakpoint
	variables for endianness - wrong way round.

2012-04-03  Joern Rennecke  <joern.rennecke@embecosm.com>

	* arc-linux-tdep.c (be_breakpoint_instruction): New variable.
	(arc_linux_init_abi): Use it.

2010-03-02  Brendan Kehoe  <brendan@zen.org>

	* arc-embed.c (arc_jtag_show_stack_frame_command): Init
	PREVIOUS_WORD.

2010-09-28  Brendan Kehoe  <brendan@zen.org>

	* arc-tdep.c (arc_initialize_disassembler): Revert pre-2008 change
	which gave init_disassemble_info a NULL pointer for the
	fprintf_func member of struct disassemble_info, which can lead
	to a crash.
	* ChangeLog.ARC: New file.

