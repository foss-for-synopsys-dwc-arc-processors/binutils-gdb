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

