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
