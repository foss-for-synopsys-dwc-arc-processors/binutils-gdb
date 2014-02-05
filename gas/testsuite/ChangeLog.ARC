2014-02-05  Joern Rennecke  <joern.rennecke@embecosm.com>

	* gas/arc/tls-3.s, gas/arc/tls-3.d: New test.
	* gas/arc/arc700.exp: Run it.

2014-01-22  Joern Rennecke  <joern.rennecke@embecosm.com>

	* gas/arc/tls-2.s, gas/arc/tls-2.d: New test.
	* gas/arc/arc700.exp: Run it.

2014-01-16  Joern Rennecke  <joern.rennecke@embecosm.com>

	* gas/arc/tls.s, gas/arc/tls.d: New test.
	* gas/arc/arc700.exp: Run it.

2014-01-14  Joern Rennecke  <joern.rennecke@embecosm.com>

	* gas/arc/warn.s: Adjust for change of default from Arctangent-A4 to
	Arctangent-A5.

2013-12-14  Joern Rennecke  <joern.rennecke@embecosm.com>

	* gas/arc/pcl.s, gas/arc/pcl.d: New test.
	* gas/arc/arc700.exp: Run it.

2013-06-14  Claudiu Zissulescu <claziss@synopsys.com>

	* gas/arc/warn.exp: Extend script for errors and warnings
        * gas/arc/extopts-err-1.s: test the extended library options for EM.

2013-06-14  Simon Cook  <simon.cook@embecosm.com>

	* gas/arc/warn.s: Update long immediate data error message

2013-06-14  Claudiu Zissulescu <claziss@synopsys.com>

	* gas/arc/warn.s: Update error message

2013-03-28  Simon Cook  <simon.cook@embecosm.com>

	* gas/arc/dsp1.d, gas/arc/dsp2.d, gas/arc/general_a700.d,
	mpy_a700.d, prefetch.d, sub_s.d: Fix patterns to check for tests.

2008-11-25  Irfan Rafiq <irfan.rafiq@arc.com>

	* gas/lns/lns.exp		TODO: Exclude for ARC 
	* gas/all/gas.exp		Overhaul testsuite. TODO: activate remaining.
	* gas/arc/{ swi, sbc, add,	Updated standards after verification.
	            sleep, brk, swi,
	            rcc, bic, extb, asl,
	            asr, sexw, adc, j, 
	            lsr,mov,ror,and, 
	            xor, rlc, or, st,
	            jl, extw,add, sub}
