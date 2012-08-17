2012-08-17  Vineet Gupta <vgupta@synopsys.com>

	* include/elf/arc.h: Introduced EF_ARC_OSABI_MSK as placeholder for
	syscall ABI ver in elfhdr e_flags bits 4:7
	Added E_ARC_OSABI_ORIG and E_ARC_OSABI_V2 as well E_ARC_OSABI_CURRENT
	to point to latest ABI ver.
	* bfd/elf32-arc.c: arc_elf_object_p() adds the ABI ver to e_flags
	* binutils/readelf.c: get_machine_flags() decodes/prints ARC OS ABI ver

2012-04-03  Joern Rennecke  <joern.rennecke@embecosm.com>

	* config.sub (arceb, arc[67]0[01], arc[67]0[01]eb): New configurations.
