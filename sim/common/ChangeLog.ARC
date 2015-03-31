2015-03-31  Mike Frysinger  <vapier@gentoo.org>

	Cherry pick commit 5a394431deb3745c04a74d2a109aca075f79afd6 from
	upstream.
	* cgen-mem.h (MEMOPS_INLINE): Change to EXTERN_INLINE.
	* cgen-ops.h (SEMOPS_INLINE): Likewise.

2015-03-29  Mike Frysinger  <vapier@gentoo.org>

	Cherry pick commit 92fc6153a6fdf2a027d9780f5945712aafad4a9e from
	upstream.
	* sim-arange.h (SIM_ARANGE_INLINE): Move above sim_addr_range_hit_p.
	(sim_addr_range_hit_p): Change INLINE to SIM_ARANGE_INLINE.
	* sim-inline.h (INLINE2): Define to gnu_inline when available.

2013-03-17  Joern Rennecke  <joern.rennecke@embecosm.com>

	* cgen-trace.c: Merge from;
	Customer-Projects/synopsys/arc_gnu/branches/arc_gnu_4.8/srcw-20120503.
	* gennltvals.sh, gentvals.sh, syscall.c: Likewise.
	* nltvals.def: Regenerate.

2007-09-17  J"orn Rennecke  <joern.rennecke@arc.com>

	* gentvals.sh: Allow target-specific definitions to override
	later generic ones.
	* gennltvals.sh: Use ${srcroot}/newlib/libc/sys/arc/sys/fcntl.h
	for open on arc.
	* nltvals.def: Regenerate.

2007-08-22  J"orn Rennecke  <joern.rennecke@arc.com>

	* cgen-trace.c (sim_cgen_disassemble_insn): Check for
	CGEN_INSN_DISASM_BITSIZE.

2007-05-02  J"orn Rennecke  <joern.rennecke@arc.com>

	* syscall.c (get_path): No longer static.

2007-04-30  J"orn Rennecke  <joern.rennecke@arc.com>

	* gennltvals.sh: Add arc code.
	* nltvals.def: Regenerate.

