2014-04-17 Claudiu Zissulescu <claziss@synopsys.com>

	* elf32-arc.c (arc_elf_object_p): Increase compatibility with
          metaware tools.

2014-04-16  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_finish_dynamic_symbol) <GOT_TLS_GD>: Use
	SYMBOL_REFERENCES_LOCAL.
	(arc_allocate_got) <GOT_TLS_GD>: Only add one reloc's size when the
	symbol reference is local.

2014-04-14  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_relocate_section): Also do adjustment for
	local tls variables for R_ARC_TLS_GD_GOT relocations.
	(elf_arc_finish_dynamic_symbol) <GOT_TLS_GD>: Fix comment to make sense.
	Fix handling of h->dynindx == -1.

	* elf32-arc.c (elf_arc_relocate_section): For a local R_ARC_TLS_GD_GOT,
	put the offset in the second got slot.
	(elf_arc_finish_dynamic_symbol) <GOT_TLS_GD>: For h->dynindx == -1,
	don't emit a R_ARC_TLS_DTPOFF reloc, just leave the contents of the
	second got slot as-is.

2014-03-24  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_check_relocs): Don't worry about relocs in pie.

2014-03-21 Claudiu Zissulescu <claziss@synopsys.com>

	* cpu-arc.c: Use ARCv2 as a generic name for ARCv2 processors.

2014-03-14 Claudiu Zissulescu <claziss@synopsys.com>

	* elf32-arc.c (elf_arc_relocate_section): Avoid truncation
	  only specific relocations. Otherwise keep the old logic.

2014-03-12 Claudiu Zissulescu <claziss@synopsys.com>

	* elf32-arc.c (elf_arc_relocate_section): Selective truncate
	  the last bits for pc relative relocations.

2014-03-12  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_ARC_link_hash_entry): Dissolve union u,
	make its members into direct members.  Changed all users.
	Add member force_got.
	(elf_ARC_link_hash_table): Rename {first,last}_deferred_tls_got
	to {first,last}_deferred_got.  Changed all users.
	(elf_arc_first_deferred_tls_got): Rename to ..
	(elf_arc_first_deferred_got) .. this.  Changed all users.
	(elf_arc_last_deferred_tls_got): Rename to ..
	(elf_arc_last_deferred_got) .. this.  Changed all users.
	(elf_ARC_link_hash_newfunc): Initialize force_got.
	(elf_ARC_discard_copies): Use SYMBOLS_CALL_LOCAL.
	(arc_got_to_pcrel): New function.
	(elf_arc_check_relocs): Defer normal GOT allocations.
	(elf_arc_relocate_section): Use arc_got_to_pcrel to resolve
	GOT relocs against local symbols directly.
	(arc_allocate_tls_got) Rename to ..
	(arc_allocate_got) .. this.  Changed caller.
	Process normal GOT allocations.

	* elf32-arc.c (elf_backend_copy_indirect_symbol): Define.
	(elf_ARC_link_hash_entry): New member got_alloc.
	(elf_ARC_link_hash_newfunc): Initialize got_alloc.
	(elf_ARC_copy_indirect_symbol): New function.
	(arc_got_to_pcrel): Add error on failure.
	(elf_arc_check_relocs): Set got_alloc.
	(arc_copy_got_alloc): New function.
	(arc_allocate_got): Call arc_copy_got_alloc via
	elf_ARC_link_hash_traverse.

2014-03-05  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_check_relocs): Check tls_type before
	considering ah->u.next_deferred.

2014-02-14  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (arc_plugin_one_reloc): No longer static.
	<R_ARC_TLS_DTPOFF{_S9}>: Add in old offset from INSN.
	(elf_arc_relocate_section) <R_ARC_TLS_DTPOFF{_S9}>: 
	The addend now provides a base symbol to subtract.
	(arc_elf32_write_relocs): New function.
	(arc_elf32_size_info): New const struct elf_size_info.
	(elf_backend_size_info): Define.

	* elf32-arc.c (arc_plugin_one_reloc): Undo recent check_overfl_neg
	change.

2014-02-11  Joern Rennecke  <joern.rennecke@embecosm.com>

	* reloc.c (BFD_RELOC_ARC_TLS_LE_32, BFD_RELOC_ARC_TLS_DTPOFF_S9):
	New values.
	* elf32-arc.c (elf_arc_howto_table): Update entry for
	R_ARC_TLS_DTPOFF.  Add entry for R_ARC_TLS_DTPOFF_S9.
	(arc_signed_reloc_type): Likewise.
	(arc_reloc_map): Add entries for R_ARC_TLS_DTPOFF and
	R_ARC_TLS_DTPOFF_S9.
	(arcompact_elf_me_reloc, arc_plugin_one_reloc): Handle
	R_ARC_TLS_DTPOFF and R_ARC_TLS_DTPOFF_S9.
	(elf_arc_check_relocs, elf_arc_relocate_section): Likewise.
	* bfd-in2.h, libbfd.h: Regenerate.

	* elf32-arc.c (elf_arc_check_relocs): When creating an executable,
	don't create GOT entries on behalf of R_ARC_TLS_IE_GOT relocs.

2014-02-11  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_relocate_section): For R_ARC_TLS_GD_GOT relocs
	against local symbols, output a R_ARC_TLS_DTPMOD reloc with zero
	symindex into output dso.

2014-02-11  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_relocate_section): Improve error message for
	unsupported GOT relocs against local symbols.

2014-02-10  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_relocate_section): Don't complain about
	R_ARC_NONE relocations against undefined symbols.

	* elf32-arc.c (elf_arc_relocate_section): For R_ARC_TLS_IE_GOT relocs
	against local symbols, output a R_ARC_TLS_TPOFF reloc into output dso.

2014-02-10  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_relocate_section) <R_ARC_TLS_IE_GOT>:
	Re-instate relocation adjustment, which was only partially dead
	after all.  Add comment.

2014-02-06  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_check_relocs): When creating an executable,
	for local symbols, change R_ARC_TLS_IE_GOT: and R_ARC_TLS_GD_GOT
	into R_ARC_TLS_LE_32.

2014-02-06  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (struct elf_ARC_link_hash_entry): Change type of
	tls_type to unsigned char.  Move pcrel_relocs_copied into
	new anonymous union u.  Remove member alloc_deferred.
	Changed all users.
	(struct elf_ARC_link_hash_table): New member deferred_tls_got.
	(elf_arc_deferred_tls_got): New define.
	(struct elf_arc_obj_tdata) <local_got_tls_type>:
	Change type to unsigned char.
	(elf_ARC_link_hash_table_create): Initialize deferred_tls_got member.
	(arc_tls_transition): Change type of second argument to
	"unsigned char *" - pointing to the tls_type.  Changed all callers.
	(elf_arc_check_relocs): Also enable tls transitions for static
	symbols, and defer GOT allocations for global symbols in
	R_ARC_TLS_IE_GOT relocs.
	Remove extra srelgot allocation for static GOT_TLS_GD variables.
	(elf_arc_relocate_section):  Also enable tls transitions for static
	symbols.
	<R_ARC_TLS_IE_GOT>: Remove dead relocation adjustment.
	(elf_arc_finish_dynamic_symbol): Remove GOT_TLS_LE handling.
	(arc_allocate_gd_got): Delete.
	(arc_allocate_tls_got): New function.
	(elf_arc_size_dynamic_sections): Call arc_allocate_tls_got instead of
	traversing the hash table with arc_allocate_gd_got.

	* elf32-arc.c (struct elf_ARC_link_hash_table): Replace member
	deferred_tls_got with first_deferred_tls_got and last_deferred_tls_got.
	(elf_arc_deferred_tls_got): Delete define.
	(elf_arc_first_deferred_tls_got): New define.
	(elf_arc_last_deferred_tls_got): Likewise.
	(elf_ARC_link_hash_table_create): Set up new members.
	(elf_arc_check_relocs): Read / write back last_deferred_tls_got
	from/to elf_arc_last_deferred_tls_got (info).
	(arc_allocate_tls_got): Read elf_arc_first_deferred_tls_got (info).

	* elf32-arc.c (elf_arc_check_relocs): Allocate local_got_offsets /
	elf_arc_local_got_tls_type indepdendent of got section.

	* elf32-arc.c (elf_arc_size_dynamic_sections): Unconditionally call
	arc_allocate_tls_got.

2014-02-06  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_check_relocs) <R_ARC_TLS_LE_{32,S9}>:
	Check hash entry pointer is non-NULL before using it.

2014-02-05  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (arc_tls_transition) <R_ARC_TLS_GD_LD>:
	Change direction of code move to better hide load latency.

2014-02-05  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_relocate_section): Move call of
	arc_tls_transition into the global symbol processing before
	the calculation of the relocation value.
	(arc_allocate_gd_got): If we are creating an executable, and
	a GOT_TLS_{IE,GD} symbol is accessed locally, change it to GOT_TLS_LE.
	(elf_arc_size_dynamic_sections): Change condition for hash table
	traversal with arc_allocate_gd_got to
	elf_hash_table (info)->dynamic_sections_created.

	* elf32-arc.c (elf_arc_finish_dynamic_symbol): Handle GOT_TLS_LE.

	* elf32-arc.c (elf_arc_finish_dynamic_symbol): Only use addend from
	GOT in the h->dynindx == -1 case.

2014-02-04  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (arc_tls_transition) <R_ARC_TLS_GD_LD>:
	Handle addend.
	(elf_arc_check_relocs): Remove unfulfillable check.

	* elf32-arc.c (elf_arc_relocate_section): Call arc_tls_transition
	only after we got the hash entry for the symbol.

2014-02-04  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (struct elf_ARC_link_hash_entry): New member
	alloc_deferred.
	(elf_ARC_link_hash_newfunc): Initialize it.
	(arc_plugin_one_reloc): Change second argument to
	enum elf_arc_reloc_type r_type.  Changed caller.
	Ignore R_ARC_NONE.
	(elf_arc_check_relocs): Remove code that tries to find out
	tls type first (which was pointless as it looked only at one
	module).  Add code to set tls_type tp GOT_TLS_LE in the normal
	switch.
	Defer allocation of R_ARC_TLS_GD_GOT.
	(arc_allocate_gd_got): New function.
	(elf_arc_size_dynamic_sections): Call traverse has table using
	arc_allocate_gd_got.

2014-02-03  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (tls_type_e): Add GOT_TLS_LE.
	(arc_plugin_one_reloc) <PLT32>: Don't scribble over add or nop.
	(arc_tls_transition): New function.
	(elf_arc_check_relocs): Find tls type of global symbols first.
	Use arc_tls_transition.
	(elf_arc_relocate_section): Use arc_tls_transition.

2014-02-03  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_check_relocs): Adjust R_ARC_TLS_GD_GOT reloc
	size for shared case too.

2014-02-03  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_finish_dynamic_symbol): Mask out bit 0
	(the 'initialized flag) of got offset in order to read got.

	* elf32-arc.c (elf_arc_relocate_section): Use SYMBOL_REFERENCES_LOCAL.

	* elf32-arc.c (elf_arc_check_relocs): Global dynamic needs two
	relocs for now.

2014-02-01  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (TCB_BASE_OFFSET): #if 0 previous definition,
	define as zero for now.

2014-01-30  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_check_relocs): Also create got section
	in static link for R_ARC_TLS_{IE,GD}_GOT.
	(elf_arc_relocate_section): Also adjust address for
	R_ARC_TLS_{IE,GD}_GOT.

	* elf32-arc.c (elf_arc_check_relocs): Remove R_ARC_TLS_{GD,IE}_GOT
	need_shared_reloc code.

	* elf32-arc.c (elf_arc_finish_dynamic_symbol): Handle GOT_TLS_GD.

2014-01-27  Joern Rennecke  <joern.rennecke@embecosm.com>
	Back out this change:
	2014-01-22  Joern Rennecke  <joern.rennecke@embecosm.com>
	* elf32-arc.c (elf_arc_relocate_section) <R_ARC_TLS_LE_{32,S9}>:
	Don't add TCB_SIZE.

2014-01-25  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_relocate_section): Don't complain about
	R_ARC_TLS_{IE,GD}_GOT relocations against undefined symbols.
	For R_ARC_TLS_IE, don't try to subtract
	elf_hash_table (info)->tls_sec->output_section->vma if there is no
	elf_hash_table (info)->tls_sec.

2014-01-24  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_ARC_link_hash_newfunc): Initialize ret->tls_type.

2014-01-23  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (arcompact_elf_me_reloc): Handle R_ARC_TLS_GD_GOT /
	R_ARC_TLS_IE_GOT / R_ARC_TLS_LE_32.
	(arc_plugin_one_reloc): Handle R_ARC_TLS_GD_GOT / R_ARC_TLS_IE_GOT.
	(elf_arc_relocate_section): Likewise.
	(elf_arc_finish_dynamic_symbol): Handle R_ARC_TLS_IE_GOT.

2014-01-22  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (elf_arc_relocate_section) <R_ARC_TLS_LE_{32,S9}>:
	Don't add TCB_SIZE.

2014-01-21  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (arc_elf_ignore_reloc, arc_elf_mkobject): New function.
	(tls_type_e): New enum.
	(elf_arc_obj_tdata): New struct.
	(elf_arc_tdata, elf_arc_local_got_tls_type): New macro.
	(ARC_IGNORE_HOWTO): Likewise.
	(elf_arc_howto_table): Add entries for R_ARC_TLS_GD_LD and
	R_ARC_TLS_GD_CALL.
	(arc_signed_reloc_type, arc_reloc_map): Likewise.
	(elf_arc_check_relocs): TLS support (WiP).
	* reloc.c: Add BFD_RELOC_ARC_TLS_GD_LD and BFD_RELOC_ARC_TLS_GD_CALL.
	* bfd-in2.h, libbfd.h: Regenerate.

2014-01-19  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (TCB_SIZE, TCB_BASE_OFFSET): Define.
	(elf_arc_howto_table) <R_ARC_TLS_LE_S9>: Change bitsize to 9.
	(arc_plugin_one_reloc): Handle R_ARC_TLS_LE_S9 and R_ARC_TLS_LE_32.
	(elf_arc_relocate_section): Likewise.

2014-01-16  Joern Rennecke  <joern.rennecke@embecosm.com>

	* reloc.c (BFD_RELOC_ARC_TLS_GD_GOT): New relocation.
	(BFD_RELOC_ARC_TLS_IE_GOT, BFD_RELOC_ARC_TLS_LE_S9): Likewise.
	(BFD_RELOC_ARC_TLS_LE_32): Likewise.
	* bfd-in2.h, libbfd.h: Regenerate.
	* elf32-arc.c (elf_arc_howto_table): Add HOWTOs for TLS relocations.
	(arc_reloc_map): Add mappings for TLS relocations.

2013-12-13  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elf32-arc.c (arc_signed_reloc_type): Add entry for R_ARC_32_PCREL.
	(arc_plugin_one_reloc): Handle R_ARC_PCREL (WiP).
	(elf_arc_check_relocs, elf_arc_relocate_section): Likewise.

	* elf32-arc.c (arc_signed_reloc_type): Add entries for TLS relocs.

2013-12-02  Simon Cook  <simon.cook@embecosm.com>

	* elf32-arc.c (elf_arc_check_relocs): Add error when relocs appear that
	shouldn't in read-only memory for shared libraries.

2013-11-22 Claudiu Zissulescu <claziss@synopsys.com>

	* elf32-arc.c (arc_elf_merge_private_bfd_data): Hard error if
	  we mix ARCv2EM with ARCv2HS objects.

2013-11-13 Claudiu Zissulescu <claziss@synopsys.com>

	* elf32-arc.c: Add arc_elf_copy_private_bfd_data() function.

2013-11-11 Claudiu Zissulescu <claziss@synopsys.com>

	* cpu-arc.c: Add HS as a valid processor type.
	* elf32-arc.c: Introduce arc_elf_set_private_flags() and
	  arc_elf_print_private_bfd_data(). Give warning if we link
	  two objects having different elf flags.

2013-11-06  Anton Kolesov  <anton.kolesov@synopsys.com>

	* elf32-arc.c (elf_backend_can_gc_sections): Set to 0, because
	--gc-sections causes known troubles for ARC.

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
