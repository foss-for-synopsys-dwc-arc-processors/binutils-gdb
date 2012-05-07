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

2010-01-29  Brendan Kehoe  <brendan.kehoe@viragelogic.com>

	* elf32-arc.c (elf_arc_relocate_section): Handle the result of
	elf_link_hash_lookup being a null pointer.

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
