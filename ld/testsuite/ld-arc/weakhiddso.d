#source: weakhid.s
#ld: --shared -m arclinux -z nocombreloc --hash-style=sysv
#objdump: -s -R -T

# Check that .weak and .weak .hidden object references are handled
# correctly when generating a DSO.  Copied from CRIS port.

.*: +file format .*arc.*

DYNAMIC SYMBOL TABLE:
0+2208 l    d  \.data	0+ \.data
0+2208 g    DO \.data	0+c x
0+      D  \*UND\*	0+ xregobj
0+2214 g    D  \.data	0+ __bss_start
0+  w   D  \*UND\*	0+ xweakobj
0+2214 g    D  \.data	0+ _edata
0+2214 g    D  \.data	0+ _end


DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE 
0+2210 R_ARC_32 +xregobj
0+ R_ARC_NONE +\*ABS\*

Contents of section \.hash:
#...
Contents of section \.data:
 2208 00000000 00000000 00000000           .*
#...