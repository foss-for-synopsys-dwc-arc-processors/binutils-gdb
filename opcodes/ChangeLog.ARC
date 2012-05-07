2011-06-15  Brendan Kehoe  <brendan@zen.org>

	* arc-dis.c (BITS): Use sizeof(word)*8-1 instead of 31 to
	accommodate 64-bit hosts.
	* arcompact-dis.c (BITS): Likewise.

2011-06-09  Brendan Kehoe  <brendan@zen.org>

	* arc-dis.h (struct arcDisState): Make ADDRESSES unsigned int.

2010-05-17  Brendan Kehoe  <brendan@zen.org>

	* arcompact-dis.c (op_MAJOR_6): Add to anon enum.
	(dsmOneArcInst): Add support for llock, scond, swape, and rtsc.
	* arc-opc.c (arc_reg_names_a700): Add dc_startr, dc_endr,
	and tsch.

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
