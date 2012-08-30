# data flush cache test - ARC700 4.10 extension

sr 0x1c2028, [DC_ENDR]   ; define a region size of 4k
sr 0x1c1024, [DC_STARTR] ; trigger flush
		         ; contents with this region
lr r0, [DC_CTRL]         ; read DC_CTRL
and.f 0, 0x4, r0	 ;
bne success		 ; flushed entries within the region
failed:			 ; failed to flush entries
