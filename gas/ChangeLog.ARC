2010-05-17  Brendan Kehoe  <brendan@zen.org>

	* config/extlib/arcextlib.s: Add ARC700 4.10 extension instructions.
	* config/tc-arc.c (suffixclass): Add SUFFIX_DIRECT.
	(LOCK_INSNS, SWAPE_INSN, RTSC_INSN): Define.
	(enum options): Add OPTION_LOCK, OPTION_SWAPE, and OPTION_RTSC.
	(md_longopts): Add processing of -mlock, -mswape, and -mrtsc.
	(md_parse_option, case OPTION_LOCK): New case.
	(md_parse_option, case OPTION_SWAPE): New case.
	(md_parse_option, case OPTION_RTSC): New case.
	(extension_macros): Add __Xlock, __Xswape, and __Xrtsc.
	(arc_process_extinstr_options): Add checks for LOCK_INSNS,
	SWAP_INSN, and OPTION_RTSC.
	(ac_suffixclass): Add SUFFIX_DIRECT.
	(arc_add_ext_inst): Handle SUFFIX_DIRECT.
	(arc_generate_extinst32_operand_strings): Add SUFFIX_DIRECT
	patterns.
	* doc/c-arc.texi: Document -mlock, -mswape, and -mrtsc.

2010-09-17  Michael Eager  <eager@eagercon.com>

	* Bug 100549 -- Apply PR gas/10704
	* symbols.c (snapshot_symbol): Revert 2006-01-09 patch for PR2117.

2010-01-25  Brendan Kehoe  <brendan.kehoe@viragelogic.com>

	* config/tc-arc.c (tc_arc_fix_adjustable): Make sure we don't
	adjust extern symbols either, in addition to weak.

2008-04-09  J"orn Rennecke  <joern.rennecke@arc.com>

	* config/tc-arc.c (arc_generate_extinst32_operand_strings): Fix
	signedness of op1, op2, op3 and operand_string.

2008-03-19  James Mundstock <jimm@arc.com>
        * config/tc-arc.c: add support for simd and dsp instructions.
	* opcodes/arc-opc.c: Fix errors in write back and cache bypass fields.
	*                    Fix encodings for instructions S12 and LIMM fields
	*                    Add fields for simd instructions.
2008-03-17  J"orn Rennecke  <joern.rennecke@arc.com>

	* config/tc-arc.c (arc_handle_align): Fix signedness problem.

2007-11-23  J"orn Rennecke  <joern.rennecke@arc.com>

	* tc-arc.c (line_separator_chars): Add '`'.

2007-08-31  J"orn Rennecke  <joern.rennecke@arc.com>

	* config/tc-arc.c (arc_ld_ext_mask, arc_user_mode_only): Define.
	(enum options): Add OPTION_USER_MODE and OPTION_LD_EXT_MASK.
	(md_longopts): Add muser-mode-only and mld-extension-reg-mask.
	(md_parse_option): Handle OPTION_USER_MODE and OPTION_LD_EXT_MASK.
	* doc/c-arc.texi: Document new options.

2007-05-16  J"orn Rennecke  <joern.rennecke@arc.com>

	From codito configure.in patch:
	* configure.tgt (arc-*-elf*): Add bfd_gas=yes.
	(arc-*-linux-uclibc*): Add.

	* configure: Regenerate.
	* Makefile.in: Regenerate.

2007-05-11  J"orn Rennecke  <joern.rennecke@arc.com>

	* config/tc-arc.c (opcode/arc.h): Don't #include.
	(loop_target_list): Remove.
	(add_loop_target, arc_check_label): Use symbol_get_tc to find the
	matching struct loop_target.  Remove list insertion.
	(struct enriched_insn, struct loop_target): Move from here...
	* config/tc-arc.h: ... to here.
	(opcode/arc.h): #include.
	(struct loop_target): Remove 'next' member.
	(struct arc_tc_sy): Define.
	(TC_SYMFIELD_TYPE, tc_symbol_new_hook): #define.
	
	* config/tc-arc.c (arc_set_ext_seg): Change to static void.
	(insert_last_insn): Fix type of sym parameter.
	(arc_process_extinstr_options): Cast results of local_symbol_make.
