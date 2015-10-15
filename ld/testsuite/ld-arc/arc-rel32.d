
.*:     file format .*

DYNAMIC RELOCATION RECORDS
OFFSET +TYPE +VALUE .*
[0-9a-f]+ R_ARC_PC32 +foo
[0-9a-f]+ R_ARC_PC32 +foo\+0x00000100
[0-9a-f]+ R_ARC_JMP_SLOT +foo


Contents of section \.data:
 [0-9a-f]+ 00000000 00000000 .*
