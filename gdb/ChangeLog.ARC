2013-01-31  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-linux-tdep.c, arc-linux-tdep.h, arc-tdep.c: Make
	non-executable.
	* arc-architecture.c, arc-elf-tdep.c: Format to
	GNU standard with indent and make non-executable.
	* arc-architecture.h, arc-aux-registers.c: Format to GNU standard
	with indent.
	* arc-aux-registers.h, arc-board.c, arc-board.h: Likewise.
	* arc-elf-tdep.h: Likewise.

2013-01-31  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-regnums-defs.h: Deleted.

2013-01-31  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-embed.c: Deleted.

2013-01-31  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-gpio.c, arc-gpio.h, arc-jtag-actionpoints.c: Deleted.
	* arc-jtag-actionpoints.h, arc-jtag-fileio.c: Likewise.
	* arc-jtag-fileio.h, arc-jtag-ops.c, arc-jtag-ops.h: Likewise.
	* arc-jtag.c, arc-jtag.h, arc-support.h: Likewise.
	* arc-elf-tdep.c: Renamed from arc-jtag-tdep.c.
	* arc-elf-tdep.h: Renamed from arc-jtag-tdep.h.
	* configure.tgt <arc*-*-*>: Remove redundant files from target.

2013-01-31  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-linux-tdep.c (arcAnalzerInstr, arc_debug): Move extern
	declarations to header.
	(arc_get_osabi): Created.
	* arc-tdep.c: Minor tidying up of comments and layout,
	(arc_gdb_init): Set info.osabi using arc_get_osabi.
	* arc-tdep.h (arcAnalzerInstr, arc_debug, arc_get_osabi): Add
	extern declarations.

2013-01-30  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-tdep.c (arc_dummy_disassembler): Created.
	(arc_gdbarch-init): set arc_dummy_disassembler as default.

2013-01-30  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-linux-tdep.c: General tidy up of commenting.
	(arc_linux_core_reg_offsets): Renamed from
	arcompact_linux_core_reg_offsets.
	(arc_linux_binutils_reg_to_regnum): Moved to start of file to
	avoid need for forward declaration. Renamed from
	binutils_reg_to_regnum.
	(arc_linux_next_pc): Renamed from next_pc. Move declarations of
	lp_end, lp_start, lp_count and status32 to start of function.
	(arc_linux_supply_gregset): Renamed from
	arcompact_linux_supply_gregset and merged with supply_gregset.
	(supply_gregset): Merged into arc_linux_supply_gregset.
	(arc_linux_is_sigtramp): Renamed from is_linux_sigtramp.
	(arc_linux_sigcontext_addr): Renamed from linux_sigcontext_addr.
	(arc_linux_register_reggroup_p): Renamed from register_reggroup_p.
	(arc_linux_pseudo_register_read): Restructured.
	(arc_linux_regset_from_core_section): Define arch field.
	(arc_linux_init_abi): Tidied up code.

2013-01-30  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-linux-tdep.c (ARC_NR_ALL_REGS): Defined for convenience.
	(next_pc): Typos and missing args corrected, use ULONGEST for reg
	reads.
	(arcompact_linux_supply_gregset): Replace ELEMENTS_IN_ARRAY by
	array size.
	(is_linux_sigtramp): Use gdbarch functions to unwind PC.
	(arc_linux_pseudo_register_read): Set a return result, restructure
	code.
	(arc_linux_register_name): Replace ELEMENTS_IN_ARRAY by array size
	and simplify code.
	(arc_linux_software_single_step): Recode to use address space.
	(arc_linux_skip_solib_resolver): Correct call to
	lookup_symbol_global, correct missing argument to
	print_core_address.
	(arc_linux_init_abi): Replace ELEMENTS_IN_ARRAY by array size.
	* arc-tdep.h (ARC_BTA_REGNUM, ARC_LP_START_REGNUM)
	(ARC_LP_END_REGNUM, ARC_LP_COUNT_REGNUM, ARC_STATUS32_REGNUM)
	(ARC_EFA_REGNUM, ARC_RET_REGNUM, ARC_ORIG_R8_REGNUM)
	(ARC_STOP_PC_REGNUM, ARC_ERET_REGNUM, ARC_STATUS32_L1_REGNUM)
	(ARC_STATUS32_L2_REGNUM, ARC_ERSTATUS_REGNUM): Define.

2013-01-30  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-tdep.c, arc-tdep.h: Corrected C++ style comments throughout.
	* arc-linux-tdep.c: Corrected C++ style comments throughout.
	(arc_debug): Added extern declaration.
	(next_pc): Replace DEBUG macro, updating print structure. Correct
	argument type for callto regcache_cooked_read_unsigned
	(arc_linux_skip_solib_resolver). Correct types for printf.

2013-01-30  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-tdep.c (arc_print_frame_info): Use print_core_address to
	print CORE_ADDR values, use phex for saved addresses.
	(arc_unwind_pc, arc_unwind_sp): Use CORE_ADDR throughout and
	print_core_address to print values.
	(arc_find_this_sp): Use phex to print hex values.
	(arc_scan_prologue, arc_push_dummy_call): Use print_core_address
	to print CORE_ADDR values.
	(arc_extract_return_value, arc_store_return_value): Use phex to
	print hex values.
	* arc-tdep.h (BYTES_IN_ADDRESS): Added.

2013-01-30  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-linux-tdep.c: Remove superfluous general comments.
	(gdbarch.h): Included after degs.h.
	(ARC_NR_REGS): Updated with explicit value.
	(Boolean): Replace with int throughout.
	(next_pc): Add gdbarch argument to arc_initialize_disassembler.

2013-01-29  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* Makefile.in: change golang.h to go-lang.h.
	* arc-tdep.c (frame-base.h): Included.
	(arc_create_cache): Use this_frame rather than next_frame.
	(arc_unwind_sp): Correct typo.
	(arc_frame_base_address): Created.
	(arc_find_this_sp): Replaces arc_find_prev_sp, and uses this_frame
	rather than next_frame.
	(arc_scan_prologue): Use this_frame rather than next_frame,
	recoding as required.
	(arc_frame_cache): Replaces arc_frame_unwind_cache. Remove code
	relating to stopping backtrace.
	(arc_extrac_return_value): Add (unused) function argument.
	(arc_extract_return_value, arc_store_return_value): Add gdbarch as
	first argument.
	(arc_register_type): Use builtin_type function.
	(arc_frame_this_id): Use this_frame rather than next_frame,
	recoding as required.
	(arg_frame_prev_register) Use this_frame rather than next_frame,
	recoding as required. Remove extra arguments and return structure.
	(arc_frame_sniffer): Deleted.
	(arc_dummy_id): Replaces arc_unwind_dummy_id and uses this_frame
	rather than next_frame.
	(arc_sigtramp_frame_cache, arg_sigtramp_frame_id): Use this_frame
	rather than next_frame, recoding as required.
	(arg_sigtramp_frame_prev_register) Use this_frame rather than
	next_frame, recoding as required. Remove extra arguments and
	return structure.
	(arc_sigtramp_frame_unwind, arc_frame_unwind)
	(arc_sigtramp_frame_base_sniffer, arc_frame_base_sniffer):
	Created.
	(arc_gdbarch_init): Updated gdbarch functions to match changes
	above. Remove frame_unwind_append_sniffer and add
	frame_unwind_append_unwinder and frame_base_append_sniffer
	calls. Add DWARF2 unwinder and sniffer.
	(arc_initialize_disassembler): Add gdbarch as first argument.
	* arc-tdep.h (ARC_ENTRY_DEBUG): Use GCC ## extension.
	(ARC_ILINK1_REGNUM, ARC_ILINK2_REGNUM): Adde definitions.
	(arg_initialize_disassembler): Update prototype to match
	implementation.

2013-01-29  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-tdep.c (ARC_BLINK_REGNUM, ARC_FP_REGNUM, ARC_SP_REGNUM)
	(BYTES_IN_REGISTER, BYTES_IN_WORD): Transferred to arc-tdep.c.
	(arc_unwind_pc, arc_unwind_sp): Moved earlier in file, added
	Doxygen commenting, and rewritten for clarity.
	(arc_find_prev_sp): Use arc_unwind_sp, rather than
	frame_unwind_register_unsigned.
	(arc_scan_prologue): Reorder entry debug logging, use
	arc_unwind_pc.
	(arc_unwind_dummy_id): Use arc_unwind_pc instead of
	frame_pc_unwind.
	(arc_sigtramp_frame_cache): Use arc_unwind_sp instead of
	frame_unwind_register.
	* arc-tdep.h (ARC_BLINK_REGNUM, ARC_FP_REGNUM, ARC_SP_REGNUM)
	(BYTES_IN_REGISTER, BYTES_IN_WORD): Transferred from arc-tdep.c.

2013-01-29  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-tdep.c (arc_find_prev_sp, arc_scan_prologue)
	(arc_frame_unwind_cache, arc_extract_return_value)
	(arc_store_return_value, arc_skip_prologue, arc_frame_this_id)
	(arc_frame_prev_register, arc_return_value)
	(arc_sigtramp_frame_cache, arc_sigtramp_frame_this_id)
	(arc_sigtramp_frame_prev_register, arc_sigtramp_frame_sniffer)
	(arc_push_dummy_call): Replace entry debug code with
	ARC_ENTRY_DEBUG macro.
	* arc-tdep.h (ARC_ENTRY_DEBUG): Created.

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

