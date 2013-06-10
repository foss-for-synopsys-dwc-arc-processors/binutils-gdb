2013-06-06  Claudiu Zissulescu <claziss@synopsys.com>

	* config/extlib/arcextlib.s : Define __ARCCOMPACT__ also for ARCv2
        * config/tc-arc.c: Add -mav2em option for EM, enable SPFP and
	DPFP extensions for EM.

2013-06-06  Simon Cook  <simon.cook@embecosm.com>

	* config/tc-arc.c (options): Added OPTION_MCPU for -mcpu
	matching.
	(md_longopts): Added new options based on updated
	documentation.
	(md_parse_option): Added support for specifying architecture
	via -mcpu option.

2013-05-20  Matt Hammond  <matt.hammond@synopsys.com>

	* doc/as.texinfo (Flonums): Change ARC to ARC architecture.
	(Align): Change arc to ARC.
	* doc/c-arc.texi: Change ARC 600 to ARC600 and ARC 700 to ARC700
	throughout. Correct punctuation of lists introduced by ':'.
	(ARC Machine Directives): Reworded example for modifiers to
	.extInstruction syntax class.
	(ARC Opcodes): Changed location for Programmer's Reference Manual.

2013-05-16  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* doc/c-arc.texi (ARC Machine Directives): Correct typo.

2013-05-16  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* doc/c-arc.texi: Spell check and correct throughout.
	(Options): Note all relevant options are implicit for ARC v2 EM,
	ARC 700 core 4 v 4.10 replaced by ARC 770 throughout. -mdsp-packa
	description clarified. -mxy description clarified. Use of backtick
	for line separator added. Add ilink and clarify use as
	register. Distinguish between double and single precision
	FPX. Mark relevant directives as deprecated, add back
	.extAuxRegister, .extCondCode, .extCoreRegister and
	.extInstruction, add upper case variants for .option.

2013-05-15  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* doc/c-arc.texi (ARC Dependent Features): Tidy up various small
	typos.

2013-05-15  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* doc/as.texinfo (Target ARC options): Remove -marc4, -marc5,
	-marc8 -mEB and -mEL. Add -mcpu, -mA6, -mARC600, -mARC601, -mA7,
	-mARC700, -mEM, -mARCv2EM, -mav2em, -mld-extension-reg-mask,
	-muser-mode-only, -mbarrel-shifter, -mdpfp, -mdpfp-compact,
	-mdpfp-fast, -mdsp-packa, -mdvbf, -mea, -mlock, -mmac-24,
	-mmac-d16, -mmin-max, -mmul64, -mno-mpy, -mnorm, -mrtsc, -msimd,
	-mspfp, -mspfp-compact, -mspfp-fast, -mswap, -mswape, -mtelephony
	and -mxy.
	* doc/c-arc.texi (ARC Dependent Features): Add descriptions of
	-mbarrel-shifter, -mcpu, -mA6, -mARC600, -mARC601, -mA7, -mARC700,
	-mEM, -mARCv2EM, -mav2em, -mld-extension-reg-mask,
	-muser-mode-only, -mdpfp -mdpfp-compact, -mdpfp-fast, -mdsp-packa,
	-mdvbf, -mea, -mmac-24, -mmac-d16, -mmin-max, -mmul64, -mno-mpy,
	-mnorm, -msimd, -mspfp, -mspfp-compact, -mspfp-fast, -mswap,
	-mtelephony and -mxy options.  Mark -EB, -EL, -mbarrel_shifter,
	-mdpfp_compact, -mdpfp_fast, -mdsp_packa, -mEA, -mmac_24,
	-mmac_d16, -mmin_max, -mspfp_compact and -mspfp_fast options as
	deprecated. Remove -mA4 and -mA5 options. Add description of '%',
	'@' and '-' syntax. Add description for 'Register Names'
	section. Add description of FPX extension for Floating Point.
	Provide definitions of .2byte, .3byte, .4byte, .half and .long
	directives. Remove .extCoreRegister, .extAuxRegister, .extCondCode
	.extCoreRegister, .extInstruction, .arc5 and .arc8 directives


2013-04-27  Joern Rennecke  <joern.rennecke@embecosm.com>

	* config/tc-arc.c (get_arc_exp_reloc_type):
	Use BFD_RELOC_ARC_PC32 instead of BFD_RELOC_32 if EXP is a difference
	with the subtrahend being a symbol in the current section.
	(md_apply_fix): Handle BFD_RELOC_ARC_PC32.

2013-04-05  Simon Cook  <simon.cook@embecosm.com>

	Port from
	2013-04-02  Claudiu Zissulescu <claziss@synopsys.com>
	* config/tc-arc.c (md_assemble): Fix fixup for %st operand.

2013-04-05  Simon Cook  <simon.cook@embecosm.com>

	Port from
	2013-03-19  Claudiu Zissulescu <claziss@synopsys.com>
	* config/tc-arc.c (md_assemble): Fixup fix for STAR9000593624.

2013-03-27  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* config/extlib/Makefile.in: Add pdf and install-pdf targets.

2013-03-20  Joern Rennecke  <joern.rennecke@embecosm.com>

	* config/tc-arc.c (tc_gen_reloc): Adjust offset to reflect
	difference between relocation location and instruction start.

2013-03-04  Simon Cook  <simon.cook@embecosm.com>

	* testsuite/gas/all/redef3.d: Replace arc-*-* with arc*-*-*.
	* testsuite/gas/arc/ex_arc700.s: Likewise.
	* testsuite/gas/arc/ld_arc700.s: Likewise.
	* testsuite/gas/arc/warn.s: Likewise.
	* testsuite/gas/lns/lns.exp: Likewise.

2013-01-30  Claudiu Zissulescu <claziss@synopsys.com>

	* config/tc-arc.c: Added ARCv2 support

2012-12-06  Simon Cook  <simon.cook@embecosm.com>

	* config/tc-arc.c (md_assemble): Possible fix for fmt chars above 0x80.

2012-12-04  Simon Cook  <simon.cook@embecosm.com>

	* config/tc-arc.c (md_assemble): Support for non-@ operand types.

2012-10-19  Simon Cook  <simon.cook@embecosm.com>

	* config/tc-arc.h: Set default assembler endianness based on
	compiled target.

2012-08-30  Simon Cook  <simon.cook@embecosm.com>

	* config/tc-arc.c: Replace references to assert macro with gas_assert.
	* Makefile.in: Regnerate.
	* as.c: Make name non-static to allow extlib directory search.
	* configure: Regenerate.

2012-05-06  Joern Rennecke  <joern.rennecke@embecosm.com>

	* config/tc-arc.c (arc_optimize_expr): Fix test for negative
	X_add_number.

2012-04-12  Joern Rennecke  <joern.rennecke@embecosm.com>

	* config/tc-arc.c (arc_optimize_expr): Also handle .&-n for small n.
	Fix warnings.

2012-04-03  Joern Rennecke  <joern.rennecke@embecosm.com>

	* configure.tgt (arc*eb, arc*-*-linux-uclibc*): New configurations.

2012-03-19  Jeremy Bennett  <jeremy.bennett@embecoms.com>

	* config/tc-arc.c <BINDIR4>: New directory to deal with extension
	library being in a build .libs sub-directory.
	(arc_process_extinstr_options): Add new search
	for extension library in build .libs sub-directory. Not clear why
	this was not there before, nor why things worked without it.

2012-02-17  Joern Rennecke  <joern.rennecke@embecosm.com>

	* config/tc-arc.c (arc_optimize_expr): New function.
	* config/tc-arc.h (md_optimize_expr): Define.
	(arc_optimize_expr): Declare.

2012-01-06  Joern Rennecke  <joern.rennecke@embecosm.com>

	* config/tc-arc.c (md_chars_to_number, md_number_to_chars): Add
	comment on the meaning of N == -4.

2011-12-02  Joern Rennecke  <joern.rennecke@embecosm.com>

	From Alexey Brodkin:
	* config/tc-arc.c (md_assemble): Make insn_name_idx unsigned.

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

2010-12-27  Michael Eager  <eager@eagercon.com>

	* config/tc-arc.c (md_assemble): Add diagnostic for
	opcode match.

2010-09-16  Michael Eager  <eager@eagercon.com>

	* Bug 100549 -- Apply PR gas/10704
        * symbols.c (snapshot_symbol): Revert 2006-01-09 patch for
		PR2117.

2010-08-20  Michael Eager  <eager@eagercon.com>

	* gas/config/extlib/arcextlib.s: set __ARCCOMPACT__ for ARC601.

2010-08-19  Michael Eager  <eager@eagercon.com>

	* config/tc-arc.c (options, md_longopts, md_parse_option): Add
	OPTION_ARC601. (arc_process_extinstr_options): Define __ARC601__.

2010-06-18  Brendan Kehoe  <brendan@zen.org>

	* config/tc-arc.c (arc_set_ext_seg): Make TEMP be 15 chars wide
	to fit at least the 13-char length.

2010-01-25  Brendan Kehoe  <brendan.kehoe@viragelogic.com>

	* config/tc-arc.c (tc_arc_fix_adjustable): Make sure we don't
	adjust extern symbols either, in addition to weak.

2009-09-07  J"orn Rennecke  <joern.rennecke@arc.com>

	* config/tc-arc.c (md_number_to_chars): Add case for 8 chars.
	(arc_parse_name) Avoid truncating pointer on 64 bit machines.
	(tc_gen_reloc): Add ATTRIBUTE_UNUSED for section parameter.
	* symbols.h (local_symbol): Declare.

2008-11-14  Irfan Rafiq <irfan.rafiq@arc.com>
            ARC'S GENERIC CHANGES
	as.c: Make "myname" non-static. - To search extlib files relative to caller path.

        * symbol.c:  Make the local_symbol_make non-static so that it could be used
        in target specific portion. It call is necessary in tc-arc.c because ARC's extension
        instruciton support through file needs to make symbols.

2008-11-10  Irfan Rafiq <irfan.rafiq@arc.com>
	* configure.tgt,	arc-linux-uclibc target.
	  configure.in,
	  configure

	* Makefile.am,		extlib additions.
	  Makefile.in.

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
