2012-10-16  Simon Cook <simon.cook@embecosm.com>

	* ChangeLog: Applied patch from 2009-02-16 by Alan Modra to solve
	segfaults.
	* emultempl/beos.em: Likewise.
	* emultempl/pe.em: Likewise.
	* emultempl/pep.em: Likewise.
	* emultempl/spuelf.em: Likewise.
	* emultempl/xtensaelf.em: Likewise.
	* ld/ldctor.c: Likewise.
	* ld/ldlang.c: Likewise.
	* ld/ldlang.h: Likewise.

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
