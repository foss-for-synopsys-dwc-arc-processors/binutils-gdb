2012-04-17  Joern Rennecke  <joern.rennecke@embecosm.com>

	* dwarf2.c (read_rangelist): Apply sanity check to offset.

2012-04-03  Joern Rennecke  <joern.rennecke@embecosm.com>

	* config.bfd (arc*, arc*-*-linux-uclibc*): New configurations.
	* config.sub (arceb, arc[67]0[01], arc[67]0[01]eb): New configurations.

2010-09-28  Brendan Kehoe  <brendan@zen.org>

	* elf32-arc.c (arc_elf_object_p): Init MACH with 0.

2010-05-31  Brendan Kehoe  <brendan@zen.org>

	* elf32-arc.c (arc_elf_object_p): Instead of returning FALSE if
	we don't recognize (e.g., a default of 0 which used to be
	processed as E_ARC_MACH_A4 which we no longer claim offer to
	support), follow the example of many other ports by letting the
	set_arch_mach callback at least make sure we've not been handed
	garbage.

