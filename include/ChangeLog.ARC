2015-03-26  Claudiu Zissulescu <claziss@synopsys.com>

	* elf/arc.h: Add R_ARC_SDA16_ST2, R_ARC_SDA_12,
	R_ARC_S21W_PCREL_PLT, R_ARC_S25H_PCREL_PLT,
	R_ARC_S25W_PCREL_PLT, R_ARC_S21H_PCREL_PLT relocations.

2015-02-18  Andrew Burgess  <andrew.burgess@embecosm.com>

	* opcode/arc.h (arc_mach_a4): Remove declaration.

2013-11-11  Claudiu Zissulescu <claziss@synopsys.com>

	* elf/arc.h: Rename E_ARC_MACH_ARCV2 to
	  EF_ARC_CPU_ARCV2EM. Define EF_ARC_CPU_GENERIC and
	  EF_ARC_CPU_ARCV2HS.

2013-06-28 Vineet Gupta <vgupta@synopsys.com>

	* elf/common.h: Replaced EM_ARCOMPACT2 with EM_ARCV2

2013-01-30 Claudiu Zissulescu <claziss@synopsys.com>

	* elf/common.h : Defined EM_ARCOMPACT2 for EM architectures
	* opcode/arc.h: Define ARC_MACH_ARCV2
	* elf/arc.h: Define E_ARC_MACH_ARCV2

2012-12-06  Simon Cook  <simon.cook@embecosm.com>

	* opcode/arc.h: Change opcode syntax strings to be unsigned.

2012-12-04  Simon Cook  <simon.cook@embecosm.com>

	* opcode/arc.h: Support for non-@ operand types.

2010-08-19  Michael Eager <eager@eagercon.com>

	* elf.h: Define E_ARC_MACH_ARC601 = 4.

14  Irfan Rafiq  <irfan.rafiq@arc.com>
	* dis-asm.h (arc_get_disassembler) Update prototype.
