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
