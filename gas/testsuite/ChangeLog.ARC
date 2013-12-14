2013-12-14  Joern Rennecke  <joern.rennecke@embecosm.com>

	* gas/arc/pcl.s, gas/arc/pcl.d: New test.
	* gas/arc/arc700.exp: Run it.

2015-02-18  Andrew Burgess  <andrew.burgess@embecosm.com>

	* gas/arc/warn.s: Update error message to reflect change in
	default architecture.

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
