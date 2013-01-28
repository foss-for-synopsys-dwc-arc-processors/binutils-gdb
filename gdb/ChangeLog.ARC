2013-01-28  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* configure.tgt (arc*-*-linux*): Remove solib.o and corelow.o.
	* Makefile.in (HFILES_NO_SRCDIR): Add arc-tdep.h.
	* arc-linux-tdep.c: Updated copyright notice.
	(config/arc/tm-linux.h, arc-linux-tdep.h, arc-support.h): No
	longer included.
	(ARC_NR_PSEUDO_REGS, ARC_NR_REGS): Added from
	obsolete tm-linux.h, pending removal to XML.
	(arc_check_pc_defined, arc_convert_aux_contents_for_write): Deleted.
	* arc-linux-tdep.h: Deleted.
	* arc-tdep.c: Updated copyright notice. Converted Boolean to int
	throughout. Stripped out verbose main commenting. Used Doxygen
	compatible comments throughout. Used GNU formatting throughout.
	(ARC_BLINK_REGNUM, ARC_FP_REGNUM, ARC_SP_REGNUM)
	(BYTES_IN_REGISTER, BYTES_IN_WORD). Temporarily moved here,
	pending move to XML.
	(arc_local_var_t): Replace LocalVariable as type throughout, using
	int rather than Boolean.
	(arc_unwind_cache_t): Replace UnwindCache as type throughout.
	(DEBUG_COMMAND, SHOW_FRAME_COMMAND)
	(SHOW_FRAME_COMMAND_USAGE): Deleted.
	(arc_debug): Replace arc_debug_target throughout and type changed
	to int.
	(arc_print_frame_info): Replaces printFrameInfo and use
	fprint_unfiltered to gdb_stdlog instead of DEBUG.
	(DEBUG): Replaced by fprintf_unfiltered to gdb_stdlog, conditional
	on arc_debug throughout.
	(arc_debug_operand_type): Replaces ARC_Debugger_OperandType_Image.
	(arc_print_insn_state): Replaces printInsnState throughout.
	(arc_read_memory_for_disassembler): Replaces
	readm_memory_for_disassembler throughout.
	(arc_set_disassembler): Replaces set_disassembler throughout.
	(dummy_disassembler): Deleted.
	(arc_create_cache): Replaces create_cache throughout.
	(arc_find_prev_sp): Replaces find_previous_stack_pointer
	throughout.
	(arc_is_callee_saved): Replaces is_callee_saved_register
	throughout.
	(arc_is_in_prologue): Replaces is_in_prologue throughout.
	(arc_scan_prologue): Replaces scan_prologue throughout.
	(arc_initialize_disassembler): Replaces initialize_disassembler
	throughout.
	(arc_frame_unwind_cache): Replaces frame_unwind_cache throughout.
	(arc_extract_return_value): Replaces extract_return_value
	throughout.
	(ENTERMSG): Replaced by fprintf_unfiltered to gdb_stdlog,
	conditional on arc_debug throughout.
	(arc_store_return_value). Replaces store_return_value throughout.
	(arc_add_reggroups, arc_set_main_name): Deleted.
	(arc_gdb_init): Group frame sniffers after architecture generic
	gdbarch set up, put OSABI specific initialization last.
	(parse_frame_specification_1, find_variables)
	(find_local_variables, identify_frame)
	(arc_jtag_show_stack_frame_command): Deleted.
	(_initialize_arc_tdep): remove show-stack. Use
	add_setshow_zinteger_cmd to set ARC specific debug.

2012-12-12  Jeremy Bennett <jeremy.bennett@embecosm.com>

	Manual merge from GDB 6.8 branch.

	* ChangeLog.ARC, arc-architecture.c, arc-architecture.h,
	* arc-aux-registers.c, arc-aux-registers.h, arc-board.c,
	* arc-board.h, arc-embed.c, arc-gpio.c, arc-gpio.h,
	* arc-jtag-actionpoints.c, arc-jtag-actionpoints.h,
	* arc-jtag-fileio.c, arc-jtag-fileio.h, arc-jtag-ops.c,
	* arc-jtag-ops.h, arc-jtag-tdep.c, arc-jtag-tdep.h, arc-jtag.c,
	* arc-jtag.h, arc-linux-tdep.c, arc-linux-tdep.h,
	* arc-regnums-defs.h, arc-support.h, arc-tdep.c, arc-tdep.h,
	* features/arc-a5-cpu.xml, features/arc-aux-registers.dtd,
	* features/arc600-cpu.xml, features/arc700-cpu.xml,
	* regformats/reg-arc.dat: Merged as new files.
	* configure.tgt: Merged.

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

