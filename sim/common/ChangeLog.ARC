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

