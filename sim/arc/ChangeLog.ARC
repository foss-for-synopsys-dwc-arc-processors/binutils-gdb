2013-03-19  Joern Rennecke  <joern.rennecke@embecosm.com>

	* sim-main.h (CGEN_INSN_WORD): Remove typedef.

2013-03-17  Joern Rennecke  <joern.rennecke@embecosm.com>

	* decode5.c, decode5.h, decode6.c, decode6.h: Regenerate.
	* decode7.c, decode7.h, cpuall.h: Likewise.
	* model5.c, model6,c, model7.c: Likewise.
	* sem5-switch.c, sem5.c, sem6-switch.c, sem6.c: Likewise.
	* sem7-switch.c, sem7.c: Likewise.

2013-03-17  Joern Rennecke  <joern.rennecke@embecosm.com>

	* Makefile.in: Merge from;
	Customer-Projects/synopsys/arc_gnu/branches/arc_gnu_4.8/srcw-20120503.
	* arc5.c, arc6.c, arc7.c, configure.ac, sim-if.c, sim-main.h: Likewise.
	* traps.c: Likewise.
	* arch.h, cpu5.h, cpu6.h, cpu7.h, configure: Regenerate.
	* arch.c, cpu5.c, cpu6.c, cpu7.c: Likewise.

	* sim-main.h (CGEN_INSN_WORD): Reinstate typedef.

2013-01-08  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* decode5.c, decode6.c, decode7.c: Replace EXTRACT_MSB0_INT with
	EXTRACT_MSB0_SINT throughout.
	* devices.c (device_error): Match function prototype to common
	declaration.
	* sim-main.h <CGEN_INSN_WORD>: Define type.
	* target-io.h: New file (based on old gdb/target-io/arc.h).
	* traps.c: Include local target-io.h instead of
	gdb/target-io/arc.h.
	(arc_syscall): Comment out unlinkable code for stat and fstat and
	abort instead (temporary workaround).

2012-12-13  Jeremy Bennett <jeremy.bennett@embecosm.com>

	* aclocal.m4: New file generated.
	* config.in, configure: Regenerated.
	* configure.ac: Updated for autoconf 2.64. Use
	common/acinclude.m4.

2012-12-12  Jeremy Bennett <jeremy.bennett@embecosm.com>

	Manual merge from GDB 6.8 branch.

	* ChangeLog.ARC, Makefile.in, arc-sim-registers.c,
	* arc-sim-registers.h, arc-sim.h, arc5.c, arc6.c, arc7.c, arch.c,
	* arch.h, config.in, configure, configure.ac, cpu5.c, cpu5.h,
	* cpu6.c, cpu6.h, cpu7.c, cpu7.h, cpuall.h, decode5.c, decode5.h,
	* decode6.c, decode6.h, decode7.c, decode7.h, devices.c, mloop5.in,
	* mloop6.in, mloop7.in, model5.c, model6.c, model7.c, sem5-switch.c,
	* sem5.c, sem6-switch.c, sem6.c, sem7-switch.c, sem7.c, sim-if.c,
	* sim-main.h, syscall.h, tconfig.in, traps-linux.c, traps.c: Merge
	as new files.

2011-11-25  Joern Rennecke  <joern.rennecke@embecosm.com>

	* configure: Regenerate - with a temporary copy of
	../common/aclocal.m4 to get the right autom4te.cache.

2011-06-28  Brendan Kehoe  <brendan@zen.org>

	* Makefile.in (stamp-{5,6,7}mloop): Add new '-shell $(SHELL)'
	argument to each invocation.

2010-04-02  Brendan Kehoe <brendan@zen.org>

	* Makefile.in (cpu5.o, decode5.o, sem5.o, model5.o): Fix
	dependency to use ARC5_INCLUDE_DEPS.

	* ChangeLog.ARC: New file.

