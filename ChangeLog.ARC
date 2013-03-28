2013-03-28  Vineet Gupta <vgupta@synopsys.com>

	* include/elf/arc.h: E_ARC_OSABI_CURRENT bumped to v3 due to newer
	kernel syscall ABI (3.9 kernel + uClibc 0.9.34)

2013-02-25  Simon Cook  <simon.cook@embecosm.com>

	* Makefile.def: Brought in from updated gcc.
	* Makefile.in: Likewise.
	* configure: Likewise.
	* configure.ac: Likewise.

2013-02-25  Simon Cook  <simon.cook@embecosm.com>

	* config.sub: Make arceb-* valid.
	* configure.ac: Make arceb-*-* valid.
	* configure: Regenerate.

2013-02-05  Simon Cook  <simon.cook@embecosm.com>

	* configure: Regenerated.

2012-08-18  Vineet Gupta <vgupta@synopsys.com>

	* include/elf/arc.h: Extended "machine" bit-field in e_flags to	8-bits,
	to make it more future safe. Thus EF_ARC_MACH_MSK changed (0xf => 0xff).
	Corollarily, syscall ABI ver place-holder is now at 8:11, thus
	E_ARC_OSABI_V2 value adjustment (0x20 => 0x200)

2012-08-17  Vineet Gupta <vgupta@synopsys.com>

	* include/elf/arc.h: Introduced EF_ARC_OSABI_MSK as placeholder for
	syscall ABI ver in elfhdr e_flags bits 4:7
	Added E_ARC_OSABI_ORIG and E_ARC_OSABI_V2 as well E_ARC_OSABI_CURRENT
	to point to latest ABI ver.
	* bfd/elf32-arc.c: arc_elf_object_p() adds the ABI ver to e_flags
	* binutils/readelf.c: get_machine_flags() decodes/prints ARC OS ABI ver

2012-04-03  Joern Rennecke  <joern.rennecke@embecosm.com>

	* config.sub (arceb, arc[67]0[01], arc[67]0[01]eb): New configurations.
