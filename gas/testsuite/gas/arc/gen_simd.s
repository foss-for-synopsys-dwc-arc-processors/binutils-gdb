# Test for the Aurora SIMD ISA 
	
	vld32		vr22,[i1,44]
	vld32           vr23,[i6,248]
	
	vld64		vr22,[i2,32]
	vld64		vr19,[i6,240]
	
	vld64w		vr22,[i1,64]
	vld64w          vr1 ,[i0,0]
	
	vld32wl		vr22,[i1,44]
	vld32wl         vr3, [i2,100]
	
	vld32wh		vr22,[i1,44]
	vld32wh         vr18,[i3,104]
	
	vld128		vr22,[i1,64]
	vld128          vr17,[i4,80]
	
	vld128r		vr22,[r12]
	vld128r         vr4 ,[r1]

	
	
	
	vst16		vr22,[i1,44]
	vst16           vr2 ,[i2,250]
	
	vst32		vr22,[i4,44]
	vst32           vr5 ,[i3,88]
	
	vst64		vr22,[i1,64]
	vst64           vr20,[i1,32]
	
	vst128		vr22,[i1,64]
	vst128          vr6 ,[i4,96]
	
	vst128r		vr22,[r12]
	vst128r         vr7 ,[r22]
	

	
	vmvw		vr2,vr4,0x2
	vmvw            vr8,vr9,10
	
	vmvzw		vr2,vr4,0x2
	vmvzw           vr11,vr12,14
	
	vmovw		vr2,r4,0x2
	vmovw           vr13,r14,15
	
	vmovzw		vr2,r4,0x1
	vmovzw          vr15,r16,17

	

	
	vmvaw		vr2,vr4,0x2
	vmvaw           vr1,vr19,20
	
	vmovaw		vr2,r4,0x1
	vmovaw          vr21,r20,34

	

	
	vaddw		vr22,vr22,vr3
	vaddw           vr19,vr3,vr2
	
	vsubw		vr22,vr22,vr3
	vsubw           vr23,vr20,vr21
	
	vmulw		vr22,vr22,vr3
	vmulw           vr23,vr4,vr3
	
	vmulfw		vr22,vr22,vr3
	vmulfw          vr6,vr8,vr9

	vbaddw		vr22,vr22,r6
	vbaddw          vr4,vr5,r3
	
	vbsubw		vr22,vr22,r5
	vbsubw          vr4,vr3,r19
	
	vbrsubw		vr22,vr22,r8
	vbrsubw         vr8,vr5,r10
	
	vbmulw		vr22,vr22,r3
	vbmulw          vr6,vr9,r11
	
	vbmulfw		vr22,vr22,r10
	vbmulfw         vr5,vr3,r22
	

	
		
	vaddaw		vr22,vr22,vr1
	vaddaw          vr1,vr2,vr5
	
	vsubaw		vr22,vr22,vr3
	vsubaw          vr4,vr5,vr6
	
	vmulaw		vr22,vr22,vr3
	vmulaw          vr7,vr8,vr9
	
	vmulfaw		vr22,vr22,vr3
	vmulfaw         vr0,vr1,vr6
	
	vbmulaw		vr22,vr22,r3
	vbmulaw         vr3,vr1,r2

	

	
	vaddsuw		vr22,vr22
	vaddsuw         vr1,vr3
	
	vabsw		vr22,vr3
	vabsw           vr3,vr5
	
	vabsaw		vr22,vr3
	vabsaw          vr7,vr9
	
	vasrw		vr22,vr22,i3
	vasrw           vr5,vr23,i4
	
	vasrwi		vr22,vr22,4
	vasrwi          vr21,vr23,11
	
	vasrrwi		vr22,vr22,4
	vasrrwi         vr20,vr19,9
	
	vasrsrwi	vr22,vr22,4
	vasrsrwi        vr5,vr1,11
	
	vsignw		vr22,vr3
	vsignw          vr15,vr11

	vmaxw		vr22,vr3,vr2
	vmaxw		vr3,vr12,vr1
	
	vminw		vr22,vr3,vr2
	vmaxaw		vr22,vr3,vr2
	
	vminaw		vr22,vr3,vr5
	vminaw		vr6,vr23,vr2
	
	vbmaxw		vr22,vr3,r5
	vbminw		vr22,vr3,r1
	
	vdifw		vr22,vr22,vr13
	vdifaw		vr22,vr22,vr13
	
	vsummw		vr5,vr6,vr20
	vand		vr22,vr22,vr3
	vor		vr22,vr22,vr3
	vxor		vr22,vr22,vr3
	vbic		vr22,vr22,vr3
	vandaw		vr22,vr22,vr3
	vbicaw		vr22,vr22,vr3
	vxoraw		vr22,vr22,vr3

	 
	vavb		vr22,vr22,vr3
	vavrb		vr22,vr22,vr3

	
	veqw		vr22,vr22,vr3
	vnew		vr22,vr22,vr3
	vlew		vr22, vr22,vr1
	vltw		vr22,vr22,vr3

	
	vexch1		vr1,vr2
	vexch2		vr1,vr2
	vexch4		vr1,vr2

	
	vupbw		vr22,vr1
	vupsbw		vr22,vr3
	
	vasrpwbi	vr4,vr6,5
	vasrpwbi        vr3,vr11,63
	
	vasrrpwbi	vr4,vr6,5
	vasrrpwbi       vr5,vr1,32
	
	vupbaw		vr22,vr1
	vupsbaw		vr22,vr3

	
	vsr8		vr22,vr10,i4
	vsr8            vr22,vr10,i1
	
	vsr8i		vr22,vr10,3
	vsr8i		vr12,vr1,34
	
	vsr8aw		vr22,vr22,i5
	vsr8aw          vr22,vr23,i3
	
	vsr8awi		vr22,vr22,4
	vsr8awi         vr10,vr10,45

	
	vmr1w		vr22,vr10,vr11
	vmr2w		vr22,vr10,vr11
	vmr3w		vr22,vr10,vr11
	vmr4w		vr22,vr10,vr11
	vmr5w		vr22,vr10,vr11
	vmr6w		vr22,vr10,vr11
	vmr7w		vr22,vr10,vr11
	
	vmrb		vr22,vr10,vr11

	
	vmr1aw		vr22,vr10,vr11
	vmr2aw		vr22,vr10,vr11
	vmr3aw		vr22,vr10,vr11
	vmr4aw		vr22,vr10,vr11
	vmr5aw		vr22,vr10,vr11
	vmr6aw		vr22,vr10,vr11
	vmr7aw		vr22,vr10,vr11

	
	vrec		r5
	vnop		r5
	vrecrun		r5
	vrun		r5	
	vendrec		r6

	
	vdirun		r5,r6
	vdorun		r5,r9

	
	vdiwr		dr1,r5
	vdiwr           dr3,r10
	vdiwr		dr2,r15
	
	vdowr		dr1,r5
	vdowr		dr3,r10
	vdowr           dr2,r11

	
	vdird		vr10,dr1
	vdird           vr10,dr2
	
	vdord		vr10,dr1
	vdord           vr10,dr5

	
	vh264ft		vr22,vr22,vr3
	vh264ft		vr22,vr13,vr4
	
	vh264f		vr22,vr22,vr13
	vh264f		vr4,vr5,vr11

	
	vvc1ft		vr22,vr22,vr13
	vvc1ft		vr13,vr14,vr14
	
	vvc1f		vr22,vr22,vr13
	vvc1f		vr13,vr22,vr3
	
	vd6tapf		vr21, vr5,3
	vd6tapf		vr21, vr1,255
	
	vinti		0
	vinti		63

	