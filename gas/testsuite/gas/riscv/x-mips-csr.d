#as: -march=rv32if_xtheadvector
#objdump: -dr

.*:[ 	]+file format .*


Disassembly of section .text:

0+000 <.text>:
[ 	]+[0-9a-f]+:[ 	]+7d102573[ 	]+csrr[ 	]+a0,mipsconfig1
[ 	]+[0-9a-f]+:[ 	]+7d402573[ 	]+csrr[ 	]+a0,mipsconfig4
[ 	]+[0-9a-f]+:[ 	]+7d702573[ 	]+csrr[ 	]+a0,mipsconfig7
[ 	]+[0-9a-f]+:[ 	]+80002573[ 	]+csrr[ 	]+a0,mipswfe
[ 	]+[0-9a-f]+:[ 	]+bf002573[ 	]+csrr[ 	]+a0,mipstcprio0
[ 	]+[0-9a-f]+:[ 	]+bf102573[ 	]+csrr[ 	]+a0,mipstcprio1
[ 	]+[0-9a-f]+:[ 	]+bf202573[ 	]+csrr[ 	]+a0,mipstcprio2
[ 	]+[0-9a-f]+:[ 	]+bf302573[ 	]+csrr[ 	]+a0,mipstcprio3
[ 	]+[0-9a-f]+:[ 	]+bf802573[ 	]+csrr[ 	]+a0,mipstcfpcm0
[ 	]+[0-9a-f]+:[ 	]+bf902573[ 	]+csrr[ 	]+a0,mipstcfpcm1
[ 	]+[0-9a-f]+:[ 	]+bfa02573[ 	]+csrr[ 	]+a0,mipstcfpcm2
[ 	]+[0-9a-f]+:[ 	]+bfb02573[ 	]+csrr[ 	]+a0,mipstcfpcm3
[ 	]+[0-9a-f]+:[ 	]+bff02573[ 	]+csrr[ 	]+a0,mipstcscfg
[ 	]+[0-9a-f]+:[ 	]+ff002573[ 	]+csrr[ 	]+a0,mipstcstat0
[ 	]+[0-9a-f]+:[ 	]+ff102573[ 	]+csrr[ 	]+a0,mipstcstat1
[ 	]+[0-9a-f]+:[ 	]+ff202573[ 	]+csrr[ 	]+a0,mipstcstat2
[ 	]+[0-9a-f]+:[ 	]+ff302573[ 	]+csrr[ 	]+a0,mipstcstat3
[ 	]+[0-9a-f]+:[ 	]+ff402573[ 	]+csrr[ 	]+a0,mipsrtmtcfg
[ 	]+[0-9a-f]+:[ 	]+7f102573[ 	]+csrr[ 	]+a0,mipsmwid
[ 	]+[0-9a-f]+:[ 	]+7f202573[ 	]+csrr[ 	]+a0,mipsmwidlist
[ 	]+[0-9a-f]+:[ 	]+7f302573[ 	]+csrr[ 	]+a0,mipsmwidseclist
[ 	]+[0-9a-f]+:[ 	]+7f402573[ 	]+csrr[ 	]+a0,mipsmlwid
[ 	]+[0-9a-f]+:[ 	]+7f502573[ 	]+csrr[ 	]+a0,mipsmwiddeleg
[ 	]+[0-9a-f]+:[ 	]+9d402573[ 	]+csrr[ 	]+a0,mipsslwid
[ 	]+[0-9a-f]+:[ 	]+fc002573[ 	]+csrr[ 	]+a0,mipsdmbase
[ 	]+[0-9a-f]+:[ 	]+80102573[ 	]+csrr[ 	]+a0,mipssecdebug

[ 	]+[0-9a-f]+:[ 	]+7d151073[ 	]+csrw[ 	]+mipsconfig1,a0
[ 	]+[0-9a-f]+:[ 	]+7d451073[ 	]+csrw[ 	]+mipsconfig4,a0
[ 	]+[0-9a-f]+:[ 	]+7d751073[ 	]+csrw[ 	]+mipsconfig7,a0
[ 	]+[0-9a-f]+:[ 	]+80051073[ 	]+csrw[ 	]+mipswfe,a0
[ 	]+[0-9a-f]+:[ 	]+bf051073[ 	]+csrw[ 	]+mipstcprio0,a0
[ 	]+[0-9a-f]+:[ 	]+bf151073[ 	]+csrw[ 	]+mipstcprio1,a0
[ 	]+[0-9a-f]+:[ 	]+bf251073[ 	]+csrw[ 	]+mipstcprio2,a0
[ 	]+[0-9a-f]+:[ 	]+bf351073[ 	]+csrw[ 	]+mipstcprio3,a0
[ 	]+[0-9a-f]+:[ 	]+bf851073[ 	]+csrw[ 	]+mipstcfpcm0,a0
[ 	]+[0-9a-f]+:[ 	]+bf951073[ 	]+csrw[ 	]+mipstcfpcm1,a0
[ 	]+[0-9a-f]+:[ 	]+bfa51073[ 	]+csrw[ 	]+mipstcfpcm2,a0
[ 	]+[0-9a-f]+:[ 	]+bfb51073[ 	]+csrw[ 	]+mipstcfpcm3,a0
[ 	]+[0-9a-f]+:[ 	]+bff51073[ 	]+csrw[ 	]+mipstcscfg,a0
[ 	]+[0-9a-f]+:[ 	]+ff051073[ 	]+csrw[ 	]+mipstcstat0,a0
[ 	]+[0-9a-f]+:[ 	]+ff151073[ 	]+csrw[ 	]+mipstcstat1,a0
[ 	]+[0-9a-f]+:[ 	]+ff251073[ 	]+csrw[ 	]+mipstcstat2,a0
[ 	]+[0-9a-f]+:[ 	]+ff351073[ 	]+csrw[ 	]+mipstcstat3,a0
[ 	]+[0-9a-f]+:[ 	]+ff451073[ 	]+csrw[ 	]+mipsrtmtcfg,a0
[ 	]+[0-9a-f]+:[ 	]+7f151073[ 	]+csrw[ 	]+mipsmwid,a0
[ 	]+[0-9a-f]+:[ 	]+7f251073[ 	]+csrw[ 	]+mipsmwidlist,a0
[ 	]+[0-9a-f]+:[ 	]+7f351073[ 	]+csrw[ 	]+mipsmwidseclist,a0
[ 	]+[0-9a-f]+:[ 	]+7f451073[ 	]+csrw[ 	]+mipsmlwid,a0
[ 	]+[0-9a-f]+:[ 	]+7f551073[ 	]+csrw[ 	]+mipsmwiddeleg,a0
[ 	]+[0-9a-f]+:[ 	]+9d451073[ 	]+csrw[ 	]+mipsslwid,a0
[ 	]+[0-9a-f]+:[ 	]+fc051073[ 	]+csrw[ 	]+mipsdmbase,a0
[ 	]+[0-9a-f]+:[ 	]+80151073[ 	]+csrw[ 	]+mipssecdebug,a0
