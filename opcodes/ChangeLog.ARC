2011-06-15  Brendan Kehoe  <brendan@zen.org>

	* arc-dis.c (BITS): Use sizeof(word)*8-1 instead of 31 to
	accommodate 64-bit hosts.
	* arcompact-dis.c (BITS): Likewise.

2011-06-09  Brendan Kehoe  <brendan@zen.org>

	* arc-dis.h (struct arcDisState): Make ADDRESSES unsigned int.
