2012-09-25  Jeremy Bennett  <jeremy.bennett@embecosm.com>

	* arcompact-dis.c (dsmOneArcInst): Remove blank line to match
	version in binutils. Set register_for_indirect_jump even where
	implicit BLINK.
	(my_sprintf): Remove unused variable auxNum.

2012-06-05  Joern Rennecke  <joern.rennecke@embecosm.com>

	* arcompact-dis.c (my_sprintf): Don't abort for "%*".

2011-06-15  Brendan Kehoe  <brendan@zen.org>

	* arc-dis.c (BITS): Use sizeof(word)*8-1 instead of 31 to
	accommodate 64-bit hosts.
	* arcompact-dis.c (BITS): Likewise.

2011-06-09  Brendan Kehoe  <brendan@zen.org>

	* arc-dis.h (struct arcDisState): Make ADDRESSES unsigned int.
