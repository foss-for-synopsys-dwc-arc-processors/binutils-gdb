2013-08-26	Anton Kolesov <akolesov@synopsys.com>

	* arc-tdep.c (arc_frame_this_id): Return correct frame code address
	without full debug symbols

2013-05-22  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-linux-tdep.c (arc_linux_is_sigtramp): Correct sizing of buf.
	* ChangeLog.ARC: Fix errors in the record.

2013-05-22  Vineet Gupta <vgupta@synopsys.com>

	* arc-linux-tdep.c (arc_linux_is_sigtramp): Fix signature of
	signal trampoline

2013-04-26  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-elf-tdep.c: Make simulator header inclusion dependent on
	WITH_SIM.
	(arc_elf_sim_map): Only define if WITH_SIM is defined.
	(arc_gdbarch_osabi_init): Only call arc_set_register_mapping if
	WITH_SIM is defined.

2013-04-18  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-elf-tdep.c (arc_push_memory_call): Do not change endianness
	of args when pushing (already done), add more debug for arg
	handing.

2013-03-25  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-elf-tdep.c (arc_elf_breakpoint_from_pc): New function based
	on old arc_breakpoint_from_pc, but using BRK_S.
	(arc_gdbarch_osabi_init): Add call to arc_elf_breakpoint_from_pc.
	* arc-linux-tdep.c (arc_linux_breakpoint_from_pc): New function based
	on old arc_breakpoint_from_pc.
	(arc_gdbarch_osabi_init): Add call to arc_linux_breakpoint_from_pc.
	* arc-tdep.c (arc_breakpoint_from_pc): Deleted.
	(arc_gdbarch_init): Delete call to arc_breakpoint_from_pc.

2013-03-22  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-linux-tdep.c (arc_gdbarch_osabi_init): Correct prototype.

2013-03-21  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-elf-tdep.c: Include simulator register header.
	(arc_elf_sim_map): New function.
	(arc_gdbarch_osabi_init): Set simulator register mapping.
	* arc-tdep.h: Add simulator register numbers for aux regs.

2013-03-20  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* configure.tgt (arc*-*-*): Remove unneeded source files.
	* Makefile.in (HFILES_NO_SRCDIR): Remove unneeded ARC headers.
	* arc-aux-registers.c: Deleted.
	* arc-aux-registers.h: Deleted.
	* arc-board.c: Deleted.
	* arc-board.h: Deleted.
	* arc-elf-tdep.c: Update commenting.
	(_initialize_arc_elf_tdep): Deleted.
	(arc_gdbarch_osabi_init): Renamed from arc_elf_init_abi and params
	changed.
	* arc-linux-tdep.c (arc_gdbarch_osabi_init): Renamed from
	arc_linux_init_abi and params changed.
	(_initialize_arc_linux_tdep): Deleted.
	* arc-tdep.c (arc_gdbarch_init): Replace call to
	gdbarch_init_osabi by call to arc_gdbarch_osabi_init.
	* arc-tdep.h (arc_gdbarch_osabi_init): Replaces arc_get_osabi.

2013-03-17  Joern Rennecke  <joern.rennecke@embecosm.com>

	* arc-tdep.c, arc-linux-tdep.c: Reflect header file name change from
	arc-dis.h to arc-dis-old.h .

2013-03-13  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-tdep.c (arc_scan_prologue): Add GDBARCH parameter. No need
	to get pc_regnum.
	(arc_skip_trampoline_code): Return PC as result.
	(arc_print_float_info): Correct type of parameters.

2013-03-13  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-tdep.c (arc_frame_unwind, arg_sigtramp_frame_unwind): set
	.stop_reason field.

2013-03-07  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-tdep.c (arc_gdbarch_init): set decr_pc_after_break to 2.

2013-03-06  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-aux-registers.c (arc_processor_version, arc_reg_access): New
	enums taken from arc-tdep.h.
	(arc_core_reg_def, arc_aux_reg_def, arc_reg_info)
	(arc_variant_info): New structs taken from arc-tdep.h.
	(arc_processor_variant_info): New static instance, renamed and
	moved out of _initialize_aux_regs.
	(INFO_OF): Use arc_processor_variant_info.
	(arc_create_variant_info): New function taken from arc_elf_tdep.c.
	(_initialize_arc_aux_regs): Remove declaration of variant, call
	arc_create_variant_info.
	* arc-elf-tdep.c (arc_elf_init_abi): Don't set
	pc_regnum_in_sigcontext, lowest_pc, breakpoint_instr,
	breakpoint_size. Don't call create_variant_info, since now done in
	arc-aux-registers.c.
	* arc-linux-tdep.c (arc_linux_init_abi): Don't set lowest_pc,
	arc_processor_variant_info, breakpoint_instr, breakpoint_size.
	* arc-tdep.c (arc_sigtramp_frame_prev_register): Don't try to use
	"ret" register for PC.
	(arc_breakpoint_from_pc): Determine directly, don't use tdep.
	(arc_register_name): Don't name registers not in the architecture.
	(arc_register_type): PC should be func_ptr type.
	(arc_print_registers_info): Correct logic for all registers.
	* arc-tdep.h (gdbarch_tdep): Remove pc_regnum_in_sigcontext,
	lowest_pc, arc_processor_variant_info, breakpoint_instr,
	breakpoint_size

2013-03-06  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-tdep.h (ARC_ENTRY_DEBUG): Don't print the filename.

2013-03-05  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-linux-tdep.c (SIGTRAMP_INSNS_LENGTH): Deleted.
	(arc_sigtramp_insns): Moved into arc_linux_is_sigtramp.
	(arc_linux_is_sigtramp): Define arc_sigtramp_insns locally,
	replace SIGTRAMP_INSNS_LENGTH with sizeof. Make endian friendly.
	(arc_linux_sigcontext_addr): Use THIS frame.

2013-03-04  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-elf-tdep.c (arc_elf_cannot_fetch_register)
	(arc_elf_cannot_store_register): Remove osabi.
	* arc-linux-tdep.c (arc_linux_cannot_fetch_register)
	(arc_linux_cannot_store_register): Remove osabi.

2013-03-04  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* regformats/reg-arc.dat: Updated to match GDB register sequence.

2013-03-04  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-elf-tdep.c (arc_elf_cannot_fetch_register)
	(arc_elf_cannot_store_register): Created.
	(arc_elf_init_abi): Add calls to set gdbarch_cannot_fetch_register
	and gdbarch_cannot_store_register.
	* arc-linux-tdep.c (arc_linux_cannot_fetch_register)
	(arc_linux_cannot_store_register): Created.
	(arc_linux_init_abi): Add calls to set
	gdbarch_cannot_fetch_register and gdbarch_cannot_store_register.
	* arc-tdep.c (arc_cannot_fetch_register)
	(arc_cannot_store_register, arc_dummy_disassembler)
	(arc_set_disassembler): Deleted.
	(arc_skip_trampoline_code): New function.
	(arc_gdbarch_init): Remove calls to set
	gdbarch_cannot_fetch_register and
	gdbarch_cannot_store_register. No need for observer to set
	disassembler, since we now only support ARCompact.
	Set gdbarch_skip_trampoline_code. Set non-steppable watchpoints.

2013-03-03  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-aux-registers.c (arc_aux_register_count): Replace
	ARC_NUM_STANDARD_CORE_REGS with ARC_NUM_STD_CORE_REGS.
	* arc-elf-tdep.c (arc_elf_init_abi): Don't set tdep
	register_reggroupt_p. Don't set gdbarch_num_regs or
	gdbarch_num_pseudo_regs. Don't set DWARF2 reg number translater
	(no longer needed). Don't call gdbarch_register_names. Don't set
	gdbarch_print_registers_info. Don't set
	gdbarch_cannot_store_register.
	(arc_elf_register_reggroup_p, arc_elf_binutils_reg_to_regnum)
	(register_names, arc_elf_register_name, print_one_aux_register)
	(arc_elf_print_registers_info, PRINT, PRINT_HW, PRINT_BY_NAME)
	(arc_elf_cannot_store_register, ARC_NR_REGS, ARC_NR_PSEUDO_REGS)
	(WATCH_MEMORY_COMMAND, BREAK_MEMORY_COMMAND, FILL_MEMORY_COMMAND)
	(WATCH_MEMORY_COMMAND_USAGE, BREAK_MEMORY_COMMAND_USAGE)
	(FILL_MEMORY_COMMAND_USAGE): Deleted.
	* arc-linux-tdep.c (register_names): Size is now ARC_TOTAL_REGS.
	(arc_linux_sc_reg_offset, arc_linux_core_reg_offsets): Size is now
	ARC_NUM_REAL_REGS.
	(arc_linux_supply_gregset): Use ARC_NUM_REAL_REGS.
	(arc_linux_init_abi): Use ARC_NUM_REAL_REGS and
	ARC_NUM_PSEUDO_REGS. Don't set tdep register_reggroupt_p. Don't
	set gdbarch_write_pc. Don't set gdbarch_num_regs or
	gdbarch_num_pseudo_regs. Don't set
	gdbarch_print_registers_info. Don't set
	gdbarch_cannot_store_register. Don't set
	gdbarch_decr_pc_after_break. Set
	gdbarch_fetch_tls_load_module_address.
	(arc_linux_write_pc, register_names, arc_linux_register_name)
	(arc_linux_print_registers_info, PRINT)
	(arc_linux_cannot_store_register): Deleted.
	* arc-tdep.c (arc_round_up_to_words): Add gdbarch as an argument
	to allow for future development.
	(arc_is_in_prologue): replace IS_ARGUMENT_REGISTER with its
	definition.
	(arc_scan_prologue): Replace MAX_PROLOGUE_LENGTH by its
	definition.
	(arc_register_type): Fully type all registers.
	(arc_frame_align): Used gdbarch_ptr_bit rather than BYTES_IN_WORD.
	(arc_virtual_frame_pointer, arc_register_name)
	(arc_push_dummy_code, arc_print_registers_info)
	(arc_print_float_info, arc_cannot_fetch_register)
	(arc_cannot_store_register, arc_get_longjmp_target): New functions.
	(arc_gdbarch_init): Reorganize to match gdbarch.h, remove
	obsolete/unecessary functions, add new functions, mostly
	transferred from ELF and Linux specific versions. Define OSABI
	before allocating gdbarch.
	* arc-tep.h (ARC_NUM_STD_CORE_REGS): Replaces
	ARC_NUM_STANDARD_CORE_REGS.
	(ARC_AUX_LP_START_REGNUM, ARC_AUX_LP_END_REGNUM)
	(ARC_AUX_PC_REGNUM, ARC_AUX_STATUS32_REGNUM)
	(ARC_AUX_STATUS32_L1_REGNUM, ARC_AUX_STATUS32_L2_REGNUM)
	(ARC_AUX_AUX_IRQ_LV12_REGNUM, ARC_AUX_AUX_IRQ_LEV_REGNUM)
	(ARC_AUX_AUX_IRQ_HINT_REGNUM, ARC_AUX_ERET_REGNUM)
	(ARC_AUX_ERBTA_REGNUM, ARC_AUX_ERSTATUS_REGNUM)
	(ARC_AUX_ECR_REGNUM, ARC_AUX_EFA_REGNUM, ARC_AUX_ICAUSE1_REGNUM)
	(ARC_AUX_ICAUSE2_REGNUM, ARC_AUX_AUX_IENABLE_REGNUM)
	(ARC_AUX_AUX_ITRIGGER_REGNUM, ARC_AUX_BTA_REGNUM)
	(ARC_AUX_BTA_L1_REGNUM, ARC_AUX_BTA_L2_REGNUM)
	(ARC_AUX_AUX_IRQ_PULSE_CANCEL_REGNUM)
	(ARC_AUX_AUX_IRQ_PENDING_REGNUM): Defined for aux registers
	supported.
	(ARC_LP_START_REGNUM, ARC_LP_END_REGNUM, ARC_PC_REGNUM)
	(ARC_STATUS32_REGNUM, ARC_STATUS32_L1_REGNUM)
	(ARC_STATUS32_L2_REGNUM, ARC_AUX_IRQ_LV12_REGNUM)
	(ARC_AUX_IRQ_LEV_REGNUM, ARC_AUX_IRQ_HINT_REGNUM, ARC_ERET_REGNUM)
	(ARC_ERBTA_REGNUM, ARC_ERSTATUS_REGNUM, ARC_ECR_REGNUM)
	(ARC_EFA_REGNUM, ARC_ICAUSE1_REGNUM, ARC_ICAUSE2_REGNUM)
	(ARC_AUX_IENABLE_REGNUM, ARC_AUX_ITRIGGER_REGNUM, ARC_BTA_REGNUM)
	(ARC_BTA_L1_REGNUM, ARC_BTA_L2_REGNUM)
	(ARC_AUX_IRQ_PULSE_CANCEL_REGNUM, ARC_AUX_IRQ_PENDING_REGNUM):
	Deleted.
	(ARC_IS_ARC_REG): Deleted.
	(MAX_PROLOGUE_LENGTH): Deleted.
	(ARC_NUM_REAL_REGS): Replaces ARC_NUM_REGS.
	(gdbarch_tdep): Remove register_reggroup_p field.
	(ARC_PC_REGNUM): Renamed from ARC_STOP_GO_REGNUM and now a raw,
	not pseudo register.
	(ARC_UCLIBC_JB_PC, ARC_NEWLIB_JB_PC): Created.
	* doxygen.config: Print static function details.

2013-02-28  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-aux-registers.c (start_ecr). Replace IS_EXTENSION_CORE_REGISTER.
	(arc_initialize_aux_reg_info, arc_core_register_number): Replace
	ARC_FIRST_EXTENSION_CORE_REGISTER by ARC_FIRST_EXT_CORE_REGNUM and
	ARC_LAST_EXTENSION_CORE_REGISTER by ARC_LAST_EXT_CORE_REGNUM.
	* arc-tdep.c (arc_is_in_prologue): Replace ARC_ABI_FRAME_POINTER
	by ARC_FP_REGNUM and ARC_ABI_STACK_POINTER by ARC_SP_REGNUM.
	(arc_print_frame_info, arc_find_this_sp, arc_is_callee_saved):
	Replace ARC_ABI_FIRST_CALLEE_SAVED_REGISTER by
	ARC_FIRST_CALLEE_SAVED_REGNUM and ARC_ABI_LAST_CALLEE_SAVED_REGISTER by
	ARC_LAST_CALLEE_SAVED_REGNUM.
	(push_dummy_call): Replace ARC_ABI_FIRST_ARGUMENT_REGISTER by
	ARC_FIRST_ARG_REGNUM and ARC_ABI_LAST_ARGUMENT_REGISTER by
	ARC_LAST_ARG_REGNUM.
	(arc_extract_return_value, arc_store_return_value): Replace
	ARC_ABI_RETURN_REGNUM by ARC_RET_REGNUM, ARC_ABI_RETURN_LOW_REGNUM
	by ARC_RET_LOW_REGNUM and ARC_ABI_RETURN_REGNUM by
	ARC_RET_HIGH_REGNUM.
	(arc_unwind_cache_t): Replaced by struct arc_unwind_cache.
	(arc_push_blink, arc_is_push_blink_fi, arc_is_push_fp_fi)
	(arc_is_update_fp_fi, arc_is_sub_sp_fi, arc_print_frame_info)
	(arc_create_cache, arc_find_this_sp, arc_is_callee_saved)
	(arc_is_in_prologue, arc_scan_prologue, arc_frame_cache)
	(arc_frame_prev_register, arc_sigtramp,frame_cache)
	(arc_sigtramp_frame_prev_register): Replace arc_unwind_cache_t by
	struct arc_unwind_cache.
	* arc-tdep.h (ARC_ABI_GLOBAL_POINTER, ARC_ABI_FRAME_POINTER)
	(ARC_ABI_STACK_POINTER): Deleted.
	(ARC_FIRST_CALLEE_SAVED_REGNUM): Replaces
	ARC_ABI_FIRST_CALLEE_SAVED_REGISTER.
	(ARC_LAST_CALLEE_SAVED_REGNUM): Replaces
	ARC_ABI_LAST_CALLEE_SAVED_REGISTER.
	(ARC_FIRST_ARG_REGNUM): Replaces ARC_ABI_FIRST_ARGUMENT_REGISTER.
	(ARC_LAST_ARG_REGNUM): Replaces ARC_ABI_LAST_ARGUMENT_REGISTER.
	(ARC_RET_REGNUM): Replaces ARC_ABI_RETURN_REGNUM.
	(ARC_RET_LOW_REGNUM): Replaces ARC_ABI_RETURN_LOW_REGNUM.
	(ARC_RET_HIGH_REGNUM): Replaces ARC_ABI_RETURN_HIGH_REGNUM.
	(ARC_FIRST_EXT_CORE_REGNUM): Replaces
	ARC_FIRST_EXTENSION_CORE_REGISTER.
	(ARC_LAST_EXT_CORE_REGNUM): Replaces
	ARC_LAST_EXTENSION_CORE_REGISTER.
	(ARC_NUM_EXT_CORE_REGS): Replace ARC_NUM_EXTENSION_CORE_REGS

2013-02-28  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-tdep.c: Added GFDL license and updated commments
	(arc_local_var_t): Deleted.
	* arc-tdep.h: Added more Doxygen compatible commenting. Removed
	AUX registers addresses.
	(ARC_STOP_GO_REGNUM): Added as pseudo reg.

2013-02-27  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* Makefile.am (HFILES_NO_SRCDIR): Updated with ARC header files.
	* arc-aux-registers.c: Replace ARC specific typedefs throughout by
	their underlying types. Remove obsolete ARC specific headers and
	add arc-elf-tdep.h as header.
	(field_meaning, field_definition, parsing_data): Make name and
	description fields non-constant. Replace ARC specific typedef'd
	types by their underlying types.
	(NO_DESCRIPTION, RESERVED, UNUSED): Make non-constant.
	* arc-aux-registers.h: Remove ARC specific typedefs. Transfer
	structs and enums to arc-tdep.h and arc-elf-tdep.h as appropriate.
	Replace ARC specific typedef'd types by their underlying types.
	* arc-board.c: Replace ARC specific typedef'd types by their
	underlying types.
	* arc-constants.h: Deleted.
	* arc-elf-tdep.c: Replace ARC specific typedef'd types by their
	underlying types. Remove obsolete ARC specific headers and add
	arc-elf-tdep.h as header. Replace arc_jtag functions throughout by
	arc_elf.
	(ARC_NR_REGS, ARC_NR_PSEUDO_REGS): Macros added.
	(EXTRACT): Macro deleted.
	(check_architecture): Deleted.
	(register_reggroup_p): Simplified.
	(REGISTER_NAME_IS): Macro deleted.
	(memory_range_command, arc_jtag_fill_memory_command)
	(arc_jtag_break_memory_command, arc_jtag_watch_memory_command)
	(arc_check_pc_defined): Deleted.
	(arc_elf_init_abi): Replaces arc_jtag_initialize.
	* arc-elf-tdep.h (arc_variant_info): Struct defn deleted.
	(arc_check_pc_defined): Deleted.
	* arc-linux-tdep.c (arc_linux_binutils_reg_to_regnum): Deleted.
	(arc_linux_pseudo_register_read, arc_linux_pseudo_register_write):
	Deleted.
	(arc_linux_init_abi): Use PC rather than STOP_PC.
	* arc-tdep.c (WORD_ALIGNED, WORDS_OCCUPIED, ROUND_UP_TO_WORDS):
	Macros replaced by functions.
	(arc_round_up_to_words): New function.
	(IS_INSTRUCTION): Macro deleted.
	(CHECK_OPERAND_STRING_AND_ACT, PUSH_BLINK, PUSH_BLINK_ACT)
	(IS_PUSH_BLINK_FI, PUSH_FP_ACT, IS_PUSH_FP_FI, UPDATE_FP_ACT)
	(IS_UPDATE_FP_FI, UPDATE_STACK_SPACE, IS_SUB_SP_FI): Macros
	replaced by functions.
	(arc_is_push_blink_fi, arc_is_push_fp_fi, arc_is_update_fp_fi)
	(arc_is_sub_sp_fi, arc_is_core_register): New functions.
	(arc_is_in_prologue): Replace macros by functions.
	* arc-tdep.h: Insert arc-constants.h. Add arc specific enums and
	structs from arc-aux-registers.h.
	* configure.tgt (arc*-*-*): Add arc-board.o.

2013-02-27  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* regformats/reg-arc.dat: Updated to match new GDB register
	sequence.

2013-02-18  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-aux-registers.h (_initialize_arc_aux_regs): Replace
	ARC_VariantsInfo by underlying struct definition.
	* arc-constants.h: Created.
	* arc-elf-tdep.c (create_variant_info): Replace ARC_VariantsInfo
	by underlying struct definition.
	* arc-tdep.h: Break out constants into arc-constants.h
	(ARC_VariantsInfo): Remove typedef
	(gdbarch_tdep): Replace ARC_VariantsInfo by underlying struct
	definition.

2013-01-31  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* arc-architecture.c, ac-architecture.h: Deleted.
	* configure.tgt <arc*-*-*>: Remove redundant files from target.

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

