2014-03-26 Claudiu Zissulescu <claziss@synopsys.com>

       * arc-opc-old.c (insert_reg): Handle SDA symbols by ld<zz>
         instructions (prefetch type instructions).

2014-03-20 Claudiu Zissulescu <claziss@synopsys.com>

       * arc-em.h: Allow swi instruction for ARC 700 architecture.
       * arc-opc-old.c (insert_reg): Insert aux register values into
         s12 and u6 instruction's fields.

2014-02-05 Claudiu Zissulescu <claziss@synopsys.com>

       * arc-opc-old.c (arc_reg_names_em): Add r58 and r59 to be used
         by ARCv2 as ACCL and ACCH.

2014-01-22 Claudiu Zissulescu <claziss@synopsys.com>

       * arc-em.h : Fix order DIV/DIVU, add HS floating point instructions.
       * arcompact-dis.c: Decode HS floating point instructions.

2013-12-18 Claudiu Zissulescu <claziss@synopsys.com>

       * arc-em.h: Fix AEX pattern to accept auxiliary registers.

2013-12-17 Claudiu Zissulescu <claziss@synopsys.com>

       * arcompact-dis.c: Add HS instructions.

2013-12-16 Claudiu Zissulescu <claziss@synopsys.com>

       * arc-em.h: Add VADD2H instruction.

2013-12-11 Claudiu Zissulescu <claziss@synopsys.com>

       * arc-opc-old.c: Add modifiers for 64 bit operands.
       * arc-em.h: Add DMACWH, DMACWHU, DMPYWH, DMPYWHU, MACD, MACDU,
         MPYD, MPYDU, QMACH, QMACHU, QMPYH, QMPYHU, VADD2, VADD4H,
         VADDSUB, VADDSUB4H,VMPY2H, VMPY2HU, VSUB2, VSUB4H, VSUBADD,
         VSUBADD4H HS instructions.

2013-11-27 Claudiu Zissulescu <claziss@synopsys.com>

       * arc-em.h: Add DMACH, DMACHU, DMPY, DMPYHU, MAC, MACU,
         VADDSUB2H, VSUB2H, and VSUBADD2H instructions.

2013-11-21 Claudiu Zissulescu <claziss@synopsys.com>

       * arc-opc-old.c: Choose the right set of register names for
         ARCv2HS.

2013-11-14 Claudiu Zissulescu <claziss@synopsys.com>

       * arc-em.h: Add LDD, STD definitions.
       * arc-opc-old.c: Add support to parse 64 bit registers.

2013-11-13 Claudiu Zissulescu <claziss@synopsys.com>

       * arc-em.h: Add XBFU definitions.
       * arc-opc-old.c: Add HS support.

2013-11-11 Claudiu Zissulescu <claziss@synopsys.com>

	* arccompact-dis.c: Replace E_ARC_MACH_ARCV2 with
	  bfd_mach_arc_arcv2.

2013-10-04 Claudiu Zissulescu <claziss@synopsys.com>

	* arc-opc-old.c: Fixed limm_p flag for prefetch instructions
	  when prefetching a small data symbol.

2013-08-05 Claudiu Zissulescu <claziss@synopsys.com>

	* arc-em.h: Remove seti [u6] and clri [u6] mnemonic variants.

2013-08-23 Anton Kolesov <akolesov@synopsys.com>

	* arcompact-dis.c, arc-dis-old.c (dsmOneArcInst): Field _addrWriteBack was
	not written to result structure. This field is required by GDB to properly
	recognize prologue in functions without full debug information.

2013-08-05 Claudiu Zissulescu <claziss@synopsys.com>

	* arc-em.h: Modify enter_s and leave_s mnemonics by adding
	  parantheses.
	* arcompact-dis.c: Fix leave_s disassembled code.

2013-07-31 Claudiu Zissulescu <claziss@synopsys.com>

	* arc-em.h: Add relocation support for ld_s r1,[gp,s11] and
	st_s r0,[gp,s11] instructions.
	* arc-opc-old.c: Likewise.

2013-07-24  Claudiu Zissulescu <claziss@synopsys.com>

	* arc-em.h: Add LLOCK mnemonic to EM

2013-07-19  Simon Cook  <simon.cook@embecosm.com>

	* arc-dis-old.c (write_comments_): Comment out unused function.
	(comment_prefix): Mark as ATTRIBUTE_UNUSED (used by above function).
	* arcompact-dis.c: Likewise.

2013-07-11  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* arc-opc-old.c (arc_opcodes): Correct parentheses change for
	"brgt%.n %B,%u,%d".

2013-07-10  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* arc-dis.c (print_insn_arc): Comment out unused function.
	* arc-opc-old.c (arc_get_branch_prediction): Add prototype
	declaration.
	(arc_reset_branch_prediction): Likewise.
	(em_jumplink_or_jump_insn): Likewise.
	(em_branch_or_jump_insn): Likewise.
	(brpredict): Comment out - unused.
	(arc_opcodes): Add parentheses to clarify expressions in pseudo
	menomnics or BRcc instruction.
	* arcompact-dis.c (CHECK_T): Add parentheses around use of "x".
	(ARCompact_decodeInstr): Remove all references to unused "bytes".
	Add extra parentheses to clarify logical expressions.
	(arcAnalyzeInstr): Remove all references to unused "bytes".

2013-07-02  Claudiu Zissulescu <claziss@synopsys.com>

	* arc-em.h: Allow mov_s.nz

2013-06-11  Claudiu Zissulescu <claziss@synopsys.com>

	* arc-em.h: Allow seti/clri instructions without []

2013-06-11  Claudiu Zissulescu <claziss@synopsys.com>

	* arc-em.h: rearange seti/clri instructions

2013-06-10  Claudiu Zissulescu <claziss@synopsys.com>

	* arc-opc-old.c: add variant of prefetch instruction

2013-06-06  Claudiu Zissulescu <claziss@synopsys.com>

	* arc-em.h: add seti/clri as valid instructions

2013-05-07  Simon Cook  <simon.cook@embecosm.com>

	* arc-opc-old.c (arc_opcodes): Added RTSC encoding.

2013-04-12  Simon Cook  <simon.cook@embecosm.com>

	* arcompact-dis.c (ARCompact_decodeInstr): Change number of bytes per
	chunk back to 1 to resolve test issues.

2013-04-05  Simon Cook  <simon.cook@embecosm.com>

	Port from
	2013-04-02  Claudiu Zissulescu <claziss@synopsys.com>
	* arc-opc-old.c (insert_offset): Change error message.

2013-04-05  Simon Cook  <simon.cook@embecosm.com>

	Port from
	2013-03-19  Claudiu Zissulescu <claziss@synopsys.com>
	* arc-opc-old.c (arc_operands_ac): Remove ARC_OPERAND_LIMM from 'o'
	operand.

2013-04-02  Simon Cook  <simon.cook@embecosm.com>

	* arc-opc-old.c (arc_opcodes): Added RTSC instruction.
	* arcompact-dis.c (dsmOneArcInst): Fixed decoding of RTSC.

2013-03-17  Joern Rennecke  <joern.rennecke@embecosm.com>

	* arc-opinst.c: Regenerate.

2013-03-17  Joern Rennecke  <joern.rennecke@embecosm.com>

	* arc-opc.c, arc-dis.c, arc-dis.h: Rename to:
	* arc-opc-old.c, arc-dis-old.c, arc-dis-old.h.
	* arc-dis-old.c, arcompact-dis.c: Reflect header file name change.
	* arc-opc-cgen.c, arc-dis-cgen.c, arc-dis-cgen.h: Delete.
	* arc-opc.c, arc-dis.c, arc-dis.h: Autogenerate with CGEN.
	* Makefile.am (HFILES): Add arc-desch and arc-opc.h.
	(TARGET_LIBOPCODES_CFILES): Add arc-asm.c, arc-desc.c, arc-dis-old.c,
	arc-ibld.c, arc-opinst.c.
	(CLEANFILES): Add stamp-arc.
	(CGEN_CPUS): Add arc.
	(ARC_DEPS): New rule.
	($(srcdir)/arc-desc.h $(srcdir)/arc-desc.c $(srcdir)/arc-opc.h
	 $(srcdir)/arc-opc.c $(srcdir)/arc-ibld.c $(srcdir)/arc-opinst.c
	 $(srcdir)/arc-asm.c $(srcdir)/arc-dis.c): Likewise.
	 (stamp-arc): Likewise.
	 * configure.in (bfd_arc_arch): Update file list.
	 * Makefile.in, configure: Regenerate.

	 * arc-asm.c, arc-desc.h, arc-ibld.c, arc-opc.h: Regenerate, using:
	 Customer-Projects/synopsys/arc_gnu/branches/arc_gnu_4.8/srcw-20120503/cgen.
	 * arc-desc.c, arc-dis.c, arc-opc.c, arc-opinst.c: Likewise.

2013-01-30  Claudiu Zissulescu <claziss@synopsys.com>

	* arc-em.h : Added ARCv2-EM instructions
	* arc-opc.h: Added support for ARCv2-EM instructions.

2013-01-30  Simon Cook  <simon.cook@embecosm.com>

	* arc-opc.c (arc_opcodes): Applied Claudiu Zissulescu's fixes to
	instruction patterns.

2013-01-07  Simon Cook  <simon.cook@embecosm.com>

	* arc-opc.c (arc_opcodes): Added assembly of Android instructions.
	* arcompact-dis.c (dsmOneArcInst): Added disassembly of Android
	instructions.

2012-12-13  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* arc-opc.c <arc_opcodes>: Initialize first agument cast to
	unsigned char *.

2012-12-12  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* arc-ext.c (arcExtMap_instName): set but unused variables
	removed.

2012-12-10  Mischa Jonker  <mischa.jonker@synopsys.com>

	* arcompact-dis.c (dsmOneArcInst): Fix decoding of register when doing
	indirect jumps with short instructions (j_s, jl_s, j_s.d, jl_s.d).
	It only worked for r0 and blink. Now it works also for r1..3, r12..15.

2012-12-10  Mischa Jonker  <mischa.jonker@synopsys.com>

	* arcompact-dis.c (dsmOneArcInst): Fix single stepping over J_S.D [r]
	state->nullifyMode was set incorrectly

2012-12-04  Simon Cook  <simon.cook@embecosm.com>

	* arc-opc.c: Increase size of arc_operand_map_a4 and arc_operand_map_ac
	to support '+' operand prefix.

2012-10-08  Simon Cook  <simon.cook@embecosm.com>

	* arcompact-dis.c (dsmOneArcInst): Patch applied for diassembly of
	ex instruction with u6 operands.


2012-10-02  Simon Cook  <simon.cook@embecosm.com>

	* arcompact-dis.c (dsmOneArcInst): Patch applied for supporting disassembly
	of instructions with 2 operands where one is a u6 operand.

2012-09-27  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* arcompact-dis.c (dsmOneArcInst): Remove blank line to match
	version in binutils. Set register_for_indirect_jump even where
	implicit BLINK.
	(my_sprintf): Remove unused variable auxNum.

2012-09-27  Simon Cook  <simon.cook@embecosm.com>

	* arcompact-dis.c (dsmOneArcInst): Added disassembler
	support for MPY, MPYH, MPYHU, MPYU instructions.

2012-09-07  Simon Cook  <simon.cook@embecosm.com>

	* arc-opc.c (arc_reg_names_a700): Correct TSCH register
	register number and type.

2012-08-30  Simon Cook  <simon.cook@embecosm.com>

	* arc-ext.c: Moved inclusion of "sysdep.h".
	* arc-desc.h: Change include for cgen/bitset.h (was opcodes/cgen-bitset.h).
	* arcompact-dis.c: Included "sysdep.h"

2012-06-05  Joern Rennecke  <joern.rennecke@embecosm.com>

	* arcompact-dis.c (my_sprintf): Don't abort for "%*".

2011-06-15  Brendan Kehoe  <brendan@zen.org>

	* arc-dis.c (BITS): Use sizeof(word)*8-1 instead of 31 to
	accommodate 64-bit hosts.
	* arcompact-dis.c (BITS): Likewise.

2011-06-09  Brendan Kehoe  <brendan@zen.org>

	* arc-dis.h (struct arcDisState): Make ADDRESSES unsigned int.

2011-05-17  Brendan Kehoe  <brendan@zen.org>

	* arcompact-dis.c (op_MAJOR_6): Add to anon enum.
	(dsmOneArcInst): Add support for llock, scond, swape, and rtsc.
	* arc-opc.c (arc_reg_names_a700): Add dc_startr, dc_endr,
	and tsch.

2011-01-20  Michael Eager  <eager@eagercon.com>

	* arc-opc.c (arc_opcodes): Add MPYW and MPYUW patterns.
	* arcompact-dis.c (dsmOneArcInst): Add decode for same.

2010-12-27  Michael Eager  <eager@eagercon.com>

	* arc-opc.c (arc_opcodes): Remove incorrect asl multibit
	pattern.

2010-08-27  Michael Eager  <eager@eagercon.com>

	* arc.h: New: ARC_MACH_ARC601.
	*.arc.c (sleep, swi): OK for ARC601.
	mach_type_map: Add ARC_MACH_ARC601.

2010-08-19  Michael Eager  <eager@eagercon.com>

	* arc-opc.c (MACH_attr, arc_cgen_mach_table): Add arc601.
	* arc-desc.h: define HAVE_CPU_ARC601F.  (mach_attr): Add
	MACH_ARC601.

2010-03-22  Brendan Kehoe  <brendan@zen.org>

	* arc-opc.c (arc_mach_a4): Make sure this is initialized to 1
	by default, since the arc_operand_map and arc_operands are also
	still the default.  Otherwise, the ARCOMPACT tables would be
	used instead, but incorrectly done with the default ARC4 for
	the other behavior.

2009-09-10  J"orn Rennecke  <joern.rennecke@arc.com>

	* arc-opc-cgen.c (arc_cgen_init_opcode_table): Comment out
	warning-generating no-op.

2008-04-09  J"orn Rennecke  <joern.rennecke@arc.com>

	Copy from configure:
	* configure.in (bfd_arc_arch): Add arc-asm.lo, arc-ibld.lo,
	arc-opc-cgen.lo and arc-opinst.lo .  Set using_cgen=yes .
	* configure: Regenerate.

	* arc-dis.h (ARCTangent_decodeInstr): Comment out prototype.
	* arc-opc.c (arc_opcode_init_tables): Avoid signed/unsigned comparison.
	* Makefile.am (CFILES): Add arc-dis-cgen.c, arc-desc.c and
	 arcompact-dis.c.
	(ALL_MACHINES): Add arc-dis-cgen.lo, arc-desc.lo and arcompact-dis.lo.
	(arc-dis.lo): Depend on arcompact-dis.h.
	(arcompact-dis.lo): New rule.
	* Makefile.in: Regenerate.
	* arcompact-dis.c (my_sprintf) <*>: Remove warning, abort rather
	than ignore.
	* cgen-dis.c (hash_insn_array): Pass big_p parameter to cd->dis_hash.
	(hash_insn_list, cgen_dis_lookup_insn): Likewise.

2008-11-14  Irfan Rafiq  <irfan.rafiq@arc.com>
	* arc-dis.c,	Target specific improvements.
	  arc-ext.c,
	  arc-opc.c


2008-11-10  Irfan Rafiq  <irfan.rafiq@arc.com>
	* arcompact-dis.c:	 Added arcompact-dis.c
	* configure.in: 	 Added arcompact-dis.c
	* configure:		 Regenerated

2008-04-09  J"orn Rennecke  <joern.rennecke@arc.com>

	* arc-ext.c (arcExtMap_add): Fix pointer signedness mismatch.

2007-11-01  J"orn Rennecke  <joern.rennecke@arc.com>

	* arc-opc.c (insert_ld_syntax): Fix check for scaled index.
	* arcompact-dis.c (dsmOneArcInst): Also disassemble .aa field
	in the presence of a long immediate.

2007-10-31  J"orn Rennecke  <joern.rennecke@arc.com>

	* arc-opc.c (ADDRESS22S_AC): Define.
	(CACHEBYPASS5_AC): Update index value.
	(insert_addr_wb): Check for '&' format.
	(insert_ld_syntax): Allow long immediate with scaled index.
	(arc_opcodes): Likewise.
	(arc_suffixes_ac): Add entry for "as" / ADDRESS22S_AC.

2007-08-31  J"orn Rennecke  <joern.rennecke@arc.com>

	* arc-opc.c (insert_ld_syntax): Use arc_ld_ext_mask to decide
	if a load to an extension register is valid.
	Only reject a load to ilink[12] if arc_user_mode_only is set.
	(insert_ex_syntax): Use same operand checks as for insert_ld_syntax.
