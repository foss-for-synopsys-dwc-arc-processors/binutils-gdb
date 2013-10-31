2013-10-31  Vineet Gupta <vgupta@synopsys.com>

	*  elf32-arc.c (elf_arc_reloc_type): Add new relocations to syncup
	with Metaware tools

2013-09-17 Anton Kolesov <akolesov@synopsys.com>

	* elf32-arc.c (elf32_arc_grok_prstatus): Fix compiler error intruduced in
	previous change.

2013-09-12 Anton Kolesov <akolesov@synopsys.com>

	* elf32-arc.c (elf32_arc_grok_prstatus): New function to parse NOTE
	section in core dump files. GDB requires this to work properly with core
	dumps.

2013-09-11 Simon Cook  <simon.cook@embecosm.com>

	* elf32-arc.c (elf_backend_default_execstack): Set default stack state
	to non-executable.

2013-07-31 Claudiu Zissulescu <claziss@synopsys.com>

	* elf32-arc.c: Add relocation support for ld_s r1,[gp,s11]
	and st_s r0,[gp,s11] instructions.

2013-07-25 Claudiu Zissulescu <claziss@synopsys.com>

	* elf32-arc.c: Use j.d instead of nop_s j_s.d in PLT entry for
	ARCv2 cores.

2013-07-24 Claudiu Zissulescu <claziss@synopsys.com>

	* elf32-arc.c: Add PLT support for ARCv2 cores.

2013-06-28 Vineet Gupta <vgupta@synopsys.com>

	* elf32-arc.c: Replaced EM_ARCOMPACT2 with EM_ARCV2

2013-06-27 Claudiu Zissulescu <claziss@synopsys.com>

	* elf32-arc.c : Clean up. Rezolve crashing of the linker when
	two different architecture binary are linked together.

2013-01-30 Claudiu Zissulescu <claziss@synopsys.com>

	* cpu-arc.c (arc_info_struct): Add EM as valid processor type.

2013-04-03  Simon Cook  <simon.cook@embecosm.com>

	* cpu-arc.c (bfd_arc_arch): Rename default A6 to ARC600.

2013-03-18  Simon Cook  <simon.cook@embecosm.com>

	* elf32-arc.c (bfd_arc_arch): Make ARC600 the default architecture.

2013-02-25  Simon Cook  <simon.cook@embecosm.com>

	* bfd/config.bfd: Make arc*-*-elf* valid for big endian ARC.

2013-02-05  Simon Cook  <simon.cook@embecosm.com>

	* elf32-arc.c (elf_arc_check_relocs): Change
	R_ARC_32/R_ARC_32_ME/R_ARC_PC32 to use
	_bfd_elf_make_dynamic_reloc_section.
	(elf_arc_relocate_section): Change R_ARC_32/R_ARC_32_ME/R_ARC_PC32 to use
	_bfd_elf_section_offset.
	(ELF_TARGET_ID): Define.

2013-01-30 Claudiu Zissulescu <claziss@synopsys.com>

	* archures.c : defined bfd_mach_arc_arcv2
	* elf32-arc.c: added ARCv2 machine number for an ARC elf file
	* cpu-arc.c : added the new EM bfd definition.


2013-01-16  Simon Cook  <simon.cook@embecosm.com>

	* cpu-arc.c (bfd_arc_arch): Make A5 default architecture to solve
	incorrect architecture outputs.

2013-01-07  Simon Cook  <simon.cook@embecosm.com>

	* elf32-arc.c: elf_backend_can_gc_sections.

2012-12-12  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* elf32-arc.c (elf_arc_relocate_section)
	(elf_arf_finish_dynamic_sections): Shadowed variables renamed.

2012-11-26  Vineet Gupta <vgupta@synopsys.com>

	* elf32-arc.c: ELF_MAXPAGESIZE set to 8k

2012-08-30  Simon Cook  <simon.cook@embecosm.com>

	* bfd-in2.h: Rebuilt.
	* elf-bfd.h (elf_target_id): Added ARC_ELF_DATA to enum for uses of
	_bfd_elf_link_hash_table_init.
	* elf32-arc.c: Update references to syn_sec_cache struct to now refer
	to sym_cache instead. Likewise with bfd_section_from_r_symndx to
	bfd_sym_from_r_symndx.
	(elf_arc_check_relocs): rel_hdr is no longer part of bfd_elf_section_data,
	use _bfd_elf_single_rel_hdr() to get sh_name instead.
	* configure: Regenerate.

2012-06-22  Joern Rennecke  <joern.rennecke@embecosm.com>

Adapt 2002/12/04 elf32-m68k.c change:
	* elf32-arc.c (struct elf_ARC_link_hash_table): Add sym_sec
	member.
	(elf_ARC_link_hash_table_create): Initialize it.
	(elf_ARC_discard_copies) : Handle symbols that are forced to be
	local due to visibility changes.
	(elf_arc_check_relocs) : Likewise.
	(elf_arc_relocate_section): Likewise.
	(elf_arc_adjust_dynamic_symbol): Likewise.
	(elf_arc_size_dynamic_sections): Likewise.

2012-04-27  Joern Rennecke  <joern.rennecke@embecosm.com>

	* configure.in (AM_INIT_AUTOMAKE): Change ARC suffix to ARC_4.4 .
	* configure: Regenerate.

2012-04-16  Joern Rennecke  <joern.rennecke@embecosm.com>

	* dwarf2.c (read_rangelist): Apply sanity check to offset.

2012-04-03  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (insn_hword): New typedef.
	(elf_arc_abs_plt0_entry): Change element type to insn_hword.
	(elf_arc_abs_pltn_entry, elf_arc_pic_plt0_entry): Likewise.
	(elf_arc_pic_pltn_entry): Likewise.
	(pltcpy): New static function.
	(elf_arc_finish_dynamic_symbol): Use it. 
	* config.bfd (arc*, arc*-*-linux-uclibc*): New configurations.

2011-12-05  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_relocate_section): Don't emit an error for
	an undefined symbol in a -shared link.

2011-04-25  Brendan Kehoe  <brendan@kaylee>

	* elf.c (_bfd_elf_map_sections_to_segments): Do not put a
	read-only section like .dynamic into a writable segment.

2011-02-11  Brendan Kehoe  <brendan@zen.org>

	* elf32-arc.c (arc_elf_object_p): Init MACH with 0.

	* elf32-arc.c (arc_elf_object_p): Instead of returning FALSE if
	we don't recognize (e.g., a default of 0 which used to be
	processed as E_ARC_MACH_A4 which we no longer claim offer to
	support), follow the example of many other ports by letting the
	set_arch_mach callback at least make sure we've not been handed
	garbage.

2010-10-19  Brendan Kehoe  <brendan@zen.org>

	* elf32-arc.c (arc_plugin_one_reloc): Reject a R_ARC_PLT32
	which tries do to more than +/- 1M with a BLcc or Bcc insn.

2010-08-31  Brendan Kehoe  <brendan@zen.org>

	* cpu-arc.c (arch_info_struct): Adjust ARCN for "ARC601" and
	beyond to avoid looping.

2010-08-19  Michael Eager  <eager@eagercon.com>

	* archures.c (bfd_architecture): Define bfd_mach_arc_arc601.
	* elf32-arc.c (arc_elf_object_p): Recognize E_ARC_MACH_ARC601.

2010-04-02  Brendan Kehoe  <brendan@zen.org>

	* cpu-arc.c (bfd_arc_arch): Change to be ARC700 by default.

	* cpu-arc.c (ARCN): New macro.
	(bfd_arc_arch, arch_info_struct): Use it.

2010-01-29  Brendan Kehoe  <brendan.kehoe@viragelogic.com>

	* elf32-arc.c (elf_arc_relocate_section): Handle the result of
	elf_link_hash_lookup being a null pointer.

2008-11-12  Irfan Rafiq  <irfan.rafiq@arc.com>
        * elf32-arc.c (arc_elf_final_write_processing,
                       arc_elf_object_p): Sync with arch_info_struct        
        * cpu-arc.c (arch_info_struct): Update info for ARC600/ARC700.
        
        
2008-10-10  Irfan Rafiq  <irfan.rafiq@arc.com>
        
        *  bfd-in2.h  : Add relocation types.
        *  config.bfd : Add arc-linux-uclibc target.
        *  config.in  : Update version.
        *  libbfd.h   : Sync. relocation types.        

2008-02-27  J"orn Rennecke  <joern.rennecke@arc.com>

	* elf32-arc.c (BFD_DEBUG_PIC): Simplify change between debug /
	non-debug mode by using #if instead of comments.
	* (arc_plugin_one_reloc) <R_ARC_PLT32>: Also support 'b' instruction.
	* (elf_arc_check_relocs): Use bfd_make_section_with_flags instead of
	separate bfd_make_section / bfd_set_section_flags for
	SEC_LINKER_CREATED sections.
	(elf_arc_relocate_section): Fix two printf format issue.
	(elf_arc_adjust_dynamic_symbol): Likewise.
	(elf_arc_size_dynamic_sections): Set SEC_EXCLUDE flag instead of
	manually removing the section from the list.

2007-10-31  J"orn Rennecke  <joern.rennecke@arc.com>

	* configure.in (AM_INIT_AUTOMAKE): Update date.
	* configure: Regenerate.
