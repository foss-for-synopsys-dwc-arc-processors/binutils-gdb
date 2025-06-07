	# xarcvvdsp - architecture set
	.option push
	.option arch, rv32i
	.include "x-arcv-vdsp.s"
	.option pop

	# xarcvvdsp - wrong number of operands

	arcv.vmv.v.s v0,v3
	arcv.vmv.v.s v3,v6
	arcv.vmv.v.s v6,v0

	arcv.vmv.s.v v0,v3
	arcv.vmv.s.v v3,v6
	arcv.vmv.s.v v6,v0

	arcv.vmvi.v.s v0,v3
	arcv.vmvi.v.s v3,v6
	arcv.vmvi.v.s v6,v0

	arcv.vmvi.s.v v0,v3
	arcv.vmvi.s.v v3,v6
	arcv.vmvi.s.v v6,v0

	arcv.vnorm.v v0
	arcv.vnorm.v v3

	arcv.vssabs.v v0
	arcv.vssabs.v v3

	arcv.vsneg.v v0
	arcv.vsneg.v v3

	arcv.vclr.v.i v0
	arcv.vclr.v.i v3

	arcv.vsra.vv v0,v3
	arcv.vsra.vv v3,v6
	arcv.vsra.vv v6,v0

	arcv.vsra.vx v0,v3
	arcv.vsra.vx v3,v6
	arcv.vsra.vx v6,v0

	arcv.vsra.vi v0,v3
	arcv.vsra.vi v3,v6
	arcv.vsra.vi v6,v0

	arcv.vsrat.vv v0,v3
	arcv.vsrat.vv v3,v6
	arcv.vsrat.vv v6,v0

	arcv.vsrat.vx v0,v3
	arcv.vsrat.vx v3,v6
	arcv.vsrat.vx v6,v0

	arcv.vsrat.vi v0,v3
	arcv.vsrat.vi v3,v6
	arcv.vsrat.vi v6,v0

	arcv.vsra.s.vv v0,v3
	arcv.vsra.s.vv v3,v6
	arcv.vsra.s.vv v6,v0

	arcv.vsra.s.vx v0,v3
	arcv.vsra.s.vx v3,v6
	arcv.vsra.s.vx v6,v0

	arcv.vsra.s.vi v0,v3
	arcv.vsra.s.vi v3,v6
	arcv.vsra.s.vi v6,v0

	arcv.vsra.2s.vv v0,v3
	arcv.vsra.2s.vv v3,v6
	arcv.vsra.2s.vv v6,v0

	arcv.vsra.2s.vx v0,v3
	arcv.vsra.2s.vx v3,v6
	arcv.vsra.2s.vx v6,v0

	arcv.vsra.2s.vi v0,v3
	arcv.vsra.2s.vi v3,v6
	arcv.vsra.2s.vi v6,v0

	arcv.vnsra.wv v0,v3
	arcv.vnsra.wv v3,v6
	arcv.vnsra.wv v6,v0

	arcv.vnsra.wx v0,v3
	arcv.vnsra.wx v3,v6
	arcv.vnsra.wx v6,v0

	arcv.vnsra.wi v0,v3
	arcv.vnsra.wi v3,v6
	arcv.vnsra.wi v6,v0

	arcv.vnsra.s.wv v0,v3
	arcv.vnsra.s.wv v3,v6
	arcv.vnsra.s.wv v6,v0

	arcv.vnsra.s.wx v0,v3
	arcv.vnsra.s.wx v3,v6
	arcv.vnsra.s.wx v6,v0

	arcv.vnsra.s.wi v0,v3
	arcv.vnsra.s.wi v3,v6
	arcv.vnsra.s.wi v6,v0

	arcv.vnsra.2s.wv v0,v3
	arcv.vnsra.2s.wv v3,v6
	arcv.vnsra.2s.wv v6,v0

	arcv.vnsra.2s.wx v0,v3
	arcv.vnsra.2s.wx v3,v6
	arcv.vnsra.2s.wx v6,v0

	arcv.vnsra.2s.wi v0,v3
	arcv.vnsra.2s.wi v3,v6
	arcv.vnsra.2s.wi v6,v0

	arcv.vnsra.qv v0,v3
	arcv.vnsra.qv v3,v6
	arcv.vnsra.qv v6,v0

	arcv.vnsra.qx v0,v3
	arcv.vnsra.qx v3,v6
	arcv.vnsra.qx v6,v0

	arcv.vnsra.qi v0,v3
	arcv.vnsra.qi v3,v6
	arcv.vnsra.qi v6,v0

	arcv.vnsra.s.qv v0,v3
	arcv.vnsra.s.qv v3,v6
	arcv.vnsra.s.qv v6,v0

	arcv.vnsra.s.qx v0,v3
	arcv.vnsra.s.qx v3,v6
	arcv.vnsra.s.qx v6,v0

	arcv.vnsra.s.qi v0,v3
	arcv.vnsra.s.qi v3,v6
	arcv.vnsra.s.qi v6,v0

	arcv.vnsra.2s.qv v0,v3
	arcv.vnsra.2s.qv v3,v6
	arcv.vnsra.2s.qv v6,v0

	arcv.vnsra.2s.qx v0,v3
	arcv.vnsra.2s.qx v3,v6
	arcv.vnsra.2s.qx v6,v0

	arcv.vnsra.2s.qi v0,v3
	arcv.vnsra.2s.qi v3,v6
	arcv.vnsra.2s.qi v6,v0

	arcv.vwsra.vv v0,v3
	arcv.vwsra.vv v3,v6
	arcv.vwsra.vv v6,v0

	arcv.vwsra.vx v0,v3
	arcv.vwsra.vx v3,v6
	arcv.vwsra.vx v6,v0

	arcv.vwsra.vi v0,v3
	arcv.vwsra.vi v3,v6
	arcv.vwsra.vi v6,v0

	arcv.vaddsub.vv v0,v3
	arcv.vaddsub.vv v3,v6
	arcv.vaddsub.vv v6,v0

	arcv.vsaddsub.vv v0,v3
	arcv.vsaddsub.vv v3,v6
	arcv.vsaddsub.vv v6,v0

	arcv.vsaaddsub.vv v0,v3
	arcv.vsaaddsub.vv v3,v6
	arcv.vsaaddsub.vv v6,v0

	arcv.vqrdot.vv v0,v3
	arcv.vqrdot.vv v3,v6
	arcv.vqrdot.vv v6,v0

	arcv.vqrdot.2s.vv v0,v3
	arcv.vqrdot.2s.vv v3,v6
	arcv.vqrdot.2s.vv v6,v0

	arcv.vwsrdot.2s.vv v0,v3
	arcv.vwsrdot.2s.vv v3,v6
	arcv.vwsrdot.2s.vv v6,v0

	arcv.vqrdotu.vv v0,v3
	arcv.vqrdotu.vv v3,v6
	arcv.vqrdotu.vv v6,v0

	arcv.vqrdotsu.vv v0,v3
	arcv.vqrdotsu.vv v3,v6
	arcv.vqrdotsu.vv v6,v0

	arcv.vwrdot.vv v0,v3
	arcv.vwrdot.vv v3,v6
	arcv.vwrdot.vv v6,v0

	arcv.vwsrdot.vv v0,v3
	arcv.vwsrdot.vv v3,v6
	arcv.vwsrdot.vv v6,v0

	arcv.vwrdotu.vv v0,v3
	arcv.vwrdotu.vv v3,v6
	arcv.vwrdotu.vv v6,v0

	arcv.vwrdotsu.vv v0,v3
	arcv.vwrdotsu.vv v3,v6
	arcv.vwrdotsu.vv v6,v0

	arcv.vwsmac.vv v0,v3
	arcv.vwsmac.vv v3,v6
	arcv.vwsmac.vv v6,v0

	arcv.vwsmac.vx v0,v3
	arcv.vwsmac.vx v3,v6
	arcv.vwsmac.vx v6,v0

	arcv.vwsnmsac.vv v0,v3
	arcv.vwsnmsac.vv v3,v6
	arcv.vwsnmsac.vv v6,v0

	arcv.vwsnmsac.vx v0,v3
	arcv.vwsnmsac.vx v3,v6
	arcv.vwsnmsac.vx v6,v0

	arcv.vwmul.hv v0,v3
	arcv.vwmul.hv v3,v6
	arcv.vwmul.hv v6,v0

	arcv.vwmul.hx v0,v3
	arcv.vwmul.hx v3,v6
	arcv.vwmul.hx v6,v0

	arcv.vwmac.hv v0,v3
	arcv.vwmac.hv v3,v6
	arcv.vwmac.hv v6,v0

	arcv.vwmac.hx v0,v3
	arcv.vwmac.hx v3,v6
	arcv.vwmac.hx v6,v0

	arcv.vwmulu.hv v0,v3
	arcv.vwmulu.hv v3,v6
	arcv.vwmulu.hv v6,v0

	arcv.vwmulu.hx v0,v3
	arcv.vwmulu.hx v3,v6
	arcv.vwmulu.hx v6,v0

	arcv.vwmacu.hv v0,v3
	arcv.vwmacu.hv v3,v6
	arcv.vwmacu.hv v6,v0

	arcv.vwmacu.hx v0,v3
	arcv.vwmacu.hx v3,v6
	arcv.vwmacu.hx v6,v0

	arcv.vwrdot.hv v0,v3
	arcv.vwrdot.hv v3,v6
	arcv.vwrdot.hv v6,v0

	arcv.vwrdotu.hv v0,v3
	arcv.vwrdotu.hv v3,v6
	arcv.vwrdotu.hv v6,v0

	arcv.vsmulf.hv v0,v3
	arcv.vsmulf.hv v3,v6
	arcv.vsmulf.hv v6,v0

	arcv.vsmulf.hx v0,v3
	arcv.vsmulf.hx v3,v6
	arcv.vsmulf.hx v6,v0

	arcv.vwmulf.hv v0,v3
	arcv.vwmulf.hv v3,v6
	arcv.vwmulf.hv v6,v0

	arcv.vwmulf.hx v0,v3
	arcv.vwmulf.hx v3,v6
	arcv.vwmulf.hx v6,v0

	arcv.vwsmacf.hv v0,v3
	arcv.vwsmacf.hv v3,v6
	arcv.vwsmacf.hv v6,v0

	arcv.vwsmacf.hx v0,v3
	arcv.vwsmacf.hx v3,v6
	arcv.vwsmacf.hx v6,v0

	arcv.vwsnmsacf.hv v0,v3
	arcv.vwsnmsacf.hv v3,v6
	arcv.vwsnmsacf.hv v6,v0

	arcv.vwsnmsacf.hx v0,v3
	arcv.vwsnmsacf.hx v3,v6
	arcv.vwsnmsacf.hx v6,v0

	arcv.vwsrdotf.hv v0,v3
	arcv.vwsrdotf.hv v3,v6
	arcv.vwsrdotf.hv v6,v0

	arcv.vmv.v.s v0,v3,t6,t0
	arcv.vmv.v.s v3,v6,t0,t0
	arcv.vmv.v.s v6,v0,t3,t0

	arcv.vmv.s.v v0,v3,t6,t0
	arcv.vmv.s.v v3,v6,t0,t0
	arcv.vmv.s.v v6,v0,t3,t0

	arcv.vmvi.v.s v0,v3,6,t0
	arcv.vmvi.v.s v3,v6,0,t0
	arcv.vmvi.v.s v6,v0,3,t0

	arcv.vmvi.s.v v0,v3,6,t0
	arcv.vmvi.s.v v3,v6,0,t0
	arcv.vmvi.s.v v6,v0,3,t0

	arcv.vnorm.v v0,v3,t0
	arcv.vnorm.v v3,v6,t0

	arcv.vssabs.v v0,v3,t0
	arcv.vssabs.v v3,v6,t0

	arcv.vsneg.v v0,v3,t0
	arcv.vsneg.v v3,v6,t0

	arcv.vclr.v.i v0,3,t0
	arcv.vclr.v.i v3,6,t0

	arcv.vsra.vv v0,v3,v6,t0
	arcv.vsra.vv v3,v6,v0,t0
	arcv.vsra.vv v6,v0,v3,t0

	arcv.vsra.vx v0,v3,t6,t0
	arcv.vsra.vx v3,v6,t0,t0
	arcv.vsra.vx v6,v0,t3,t0

	arcv.vsra.vi v0,v3,6,t0
	arcv.vsra.vi v3,v6,0,t0
	arcv.vsra.vi v6,v0,3,t0

	arcv.vsrat.vv v0,v3,v6,t0
	arcv.vsrat.vv v3,v6,v0,t0
	arcv.vsrat.vv v6,v0,v3,t0

	arcv.vsrat.vx v0,v3,t6,t0
	arcv.vsrat.vx v3,v6,t0,t0
	arcv.vsrat.vx v6,v0,t3,t0

	arcv.vsrat.vi v0,v3,6,t0
	arcv.vsrat.vi v3,v6,0,t0
	arcv.vsrat.vi v6,v0,3,t0

	arcv.vsra.s.vv v0,v3,v6,t0
	arcv.vsra.s.vv v3,v6,v0,t0
	arcv.vsra.s.vv v6,v0,v3,t0

	arcv.vsra.s.vx v0,v3,t6,t0
	arcv.vsra.s.vx v3,v6,t0,t0
	arcv.vsra.s.vx v6,v0,t3,t0

	arcv.vsra.s.vi v0,v3,6,t0
	arcv.vsra.s.vi v3,v6,0,t0
	arcv.vsra.s.vi v6,v0,3,t0

	arcv.vsra.2s.vv v0,v3,v6,t0
	arcv.vsra.2s.vv v3,v6,v0,t0
	arcv.vsra.2s.vv v6,v0,v3,t0

	arcv.vsra.2s.vx v0,v3,t6,t0
	arcv.vsra.2s.vx v3,v6,t0,t0
	arcv.vsra.2s.vx v6,v0,t3,t0

	arcv.vsra.2s.vi v0,v3,6,t0
	arcv.vsra.2s.vi v3,v6,0,t0
	arcv.vsra.2s.vi v6,v0,3,t0

	arcv.vnsra.wv v0,v3,v6,t0
	arcv.vnsra.wv v3,v6,v0,t0
	arcv.vnsra.wv v6,v0,v3,t0

	arcv.vnsra.wx v0,v3,t6,t0
	arcv.vnsra.wx v3,v6,t0,t0
	arcv.vnsra.wx v6,v0,t3,t0

	arcv.vnsra.wi v0,v3,6,t0
	arcv.vnsra.wi v3,v6,0,t0
	arcv.vnsra.wi v6,v0,3,t0

	arcv.vnsra.s.wv v0,v3,v6,t0
	arcv.vnsra.s.wv v3,v6,v0,t0
	arcv.vnsra.s.wv v6,v0,v3,t0

	arcv.vnsra.s.wx v0,v3,t6,t0
	arcv.vnsra.s.wx v3,v6,t0,t0
	arcv.vnsra.s.wx v6,v0,t3,t0

	arcv.vnsra.s.wi v0,v3,6,t0
	arcv.vnsra.s.wi v3,v6,0,t0
	arcv.vnsra.s.wi v6,v0,3,t0

	arcv.vnsra.2s.wv v0,v3,v6,t0
	arcv.vnsra.2s.wv v3,v6,v0,t0
	arcv.vnsra.2s.wv v6,v0,v3,t0

	arcv.vnsra.2s.wx v0,v3,t6,t0
	arcv.vnsra.2s.wx v3,v6,t0,t0
	arcv.vnsra.2s.wx v6,v0,t3,t0

	arcv.vnsra.2s.wi v0,v3,6,t0
	arcv.vnsra.2s.wi v3,v6,0,t0
	arcv.vnsra.2s.wi v6,v0,3,t0

	arcv.vnsra.qv v0,v3,v6,t0
	arcv.vnsra.qv v3,v6,v0,t0
	arcv.vnsra.qv v6,v0,v3,t0

	arcv.vnsra.qx v0,v3,t6,t0
	arcv.vnsra.qx v3,v6,t0,t0
	arcv.vnsra.qx v6,v0,t3,t0

	arcv.vnsra.qi v0,v3,6,t0
	arcv.vnsra.qi v3,v6,0,t0
	arcv.vnsra.qi v6,v0,3,t0

	arcv.vnsra.s.qv v0,v3,v6,t0
	arcv.vnsra.s.qv v3,v6,v0,t0
	arcv.vnsra.s.qv v6,v0,v3,t0

	arcv.vnsra.s.qx v0,v3,t6,t0
	arcv.vnsra.s.qx v3,v6,t0,t0
	arcv.vnsra.s.qx v6,v0,t3,t0

	arcv.vnsra.s.qi v0,v3,6,t0
	arcv.vnsra.s.qi v3,v6,0,t0
	arcv.vnsra.s.qi v6,v0,3,t0

	arcv.vnsra.2s.qv v0,v3,v6,t0
	arcv.vnsra.2s.qv v3,v6,v0,t0
	arcv.vnsra.2s.qv v6,v0,v3,t0

	arcv.vnsra.2s.qx v0,v3,t6,t0
	arcv.vnsra.2s.qx v3,v6,t0,t0
	arcv.vnsra.2s.qx v6,v0,t3,t0

	arcv.vnsra.2s.qi v0,v3,6,t0
	arcv.vnsra.2s.qi v3,v6,0,t0
	arcv.vnsra.2s.qi v6,v0,3,t0

	arcv.vwsra.vv v0,v3,v6,t0
	arcv.vwsra.vv v3,v6,v0,t0
	arcv.vwsra.vv v6,v0,v3,t0

	arcv.vwsra.vx v0,v3,t6,t0
	arcv.vwsra.vx v3,v6,t0,t0
	arcv.vwsra.vx v6,v0,t3,t0

	arcv.vwsra.vi v0,v3,6,t0
	arcv.vwsra.vi v3,v6,0,t0
	arcv.vwsra.vi v6,v0,3,t0

	arcv.vaddsub.vv v0,v3,v6,t0
	arcv.vaddsub.vv v3,v6,v0,t0
	arcv.vaddsub.vv v6,v0,v3,t0

	arcv.vsaddsub.vv v0,v3,v6,t0
	arcv.vsaddsub.vv v3,v6,v0,t0
	arcv.vsaddsub.vv v6,v0,v3,t0

	arcv.vsaaddsub.vv v0,v3,v6,t0
	arcv.vsaaddsub.vv v3,v6,v0,t0
	arcv.vsaaddsub.vv v6,v0,v3,t0

	arcv.vqrdot.vv v0,v3,v6,t0
	arcv.vqrdot.vv v3,v6,v0,t0
	arcv.vqrdot.vv v6,v0,v3,t0

	arcv.vqrdot.2s.vv v0,v3,v6,t0
	arcv.vqrdot.2s.vv v3,v6,v0,t0
	arcv.vqrdot.2s.vv v6,v0,v3,t0

	arcv.vwsrdot.2s.vv v0,v3,v6,t0
	arcv.vwsrdot.2s.vv v3,v6,v0,t0
	arcv.vwsrdot.2s.vv v6,v0,v3,t0

	arcv.vqrdotu.vv v0,v3,v6,t0
	arcv.vqrdotu.vv v3,v6,v0,t0
	arcv.vqrdotu.vv v6,v0,v3,t0

	arcv.vqrdotsu.vv v0,v3,v6,t0
	arcv.vqrdotsu.vv v3,v6,v0,t0
	arcv.vqrdotsu.vv v6,v0,v3,t0

	arcv.vwrdot.vv v0,v3,v6,t0
	arcv.vwrdot.vv v3,v6,v0,t0
	arcv.vwrdot.vv v6,v0,v3,t0

	arcv.vwsrdot.vv v0,v3,v6,t0
	arcv.vwsrdot.vv v3,v6,v0,t0
	arcv.vwsrdot.vv v6,v0,v3,t0

	arcv.vwrdotu.vv v0,v3,v6,t0
	arcv.vwrdotu.vv v3,v6,v0,t0
	arcv.vwrdotu.vv v6,v0,v3,t0

	arcv.vwrdotsu.vv v0,v3,v6,t0
	arcv.vwrdotsu.vv v3,v6,v0,t0
	arcv.vwrdotsu.vv v6,v0,v3,t0

	arcv.vwsmac.vv v0,v3,v6,t0
	arcv.vwsmac.vv v3,v6,v0,t0
	arcv.vwsmac.vv v6,v0,v3,t0

	arcv.vwsmac.vx v0,v3,t6,t0
	arcv.vwsmac.vx v3,v6,t0,t0
	arcv.vwsmac.vx v6,v0,t3,t0

	arcv.vwsnmsac.vv v0,v3,v6,t0
	arcv.vwsnmsac.vv v3,v6,v0,t0
	arcv.vwsnmsac.vv v6,v0,v3,t0

	arcv.vwsnmsac.vx v0,v3,t6,t0
	arcv.vwsnmsac.vx v3,v6,t0,t0
	arcv.vwsnmsac.vx v6,v0,t3,t0

	arcv.vwmul.hv v0,v3,v6,t0
	arcv.vwmul.hv v3,v6,v0,t0
	arcv.vwmul.hv v6,v0,v3,t0

	arcv.vwmul.hx v0,v3,t6,t0
	arcv.vwmul.hx v3,v6,t0,t0
	arcv.vwmul.hx v6,v0,t3,t0

	arcv.vwmac.hv v0,v3,v6,t0
	arcv.vwmac.hv v3,v6,v0,t0
	arcv.vwmac.hv v6,v0,v3,t0

	arcv.vwmac.hx v0,v3,t6,t0
	arcv.vwmac.hx v3,v6,t0,t0
	arcv.vwmac.hx v6,v0,t3,t0

	arcv.vwmulu.hv v0,v3,v6,t0
	arcv.vwmulu.hv v3,v6,v0,t0
	arcv.vwmulu.hv v6,v0,v3,t0

	arcv.vwmulu.hx v0,v3,t6,t0
	arcv.vwmulu.hx v3,v6,t0,t0
	arcv.vwmulu.hx v6,v0,t3,t0

	arcv.vwmacu.hv v0,v3,v6,t0
	arcv.vwmacu.hv v3,v6,v0,t0
	arcv.vwmacu.hv v6,v0,v3,t0

	arcv.vwmacu.hx v0,v3,t6,t0
	arcv.vwmacu.hx v3,v6,t0,t0
	arcv.vwmacu.hx v6,v0,t3,t0

	arcv.vwrdot.hv v0,v3,v6,t0
	arcv.vwrdot.hv v3,v6,v0,t0
	arcv.vwrdot.hv v6,v0,v3,t0

	arcv.vwrdotu.hv v0,v3,v6,t0
	arcv.vwrdotu.hv v3,v6,v0,t0
	arcv.vwrdotu.hv v6,v0,v3,t0

	arcv.vsmulf.hv v0,v3,v6,t0
	arcv.vsmulf.hv v3,v6,v0,t0
	arcv.vsmulf.hv v6,v0,v3,t0

	arcv.vsmulf.hx v0,v3,t6,t0
	arcv.vsmulf.hx v3,v6,t0,t0
	arcv.vsmulf.hx v6,v0,t3,t0

	arcv.vwmulf.hv v0,v3,v6,t0
	arcv.vwmulf.hv v3,v6,v0,t0
	arcv.vwmulf.hv v6,v0,v3,t0

	arcv.vwmulf.hx v0,v3,t6,t0
	arcv.vwmulf.hx v3,v6,t0,t0
	arcv.vwmulf.hx v6,v0,t3,t0

	arcv.vwsmacf.hv v0,v3,v6,t0
	arcv.vwsmacf.hv v3,v6,v0,t0
	arcv.vwsmacf.hv v6,v0,v3,t0

	arcv.vwsmacf.hx v0,v3,t6,t0
	arcv.vwsmacf.hx v3,v6,t0,t0
	arcv.vwsmacf.hx v6,v0,t3,t0

	arcv.vwsnmsacf.hv v0,v3,v6,t0
	arcv.vwsnmsacf.hv v3,v6,v0,t0
	arcv.vwsnmsacf.hv v6,v0,v3,t0

	arcv.vwsnmsacf.hx v0,v3,t6,t0
	arcv.vwsnmsacf.hx v3,v6,t0,t0
	arcv.vwsnmsacf.hx v6,v0,t3,t0

	arcv.vwsrdotf.hv v0,v3,v6,t0
	arcv.vwsrdotf.hv v3,v6,v0,t0
	arcv.vwsrdotf.hv v6,v0,v3,t0

	# xarcvvdsp - wrong operand types

	arcv.vmv.v.s 0,v3,t6
	arcv.vmv.v.s v0,3,t6
	arcv.vmv.v.s v0,v3,6

	arcv.vmv.s.v 0,v3,t6
	arcv.vmv.s.v v0,3,t6
	arcv.vmv.s.v v0,v3,6

	arcv.vmvi.v.s 0,v3,6
	arcv.vmvi.v.s v0,3,6
	arcv.vmvi.v.s v0,v3,v6

	arcv.vmvi.s.v 0,v3,6
	arcv.vmvi.s.v v0,3,6
	arcv.vmvi.s.v v0,v3,v6

	arcv.vnorm.v 0,v3
	arcv.vnorm.v v0,3

	arcv.vssabs.v 0,v3
	arcv.vssabs.v v0,3

	arcv.vsneg.v 0,v3
	arcv.vsneg.v v0,3

	arcv.vclr.v.i 0,3
	arcv.vclr.v.i v0,v3

	arcv.vsra.vv 0,v3,v6
	arcv.vsra.vv v0,3,v6
	arcv.vsra.vv v0,v3,6

	arcv.vsra.vx 0,v3,t6
	arcv.vsra.vx v0,3,t6
	arcv.vsra.vx v0,v3,6

	arcv.vsra.vi 0,v3,6
	arcv.vsra.vi v0,3,6
	arcv.vsra.vi v0,v3,v6

	arcv.vsrat.vv 0,v3,v6
	arcv.vsrat.vv v0,3,v6
	arcv.vsrat.vv v0,v3,6

	arcv.vsrat.vx 0,v3,t6
	arcv.vsrat.vx v0,3,t6
	arcv.vsrat.vx v0,v3,6

	arcv.vsrat.vi 0,v3,6
	arcv.vsrat.vi v0,3,6
	arcv.vsrat.vi v0,v3,v6

	arcv.vsra.s.vv 0,v3,v6
	arcv.vsra.s.vv v0,3,v6
	arcv.vsra.s.vv v0,v3,6

	arcv.vsra.s.vx 0,v3,t6
	arcv.vsra.s.vx v0,3,t6
	arcv.vsra.s.vx v0,v3,6

	arcv.vsra.s.vi 0,v3,6
	arcv.vsra.s.vi v0,3,6
	arcv.vsra.s.vi v0,v3,v6

	arcv.vsra.2s.vv 0,v3,v6
	arcv.vsra.2s.vv v0,3,v6
	arcv.vsra.2s.vv v0,v3,6

	arcv.vsra.2s.vx 0,v3,t6
	arcv.vsra.2s.vx v0,3,t6
	arcv.vsra.2s.vx v0,v3,6

	arcv.vsra.2s.vi 0,v3,6
	arcv.vsra.2s.vi v0,3,6
	arcv.vsra.2s.vi v0,v3,v6

	arcv.vnsra.wv 0,v3,v6
	arcv.vnsra.wv v0,3,v6
	arcv.vnsra.wv v0,v3,6

	arcv.vnsra.wx 0,v3,t6
	arcv.vnsra.wx v0,3,t6
	arcv.vnsra.wx v0,v3,6

	arcv.vnsra.wi 0,v3,6
	arcv.vnsra.wi v0,3,6
	arcv.vnsra.wi v0,v3,v6

	arcv.vnsra.s.wv 0,v3,v6
	arcv.vnsra.s.wv v0,3,v6
	arcv.vnsra.s.wv v0,v3,6

	arcv.vnsra.s.wx 0,v3,t6
	arcv.vnsra.s.wx v0,3,t6
	arcv.vnsra.s.wx v0,v3,6

	arcv.vnsra.s.wi 0,v3,6
	arcv.vnsra.s.wi v0,3,6
	arcv.vnsra.s.wi v0,v3,v6

	arcv.vnsra.2s.wv 0,v3,v6
	arcv.vnsra.2s.wv v0,3,v6
	arcv.vnsra.2s.wv v0,v3,6

	arcv.vnsra.2s.wx 0,v3,t6
	arcv.vnsra.2s.wx v0,3,t6
	arcv.vnsra.2s.wx v0,v3,6

	arcv.vnsra.2s.wi 0,v3,6
	arcv.vnsra.2s.wi v0,3,6
	arcv.vnsra.2s.wi v0,v3,v6

	arcv.vnsra.qv 0,v3,v6
	arcv.vnsra.qv v0,3,v6
	arcv.vnsra.qv v0,v3,6

	arcv.vnsra.qx 0,v3,t6
	arcv.vnsra.qx v0,3,t6
	arcv.vnsra.qx v0,v3,6

	arcv.vnsra.qi 0,v3,6
	arcv.vnsra.qi v0,3,6
	arcv.vnsra.qi v0,v3,v6

	arcv.vnsra.s.qv 0,v3,v6
	arcv.vnsra.s.qv v0,3,v6
	arcv.vnsra.s.qv v0,v3,6

	arcv.vnsra.s.qx 0,v3,t6
	arcv.vnsra.s.qx v0,3,t6
	arcv.vnsra.s.qx v0,v3,6

	arcv.vnsra.s.qi 0,v3,6
	arcv.vnsra.s.qi v0,3,6
	arcv.vnsra.s.qi v0,v3,v6

	arcv.vnsra.2s.qv 0,v3,v6
	arcv.vnsra.2s.qv v0,3,v6
	arcv.vnsra.2s.qv v0,v3,6

	arcv.vnsra.2s.qx 0,v3,t6
	arcv.vnsra.2s.qx v0,3,t6
	arcv.vnsra.2s.qx v0,v3,6

	arcv.vnsra.2s.qi 0,v3,6
	arcv.vnsra.2s.qi v0,3,6
	arcv.vnsra.2s.qi v0,v3,v6

	arcv.vwsra.vv 0,v3,v6
	arcv.vwsra.vv v0,3,v6
	arcv.vwsra.vv v0,v3,6

	arcv.vwsra.vx 0,v3,t6
	arcv.vwsra.vx v0,3,t6
	arcv.vwsra.vx v0,v3,6

	arcv.vwsra.vi 0,v3,6
	arcv.vwsra.vi v0,3,6
	arcv.vwsra.vi v0,v3,v6

	arcv.vaddsub.vv 0,v3,v6
	arcv.vaddsub.vv v0,3,v6
	arcv.vaddsub.vv v0,v3,6

	arcv.vsaddsub.vv 0,v3,v6
	arcv.vsaddsub.vv v0,3,v6
	arcv.vsaddsub.vv v0,v3,6

	arcv.vsaaddsub.vv 0,v3,v6
	arcv.vsaaddsub.vv v0,3,v6
	arcv.vsaaddsub.vv v0,v3,6

	arcv.vqrdot.vv 0,v3,v6
	arcv.vqrdot.vv v0,3,v6
	arcv.vqrdot.vv v0,v3,6

	arcv.vqrdot.2s.vv 0,v3,v6
	arcv.vqrdot.2s.vv v0,3,v6
	arcv.vqrdot.2s.vv v0,v3,6

	arcv.vwsrdot.2s.vv 0,v3,v6
	arcv.vwsrdot.2s.vv v0,3,v6
	arcv.vwsrdot.2s.vv v0,v3,6

	arcv.vqrdotu.vv 0,v3,v6
	arcv.vqrdotu.vv v0,3,v6
	arcv.vqrdotu.vv v0,v3,6

	arcv.vqrdotsu.vv 0,v3,v6
	arcv.vqrdotsu.vv v0,3,v6
	arcv.vqrdotsu.vv v0,v3,6

	arcv.vwrdot.vv 0,v3,v6
	arcv.vwrdot.vv v0,3,v6
	arcv.vwrdot.vv v0,v3,6

	arcv.vwsrdot.vv 0,v3,v6
	arcv.vwsrdot.vv v0,3,v6
	arcv.vwsrdot.vv v0,v3,6

	arcv.vwrdotu.vv 0,v3,v6
	arcv.vwrdotu.vv v0,3,v6
	arcv.vwrdotu.vv v0,v3,6

	arcv.vwrdotsu.vv 0,v3,v6
	arcv.vwrdotsu.vv v0,3,v6
	arcv.vwrdotsu.vv v0,v3,6

	arcv.vwsmac.vv 0,v3,v6
	arcv.vwsmac.vv v0,3,v6
	arcv.vwsmac.vv v0,v3,6

	arcv.vwsmac.vx 0,v3,t6
	arcv.vwsmac.vx v0,3,t6
	arcv.vwsmac.vx v0,v3,6

	arcv.vwsnmsac.vv 0,v3,v6
	arcv.vwsnmsac.vv v0,3,v6
	arcv.vwsnmsac.vv v0,v3,6

	arcv.vwsnmsac.vx 0,v3,t6
	arcv.vwsnmsac.vx v0,3,t6
	arcv.vwsnmsac.vx v0,v3,6

	arcv.vwmul.hv 0,v3,v6
	arcv.vwmul.hv v0,3,v6
	arcv.vwmul.hv v0,v3,6

	arcv.vwmul.hx 0,v3,t6
	arcv.vwmul.hx v0,3,t6
	arcv.vwmul.hx v0,v3,6

	arcv.vwmac.hv 0,v3,v6
	arcv.vwmac.hv v0,3,v6
	arcv.vwmac.hv v0,v3,6

	arcv.vwmac.hx 0,v3,t6
	arcv.vwmac.hx v0,3,t6
	arcv.vwmac.hx v0,v3,6

	arcv.vwmulu.hv 0,v3,v6
	arcv.vwmulu.hv v0,3,v6
	arcv.vwmulu.hv v0,v3,6

	arcv.vwmulu.hx 0,v3,t6
	arcv.vwmulu.hx v0,3,t6
	arcv.vwmulu.hx v0,v3,6

	arcv.vwmacu.hv 0,v3,v6
	arcv.vwmacu.hv v0,3,v6
	arcv.vwmacu.hv v0,v3,6

	arcv.vwmacu.hx 0,v3,t6
	arcv.vwmacu.hx v0,3,t6
	arcv.vwmacu.hx v0,v3,6

	arcv.vwrdot.hv 0,v3,v6
	arcv.vwrdot.hv v0,3,v6
	arcv.vwrdot.hv v0,v3,6

	arcv.vwrdotu.hv 0,v3,v6
	arcv.vwrdotu.hv v0,3,v6
	arcv.vwrdotu.hv v0,v3,6

	arcv.vsmulf.hv 0,v3,v6
	arcv.vsmulf.hv v0,3,v6
	arcv.vsmulf.hv v0,v3,6

	arcv.vsmulf.hx 0,v3,t6
	arcv.vsmulf.hx v0,3,t6
	arcv.vsmulf.hx v0,v3,6

	arcv.vwmulf.hv 0,v3,v6
	arcv.vwmulf.hv v0,3,v6
	arcv.vwmulf.hv v0,v3,6

	arcv.vwmulf.hx 0,v3,t6
	arcv.vwmulf.hx v0,3,t6
	arcv.vwmulf.hx v0,v3,6

	arcv.vwsmacf.hv 0,v3,v6
	arcv.vwsmacf.hv v0,3,v6
	arcv.vwsmacf.hv v0,v3,6

	arcv.vwsmacf.hx 0,v3,t6
	arcv.vwsmacf.hx v0,3,t6
	arcv.vwsmacf.hx v0,v3,6

	arcv.vwsnmsacf.hv 0,v3,v6
	arcv.vwsnmsacf.hv v0,3,v6
	arcv.vwsnmsacf.hv v0,v3,6

	arcv.vwsnmsacf.hx 0,v3,t6
	arcv.vwsnmsacf.hx v0,3,t6
	arcv.vwsnmsacf.hx v0,v3,6

	arcv.vwsrdotf.hv 0,v3,v6
	arcv.vwsrdotf.hv v0,3,v6
	arcv.vwsrdotf.hv v0,v3,6
