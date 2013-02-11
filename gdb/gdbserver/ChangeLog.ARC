2013-02-11  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* linux-arc-low.c: Use arc-tdep.h rather than tm-linux.h as
	header.

2012-12-12  Jeremy Bennett <jeremy.bennett@embecosm.com>

	Manual merge from GDB 6.8 branch.

	* linux-arc-low.c: Merged as new file.
	* Makefile.in, configure.src: Merged.

2012-12-11  Noam Camus  <noamc@ezchip.com>

	* linux-arc-low.c <arc_breakpoint>: Define as short not long.
	(arc_breakpoint_at): Use short for insn, not long.

2012-12-10  Mischa Jonker  <mischa.jonker@synopsys.com>

	* linux-low.c: Adapt debug print for writing up to 4 bytes to
	handle big endian as well. (support for 3 bytes dropped)

2012-09-21  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* linux-arc-low.c: Fix comment typo.
	* linux-low.c: Backport fix for debug of writing to show up to 4
	bytes.

2012-08-17  Vineet Gupta  <vgupta@synopsys.com>

	* linux-arc-low.c: <arc_regmap> updated per Linux 3.2 kernel pt_regs
	layout change

2012-04-14  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* server.c (main): Response to 'X' for zero length packet should
	be null, not error, to indicate "not-supported".

2012-02-16  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* linux-arc-low.c: Include config/arc/tm-linux.h to pick up
	constants from main GDB.
	<arc_num_regs>: Replace throughout by ARC_NR_REGS.
	(arc_cannot_store_register): Use symbolic register names.
	(arc_cannot_fetch_register): Check for negative value.
	<debug_threads>: Removed extern definition (this is provided in
	server.h).

2012-01-27  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* linux-arc-low.c: Include asm/ptrace.h instead of linux/user.h
	<OFFSET>: macro deleted.
	<arc_regmap>: rewritten to use ptrace offsets.
	* build_gdbserver.sh: Deleted.
	* ChangeLog.ARC: New file.
