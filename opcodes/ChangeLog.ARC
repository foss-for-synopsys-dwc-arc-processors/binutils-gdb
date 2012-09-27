2012-09-27  Simon Cook  <simon.cook@embecosm.com>

	* arcompact-dis.c (dsmOneArcInst): Added disassembler
	support for MPY, MPYH, MPYHU, MPYU instructions.

2012-06-05  Joern Rennecke  <joern.rennecke@embecosm.com>

	* arcompact-dis.c (my_sprintf): Don't abort for "%*".

2011-06-15  Brendan Kehoe  <brendan@zen.org>

	* arc-dis.c (BITS): Use sizeof(word)*8-1 instead of 31 to
	accommodate 64-bit hosts.
	* arcompact-dis.c (BITS): Likewise.

2011-06-09  Brendan Kehoe  <brendan@zen.org>

	* arc-dis.h (struct arcDisState): Make ADDRESSES unsigned int.
