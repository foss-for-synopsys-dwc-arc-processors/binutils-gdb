2014-02-11  Joern Rennecke  <joern.rennecke@embecosm.com>

	* arc.h (elf_arc_reloc_type): Add R_ARC_TLS_DTPOFF_S9 at 0x49,
	move following allocations.

2014-01-21  Joern Rennecke  <joern.rennecke@embecosm.com>

	* arc.h (elf_arc_reloc_type): Add R_ARC_TLS_GD_LD and R_ARC_TLS_GD_CALL.
	Move up R_ARC_TLS_IE_GOT, R_ARC_TLS_LE_S9 and R_ARC_TLS_LE_32.

2013-12-13  Joern Rennecke  <joern.rennecke@embecosm.com>

	* arc.h (elf_arc_reloc_type): Add R_ARC_32_PCREL.

	* arc.h (elf_arc_reloc_type): Add R_ARC_TLS_DTPMOD, R_ARC_TLS_DTPOFF,
	R_ARC_TLS_TPOFF, R_ARC_TLS_GD_GOT, R_ARC_TLS_IE_GOT and
	R_ARC_TLS_LE_S9.

2008-11-14  Irfan Rafiq  <irfan.rafiq@arc.com>
        * common.h (EM_ARCOMPACT) Removed obsolete flag and added new for ARCOMPACT cores.
