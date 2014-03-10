2014-03-10  Joern Rennecke  <joern.rennecke@embecosm.com>

	* scripttempl/arclinux.sc: PROVIDE_HIDDEN .tdata (in case the
	section won't be included).

2013-07-15: Christian Ruppert <christian.ruppert@abilis.com>

	* scripttempl/arcelf.sc: Only define ENTRY when not relocating.

2013-06-25  Simon Cook  <simon.cook@embecosm.com>

	* scripttempl/arclinux.sc: Only define ENTRY when not relocating.

2013-05-24  Vineet Gupta <vgupta@synopsys.com>

	* emulparams/arclinux.sh: Define COMMONPAGESIZE as 8k which
	enables generation of DATA_SEGMENT_ALIGN in linker scripts.
	* emulparams/arclinux_prof.sh: likewise
	* emulparams/arceblinux.sh: likewise
	* emulparams/arceblinux_prof.sh: likewise

2013-03-18  Simon Cook  <simon.cook@embecosm.com>

	* emulparams/arcelf.sh, emulparams/arcelf_prof.sh, emulparams/arclinux.sh,
	emulparams/arclinux.sh: Set OUTPUT_FORMAT based on toolchain endianness.
	* configure.tgt: Combined little and big endian target emulations.
	* Makefile.am (ALL_EMULATION_SOURCES): Removed big endian specific sources.
	* Makefile.in: Regenerated.

2013-03-12  Simon Cook  <simon.cook@embecosm.com>

	* emulparams/arcelf_prof.sh, emulparams/arcebelf_prof.sh: Change
	TEMPLATE_NAME to elf32.

2013-03-12  Simon Cook  <simon.cook@embecosm.com>

	* emulparams/arcelf.sh, emulparams/arcebelf.sh: Change TEMPLATE_NAME
	to elf32.

2013-03-04  Simon Cook  <simon.cook@embecosm.com>

	* Makefile.am (ALL_EMULATION_SOURCES): Added big endian sources.
	* Makefile.in: Regenerated.
	* configure.tgt: Added big endian ARC configurations.
	* emulparams/arcebelf.sh, emulparams/arcebelf_prof.sh,
	emulparams/arceblinux.sh, emulparams/arceblinux_prof.sh: New files.
	* testsuite/ld-discard/extern.d: Replace arc-*-* with arc*-*-*.
	* testsuite/ld-discard/start.d: Likewise.
	* testsuite/ld-discard/static.d: Likewise.
	* testsuite/ld-elf/group1.d: Likewise.
	* testsuite/ld-elf/group8a.d: Likewise.
	* testsuite/ld-elf/group9a.d: Likewise.
	* testsuite/ld-elf/group9b.d: Likewise.
	* testsuite/ld-elf/linkonce2.d: Likewise.
	* testsuite/ld-elf/merge.d: Likewise.
	* testsuite/ld-elf/merge2.d: Likewise.
	* testsuite/ld-elf/orphan-region.d: Likewise.
	* testsuite/ld-elf/orphan.d: Likewise.
	* testsuite/ld-elf/orphan3.d: Likewise.
	* testsuite/ld-elf/pr12851.d: Likewise.
	* testsuite/ld-elf/pr12975.d: Likewise.
	* testsuite/ld-elf/pr13195.d: Likewise.
	* testsuite/ld-elf/pr349.d: Likewise.
	* testsuite/ld-elf/sec64k.exp: Likewise.
	* testsuite/ld-elf/warn1.d: Likewise.
	* testsuite/ld-elf/warn2.d: Likewise.
	* testsuite/ld-elf/warn3.d: Likewise.
	* testsuite/lib/ld-lib.exp: Likewise.

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
