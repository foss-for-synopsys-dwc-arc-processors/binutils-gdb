2013-02-26  Simon Cook  <simon.cook@embecosm.com>

	* configure.tgt (arc*-*-elf*): Add arclinux emulation scripts.
	(arc*-*-linux-uclibc*): Add arcelf emulation scripts.
	* scripttempl/elfarc.sc: Set default linker endianness based on
	configured target.

2013-02-25  Simon Cook  <simon.cook@embecosm.com>

	* configure.tgt: Make arc*-*-elf* valid for big endian ARC.

2013-02-05  Simon Cook  <simon.cook@embecosm.com>

	* configure.tgt: Split elf and uClibc default emulation script definitons.
	* Makefile.am: Correct emulation sources file names.
	* Makefile.in: Regenerated.

2012-10-19  Simon Cook  <simon.cook@embecosm.com>

	* scripttempl/arclinux.sc: Set default linker endianness based on
	configured target.

2012-10-18  Simon Cook <simon.cook@embecosm.com>

	* scripttempl/arclinux.sc: Applied patch from Vineet to solve
	aggregation of of .arcextmap sections.
	* scripttempl/elfarc.sc: Likewise.

2012-04-03  Joern Rennecke  <joern.rennecke@embecosm.com>

	* configure.tgt (arc*-*-linux-uclibc*): New configurations.

2011-11-29  Joern Rennecke  <joern.rennecke@embecosm.com>

	* elfarc.sc: Copy .gcc_except_table handling from elf.sc.

2008-04-09  J"orn Rennecke  <joern.rennecke@arc.com>

	Makefile.am (earcelf.c): Fix dependency.

	* Makefile.am (ALL_EMULATIONS): Add earcelf_prof.o and earclinux_prof.o.
	(earcelf_prof.c, earclinux_prof.c): New rules.
	* Makefile.in: Regenerate.
	* emulparams/arcelf.sh (OTHER_READONLY_SECTIONS): Don't define.
	(OTHER_BSS_SECTIONS): Likewise.
	* (OTHER_SECTIONS): Define.
	* emulparams/arclinux.sh (OTHER_SECTIONS): Define.
	* emulparams/arcelf_prof.sh, emulparams/arclinux_prof.sh: New files.
	* configure.tgt (arc-*-elf* | arc-*-linux-uclibc*): Add arcelf_prof
	and arclinux_prof to targ_extra_emuls.

2007-09-11  J"orn Rennecke  <joern.rennecke@arc.com>

	* emulparams/arcelf.sh (OTHER_READONLY_SECTIONS): Define.
	(OTHER_BSS_SECTIONS): Likewise.

2007-08-08  J"orn Rennecke  <joern.rennecke@arc.com>

	* emulparams/arcelf.sh (TEXT_START_ADDR): Now 0x100.
	(NONPAGED_TEXT_START_ADDR): Don't define.
	(EMBEDDED): Set to yes.

2007-05-10  J"orn Rennecke  <joern.rennecke@arc.com>

	* scripttempl/arclinux.sc (SECTIONS): Check symbols __HEAP_SIZE,
	__DEFAULT_HEAP_SIZE, __STACK_SIZE and __DEFAULT_STACK_SIZE.
	* scripttempl/elfarc.sc: Likewise.
