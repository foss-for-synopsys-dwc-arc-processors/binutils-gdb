2013-03-05  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* linux-arc-low.c (arch_arc_setup): Convert offsets to byte
	offsets.
	(arc_fetch_register): Convert offset to byte offset.

2013-03-05  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* configure.srv (arc*-*-linux*): Add srv_usrregs for legacy.
	* linux-arc-low.c: Reorder functions for clarity and tidy up
	commenting generally.
	(struct user_regs_scratch): based on ptrace.h structs.
	(arc_arch_setup): Initalize register map for ARC v2 ABI.
	(arc_num_regs): Deleted and relaced by the_low_target.num_regs
	throughout.
	(arc_fetch_register, arc_breakpoint_at): New functions.
	(target_regsets): Correct field names.
	(the_low_target): Add entry for breakpoint_at and optionally
	fetch_register.

2013-03-04  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* linux-arc-low.c (arc_fill_regset): Use regbuf->scratch.ret
	rather than regbuf->reg.
	(arc_store_regset): Typo - use supply_register_by_name rather than
	collect_register_by_name for stop_pc.

2013-03-04  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* linux-arc-low.c (orig_r8) Deleted.
	(arc_cannot_store_register, arc_cannot_fetch_register): Updated to
	correctly reflect user space r/w status of registers.
	(arc_set_pc): Simplified - issues are dealt with in
	arc_fill_gregset and arc_store_gregset.
	(arc_fill_gregset, arc_store_gregset): No need for orig_r8 any
	more (it goes in ARV v3 ABI anyway).

2013-02-27  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* configure.srv (arc*-*-linux*): Remove srv_linux_usrregs and
	replace with srv_linux_regsets.
	* linux-arc-low.c: Commenting updated throughout.
	(regdef.h): Include file added.
	(../arc-constants.h, asm/trace.h): Include files removed
	(elf.h, linux/ptrace.h): Added.
	(ARC_NR_REGS): Removed throughout, replaced where appropriate by
	arc_num_regs.
	(arc_regmap): Removed.
	(struct user_regs_struct) [ARC_LEGACY_PTRACE_ABI]: Added
	conditionally to define struture, pending its adoption in mainline
	Linux.
	(orig_r8): Created to track latest value of orig_r8 register.
	(arc_num_regs): Created.
	(init_registers_arc): Declared as extern.
	(arc_arch_setup): Initialize arc_num_regs from regcache size.
	(arc_get_pc): Name of register is changed.
	(arc_set_pc): Rewritten to use new register structure.
	(arc_fill_gregset, arc_store_gregset): Created.
	(target_regsets): Created.
	(the_low_target): Reordered to omit obsolete functions and
	variables and use named elements.

2013-02-27  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* Makefile.in (SFILES): Correct location of common files.

2013-02-19  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* configure.srv (arc*-*-linux*): Add linux-osdata.o,
	linux-procfs.o and linux-ptrace.o to srv_tgt_obj.
	(arc*-*): Deleted.
	* linux-arc-low.c (init_registers_arc): Provide prototype.
	(arc_arch_setup): Created.
	(arc_get_pc): add regcache first argument, use in call to
	collect_register_by_name.
	(arc_set_pc): add regcache first argument, use in call to
	supply_register_by_name.
	(arc_reinsert_addr): allocate regcache and pass to
	collect_register_by_name.
	(the_low_target): Add arc_arch_setup, insert NULLs for new shape
	of structure.

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
