; All the options, beside the processor selection and FPX extensions, should be ignored by GAS
; { dg-do assemble }
; { dg-options "--mcpu=ARCv2EM -mswap -mnorm -mbarrel-shifter -mmin-max -mno-mpy -mea -mEA -mmul64 -msimd -mmac-d16 -mmac-24 -mdsp-packa -mcrc -mdvbf -mtelephony  -mxy -mlock -mswape -mrtsc -mspfp -mdpfp" }
.macro genError name
.ifdef \name
	.print "Test Falied for \name"
	.err
.endif
.endm

    genError __Xswap
    genError __Xnorm
    genError __Xbarrel_shifter
    genError __Xmin_max
    genError __Xno_mpy
    genError __Xea
    genError __Xmult32
    genError __Xsimd
    genError __Xxmac_d16
    genError __Xxmac_24
    genError __Xdsp_packa
    genError __Xcrc
    genError __Xdvbf
    genError __Xtelephony
    genError __Xxy
    genError __Xlock
    genError __Xswape
    genError __Xrtsc

.ifndef __Xspfp
	.print "SPFP failed"
	.err
.endif
.ifndef __Xdpfp
	.print "DPFP failed"
	.err
.endif

