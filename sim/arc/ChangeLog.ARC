2011-11-25  Joern Rennecke  <joern.rennecke@embecosm.com>

	* configure: Regenerate - with a temporary copy of
	../common/aclocal.m4 to get the right autom4te.cache.

2011-06-28  Brendan Kehoe  <brendan@zen.org>

	* Makefile.in (stamp-{5,6,7}mloop): Add new '-shell $(SHELL)'
	argument to each invocation.

2010-04-02  Brendan Kehoe <brendan@zen.org>

	* Makefile.in (cpu5.o, decode5.o, sem5.o, model5.o): Fix
	dependency to use ARC5_INCLUDE_DEPS.
	
	* ChangeLog.ARC: New file.

