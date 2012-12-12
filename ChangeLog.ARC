2012-12-12  Jeremy Bennett <jeremy.bennett@embecosm.com>

	Manual merge from GDB 6.8 branch.

	* README.arcgdb: Merged as new file.
	* config.sub: Merged.

2012-04-03  Joern Rennecke  <joern.rennecke@embecosm.com>

	* config.sub (arceb, arc[67]0[01], arc[67]0[01]eb): New configurations.

2011-03-01  Brendan Kehoe  <brendan@zen.org>

	Bring better disassembly in from binutils-2.19; this includes
	some bits for the ARC601 support to sync the trees.
	* include/opcode/arc.h: Updated.
	* opcodes/{arc-dis.c, arc-dis.h, arc-opc.c, arc-opc.h,
	arc-dis-cgen.c, arc-dis-cgen.h, arcompact-dis.c,
	arcompact-dis.h, arc-opc-cgen.c, arc-opc-cgen.h}: Updated.
	* include/dis-asm.h (arc_get_disassembler): Change arg to bfd*.
	* include/elf/arc.h: Updated.
	* gdb/arc-linux-tdep.c: Include opcodes/arc-dis.h for
	arcDisState.
