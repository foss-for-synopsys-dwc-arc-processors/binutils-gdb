	.balign 4
	add r2,pcl,@.L1@pcl
	add r2,pcl,@.L2@pcl
	add r2,pcl,@foo@pcl
	ld r0,[pcl,.L1@pcl]
	ld r0,[pcl,.L2@pcl]
	ld r0,[pcl,foo@pcl]
.L1:
	nop_s
.L2:
	add r2,pcl,@.L1@pcl
	add r2,pcl,@.L2@pcl
	add r2,pcl,@foo@pcl
	ld r0,[pcl,.L1@pcl]
	ld r0,[pcl,.L2@pcl]
	ld r0,[pcl,foo@pcl]
