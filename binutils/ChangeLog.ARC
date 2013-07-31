2013-07-30 Vineet Gupta <vgupta@synopsys.com>

	* readelf.c (get_machine_flags): print ABI v3 flag for EM_ARCOMPACT.
	EM_ARCV2 only supports E_ARC_OSABI_V3 in Linux OS ABI

2013-06-28 Vineet Gupta <vgupta@synopsys.com>

	* readelf.c : Globally replaced EM_ARCOMPACT2 with EM_ARCV2.
	(get_machine_flags) Changed strings to "ARCv2"
	(get_machine_name) likewise

2012-10-08  Simon Cook  <simon.cook@embecosm.com>

	* testsuite/binutils-all/arc: Added objdump test

2012-08-30  Simon Cook  <simon.cook@embecosm.com>

    * readelf.c (is_32bit_abs_reloc): Change reloc type to match elf/arc.h.
    (get_machine_name): Replace EM_ARC_A5 with EM_ARCOMPACT.

2010-08-19  Michael Eager  <eager@eagercon.com>

	* readelf.c (get_machine_flags): Return ARC601 for E_ARC_MACH_ARC601.

