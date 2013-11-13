/*ASR8 */
{ (unsigned char *) "asr8%.f %#,%C%F",                       0xF8FF003F, 0x282F000D, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "asr8%.f %#,%u%F",                       0xF8FF003F, 0x286F000D, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "asr8%.f%Q %#,%L%F",                     0xF8FF0FFF, 0x282F0F8D, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "asr8%.f 0,%C%F",                        0xFFFF703F, 0x2E2F700D, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "asr8%.f 0,%u%F",                        0xFFFF703F, 0x2E6F700D, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "asr8%.f%Q 0,%L%F",                      0xFFFF7FFF, 0x2E2F7F8D, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*ASR16 */
{ (unsigned char *) "asr16%.f %#,%C%F",                      0xF8FF003F, 0x282F000C, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "asr16%.f %#,%u%F",                      0xF8FF003F, 0x286F000C, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "asr16%.f%Q %#,%L%F",                    0xF8FF0FFF, 0x282F0F8C, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "asr16%.f 0,%C%F",                       0xFFFF703F, 0x2E2F700C, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "asr16%.f 0,%u%F",                       0xFFFF703F, 0x2E6F700C, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "asr16%.f%Q 0,%L%F",                     0xFFFF7FFF, 0x2E2F7F8C, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*FFS */
{ (unsigned char *) "ffs%.f %#,%u%F",                        0xF8FF003F, 0x286F0012, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ffs%.f 0,%u%F",                         0xFFFF703F, 0x2E6F7012, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ffs%.f %#,%C%F",                        0xF8FF003F, 0x282F0012, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ffs%.f%Q %#,%L%F",                      0xF8FF0FFF, 0x282F0F92, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ffs%.f 0,%C%F",                         0xFFFF703F, 0x2E2F7012, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ffs%.f%Q 0,%L%F",                       0xFFFF7FFF, 0x2E2F7F92, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*FLS */
{ (unsigned char *) "fls%.f %#,%u%F",                        0xF8FF003F, 0x286F0013, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "fls%.f 0,%u%F",                         0xFFFF703F, 0x2E6F7013, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "fls%.f %#,%C%F",                        0xF8FF003F, 0x282F0013, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "fls%.f%Q %#,%L%F",                      0xF8FF0FFF, 0x282F0F93, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "fls%.f 0,%C%F",                         0xFFFF703F, 0x2E2F7013, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "fls%.f%Q 0,%L%F",                       0xFFFF7FFF, 0x2E2F7F93, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*KFLAG */
{ (unsigned char *) "kflag %C",                              0xFFFFF03F, 0x20298000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "kflag %u",                              0xFFFFF03F, 0x20698000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "kflag %K",                              0xFFFFF000, 0x20A98000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "kflag%Q %L",                            0xFFFFFFFF, 0x20298F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "kflag%.q %C",                           0xFFFFF020, 0x20E98000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "kflag%.q %u",                           0xFFFFF020, 0x20E98020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "kflag%.q%Q %L",                         0xFFFFFFE0, 0x20E98F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*LSL16 */
{ (unsigned char *) "lsl16%.f %#,%C%F",                      0xF8FF003F, 0x282F000A, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsl16%.f 0,%C%F",                       0xFFFF703F, 0x2E2F700A, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsl16%.f %#,%u%F",                      0xF8FF003F, 0x286F000A, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsl16%.f 0,%u%F",                       0xFFFF703F, 0x2E6F700A, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsl16%.f%Q %#,%L%F",                    0xF8FF0FFF, 0x282F0F8A, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsl16%.f%Q 0,%L%F",                     0xFFFF7FFF, 0x2E2F7F8A, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*LSL8 */
{ (unsigned char *) "lsl8%.f %#,%C%F",                       0xF8FF003F, 0x282F000F, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsl8%.f 0,%C%F",                        0xFFFF703F, 0x2E2F700F, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsl8%.f %#,%u%F",                       0xF8FF003F, 0x286F000F, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsl8%.f 0,%u%F",                        0xFFFF703F, 0x2E6F700F, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsl8%.f%Q %#,%L%F",                     0xF8FF0FFF, 0x282F0F8F, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsl8%.f%Q 0,%L%F",                      0xFFFF7FFF, 0x2E2F7F8F, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*LSR16 */
{ (unsigned char *) "lsr16%.f %#,%C%F",                      0xF8FF003F, 0x282F000B, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsr16%.f 0,%C%F",                       0xFFFF703F, 0x2E2F700B, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsr16%.f %#,%u%F",                      0xF8FF003F, 0x286F000B, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsr16%.f 0,%u%F",                       0xFFFF703F, 0x2E6F700B, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsr16%.f%Q %#,%L%F",                    0xF8FF0FFF, 0x282F0F8B, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsr16%.f%Q 0,%L%F",                     0xFFFF7FFF, 0x2E2F7F8B, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*LSR8 */
{ (unsigned char *) "lsr8%.f %#,%C%F",                       0xF8FF003F, 0x282F000E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsr8%.f 0,%C%F",                        0xFFFF703F, 0x2E2F700E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsr8%.f %#,%u%F",                       0xF8FF003F, 0x286F000E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsr8%.f 0,%u%F",                        0xFFFF703F, 0x2E6F700E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsr8%.f%Q %#,%L%F",                     0xF8FF0FFF, 0x282F0F8E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lsr8%.f%Q 0,%L%F",                      0xFFFF7FFF, 0x2E2F7F8E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*ROL */
{ (unsigned char *) "rol%.f %#,%C%F",                        0xF8FF003F, 0x202F000D, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rol%.f 0,%C%F",                         0xFFFF703F, 0x262F700D, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rol%.f %#,%u%F",                        0xF8FF003F, 0x206F000D, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rol%.f 0,%u%F",                         0xFFFF703F, 0x266F700D, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rol8%.f %#,%C%F",                       0xF8FF003F, 0x282F0010, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rol8%.f 0,%C%F",                        0xFFFF703F, 0x2E2F7010, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rol8%.f %#,%u%F",                       0xF8FF003F, 0x286F0010, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rol8%.f 0,%u%F",                        0xFFFF703F, 0x2E6F7010, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rol%.f%Q %#,%L%F",                      0xF8FF0FFF, 0x202F0F8D, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rol%.f%Q 0,%L%F",                       0xFFFF7FFF, 0x262F7F8D, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rol8%.f%Q %#,%L%F",                     0xF8FF0FFF, 0x282F0F90, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rol8%.f%Q 0,%L%F",                      0xFFFF7FFF, 0x2E2F7F90, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*ROR8 */
{ (unsigned char *) "ror8%.f %#,%C%F",                       0xF8FF003F, 0x282F0011, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ror8%.f 0,%C%F",                        0xFFFF703F, 0x2E2F7011, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ror8%.f %#,%u%F",                       0xF8FF003F, 0x286F0011, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ror8%.f 0,%u%F",                        0xFFFF703F, 0x2E6F7011, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ror8%.f%Q %#,%L%F",                     0xF8FF0FFF, 0x282F0F91, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ror8%.f%Q 0,%L%F",                      0xFFFF7FFF, 0x2E2F7F91, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*SETEQ */
/* seteq<.cc><.f>    b,b,u6 	0010 0bbb 1111 1000 FBBB uuuu uu1Q QQQQ  */
{ (unsigned char *) "seteq%.q%.f %#,%B,%u%F",                0xF8FF0020, 0x20F80020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    b,b,s12 	0010 0bbb 1011 1000 FBBB ssss ssSS SSSS  */
{ (unsigned char *) "seteq%.f %#,%B,%K%F",                   0xF8FF0000, 0x20B80000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.cc><.f>    b,b,c 	0010 0bbb 1111 1000 FBBB CCCC CC0Q QQQQ  */
{ (unsigned char *) "seteq%.q%.f %#,%B,%C%F",                0xF8FF0020, 0x20F80000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.cc><.f>    b,b,limm 	0010 0bbb 1111 1000 FBBB 1111 100Q QQQQ  */
{ (unsigned char *) "seteq%.q%.f%Q %#,%B,%L%F",              0xF8FF0FE0, 0x20F80F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    a,b,c   	0010 0bbb 0011 1000 FBBB CCCC CCAA AAAA  */
{ (unsigned char *) "seteq%.f %A,%B,%C%F",                   0xF8FF0000, 0x20380000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    a,limm,c 	0010 0110 0011 1000 F111 CCCC CCAA AAAA  */
{ (unsigned char *) "seteq%.f%Q %A,%L,%C%F",                 0xFFFF7000, 0x26387000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    a,b,u6  	0010 0bbb 0111 1000 FBBB uuuu uuAA AAAA  */
{ (unsigned char *) "seteq%.f %A,%B,%u%F",                   0xF8FF0000, 0x20780000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    a,b,limm 	0010 0bbb 0011 1000 FBBB 1111 10AA AAAA  */
{ (unsigned char *) "seteq%.f%Q %A,%B,%L%F",                 0xF8FF0FC0, 0x20380F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    a,limm,u6 	0010 0110 0111 1000 F111 uuuu uuAA AAAA  */
{ (unsigned char *) "seteq%.f%Q %A,%L,%u%F",                 0xFFFF7000, 0x26787000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    a,limm,limm 	0010 0110 0011 1000 F111 1111 10AA AAAA  */
{ (unsigned char *) "seteq%.f%Q %A,%L,%L%F",                 0xFFFF7FC0, 0x26387F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    0,b,c   	0010 0bbb 0011 1000 FBBB CCCC CC11 1110  */
{ (unsigned char *) "seteq%.f 0,%B,%C%F",                    0xF8FF003F, 0x2038003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    0,limm,c 	0010 0110 0011 1000 F111 CCCC CC11 1110  */
{ (unsigned char *) "seteq%.f%Q 0,%L,%C%F",                  0xFFFF703F, 0x2638703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    0,b,u6  	0010 0bbb 0111 1000 FBBB uuuu uu11 1110  */
{ (unsigned char *) "seteq%.f 0,%B,%u%F",                    0xF8FF003F, 0x2078003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    0,b,limm 	0010 0bbb 0011 1000 FBBB 1111 1011 1110  */
{ (unsigned char *) "seteq%.f%Q 0,%B,%L%F",                  0xF8FF0FFF, 0x20380FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    0,limm,u6 	0010 0110 0111 1000 F111 uuuu uu11 1110  */
{ (unsigned char *) "seteq%.f%Q 0,%L,%u%F",                  0xFFFF703F, 0x2678703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    0,limm,s12 	0010 0110 1011 1000 F111 ssss ssSS SSSS  */
{ (unsigned char *) "seteq%.f%Q 0,%L,%K%F",                  0xFFFF7000, 0x26B87000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.f>    0,limm,limm 	0010 0110 0011 1000 F111 1111 1011 1110  */
{ (unsigned char *) "seteq%.f%Q 0,%L,%L%F",                  0xFFFF7FFF, 0x26387FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.cc><.f>    0,limm,c 	0010 0110 1111 1000 F111 CCCC CC0Q QQQQ  */
{ (unsigned char *) "seteq%.q%.f%Q 0,%L,%C%F",               0xFFFF7020, 0x26F87000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.cc><.f>    0,limm,u6 	0010 0110 1111 1000 F111 uuuu uu1Q QQQQ  */
{ (unsigned char *) "seteq%.q%.f%Q 0,%L,%u%F",               0xFFFF7020, 0x26F87020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seteq<.cc><.f>    0,limm,limm 	0010 0110 1111 1000 F111 1111 100Q QQQQ  */
{ (unsigned char *) "seteq%.q%.f%Q 0,%L,%L%F",               0xFFFF7FE0, 0x26F87F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*SETNE */
/* setne<.f>    a,b,c   	0010 0bbb 0011 1001 FBBB CCCC CCAA AAAA  */
{ (unsigned char *) "setne%.f %A,%B,%C%F",                   0xF8FF0000, 0x20390000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    a,b,u6  	0010 0bbb 0111 1001 FBBB uuuu uuAA AAAA  */
{ (unsigned char *) "setne%.f %A,%B,%u%F",                   0xF8FF0000, 0x20790000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    a,limm,u6 	0010 0110 0111 1001 F111 uuuu uuAA AAAA  */
{ (unsigned char *) "setne%.f%Q %A,%L,%u%F",                 0xFFFF7000, 0x26797000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    0,b,u6  	0010 0bbb 0111 1001 FBBB uuuu uu11 1110  */
{ (unsigned char *) "setne%.f 0,%B,%u%F",                    0xF8FF003F, 0x2079003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    0,limm,u6 	0010 0110 0111 1001 F111 uuuu uu11 1110  */
{ (unsigned char *) "setne%.f%Q 0,%L,%u%F",                  0xFFFF703F, 0x2679703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    b,b,s12 	0010 0bbb 1011 1001 FBBB ssss ssSS SSSS  */
{ (unsigned char *) "setne%.f %#,%B,%K%F",                   0xF8FF0000, 0x20B90000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    0,limm,s12 	0010 0110 1011 1001 F111 ssss ssSS SSSS  */
{ (unsigned char *) "setne%.f%Q 0,%L,%K%F",                  0xFFFF7000, 0x26B97000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    0,b,c   	0010 0bbb 0011 1001 FBBB CCCC CC11 1110  */
{ (unsigned char *) "setne%.f 0,%B,%C%F",                    0xF8FF003F, 0x2039003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    0,limm,c 	0010 0110 0011 1001 F111 CCCC CC11 1110  */
{ (unsigned char *) "setne%.f%Q 0,%L,%C%F",                  0xFFFF703F, 0x2639703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    0,b,limm 	0010 0bbb 0011 1001 FBBB 1111 1011 1110  */
{ (unsigned char *) "setne%.f%Q 0,%B,%L%F",                  0xF8FF0FFF, 0x20390FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    0,limm,limm 	0010 0110 0011 1001 F111 1111 1011 1110  */
{ (unsigned char *) "setne%.f%Q 0,%L,%L%F",                  0xFFFF7FFF, 0x26397FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.cc><.f>    b,b,c 	0010 0bbb 1111 1001 FBBB CCCC CC0Q QQQQ  */
{ (unsigned char *) "setne%.q%.f %#,%B,%C%F",                0xF8FF0020, 0x20F90000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.cc><.f>    b,b,u6 	0010 0bbb 1111 1001 FBBB uuuu uu1Q QQQQ  */
{ (unsigned char *) "setne%.q%.f %#,%B,%u%F",                0xF8FF0020, 0x20F90020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.cc><.f>    0,limm,u6 	0010 0110 1111 1001 F111 uuuu uu1Q QQQQ  */
{ (unsigned char *) "setne%.q%.f%Q 0,%L,%u%F",               0xFFFF7020, 0x26F97020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.cc><.f>    b,b,limm 	0010 0bbb 1111 1001 FBBB 1111 100Q QQQQ  */
{ (unsigned char *) "setne%.q%.f%Q %#,%B,%L%F",              0xF8FF0FE0, 0x20F90F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.cc><.f>    0,limm,c 	0010 0110 1111 1001 F111 CCCC CC0Q QQQQ  */
{ (unsigned char *) "setne%.q%.f%Q 0,%L,%C%F",               0xFFFF7020, 0x26F97000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.cc><.f>    0,limm,limm 	0010 0110 1111 1001 F111 1111 100Q QQQQ  */
{ (unsigned char *) "setne%.q%.f%Q 0,%L,%L%F",               0xFFFF7FE0, 0x26F97F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    a,limm,c 	0010 0110 0011 1001 F111 CCCC CCAA AAAA  */
{ (unsigned char *) "setne%.f%Q %A,%L,%C%F",                 0xFFFF7000, 0x26397000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    a,b,limm 	0010 0bbb 0011 1001 FBBB 1111 10AA AAAA  */
{ (unsigned char *) "setne%.f%Q %A,%B,%L%F",                 0xF8FF0FC0, 0x20390F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setne<.f>    a,limm,limm 	0010 0110 0011 1001 F111 1111 10AA AAAA  */
{ (unsigned char *) "setne%.f%Q %A,%L,%L%F",                 0xFFFF7FC0, 0x26397F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*SETLT */
/* setlt<.f>    a,b,c   	0010 0bbb 0011 1010 FBBB CCCC CCAA AAAA  */
{ (unsigned char *) "setlt%.f %A,%B,%C%F",                   0xF8FF0000, 0x203A0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    0,b,c   	0010 0bbb 0011 1010 FBBB CCCC CC11 1110  */
{ (unsigned char *) "setlt%.f 0,%B,%C%F",                    0xF8FF003F, 0x203A003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    a,b,u6  	0010 0bbb 0111 1010 FBBB uuuu uuAA AAAA  */
{ (unsigned char *) "setlt%.f %A,%B,%u%F",                   0xF8FF0000, 0x207A0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    a,limm,u6 	0010 0110 0111 1010 F111 uuuu uuAA AAAA  */
{ (unsigned char *) "setlt%.f%Q %A,%L,%u%F",                 0xFFFF7000, 0x267A7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    0,b,u6  	0010 0bbb 0111 1010 FBBB uuuu uu11 1110  */
{ (unsigned char *) "setlt%.f 0,%B,%u%F",                    0xF8FF003F, 0x207A003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    0,limm,u6 	0010 0110 0111 1010 F111 uuuu uu11 1110  */
{ (unsigned char *) "setlt%.f%Q 0,%L,%u%F",                  0xFFFF703F, 0x267A703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    b,b,s12 	0010 0bbb 1011 1010 FBBB ssss ssSS SSSS  */
{ (unsigned char *) "setlt%.f %#,%B,%K%F",                   0xF8FF0000, 0x20BA0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    0,limm,s12 	0010 0110 1011 1010 F111 ssss ssSS SSSS  */
{ (unsigned char *) "setlt%.f%Q 0,%L,%K%F",                  0xFFFF7000, 0x26BA7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.cc><.f>    b,b,c 	0010 0bbb 1111 1010 FBBB CCCC CC0Q QQQQ  */
{ (unsigned char *) "setlt%.q%.f %#,%B,%C%F",                0xF8FF0020, 0x20FA0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.cc><.f>    b,b,u6 	0010 0bbb 1111 1010 FBBB uuuu uu1Q QQQQ  */
{ (unsigned char *) "setlt%.q%.f %#,%B,%u%F",                0xF8FF0020, 0x20FA0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.cc><.f>    0,limm,u6 	0010 0110 1111 1010 F111 uuuu uu1Q QQQQ  */
{ (unsigned char *) "setlt%.q%.f%Q 0,%L,%u%F",               0xFFFF7020, 0x26FA7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.cc><.f>    b,b,limm 	0010 0bbb 1111 1010 FBBB 1111 100Q QQQQ  */
{ (unsigned char *) "setlt%.q%.f%Q %#,%B,%L%F",              0xF8FF0FE0, 0x20FA0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.cc><.f>    0,limm,c 	0010 0110 1111 1010 F111 CCCC CC0Q QQQQ  */
{ (unsigned char *) "setlt%.q%.f%Q 0,%L,%C%F",               0xFFFF7020, 0x26FA7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.cc><.f>    0,limm,limm 	0010 0110 1111 1010 F111 1111 100Q QQQQ  */
{ (unsigned char *) "setlt%.q%.f%Q 0,%L,%L%F",               0xFFFF7FE0, 0x26FA7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    a,limm,c 	0010 0110 0011 1010 F111 CCCC CCAA AAAA  */
{ (unsigned char *) "setlt%.f%Q %A,%L,%C%F",                 0xFFFF7000, 0x263A7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    a,b,limm 	0010 0bbb 0011 1010 FBBB 1111 10AA AAAA  */
{ (unsigned char *) "setlt%.f%Q %A,%B,%L%F",                 0xF8FF0FC0, 0x203A0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    a,limm,limm 	0010 0110 0011 1010 F111 1111 10AA AAAA  */
{ (unsigned char *) "setlt%.f%Q %A,%L,%L%F",                 0xFFFF7FC0, 0x263A7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    0,limm,c 	0010 0110 0011 1010 F111 CCCC CC11 1110  */
{ (unsigned char *) "setlt%.f%Q 0,%L,%C%F",                  0xFFFF703F, 0x263A703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    0,b,limm 	0010 0bbb 0011 1010 FBBB 1111 1011 1110  */
{ (unsigned char *) "setlt%.f%Q 0,%B,%L%F",                  0xF8FF0FFF, 0x203A0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlt<.f>    0,limm,limm 	0010 0110 0011 1010 F111 1111 1011 1110  */
{ (unsigned char *) "setlt%.f%Q 0,%L,%L%F",                  0xFFFF7FFF, 0x263A7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*SETGT */
/* setgt<.f>    a,b,c   	0010 0bbb 0011 1111 FBBB CCCC CCAA AAAA  */
{ (unsigned char *) "setgt%.f %A,%B,%C%F",                   0xF8FF0000, 0x203F0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    0,b,c   	0010 0bbb 0011 1111 FBBB CCCC CC11 1110  */
{ (unsigned char *) "setgt%.f 0,%B,%C%F",                    0xF8FF003F, 0x203F003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    a,b,u6  	0010 0bbb 0111 1111 FBBB uuuu uuAA AAAA  */
{ (unsigned char *) "setgt%.f %A,%B,%u%F",                   0xF8FF0000, 0x207F0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    a,limm,u6 	0010 0110 0111 1111 F111 uuuu uuAA AAAA  */
{ (unsigned char *) "setgt%.f%Q %A,%L,%u%F",                 0xFFFF7000, 0x267F7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    0,b,u6  	0010 0bbb 0111 1111 FBBB uuuu uu11 1110  */
{ (unsigned char *) "setgt%.f 0,%B,%u%F",                    0xF8FF003F, 0x207F003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    0,limm,u6 	0010 0110 0111 1111 F111 uuuu uu11 1110  */
{ (unsigned char *) "setgt%.f%Q 0,%L,%u%F",                  0xFFFF703F, 0x267F703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    b,b,s12 	0010 0bbb 1011 1111 FBBB ssss ssSS SSSS  */
{ (unsigned char *) "setgt%.f %#,%B,%K%F",                   0xF8FF0000, 0x20BF0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    0,limm,s12 	0010 0110 1011 1111 F111 ssss ssSS SSSS  */
{ (unsigned char *) "setgt%.f%Q 0,%L,%K%F",                  0xFFFF7000, 0x26BF7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.cc><.f>    b,b,c 	0010 0bbb 1111 1111 FBBB CCCC CC0Q QQQQ  */
{ (unsigned char *) "setgt%.q%.f %#,%B,%C%F",                0xF8FF0020, 0x20FF0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.cc><.f>    b,b,u6 	0010 0bbb 1111 1111 FBBB uuuu uu1Q QQQQ  */
{ (unsigned char *) "setgt%.q%.f %#,%B,%u%F",                0xF8FF0020, 0x20FF0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.cc><.f>    0,limm,u6 	0010 0110 1111 1111 F111 uuuu uu1Q QQQQ  */
{ (unsigned char *) "setgt%.q%.f%Q 0,%L,%u%F",               0xFFFF7020, 0x26FF7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.cc><.f>    b,b,limm 	0010 0bbb 1111 1111 FBBB 1111 100Q QQQQ  */
{ (unsigned char *) "setgt%.q%.f%Q %#,%B,%L%F",              0xF8FF0FE0, 0x20FF0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.cc><.f>    0,limm,c 	0010 0110 1111 1111 F111 CCCC CC0Q QQQQ  */
{ (unsigned char *) "setgt%.q%.f%Q 0,%L,%C%F",               0xFFFF7020, 0x26FF7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.cc><.f>    0,limm,limm 	0010 0110 1111 1111 F111 1111 100Q QQQQ  */
{ (unsigned char *) "setgt%.q%.f%Q 0,%L,%L%F",               0xFFFF7FE0, 0x26FF7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    a,limm,c 	0010 0110 0011 1111 F111 CCCC CCAA AAAA  */
{ (unsigned char *) "setgt%.f%Q %A,%L,%C%F",                 0xFFFF7000, 0x263F7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    a,b,limm 	0010 0bbb 0011 1111 FBBB 1111 10AA AAAA  */
{ (unsigned char *) "setgt%.f%Q %A,%B,%L%F",                 0xF8FF0FC0, 0x203F0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    a,limm,limm 	0010 0110 0011 1111 F111 1111 10AA AAAA  */
{ (unsigned char *) "setgt%.f%Q %A,%L,%L%F",                 0xFFFF7FC0, 0x263F7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    0,limm,c 	0010 0110 0011 1111 F111 CCCC CC11 1110  */
{ (unsigned char *) "setgt%.f%Q 0,%L,%C%F",                  0xFFFF703F, 0x263F703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    0,b,limm 	0010 0bbb 0011 1111 FBBB 1111 1011 1110  */
{ (unsigned char *) "setgt%.f%Q 0,%B,%L%F",                  0xF8FF0FFF, 0x203F0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setgt<.f>    0,limm,limm 	0010 0110 0011 1111 F111 1111 1011 1110  */
{ (unsigned char *) "setgt%.f%Q 0,%L,%L%F",                  0xFFFF7FFF, 0x263F7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},

/*SETGE */
/* setge<.f>    a,b,c   	0010 0bbb 0011 1011 FBBB CCCC CCAA AAAA  */
{ (unsigned char *) "setge%.f %A,%B,%C%F",                   0xF8FF0000, 0x203B0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    0,b,c   	0010 0bbb 0011 1011 FBBB CCCC CC11 1110  */
{ (unsigned char *) "setge%.f 0,%B,%C%F",                    0xF8FF003F, 0x203B003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    a,b,u6  	0010 0bbb 0111 1011 FBBB uuuu uuAA AAAA  */
{ (unsigned char *) "setge%.f %A,%B,%u%F",                   0xF8FF0000, 0x207B0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    a,limm,u6 	0010 0110 0111 1011 F111 uuuu uuAA AAAA  */
{ (unsigned char *) "setge%.f%Q %A,%L,%u%F",                 0xFFFF7000, 0x267B7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    0,b,u6  	0010 0bbb 0111 1011 FBBB uuuu uu11 1110  */
{ (unsigned char *) "setge%.f 0,%B,%u%F",                    0xF8FF003F, 0x207B003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    0,limm,u6 	0010 0110 0111 1011 F111 uuuu uu11 1110  */
{ (unsigned char *) "setge%.f%Q 0,%L,%u%F",                  0xFFFF703F, 0x267B703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    b,b,s12 	0010 0bbb 1011 1011 FBBB ssss ssSS SSSS  */
{ (unsigned char *) "setge%.f %#,%B,%K%F",                   0xF8FF0000, 0x20BB0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    0,limm,s12 	0010 0110 1011 1011 F111 ssss ssSS SSSS  */
{ (unsigned char *) "setge%.f%Q 0,%L,%K%F",                  0xFFFF7000, 0x26BB7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.cc><.f>    b,b,c 	0010 0bbb 1111 1011 FBBB CCCC CC0Q QQQQ  */
{ (unsigned char *) "setge%.q%.f %#,%B,%C%F",                0xF8FF0020, 0x20FB0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.cc><.f>    b,b,u6 	0010 0bbb 1111 1011 FBBB uuuu uu1Q QQQQ  */
{ (unsigned char *) "setge%.q%.f %#,%B,%u%F",                0xF8FF0020, 0x20FB0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.cc><.f>    0,limm,u6 	0010 0110 1111 1011 F111 uuuu uu1Q QQQQ  */
{ (unsigned char *) "setge%.q%.f%Q 0,%L,%u%F",               0xFFFF7020, 0x26FB7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.cc><.f>    b,b,limm 	0010 0bbb 1111 1011 FBBB 1111 100Q QQQQ  */
{ (unsigned char *) "setge%.q%.f%Q %#,%B,%L%F",              0xF8FF0FE0, 0x20FB0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.cc><.f>    0,limm,c 	0010 0110 1111 1011 F111 CCCC CC0Q QQQQ  */
{ (unsigned char *) "setge%.q%.f%Q 0,%L,%C%F",               0xFFFF7020, 0x26FB7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.cc><.f>    0,limm,limm 	0010 0110 1111 1011 F111 1111 100Q QQQQ  */
{ (unsigned char *) "setge%.q%.f%Q 0,%L,%L%F",               0xFFFF7FE0, 0x26FB7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    a,limm,c 	0010 0110 0011 1011 F111 CCCC CCAA AAAA  */
{ (unsigned char *) "setge%.f%Q %A,%L,%C%F",                 0xFFFF7000, 0x263B7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    a,b,limm 	0010 0bbb 0011 1011 FBBB 1111 10AA AAAA  */
{ (unsigned char *) "setge%.f%Q %A,%B,%L%F",                 0xF8FF0FC0, 0x203B0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    a,limm,limm 	0010 0110 0011 1011 F111 1111 10AA AAAA  */
{ (unsigned char *) "setge%.f%Q %A,%L,%L%F",                 0xFFFF7FC0, 0x263B7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    0,limm,c 	0010 0110 0011 1011 F111 CCCC CC11 1110  */
{ (unsigned char *) "setge%.f%Q 0,%L,%C%F",                  0xFFFF703F, 0x263B703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    0,b,limm 	0010 0bbb 0011 1011 FBBB 1111 1011 1110  */
{ (unsigned char *) "setge%.f%Q 0,%B,%L%F",                  0xF8FF0FFF, 0x203B0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setge<.f>    0,limm,limm 	0010 0110 0011 1011 F111 1111 1011 1110  */
{ (unsigned char *) "setge%.f%Q 0,%L,%L%F",                  0xFFFF7FFF, 0x263B7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},

/*SETLO */
/* setlo<.f>    a,b,c   	0010 0bbb 0011 1100 FBBB CCCC CCAA AAAA  */
{ (unsigned char *) "setlo%.f %A,%B,%C%F",                   0xF8FF0000, 0x203C0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    0,b,c   	0010 0bbb 0011 1100 FBBB CCCC CC11 1110  */
{ (unsigned char *) "setlo%.f 0,%B,%C%F",                    0xF8FF003F, 0x203C003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    a,b,u6  	0010 0bbb 0111 1100 FBBB uuuu uuAA AAAA  */
{ (unsigned char *) "setlo%.f %A,%B,%u%F",                   0xF8FF0000, 0x207C0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    a,limm,u6 	0010 0110 0111 1100 F111 uuuu uuAA AAAA  */
{ (unsigned char *) "setlo%.f%Q %A,%L,%u%F",                 0xFFFF7000, 0x267C7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    0,b,u6  	0010 0bbb 0111 1100 FBBB uuuu uu11 1110  */
{ (unsigned char *) "setlo%.f 0,%B,%u%F",                    0xF8FF003F, 0x207C003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    0,limm,u6 	0010 0110 0111 1100 F111 uuuu uu11 1110  */
{ (unsigned char *) "setlo%.f%Q 0,%L,%u%F",                  0xFFFF703F, 0x267C703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    b,b,s12 	0010 0bbb 1011 1100 FBBB ssss ssSS SSSS  */
{ (unsigned char *) "setlo%.f %#,%B,%K%F",                   0xF8FF0000, 0x20BC0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    0,limm,s12 	0010 0110 1011 1100 F111 ssss ssSS SSSS  */
{ (unsigned char *) "setlo%.f%Q 0,%L,%K%F",                  0xFFFF7000, 0x26BC7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.cc><.f>    b,b,c 	0010 0bbb 1111 1100 FBBB CCCC CC0Q QQQQ  */
{ (unsigned char *) "setlo%.q%.f %#,%B,%C%F",                0xF8FF0020, 0x20FC0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.cc><.f>    b,b,u6 	0010 0bbb 1111 1100 FBBB uuuu uu1Q QQQQ  */
{ (unsigned char *) "setlo%.q%.f %#,%B,%u%F",                0xF8FF0020, 0x20FC0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.cc><.f>    0,limm,u6 	0010 0110 1111 1100 F111 uuuu uu1Q QQQQ  */
{ (unsigned char *) "setlo%.q%.f%Q 0,%L,%u%F",               0xFFFF7020, 0x26FC7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.cc><.f>    b,b,limm 	0010 0bbb 1111 1100 FBBB 1111 100Q QQQQ  */
{ (unsigned char *) "setlo%.q%.f%Q %#,%B,%L%F",              0xF8FF0FE0, 0x20FC0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.cc><.f>    0,limm,c 	0010 0110 1111 1100 F111 CCCC CC0Q QQQQ  */
{ (unsigned char *) "setlo%.q%.f%Q 0,%L,%C%F",               0xFFFF7020, 0x26FC7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.cc><.f>    0,limm,limm 	0010 0110 1111 1100 F111 1111 100Q QQQQ  */
{ (unsigned char *) "setlo%.q%.f%Q 0,%L,%L%F",               0xFFFF7FE0, 0x26FC7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    a,limm,c 	0010 0110 0011 1100 F111 CCCC CCAA AAAA  */
{ (unsigned char *) "setlo%.f%Q %A,%L,%C%F",                 0xFFFF7000, 0x263C7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    a,b,limm 	0010 0bbb 0011 1100 FBBB 1111 10AA AAAA  */
{ (unsigned char *) "setlo%.f%Q %A,%B,%L%F",                 0xF8FF0FC0, 0x203C0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    a,limm,limm 	0010 0110 0011 1100 F111 1111 10AA AAAA  */
{ (unsigned char *) "setlo%.f%Q %A,%L,%L%F",                 0xFFFF7FC0, 0x263C7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    0,limm,c 	0010 0110 0011 1100 F111 CCCC CC11 1110  */
{ (unsigned char *) "setlo%.f%Q 0,%L,%C%F",                  0xFFFF703F, 0x263C703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    0,b,limm 	0010 0bbb 0011 1100 FBBB 1111 1011 1110  */
{ (unsigned char *) "setlo%.f%Q 0,%B,%L%F",                  0xF8FF0FFF, 0x203C0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setlo<.f>    0,limm,limm 	0010 0110 0011 1100 F111 1111 1011 1110  */
{ (unsigned char *) "setlo%.f%Q 0,%L,%L%F",                  0xFFFF7FFF, 0x263C7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},

/*SETHS */
/* seths<.f>    a,b,c   	0010 0bbb 0011 1101 FBBB CCCC CCAA AAAA  */
{ (unsigned char *) "seths%.f %A,%B,%C%F",                   0xF8FF0000, 0x203D0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    0,b,c   	0010 0bbb 0011 1101 FBBB CCCC CC11 1110  */
{ (unsigned char *) "seths%.f 0,%B,%C%F",                    0xF8FF003F, 0x203D003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    a,b,u6  	0010 0bbb 0111 1101 FBBB uuuu uuAA AAAA  */
{ (unsigned char *) "seths%.f %A,%B,%u%F",                   0xF8FF0000, 0x207D0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    a,limm,u6 	0010 0110 0111 1101 F111 uuuu uuAA AAAA  */
{ (unsigned char *) "seths%.f%Q %A,%L,%u%F",                 0xFFFF7000, 0x267D7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    0,b,u6  	0010 0bbb 0111 1101 FBBB uuuu uu11 1110  */
{ (unsigned char *) "seths%.f 0,%B,%u%F",                    0xF8FF003F, 0x207D003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    0,limm,u6 	0010 0110 0111 1101 F111 uuuu uu11 1110  */
{ (unsigned char *) "seths%.f%Q 0,%L,%u%F",                  0xFFFF703F, 0x267D703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    b,b,s12 	0010 0bbb 1011 1101 FBBB ssss ssSS SSSS  */
{ (unsigned char *) "seths%.f %#,%B,%K%F",                   0xF8FF0000, 0x20BD0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    0,limm,s12 	0010 0110 1011 1101 F111 ssss ssSS SSSS  */
{ (unsigned char *) "seths%.f%Q 0,%L,%K%F",                  0xFFFF7000, 0x26BD7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.cc><.f>    b,b,c 	0010 0bbb 1111 1101 FBBB CCCC CC0Q QQQQ  */
{ (unsigned char *) "seths%.q%.f %#,%B,%C%F",                0xF8FF0020, 0x20FD0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.cc><.f>    b,b,u6 	0010 0bbb 1111 1101 FBBB uuuu uu1Q QQQQ  */
{ (unsigned char *) "seths%.q%.f %#,%B,%u%F",                0xF8FF0020, 0x20FD0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.cc><.f>    0,limm,u6 	0010 0110 1111 1101 F111 uuuu uu1Q QQQQ  */
{ (unsigned char *) "seths%.q%.f%Q 0,%L,%u%F",               0xFFFF7020, 0x26FD7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.cc><.f>    b,b,limm 	0010 0bbb 1111 1101 FBBB 1111 100Q QQQQ  */
{ (unsigned char *) "seths%.q%.f%Q %#,%B,%L%F",              0xF8FF0FE0, 0x20FD0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.cc><.f>    0,limm,c 	0010 0110 1111 1101 F111 CCCC CC0Q QQQQ  */
{ (unsigned char *) "seths%.q%.f%Q 0,%L,%C%F",               0xFFFF7020, 0x26FD7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.cc><.f>    0,limm,limm 	0010 0110 1111 1101 F111 1111 100Q QQQQ  */
{ (unsigned char *) "seths%.q%.f%Q 0,%L,%L%F",               0xFFFF7FE0, 0x26FD7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    a,limm,c 	0010 0110 0011 1101 F111 CCCC CCAA AAAA  */
{ (unsigned char *) "seths%.f%Q %A,%L,%C%F",                 0xFFFF7000, 0x263D7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    a,b,limm 	0010 0bbb 0011 1101 FBBB 1111 10AA AAAA  */
{ (unsigned char *) "seths%.f%Q %A,%B,%L%F",                 0xF8FF0FC0, 0x203D0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    a,limm,limm 	0010 0110 0011 1101 F111 1111 10AA AAAA  */
{ (unsigned char *) "seths%.f%Q %A,%L,%L%F",                 0xFFFF7FC0, 0x263D7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    0,limm,c 	0010 0110 0011 1101 F111 CCCC CC11 1110  */
{ (unsigned char *) "seths%.f%Q 0,%L,%C%F",                  0xFFFF703F, 0x263D703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    0,b,limm 	0010 0bbb 0011 1101 FBBB 1111 1011 1110  */
{ (unsigned char *) "seths%.f%Q 0,%B,%L%F",                  0xF8FF0FFF, 0x203D0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* seths<.f>    0,limm,limm 	0010 0110 0011 1101 F111 1111 1011 1110  */
{ (unsigned char *) "seths%.f%Q 0,%L,%L%F",                  0xFFFF7FFF, 0x263D7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},

/*SETLE */
/* setle<.f>    a,b,c   	0010 0bbb 0011 1110 FBBB CCCC CCAA AAAA  */
{ (unsigned char *) "setle%.f %A,%B,%C%F",                   0xF8FF0000, 0x203E0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    0,b,c   	0010 0bbb 0011 1110 FBBB CCCC CC11 1110  */
{ (unsigned char *) "setle%.f 0,%B,%C%F",                    0xF8FF003F, 0x203E003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    a,b,u6  	0010 0bbb 0111 1110 FBBB uuuu uuAA AAAA  */
{ (unsigned char *) "setle%.f %A,%B,%u%F",                   0xF8FF0000, 0x207E0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    a,limm,u6 	0010 0110 0111 1110 F111 uuuu uuAA AAAA  */
{ (unsigned char *) "setle%.f%Q %A,%L,%u%F",                 0xFFFF7000, 0x267E7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    0,b,u6  	0010 0bbb 0111 1110 FBBB uuuu uu11 1110  */
{ (unsigned char *) "setle%.f 0,%B,%u%F",                    0xF8FF003F, 0x207E003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    0,limm,u6 	0010 0110 0111 1110 F111 uuuu uu11 1110  */
{ (unsigned char *) "setle%.f%Q 0,%L,%u%F",                  0xFFFF703F, 0x267E703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    b,b,s12 	0010 0bbb 1011 1110 FBBB ssss ssSS SSSS  */
{ (unsigned char *) "setle%.f %#,%B,%K%F",                   0xF8FF0000, 0x20BE0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    0,limm,s12 	0010 0110 1011 1110 F111 ssss ssSS SSSS  */
{ (unsigned char *) "setle%.f%Q 0,%L,%K%F",                  0xFFFF7000, 0x26BE7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.cc><.f>    b,b,c 	0010 0bbb 1111 1110 FBBB CCCC CC0Q QQQQ  */
{ (unsigned char *) "setle%.q%.f %#,%B,%C%F",                0xF8FF0020, 0x20FE0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.cc><.f>    b,b,u6 	0010 0bbb 1111 1110 FBBB uuuu uu1Q QQQQ  */
{ (unsigned char *) "setle%.q%.f %#,%B,%u%F",                0xF8FF0020, 0x20FE0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.cc><.f>    0,limm,u6 	0010 0110 1111 1110 F111 uuuu uu1Q QQQQ  */
{ (unsigned char *) "setle%.q%.f%Q 0,%L,%u%F",               0xFFFF7020, 0x26FE7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.cc><.f>    b,b,limm 	0010 0bbb 1111 1110 FBBB 1111 100Q QQQQ  */
{ (unsigned char *) "setle%.q%.f%Q %#,%B,%L%F",              0xF8FF0FE0, 0x20FE0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.cc><.f>    0,limm,c 	0010 0110 1111 1110 F111 CCCC CC0Q QQQQ  */
{ (unsigned char *) "setle%.q%.f%Q 0,%L,%C%F",               0xFFFF7020, 0x26FE7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.cc><.f>    0,limm,limm 	0010 0110 1111 1110 F111 1111 100Q QQQQ  */
{ (unsigned char *) "setle%.q%.f%Q 0,%L,%L%F",               0xFFFF7FE0, 0x26FE7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    a,limm,c 	0010 0110 0011 1110 F111 CCCC CCAA AAAA  */
{ (unsigned char *) "setle%.f%Q %A,%L,%C%F",                 0xFFFF7000, 0x263E7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    a,b,limm 	0010 0bbb 0011 1110 FBBB 1111 10AA AAAA  */
{ (unsigned char *) "setle%.f%Q %A,%B,%L%F",                 0xF8FF0FC0, 0x203E0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    a,limm,limm 	0010 0110 0011 1110 F111 1111 10AA AAAA  */
{ (unsigned char *) "setle%.f%Q %A,%L,%L%F",                 0xFFFF7FC0, 0x263E7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    0,limm,c 	0010 0110 0011 1110 F111 CCCC CC11 1110  */
{ (unsigned char *) "setle%.f%Q 0,%L,%C%F",                  0xFFFF703F, 0x263E703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    0,b,limm 	0010 0bbb 0011 1110 FBBB 1111 1011 1110  */
{ (unsigned char *) "setle%.f%Q 0,%B,%L%F",                  0xF8FF0FFF, 0x203E0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* setle<.f>    0,limm,limm 	0010 0110 0011 1110 F111 1111 1011 1110  */
{ (unsigned char *) "setle%.f%Q 0,%L,%L%F",                  0xFFFF7FFF, 0x263E7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},

/*SWI */
/* swi                  	0010 0010 0110 1111 0000 0000 0011 1111  */
{ (unsigned char *) "swi",                                  0xFFFFFFFF, 0x226F003F, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* swi_s                	0111 1010 1110 0000  */
{ (unsigned char *) "swi_s",                                0xFFFF, 0x7AE0, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* sub_s    a,b,c               0100 1bbb ccc1 0aaa  */
{ (unsigned char *) "sub_s %a,%b,%c",                        0xF818, 0x4810, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*STH_S */
/* sth_s    c,[b,u6]            1011 0bbb cccu uuuu  */
{ (unsigned char *) "sth_s %c,[%b,%k]",                      0xF800, 0xB000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sth_s %c,[%b]",                         0xF800, 0xB000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*SEXH */
{ (unsigned char *) "sexh%.f %#,%C%F",                       0xF8FF003F, 0x202F0006, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sexh%.f %#,%u%F",                       0xF8FF003F, 0x206F0006, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sexh%.f 0,%C%F",                        0xFFFF703F, 0x262F7006, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sexh%.f 0,%u%F",                        0xFFFF703F, 0x266F7006, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sexh%.f%Q %#,%L%F",                     0xF8FF0FFF, 0x202F0F86, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sexh%.f%Q 0,%L%F",                      0xFFFF7FFF, 0x262F7F86, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sexh_s %b,%c",                          0xF81F, 0x780E, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*EXTH */
{ (unsigned char *) "exth%.f %#,%C%F",                       0xF8FF003F, 0x202F0008, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "exth%.f %#,%u%F",                       0xF8FF003F, 0x206F0008, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "exth%.f%Q %#,%L%F",                     0xF8FF0FFF, 0x202F0F88, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "exth%.f 0,%C%F",                        0xFFFF703F, 0x262F7008, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "exth%.f 0,%u%F",                        0xFFFF703F, 0x266F7008, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "exth%.f%Q 0,%L%F",                      0xFFFF7FFF, 0x262F7F88, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "exth_s %b,%c",                          0xF81F, 0x7810, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*DIV */
{ (unsigned char *) "div%.q%.f %#,%B,%u%F",                  0xF8FF0020, 0x28C40020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.q%.f%Q 0,%L,%u%F",                 0xFFFF7020, 0x2EC47020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f %A,%B,%u%F",                     0xF8FF0000, 0x28440000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f%Q %A,%L,%u%F",                   0xFFFF7000, 0x2E447000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f 0,%B,%u%F",                      0xF8FF003F, 0x2844003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f%Q 0,%L,%u%F",                    0xFFFF703F, 0x2E44703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f %#,%B,%K%F",                     0xF8FF0000, 0x28840000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f%Q 0,%L,%K%F",                    0xFFFF7000, 0x2E847000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f %A,%B,%C%F",                     0xF8FF0000, 0x28040000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f%Q %A,%L,%C%F",                   0xFFFF7000, 0x2E047000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f%Q %A,%B,%L%F",                   0xF8FF0FC0, 0x28040F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f%Q %A,%L,%L%F",                   0xFFFF7FC0, 0x2E047F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f 0,%B,%C%F",                      0xF8FF003F, 0x2804003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f%Q 0,%L,%C%F",                    0xFFFF703F, 0x2E04703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f%Q 0,%B,%L%F",                    0xF8FF0FFF, 0x28040FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.f%Q 0,%L,%L%F",                    0xFFFF7FFF, 0x2E047FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.q%.f %#,%B,%C%F",                  0xF8FF0020, 0x28C40000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.q%.f%Q %#,%B,%L%F",                0xF8FF0FE0, 0x28C40F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.q%.f%Q 0,%L,%C%F",                 0xFFFF7020, 0x2EC47000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "div%.q%.f%Q 0,%L,%L%F",                 0xFFFF7FE0, 0x2EC47F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*DIVU */
{ (unsigned char *) "divu%.q%.f %#,%B,%u%F",                 0xF8FF0020, 0x28C50020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.q%.f%Q 0,%L,%u%F",                0xFFFF7020, 0x2EC57020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f %A,%B,%u%F",                    0xF8FF0000, 0x28450000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f%Q %A,%L,%u%F",                  0xFFFF7000, 0x2E457000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f 0,%B,%u%F",                     0xF8FF003F, 0x2845003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f%Q 0,%L,%u%F",                   0xFFFF703F, 0x2E45703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f %#,%B,%K%F",                    0xF8FF0000, 0x28850000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f%Q 0,%L,%K%F",                   0xFFFF7000, 0x2E857000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f %A,%B,%C%F",                    0xF8FF0000, 0x28050000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f%Q %A,%L,%C%F",                  0xFFFF7000, 0x2E057000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f%Q %A,%B,%L%F",                  0xF8FF0FC0, 0x28050F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f%Q %A,%L,%L%F",                  0xFFFF7FC0, 0x2E057F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f 0,%B,%C%F",                     0xF8FF003F, 0x2805003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f%Q 0,%L,%C%F",                   0xFFFF703F, 0x2E05703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f%Q 0,%B,%L%F",                   0xF8FF0FFF, 0x28050FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.f%Q 0,%L,%L%F",                   0xFFFF7FFF, 0x2E057FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.q%.f %#,%B,%C%F",                 0xF8FF0020, 0x28C50000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.q%.f%Q %#,%B,%L%F",               0xF8FF0FE0, 0x28C50F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.q%.f%Q 0,%L,%C%F",                0xFFFF7020, 0x2EC57000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "divu%.q%.f%Q 0,%L,%L%F",                0xFFFF7FE0, 0x2EC57F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BMSKN */
{ (unsigned char *) "bmskn%.f %A,%B,%u%F",                   0xF8FF0000, 0x206C0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f%Q %A,%L,%u%F",                 0xFFFF7000, 0x266C7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f 0,%B,%u%F",                    0xF8FF003F, 0x206C003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f%Q 0,%L,%u%F",                  0xFFFF703F, 0x266C703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f %#,%B,%K%F",                   0xF8FF0000, 0x20AC0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f%Q 0,%L,%K%F",                  0xFFFF7000, 0x26AC7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f %A,%B,%C%F",                   0xF8FF0000, 0x202C0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f%Q %A,%L,%C%F",                 0xFFFF7000, 0x262C7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f%Q %A,%B,%L%F",                 0xF8FF0FC0, 0x202C0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f%Q %A,%L,%L%F",                 0xFFFF7FC0, 0x262C7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f 0,%B,%C%F",                    0xF8FF003F, 0x202C003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f%Q 0,%L,%C%F",                  0xFFFF703F, 0x262C703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f%Q 0,%B,%L%F",                  0xF8FF0FFF, 0x202C0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.f%Q 0,%L,%L%F",                  0xFFFF7FFF, 0x262C7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.q%.f %#,%B,%C%F",                0xF8FF0020, 0x20EC0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.q%.f %#,%B,%u%F",                0xF8FF0020, 0x20EC0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.q%.f%Q 0,%L,%u%F",               0xFFFF7020, 0x26EC7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.q%.f%Q %#,%B,%L%F",              0xF8FF0FE0, 0x20EC0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.q%.f%Q 0,%L,%C%F",               0xFFFF7020, 0x26EC7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bmskn%.q%.f%Q 0,%L,%L%F",               0xFFFF7FE0, 0x26EC7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BI */
{ (unsigned char *) "bi [%C]",                               0xFFFFF03F, 0x20240000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BIH */
{ (unsigned char *) "bih [%C]",                              0xFFFFF03F, 0x20250000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*JEQ_S */
{ (unsigned char *) "jeq_s [%9]",                            0xFFFF, 0x7CE0, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*JNE_S */
{ (unsigned char *) "jne_s [%9]",                            0xFFFF, 0x7DE0, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*MPY_S */
{ (unsigned char *) "mpy_s %b,%b,%c",                        0xF81F, 0x780C, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*MPYM */
{ (unsigned char *) "mpym%.f %A,%B,%C%F",                    0xF8FF0000, 0x201B0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f 0,%B,%C%F",                     0xF8FF003F, 0x201B003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f %A,%B,%u%F",                    0xF8FF0000, 0x205B0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f%Q %A,%L,%u%F",                  0xFFFF7000, 0x265B7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f 0,%B,%u%F",                     0xF8FF003F, 0x205B003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f%Q 0,%L,%u%F",                   0xFFFF703F, 0x265B703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f %#,%B,%K%F",                    0xF8FF0000, 0x209B0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f%Q 0,%L,%K%F",                   0xFFFF7000, 0x269B7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.q%.f %#,%B,%C%F",                 0xF8FF0020, 0x20DB0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.q%.f %#,%B,%u%F",                 0xF8FF0020, 0x20DB0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.q%.f%Q %#,%B,%L%F",               0xF8FF0FE0, 0x20DB0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.q%.f%Q 0,%L,%C%F",                0xFFFF7020, 0x26DB7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.q%.f%Q 0,%L,%L%F",                0xFFFF7FE0, 0x26DB7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.q%.f%Q 0,%L,%u%F",                0xFFFF7020, 0x26DB7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f%Q %A,%L,%C%F",                  0xFFFF7000, 0x261B7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f%Q %A,%B,%L%F",                  0xF8FF0FC0, 0x201B0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f%Q %A,%L,%L%F",                  0xFFFF7FC0, 0x261B7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f%Q 0,%L,%C%F",                   0xFFFF703F, 0x261B703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f%Q 0,%B,%L%F",                   0xF8FF0FFF, 0x201B0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpym%.f%Q 0,%L,%L%F",                   0xFFFF7FFF, 0x261B7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*MPYMU */
{ (unsigned char *) "mpymu%.f %A,%B,%C%F",                   0xF8FF0000, 0x201C0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f 0,%B,%C%F",                    0xF8FF003F, 0x201C003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f %A,%B,%u%F",                   0xF8FF0000, 0x205C0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f%Q %A,%L,%u%F",                 0xFFFF7000, 0x265C7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f 0,%B,%u%F",                    0xF8FF003F, 0x205C003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f%Q 0,%L,%u%F",                  0xFFFF703F, 0x265C703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f %#,%B,%K%F",                   0xF8FF0000, 0x209C0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f%Q 0,%L,%K%F",                  0xFFFF7000, 0x269C7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.q%.f %#,%B,%C%F",                0xF8FF0020, 0x20DC0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.q%.f %#,%B,%u%F",                0xF8FF0020, 0x20DC0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.q%.f%Q %#,%B,%L%F",              0xF8FF0FE0, 0x20DC0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.q%.f%Q 0,%L,%C%F",               0xFFFF7020, 0x26DC7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.q%.f%Q 0,%L,%L%F",               0xFFFF7FE0, 0x26DC7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.q%.f%Q 0,%L,%u%F",               0xFFFF7020, 0x26DC7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f%Q %A,%L,%C%F",                 0xFFFF7000, 0x261C7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f%Q %A,%B,%L%F",                 0xF8FF0FC0, 0x201C0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f%Q %A,%L,%L%F",                 0xFFFF7FC0, 0x261C7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f%Q 0,%L,%C%F",                  0xFFFF703F, 0x261C703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f%Q 0,%B,%L%F",                  0xF8FF0FFF, 0x201C0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpymu%.f%Q 0,%L,%L%F",                  0xFFFF7FFF, 0x261C7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*MPYUW */
{ (unsigned char *) "mpyuw%.f %A,%B,%C%F",                   0xF8FF0000, 0x201F0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f 0,%B,%C%F",                    0xF8FF003F, 0x201F003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f %A,%B,%u%F",                   0xF8FF0000, 0x205F0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f%Q %A,%L,%u%F",                 0xFFFF7000, 0x265F7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f 0,%B,%u%F",                    0xF8FF003F, 0x205F003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f%Q 0,%L,%u%F",                  0xFFFF703F, 0x265F703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f %#,%B,%K%F",                   0xF8FF0000, 0x209F0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f%Q 0,%L,%K%F",                  0xFFFF7000, 0x269F7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.q%.f %#,%B,%C%F",                0xF8FF0020, 0x20DF0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.q%.f %#,%B,%u%F",                0xF8FF0020, 0x20DF0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.q%.f%Q %#,%B,%L%F",              0xF8FF0FE0, 0x20DF0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.q%.f%Q 0,%L,%C%F",               0xFFFF7020, 0x26DF7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.q%.f%Q 0,%L,%L%F",               0xFFFF7FE0, 0x26DF7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.q%.f%Q 0,%L,%u%F",               0xFFFF7020, 0x26DF7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f%Q %A,%L,%C%F",                 0xFFFF7000, 0x261F7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f%Q %A,%B,%L%F",                 0xF8FF0FC0, 0x201F0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f%Q %A,%L,%L%F",                 0xFFFF7FC0, 0x261F7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f%Q 0,%L,%C%F",                  0xFFFF703F, 0x261F703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f%Q 0,%B,%L%F",                  0xF8FF0FFF, 0x201F0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyuw%.f%Q 0,%L,%L%F",                  0xFFFF7FFF, 0x261F7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*MPYUW_S */
{ (unsigned char *) "mpyuw_s %b,%b,%c",                      0xF81F, 0x780A, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*MPYW_S */
{ (unsigned char *) "mpyw_s %b,%b,%c",                       0xF81F, 0x7809, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*MPYW */
{ (unsigned char *) "mpyw%.f %A,%B,%C%F",                    0xF8FF0000, 0x201E0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f 0,%B,%C%F",                     0xF8FF003F, 0x201E003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f %A,%B,%u%F",                    0xF8FF0000, 0x205E0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f%Q %A,%L,%u%F",                  0xFFFF7000, 0x265E7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f 0,%B,%u%F",                     0xF8FF003F, 0x205E003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f%Q 0,%L,%u%F",                   0xFFFF703F, 0x265E703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f %#,%B,%K%F",                    0xF8FF0000, 0x209E0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f%Q 0,%L,%K%F",                   0xFFFF7000, 0x269E7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.q%.f %#,%B,%C%F",                 0xF8FF0020, 0x20DE0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.q%.f %#,%B,%u%F",                 0xF8FF0020, 0x20DE0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.q%.f%Q %#,%B,%L%F",               0xF8FF0FE0, 0x20DE0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.q%.f%Q 0,%L,%C%F",                0xFFFF7020, 0x26DE7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.q%.f%Q 0,%L,%L%F",                0xFFFF7FE0, 0x26DE7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.q%.f%Q 0,%L,%u%F",                0xFFFF7020, 0x26DE7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f%Q %A,%L,%C%F",                  0xFFFF7000, 0x261E7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f%Q %A,%B,%L%F",                  0xF8FF0FC0, 0x201E0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f%Q %A,%L,%L%F",                  0xFFFF7FC0, 0x261E7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f%Q 0,%L,%C%F",                   0xFFFF703F, 0x261E703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f%Q 0,%B,%L%F",                   0xF8FF0FFF, 0x201E0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyw%.f%Q 0,%L,%L%F",                   0xFFFF7FFF, 0x261E7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*NORMH */
{ (unsigned char *) "normh%.f %#,%C%F",                      0xF8FF003F, 0x282F0008, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "normh%.f 0,%C%F",                       0xFFFF703F, 0x2E2F7008, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "normh%.f %#,%u%F",                      0xF8FF003F, 0x286F0008, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "normh%.f 0,%u%F",                       0xFFFF703F, 0x2E6F7008, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "normh%.f%Q %#,%L%F",                    0xF8FF0FFF, 0x282F0F88, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "normh%.f%Q 0,%L%F",                     0xFFFF7FFF, 0x2E2F7F88, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*REM */
{ (unsigned char *) "rem%.f %A,%B,%C%F",                     0xF8FF0000, 0x28080000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f 0,%B,%C%F",                      0xF8FF003F, 0x2808003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f %A,%B,%u%F",                     0xF8FF0000, 0x28480000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f%Q %A,%L,%u%F",                   0xFFFF7000, 0x2E487000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f 0,%B,%u%F",                      0xF8FF003F, 0x2848003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f%Q 0,%L,%u%F",                    0xFFFF703F, 0x2E48703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f %#,%B,%K%F",                     0xF8FF0000, 0x28880000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f%Q 0,%L,%K%F",                    0xFFFF7000, 0x2E887000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.q%.f %#,%B,%C%F",                  0xF8FF0020, 0x28C80000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.q%.f %#,%B,%u%F",                  0xF8FF0020, 0x28C80020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.q%.f%Q %#,%B,%L%F",                0xF8FF0FE0, 0x28C80F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.q%.f%Q 0,%L,%C%F",                 0xFFFF7020, 0x2EC87000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.q%.f%Q 0,%L,%L%F",                 0xFFFF7FE0, 0x2EC87F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.q%.f%Q 0,%L,%u%F",                 0xFFFF7020, 0x2EC87020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f%Q %A,%L,%C%F",                   0xFFFF7000, 0x2E087000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f%Q %A,%B,%L%F",                   0xF8FF0FC0, 0x28080F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f%Q %A,%L,%L%F",                   0xFFFF7FC0, 0x2E087F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f%Q 0,%L,%C%F",                    0xFFFF703F, 0x2E08703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f%Q 0,%B,%L%F",                    0xF8FF0FFF, 0x28080FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "rem%.f%Q 0,%L,%L%F",                    0xFFFF7FFF, 0x2E087FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*REMU */
{ (unsigned char *) "remu%.f %A,%B,%C%F",                    0xF8FF0000, 0x28090000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f 0,%B,%C%F",                     0xF8FF003F, 0x2809003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f %A,%B,%u%F",                    0xF8FF0000, 0x28490000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f%Q %A,%L,%u%F",                  0xFFFF7000, 0x2E497000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f 0,%B,%u%F",                     0xF8FF003F, 0x2849003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f%Q 0,%L,%u%F",                   0xFFFF703F, 0x2E49703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f %#,%B,%K%F",                    0xF8FF0000, 0x28890000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f%Q 0,%L,%K%F",                   0xFFFF7000, 0x2E897000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.q%.f %#,%B,%C%F",                 0xF8FF0020, 0x28C90000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.q%.f %#,%B,%u%F",                 0xF8FF0020, 0x28C90020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.q%.f%Q %#,%B,%L%F",               0xF8FF0FE0, 0x28C90F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.q%.f%Q 0,%L,%C%F",                0xFFFF7020, 0x2EC97000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.q%.f%Q 0,%L,%L%F",                0xFFFF7FE0, 0x2EC97F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.q%.f%Q 0,%L,%u%F",                0xFFFF7020, 0x2EC97020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f%Q %A,%L,%C%F",                  0xFFFF7000, 0x2E097000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f%Q %A,%B,%L%F",                  0xF8FF0FC0, 0x28090F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f%Q %A,%L,%L%F",                  0xFFFF7FC0, 0x2E097F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f%Q 0,%L,%C%F",                   0xFFFF703F, 0x2E09703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f%Q 0,%B,%L%F",                   0xF8FF0FFF, 0x28090FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "remu%.f%Q 0,%L,%L%F",                   0xFFFF7FFF, 0x2E097FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*LDH_S */
{ (unsigned char *) "ldh_s %a,[%b,%c]",                      0xF818, 0x6010, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldh_s %c,[%b,%k]",                      0xF800, 0x9000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldh_s %c,[%b]",                         0xF800, 0x9000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldh_s %4,[%5,%[L]",                     0xFE00, 0xCC00, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldh_s %4,[%5,%O]",                      0xFE00, 0xCC00, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldh_s %4,[%5]",                         0xFE00, 0xCC00, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldh_s.x %c,[%b,%k]",                    0xF800, 0x9800, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldh_s.x %c,[%b]",                       0xF800, 0x9800, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*LR */
/* lr    b,[c]          	0010 0bbb 0010 1010 RBBB CCCC CCRR RRRR  */
{ (unsigned char *) "lr %#,[%C]",                            0xF8FF803F, 0x202A0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* lr    b,[u6]         	0010 0bbb 0110 1010 RBBB uuuu uu00 0000  */
{ (unsigned char *) "lr %#,[%u]",                            0xF8FF803F, 0x206A0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* lr    b,[s12]        	0010 0bbb 1010 1010 RBBB ssss ssSS SSSS  */
{ (unsigned char *) "lr %#,[%GC]",                           0xF8FF8000, 0x20AA0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lr %#,[%K]",                            0xF8FF8000, 0x20AA0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* lr    b,[limm]       	0010 0bbb 0010 1010 RBBB 1111 10RR RRRR  */
{ (unsigned char *) "lr%Q %#,[%L]",                          0xF8FF8FFF, 0x202A0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*SR */
{ (unsigned char *) "sr %B,[%C]",                            0xF8FF803F, 0x202B0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sr %B,[%u]",                            0xF8FF803F, 0x206B0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sr %B,[%K]",                            0xF8FF8000, 0x20AB0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sr %B,[%GC]",                           0xF8FF8000, 0x20AB0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sr%Q %B,[%L]",                          0xF8FF8FFF, 0x202B0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sr%Q %L,[%C]",                          0xFFFFF03F, 0x262B7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sr%Q %L,[%u]",                          0xFFFFF03F, 0x266B7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sr%Q %L,[%K]",                          0xFFFFF000, 0x26AB7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sr%Q %L,[%GC]",                         0xFFFFF000, 0x26AB7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*AEX */
{ (unsigned char *) "aex %B,[%C]",                           0xF8FF803F, 0x20270000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "aex %B,[%u]",                           0xF8FF803F, 0x20670000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "aex %B,[%K]",                           0xF8FF8000, 0x20A70000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "aex %B,[%CG]",                          0xF8FF8000, 0x20A70000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "aex%Q %B,[%L]",                         0xF8FF8FFF, 0x20270F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "aex%.q %B,[%C]",                        0xF8FF8020, 0x20E70000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "aex%.q %B,[%u]",                        0xF8FF8020, 0x20E70020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "aex%.q%Q %B,[%L]",                      0xF8FF8FE0, 0x20E70F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*CLRI */
/* clri    c            	0010 0111 0010 1111 0000 CCCC CC11 1111  */
{ (unsigned char *) "clri %C",                             0xFFFFF03F, 0x272F003F, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* clri    u6           	0010 0111 0110 1111 0000 uuuu uu11 1111  */
{ (unsigned char *) "clri %u",                                0xFFFFF03F, 0x276F003F, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "clri",                                   0xFFFFFFFF, 0x276F003F, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*LP */
{ (unsigned char *) "lp %Y",                                 0xFFFFF000, 0x20A80000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lp %y",                                 0xFFFFF03F, 0x20680000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lp%.q %y",                              0xFFFFF020, 0x20E80020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "lp%q %y",                               0xFFFFF020, 0x20E80020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*SETI */
{ (unsigned char *) "seti %C",                                0xFFFFF03F, 0x262F003F, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "seti %u",                                0xFFFFF03F, 0x266F003F, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "seti",                                   0xFFFFFFFF, 0x266F003F, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*ADD_S */
/* add_s    a,b,c       	0110 0bbb ccc1 1aaa  */
{ (unsigned char *) "add_s %a,%b,%c",                        0xF818, 0x6018, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* add_s    b,b,h       	0111 0bbb hhh0 00HH  */
{ (unsigned char *) "add_s %b,%b,%Ä",                        0xF81C, 0x7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* add_s    h,h,s3      	0111 0sss hhh0 01HH  */
{ (unsigned char *) "add_s %Ä,%Ä,%Ö",                        0xF81C, 0x7004, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* add_s    b,sp,u7     	1100 0bbb 100u uuuu  */
{ (unsigned char *) "add_s %b,%6,%l",                        0xF8E0, 0xC080, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* add_s    b,b,u7      	1110 0bbb 0uuu uuuu  */
{ (unsigned char *) "add_s %b,%b,%j",                        0xF880, 0xE000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* add_s    c,b,u3      	0110 1bbb ccc0 0uuu  */
{ (unsigned char *) "add_s %c,%b,%e",                        0xF818, 0x6800, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* add_s    SP,SP,u7    	1100 0000 101u uuuu  */
{ (unsigned char *) "add_s %6,%6,%l",                        0xFFE0, 0xC0A0, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* add_s    R0,GP,s11   	1100 111s ssss ssss  */
{ (unsigned char *) "add_s %4,%5,%R",                        0xFE00, 0xCE00, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* add_s    R0,b,Au6    	0100 1bbb 0UUU 1uuu  */
{ (unsigned char *) "add_s %4,%b,%Ü",                        0xF888, 0x4808, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* add_s    R1,b,Au6    	0100 1bbb 1UUU 1uuu  */
{ (unsigned char *) "add_s %Å,%b,%Ü",                        0xF888, 0x4888, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* add_s    0,limm,s3   	0111 0sss 1100 0111  */
{ (unsigned char *) "add_s%Q 0,%L,%Ö",                       0xF8FF, 0x70C7, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* add_s    b,b,limm    	0111 0bbb 1100 0011  */
{ (unsigned char *) "add_s%Q %b,%b,%L",                      0xF8FF, 0x70C3, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*CMP_S */
/* cmp_s    b,h         	0111 0bbb hhh1 00HH  */
{ (unsigned char *) "cmp_s %b,%Ä",                           0xF81C, 0x7010, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* cmp_s    h,s3        	0111 0sss hhh1 01HH  */
{ (unsigned char *) "cmp_s %Ä,%Ö",                           0xF81C, 0x7014, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* cmp_s    b,u7        	1110 0bbb 1uuu uuuu  */
{ (unsigned char *) "cmp_s %b,%j",                           0xF880, 0xE080, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* cmp_s    b,limm      	0111 0bbb 1101 0011  */
{ (unsigned char *) "cmp_s%Q %b,%L",                         0xF8FF, 0x70D3, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* cmp_s    limm,s3     	0111 0sss 1101 0111  */
{ (unsigned char *) "cmp_s%Q %L,%Ö",                         0xF8FF, 0x70D7, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*ENTER_S */
/* enter_s    Eu6       	1100 00UU 111u uuu0  */
{ (unsigned char *) "enter_s {%á}",                          0xFCE1, 0xC0E0, ARC_MACH_ARCV2, 0, 0, 0, 0},

/*EI_S */
/* ei_s    u10          	0101 11uu uuuu uuuu  */
{ (unsigned char *) "ei_s %à",                               0xFC00, 0x5C00, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*JLI_S */
/* jli_s    u10         	0101 10uu uuuu uuuu  */
{ (unsigned char *) "jli_s %à",                              0xFC00, 0x5800, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*LDI_S */
/* ldi_s    b,[Lu7]     	0101 0bbb UUUU 1uuu  */
{ (unsigned char *) "ldi_s %b,[%â]",                         0xF808, 0x5008, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*LEAVE_S */
/* leave_s    u7        	1100 0UUU 110u uuu0  */
{ (unsigned char *) "leave_s {%ä}",                          0xF8E1, 0xC0C0, ARC_MACH_ARCV2, 0, 0, 0, 0},

/*MOV_S */
/* mov_s    h,s3        	0111 0sss hhh0 11HH  */
{ (unsigned char *) "mov_s %Ä,%Ö",                           0xF81C, 0x700C, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* mov_s    0,s3        	0111 0sss 1100 1111  */
{ (unsigned char *) "mov_s 0,%Ö",                            0xF8FF, 0x70CF, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* mov_s    b,u8        	1101 1bbb uuuu uuuu  */
{ (unsigned char *) "mov_s %b,%J",                           0xF800, 0xD800, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* mov_s    g,h         	0100 0ggg hhhG G0HH  */
{ (unsigned char *) "mov_s %å,%Ä",                           0xF804, 0x4000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* mov_s    g,limm      	0100 0ggg 110G G011  */
{ (unsigned char *) "mov_s%Q %å,%L",                         0xF8E7, 0x40C3, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* mov_s    0,h         	0100 0110 hhh1 10HH  */
{ (unsigned char *) "mov_s 0,%Ä",                            0xFF1C, 0x4618, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* mov_s    0,limm      	0100 0110 1101 1011  */
{ (unsigned char *) "mov_s%Q 0,%L",                          0xFFFF, 0x46DB, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* mov_s.ne    b,h      	0111 0bbb hhh1 11HH  */
{ (unsigned char *) "mov_s.ne %b,%Ä",                        0xF81C, 0x701C, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* mov_s.nz    b,h      	0111 0bbb hhh1 11HH  */
{ (unsigned char *) "mov_s.nz %b,%Ä",                        0xF81C, 0x701C, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* mov_s.ne    b, 0  This is a sub_s.ne b,b,b */
/*{ (unsigned char *) "mov_s.ne %b,0",                     0xF8FF, 0x78C0, ARC_MACH_ARCV2, 0, 0, 0, 0},*/
/* mov_s.ne    b,limm   	0111 0bbb 1101 1111  */
{ (unsigned char *) "mov_s.ne%Q %b,%L",                      0xF8FF, 0x70DF, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*LDI */
{ (unsigned char *) "ldi %#,[%C]",                           0xF8FF803F, 0x20260000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldi 0,[%C]",                            0xFFFFF03F, 0x26267000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldi %#,[%u]",                           0xF8FF803F, 0x20660000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldi 0,[%u]",                            0xFFFFF03F, 0x26667000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldi %#,[%K]",                           0xF8FF8000, 0x20A60000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldi 0,[%K]",                            0xFFFFF000, 0x26A67000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldi%.q %#,[%u]",                        0xF8FF8020, 0x20E60020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldi%.q 0,[%u]",                         0xFFFFF020, 0x26E67020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldi%Q %#,[%L]",                         0xF8FF8FFF, 0x20260F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ldi%Q 0,[%L]",                          0xFFFFFFFF, 0x26267F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*ST_S */
/* st_s    R0,[GP,Ss11] 	0101 0SSS SSS1 0sss  */
{ (unsigned char *) "st_s %4,[%5,%[L]",                         0xF818, 0x5010, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "st_s %4,[%5,%ç]",                       0xF818, 0x5010, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "st_s %4,[%5]",                             0xF818, 0x5010, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*ST */
{ (unsigned char *) "st%z%.w%.D %Ñ,[%g]%0",                  0xF8FF8001, 0x18000001, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "st%z%.w%.D %Ñ,[%g,%o]%0",               0xF8000001, 0x18000001, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "st%z%.w%.D %C,[%g]%0",                  0xF8FF8001, 0x18000000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "st%z%.w%.D %C,[%g,%[L]%0",               0xF8000001, 0x18000000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "st%z%.w%.D %C,[%g,%o]%0",               0xF8000001, 0x18000000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "st%z%.D%Q %C,[%L]%0",                   0xFFFFF019, 0x1E007000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "st%z%.w%.D%Q %Ñ,[%L]%0",             0xFF007001, 0x1E007001, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "st%z%.w%.D%Q %Ñ,[%L,%o]%0",             0xFF007001, 0x1E007001, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "st%z%.w%.D%Q %L,[%g]%0",                0xF8000FC1, 0x18000F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "st%z%.w%.D%Q %L,[%g,%o]%0",             0xF8000FC1, 0x18000F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "st%z%.w%.D%Q %L,[%L,%o]%0",             0xFF007FC1, 0x1E007F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*LD_S */
/* ld_s    R0,[h,Lu5]   	0100 0U00 hhhu u1HH  */
{ (unsigned char *) "ld_s %4,[%Ä,%é]",                       0xFB04, 0x4004, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* ld_s    R1,[h,Lu5]   	0100 0U01 hhhu u1HH  */
{ (unsigned char *) "ld_s %Å,[%Ä,%é]",                       0xFB04, 0x4104, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* ld_s    R2,[h,Lu5]   	0100 0U10 hhhu u1HH  */
{ (unsigned char *) "ld_s %Ç,[%Ä,%é]",                       0xFB04, 0x4204, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* ld_s    R3,[h,Lu5]   	0100 0U11 hhhu u1HH  */
{ (unsigned char *) "ld_s %É,[%Ä,%é]",                       0xFB04, 0x4304, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* ld_s<.aa>    a,[b,c] 	0100 1bbb ccc0 0aaa  */
{ (unsigned char *) "ld_s.as %a,[%b,%c]",                    0xF818, 0x4800, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* ld_s    R1,[GP,Ss11] 	0101 0SSS SSS0 0sss  */
{ (unsigned char *) "ld_s %Å,[%5,%[L]",                         0xF818, 0x5000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ld_s %Å,[%5,%ç]",                       0xF818, 0x5000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "ld_s %Å,[%5]",                             0xF818, 0x5000, ARC_MACH_ARCV2, 0, 0, 0, 0},

/*J missing J [BLINK]*/
/* j    c               	0010 0RRR 0010 0000 RRRR CCCC CCRR RRRR  */
{ (unsigned char *) "j [%C]",                                0xFFFFF03F, 0x20200000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* j    u6              	0010 0RRR 0110 0000 RRRR uuuu uuRR RRRR  */
{ (unsigned char *) "j %u",                                  0xFFFFF03F, 0x20600000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* j    s12             	0010 0RRR 1010 0000 RRRR ssss ssSS SSSS  */
{ (unsigned char *) "j %K",                                  0xFFFFF000, 0x20A00000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* j    limm            	0010 0RRR 0010 0000 RRRR 1111 10RR RRRR  */
{ (unsigned char *) "j%Q %L",                                0xFFFFFFFF, 0x20200F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* j<.cc>    c          	0010 0RRR 1110 0000 RRRR CCCC CC0Q QQQQ  */
{ (unsigned char *) "j%q [%C]",                              0xFFFFF020, 0x20E00000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* j<.cc>    u6         	0010 0RRR 1110 0000 RRRR uuuu uu1Q QQQQ  */
{ (unsigned char *) "j%q %u",                                0xFFFFF020, 0x20E00020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* j<.cc>    limm       	0010 0RRR 1110 0000 RRRR 1111 100Q QQQQ  */
{ (unsigned char *) "j%q%Q %L",                              0xFFFFFFE0, 0x20E00F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* j.D    c             	0010 0RRR 0010 0001 RRRR CCCC CCRR RRRR  */
{ (unsigned char *) "j.d [%C]",                              0xFFFFF03F, 0x20210000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* j.D    u6            	0010 0RRR 0110 0001 RRRR uuuu uuRR RRRR  */
{ (unsigned char *) "j.d %u",                                0xFFFFF03F, 0x20610000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* j.D    s12           	0010 0RRR 1010 0001 RRRR ssss ssSS SSSS  */
{ (unsigned char *) "j.d %K",                                0xFFFFF000, 0x20A10000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* j<.cc>.D    c        	0010 0RRR 1110 0001 RRRR CCCC CC0Q QQQQ  */
{ (unsigned char *) "j%q.d [%C]",                            0xFFFFF020, 0x20E10000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* j<.cc>.D    u6       	0010 0RRR 1110 0001 RRRR uuuu uu1Q QQQQ  */
{ (unsigned char *) "j%q.d %u",                              0xFFFFF020, 0x20E10020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*JL */
/* jl    c              	0010 0RRR 0010 0010 RRRR CCCC CCRR RRRR  */
{ (unsigned char *) "jl [%C]",                               0xFFFFF03F, 0x20220000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* jl    u6             	0010 0RRR 0110 0010 RRRR uuuu uuRR RRRR  */
{ (unsigned char *) "jl %u",                                 0xFFFFF03F, 0x20620000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* jl    s12            	0010 0RRR 1010 0010 RRRR ssss ssSS SSSS  */
{ (unsigned char *) "jl %K",                                 0xFFFFF000, 0x20A20000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* jl    limm           	0010 0RRR 0010 0010 RRRR 1111 10RR RRRR  */
{ (unsigned char *) "jl%Q %L",                               0xFFFFFFFF, 0x20220F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* jl<.cc>    c         	0010 0RRR 1110 0010 RRRR CCCC CC0Q QQQQ  */
{ (unsigned char *) "jl%q [%C]",                             0xFFFFF020, 0x20E20000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* jl<.cc>    u6        	0010 0RRR 1110 0010 RRRR uuuu uu1Q QQQQ  */
{ (unsigned char *) "jl%q %u",                               0xFFFFF020, 0x20E20020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* jl<.cc>    limm      	0010 0RRR 1110 0010 RRRR 1111 100Q QQQQ  */
{ (unsigned char *) "jl%q%Q %L",                             0xFFFFFFE0, 0x20E20F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* jl.D    c            	0010 0RRR 0010 0011 RRRR CCCC CCRR RRRR  */
{ (unsigned char *) "jl.d [%C]",                             0xFFFFF03F, 0x20230000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* jl.D    u6           	0010 0RRR 0110 0011 RRRR uuuu uuRR RRRR  */
{ (unsigned char *) "jl.d %u",                               0xFFFFF03F, 0x20630000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* jl.D    s12          	0010 0RRR 1010 0011 RRRR ssss ssSS SSSS  */
{ (unsigned char *) "jl.d %K",                               0xFFFFF000, 0x20A30000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* jl<.cc>.D    c       	0010 0RRR 1110 0011 RRRR CCCC CC0Q QQQQ  */
{ (unsigned char *) "jl%q.d [%C]",                           0xFFFFF020, 0x20E30000, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* jl<.cc>.D    u6      	0010 0RRR 1110 0011 RRRR uuuu uu1Q QQQQ  */
{ (unsigned char *) "jl%q.d %u",                             0xFFFFF020, 0x20E30020, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BBIT0 */
{ (unsigned char *) "bbit0%.n%.è %B,%C,%d%ê",                0xF8010017, 0x8010006, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit0%.n%.è %B,%u,%d%ê",                0xF8010017, 0x8010016, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit0%.è%.n %B,%C,%d%ê",                0xF8010017, 0x8010006, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit0%.è%.n %B,%u,%d%ê",                0xF8010017, 0x8010016, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit0%.è%Q %B,%L,%d%ê",                 0xF8010FF7, 0x8010F86, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit0%.è%Q %L,%C,%d%ê",                 0xFF017037, 0xE017006, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit0%.è%Q %L,%u,%d%ê",                 0xFF017037, 0xE017016, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit0%.è%Q %L,%L,%d%ê",                 0xFF017FF7, 0xE017F86, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BBIT1 */
{ (unsigned char *) "bbit1%.n%.è %B,%C,%d%ê",                0xF8010017, 0x8010007, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit1%.n%.è %B,%u,%d%ê",                0xF8010017, 0x8010017, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit1%.è%.n %B,%C,%d%ê",                0xF8010017, 0x8010007, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit1%.è%.n %B,%u,%d%ê",                0xF8010017, 0x8010017, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit1%.è%Q %B,%L,%d%ê",                 0xF8010FF7, 0x8010F87, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit1%.è%Q %L,%C,%d%ê",                 0xFF017037, 0xE017007, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit1%.è%Q %L,%u,%d%ê",                 0xFF017037, 0xE017017, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "bbit1%.è%Q %L,%L,%d%ê",                 0xFF017FF7, 0xE017F87, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BREQ */
{ (unsigned char *) "breq%.n%.è %B,%C,%d%ë",                 0xF8010017, 0x8010000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "breq%.n%.è %B,%u,%d%ë",                 0xF8010017, 0x8010010, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "breq%.è%.n %B,%C,%d%ë",                 0xF8010017, 0x8010000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "breq%.è%.n %B,%u,%d%ë",                 0xF8010017, 0x8010010, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "breq%.è%Q %B,%L,%d%ë",                  0xF8010FF7, 0x8010F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "breq%.è%Q %L,%C,%d%ë",                  0xFF017037, 0xE017000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "breq%.è%Q %L,%u,%d%ë",                  0xFF017037, 0xE017010, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "breq%.è%Q %L,%L,%d%ë",                  0xFF017FF7, 0xE017F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRNE */
{ (unsigned char *) "brne%.n%.è %B,%C,%d%ë",                 0xF8010017, 0x8010001, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brne%.n%.è %B,%u,%d%ë",                 0xF8010017, 0x8010011, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brne%.è%.n %B,%C,%d%ë",                 0xF8010017, 0x8010001, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brne%.è%.n %B,%u,%d%ë",                 0xF8010017, 0x8010011, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brne%.è%Q %B,%L,%d%ë",                  0xF8010FF7, 0x8010F81, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brne%.è%Q %L,%C,%d%ë",                  0xFF017037, 0xE017001, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brne%.è%Q %L,%u,%d%ë",                  0xFF017037, 0xE017011, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brne%.è%Q %L,%L,%d%ë",                  0xFF017FF7, 0xE017F81, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRLT */
{ (unsigned char *) "brlt%.n%.è %B,%C,%d%ë",                 0xF8010017, 0x8010002, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlt%.n%.è %B,%u,%d%ë",                 0xF8010017, 0x8010012, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlt%.è%.n %B,%C,%d%ë",                 0xF8010017, 0x8010002, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlt%.è%.n %B,%u,%d%ë",                 0xF8010017, 0x8010012, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlt%.è%Q %B,%L,%d%ë",                  0xF8010FF7, 0x8010F82, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlt%.è%Q %L,%C,%d%ë",                  0xFF017037, 0xE017002, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlt%.è%Q %L,%u,%d%ë",                  0xFF017037, 0xE017012, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlt%.è%Q %L,%L,%d%ë",                  0xFF017FF7, 0xE017F82, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRGE */
{ (unsigned char *) "brge%.n%.è %B,%C,%d%ë",                 0xF8010017, 0x8010003, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brge%.n%.è %B,%u,%d%ë",                 0xF8010017, 0x8010013, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brge%.è%.n %B,%C,%d%ë",                 0xF8010017, 0x8010003, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brge%.è%.n %B,%u,%d%ë",                 0xF8010017, 0x8010013, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brge%.è%Q %B,%L,%d%ë",                  0xF8010FF7, 0x8010F83, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brge%.è%Q %L,%C,%d%ë",                  0xFF017037, 0xE017003, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brge%.è%Q %L,%u,%d%ë",                  0xFF017037, 0xE017013, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brge%.è%Q %L,%L,%d%ë",                  0xFF017FF7, 0xE017F83, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRLO */
{ (unsigned char *) "brlo%.n%.è %B,%C,%d%ë",                 0xF8010017, 0x8010004, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlo%.n%.è %B,%u,%d%ë",                 0xF8010017, 0x8010014, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlo%.è%.n %B,%C,%d%ë",                 0xF8010017, 0x8010004, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlo%.è%.n %B,%u,%d%ë",                 0xF8010017, 0x8010014, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlo%.è%Q %B,%L,%d%ë",                  0xF8010FF7, 0x8010F84, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlo%.è%Q %L,%C,%d%ë",                  0xFF017037, 0xE017004, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlo%.è%Q %L,%u,%d%ë",                  0xFF017037, 0xE017014, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brlo%.è%Q %L,%L,%d%ë",                  0xFF017FF7, 0xE017F84, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRHS */
{ (unsigned char *) "brhs%.n%.è %B,%C,%d%ë",                 0xF8010017, 0x8010005, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brhs%.n%.è %B,%u,%d%ë",                 0xF8010017, 0x8010015, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brhs%.è%.n %B,%C,%d%ë",                 0xF8010017, 0x8010005, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brhs%.è%.n %B,%u,%d%ë",                 0xF8010017, 0x8010015, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brhs%.è%Q %B,%L,%d%ë",                  0xF8010FF7, 0x8010F85, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brhs%.è%Q %L,%C,%d%ë",                  0xFF017037, 0xE017005, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brhs%.è%Q %L,%u,%d%ë",                  0xFF017037, 0xE017015, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brhs%.è%Q %L,%L,%d%ë",                  0xFF017FF7, 0xE017F85, ARC_MACH_ARCV2, 0, 0, 0, 0},

/*Pseudo mnemonics for BRcc instruction */
/*BRGT b,c,s9 */
{ (unsigned char *) "brgt%.n%.è %C,%B,%d%ë",                 0xF8010017, 0x8010002, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brgt%.è%.n %C,%B,%d%ë",                 0xF8010017, 0x8010002, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRGT b,u6,s9*/
{ (unsigned char *) "brgt%.n%.è %B,%u,%d%ë",                 0xF8010017, 0x8010013, ARC_MACH_ARCV2 | ARC_INCR_U6, 0, 0, 0, 0},
{ (unsigned char *) "brgt%.è%.n %B,%u,%d%ë",                 0xF8010017, 0x8010013, ARC_MACH_ARCV2 | ARC_INCR_U6, 0, 0, 0, 0},
/*BRGT b,limm,s9*/
{ (unsigned char *) "brgt%.è%Q %C,%L,%d%ë",                  0xFF017037, 0xE017002, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRGT limm,c,s9*/
{ (unsigned char *) "brgt%.è%Q %L,%B,%d%ë",                  0xF8010FF7, 0x8010F82, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRGT limm,u6,s9*/
{ (unsigned char *) "brgt%.è%Q %L,%u,%d%ë",                  0xFF017037, 0xE017013, ARC_MACH_ARCV2 | ARC_INCR_U6, 0, 0, 0, 0},

/*BRHI b,c,s9*/
{ (unsigned char *) "brhi%.n%.è %C,%B,%d%ë",                 0xF8010017, 0x8010004, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brhi%.è%.n %C,%B,%d%ë",                 0xF8010017, 0x8010004, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRHI b,u6,s9*/
{ (unsigned char *) "brhi%.n%.è %B,%u,%d%ë",                 0xF8010017, 0x8010015, ARC_MACH_ARCV2 | ARC_INCR_U6, 0, 0, 0, 0},
{ (unsigned char *) "brhi%.è%.n %B,%u,%d%ë",                 0xF8010017, 0x8010015, ARC_MACH_ARCV2 | ARC_INCR_U6, 0, 0, 0, 0},
/*BRHI b,limm,s9*/
{ (unsigned char *) "brhi%.è%Q %C,%L,%d%ë",                  0xFF017037, 0xE017004, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRHI limm,c,s9*/
{ (unsigned char *) "brhi%.è%Q %L,%B,%d%ë",                  0xF8010FF7, 0x8010F84, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRHI limm,u6,s9*/
{ (unsigned char *) "brhi%.è%Q %L,%u,%d%ë",                  0xFF017037, 0xE017015, ARC_MACH_ARCV2 | ARC_INCR_U6, 0, 0, 0, 0},


/*BRLE b,c,s9*/
{ (unsigned char *) "brle%.n%.è %C,%B,%d%ë",                 0xF8010017, 0x8010003, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brle%.è%.n %C,%B,%d%ë",                 0xF8010017, 0x8010003, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRLE b,u6,s9*/
{ (unsigned char *) "brle%.n%.è %B,%u,%d%ë",                 0xF8010017, 0x8010012, ARC_MACH_ARCV2 | ARC_INCR_U6, 0, 0, 0, 0},
{ (unsigned char *) "brle%.è%.n %B,%u,%d%ë",                 0xF8010017, 0x8010012, ARC_MACH_ARCV2 | ARC_INCR_U6, 0, 0, 0, 0},
/*BRLE b,limm,s9*/
{ (unsigned char *) "brle%.è%Q %C,%L,%d%ë",                  0xFF017037, 0xE017003, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRLE limm,c,s9*/
{ (unsigned char *) "brle%.è%Q %L,%B,%d%ë",                  0xF8010FF7, 0x8010F83, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRLE limm,u6,s9*/
{ (unsigned char *) "brle%.è%Q %L,%u,%d%ë",                  0xFF017037, 0xE017012, ARC_MACH_ARCV2 | ARC_INCR_U6, 0, 0, 0, 0},


/*BRLS b,c,s9*/
{ (unsigned char *) "brls%.n%.è %C,%B,%d%ë",                 0xF8010017, 0x8010005, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "brls%.è%.n %C,%B,%d%ë",                 0xF8010017, 0x8010005, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRLS b,u6,s9*/
{ (unsigned char *) "brls%.n%.è %B,%u,%d%ë",                 0xF8010017, 0x8010014, ARC_MACH_ARCV2 | ARC_INCR_U6, 0, 0, 0, 0},
{ (unsigned char *) "brls%.è%.n %B,%u,%d%ë",                 0xF8010017, 0x8010014, ARC_MACH_ARCV2 | ARC_INCR_U6, 0, 0, 0, 0},
/*BRLS b,limm,s9*/
{ (unsigned char *) "brls%.è%Q %C,%L,%d%ë",                  0xFF017037, 0xE017005, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRLS limm,c,s9*/
{ (unsigned char *) "brls%.è%Q %L,%B,%d%ë",                  0xF8010FF7, 0x8010F85, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*BRLS limm,u6,s9*/
{ (unsigned char *) "brls%.è%Q %L,%u,%d%ë",                  0xFF017037, 0xE017014, ARC_MACH_ARCV2 | ARC_INCR_U6, 0, 0, 0, 0},

/*/*End*/

/*MPY */
{ (unsigned char *) "mpy%.f %A,%B,%C%F",                     0xF8FF0000, 0x201A0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f %A,%B,%u%F",                     0xF8FF0000, 0x205A0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f %#,%B,%K%F",                     0xF8FF0000, 0x209A0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f 0,%B,%C%F",                      0xF8FF003F, 0x201A003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f 0,%B,%u%F",                      0xF8FF003F, 0x205A003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f%Q %A,%L,%C%F",                   0xFFFF7000, 0x261A7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f%Q %A,%L,%u%F",                   0xFFFF7000, 0x265A7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f%Q %A,%B,%L%F",                   0xF8FF0FC0, 0x201A0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f%Q %A,%L,%L%F",                   0xFFFF7FC0, 0x261A7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f%Q 0,%L,%C%F",                    0xFFFF703F, 0x261A703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f%Q 0,%L,%u%F",                    0xFFFF703F, 0x265A703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f%Q 0,%L,%K%F",                    0xFFFF7000, 0x269A7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f%Q 0,%B,%L%F",                    0xF8FF0FFF, 0x201A0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.f%Q 0,%L,%L%F",                    0xFFFF7FFF, 0x261A7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.q%.f %#,%B,%C%F",                  0xF8FF0020, 0x20DA0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.q%.f %#,%B,%u%F",                  0xF8FF0020, 0x20DA0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.q%.f%Q %#,%B,%L%F",                0xF8FF0FE0, 0x20DA0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.q%.f%Q 0,%L,%C%F",                 0xFFFF7020, 0x26DA7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.q%.f%Q 0,%L,%u%F",                 0xFFFF7020, 0x26DA7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpy%.q%.f%Q 0,%L,%L%F",                 0xFFFF7FE0, 0x26DA7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*MPYU */
{ (unsigned char *) "mpyu%.f %A,%B,%C%F",                    0xF8FF0000, 0x201D0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f %A,%B,%u%F",                    0xF8FF0000, 0x205D0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f %#,%B,%K%F",                    0xF8FF0000, 0x209D0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f 0,%B,%C%F",                     0xF8FF003F, 0x201D003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f 0,%B,%u%F",                     0xF8FF003F, 0x205D003E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f%Q %A,%L,%C%F",                  0xFFFF7000, 0x261D7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f%Q %A,%L,%u%F",                  0xFFFF7000, 0x265D7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f%Q %A,%B,%L%F",                  0xF8FF0FC0, 0x201D0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f%Q %A,%L,%L%F",                  0xFFFF7FC0, 0x261D7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f%Q 0,%L,%C%F",                   0xFFFF703F, 0x261D703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f%Q 0,%L,%u%F",                   0xFFFF703F, 0x265D703E, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f%Q 0,%L,%K%F",                   0xFFFF7000, 0x269D7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f%Q 0,%B,%L%F",                   0xF8FF0FFF, 0x201D0FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.f%Q 0,%L,%L%F",                   0xFFFF7FFF, 0x261D7FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.q%.f %#,%B,%C%F",                 0xF8FF0020, 0x20DD0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.q%.f %#,%B,%u%F",                 0xF8FF0020, 0x20DD0020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.q%.f%Q %#,%B,%L%F",               0xF8FF0FE0, 0x20DD0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.q%.f%Q 0,%L,%C%F",                0xFFFF7020, 0x26DD7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.q%.f%Q 0,%L,%u%F",                0xFFFF7020, 0x26DD7020, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "mpyu%.q%.f%Q 0,%L,%L%F",                0xFFFF7FE0, 0x26DD7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*NORM */
{ (unsigned char *) "norm%.f %#,%C%F",                       0xF8FF003F, 0x282F0001, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "norm%.f %#,%u%F",                       0xF8FF003F, 0x286F0001, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "norm%.f 0,%C%F",                        0xFFFF703F, 0x2E2F7001, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "norm%.f 0,%u%F",                        0xFFFF703F, 0x2E6F7001, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "norm%.f%Q %#,%L%F",                     0xF8FF0FFF, 0x282F0F81, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "norm%.f%Q 0,%L%F",                      0xFFFF7FFF, 0x2E2F7F81, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*SWAP */
{ (unsigned char *) "swap%.f %#,%C%F",                       0xF8FF003F, 0x282F0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "swap%.f %#,%u%F",                       0xF8FF003F, 0x286F0000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "swap%.f%Q %#,%L%F",                     0xF8FF0FFF, 0x282F0F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "swap%.f 0,%C%F",                        0xFFFF703F, 0x2E2F7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "swap%.f 0,%u%F",                        0xFFFF703F, 0x2E6F7000, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "swap%.f%Q 0,%L%F",                      0xFFFF7FFF, 0x2E2F7F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*SWAPE */
{ (unsigned char *) "swape%.f %#,%C%F",                      0xF8FF003F, 0x282F0009, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "swape%.f %#,%u%F",                      0xF8FF003F, 0x286F0009, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "swape%.f%Q %#,%L%F",                    0xF8FF0FFF, 0x282F0F89, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "swape%.f 0,%C%F",                       0xFFFF703F, 0x2E2F7009, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "swape%.f 0,%u%F",                       0xFFFF703F, 0x2E6F7009, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "swape%.f%Q 0,%L%F",                     0xFFFF7FFF, 0x2E2F7F89, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*RTIE */
/* rtie                         0010 0100 0110 1111 0000 0000 0011 1111  */
{ (unsigned char *) "rtie",                                 0xFFFFFFFF, 0x246F003F, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*SLEEP */
{ (unsigned char *) "sleep %C",                              0xFFFFF03F, 0x212F003F, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sleep %u",                              0xFFFFF03F, 0x216F003F, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sleep%Q %L",                            0xFFFFFFFF, 0x212F0FBF, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "sleep",                                 0xFFFFFFFF, 0x216F003F, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*SCOND */
/* scond<.di>    b,[c]  	0010 0bbb 0010 1111 DBBB CCCC CC01 0001  */
{ (unsigned char *) "scond%.V %B,[%C]",                      0xF8FF003F, 0x202F0011, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* scond<.di>    b,[u6] 	0010 0bbb 0110 1111 DBBB uuuu uu01 0001  */
{ (unsigned char *) "scond%.V %B,[%u]",                      0xF8FF003F, 0x206F0011, ARC_MACH_ARCV2, 0, 0, 0, 0},
/* scond<.di>    b,[limm] 	0010 0bbb 0010 1111 DBBB 1111 1001 0001  */
{ (unsigned char *) "scond%.V%Q %B,[%L]",                    0xF8FF0FFF, 0x202F0F91, ARC_MACH_ARCV2, 0, 0, 0, 0},


/*BIC*/
{ (unsigned char *) "bic%.f%Q %A,%L,%L%F",                   0xFFFF7FC0, 0x26067F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*MAX/MIN*/
{ (unsigned char *) "max%.f%Q 0,%L,%L%F",                    0xFFFF7FFF, 0x26087FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "max%.q%.f%Q 0,%L,%L%F",                 0xFFFF7FE0, 0x26C87F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "min%.f%Q 0,%L,%L%F",                    0xFFFF7FFF, 0x26097FBE, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "min%.q%.f%Q 0,%L,%L%F",                 0xFFFF7FE0, 0x26C97F80, ARC_MACH_ARCV2, 0, 0, 0, 0},
/*SUB1/SUB3*/
{ (unsigned char *) "sub1%.f%Q %A,%L,%L%F",                  0xFFFF7FC0, 0x26177F80, ARC_MACH_ARCV2, 0, 0, 0, 0},

/*LLOCK */
{ (unsigned char *) "llock%.V %B,[%C]",                        0xF8FF003F, 0x202F0010, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "llock%.V%Q %B,[%L]",                      0xF8FF0FFF, 0x202F0F90, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "llock%.V 0,[%C]",                         0xFFFF703F, 0x262F7010, ARC_MACH_ARCV2, 0, 0, 0, 0},
{ (unsigned char *) "llock%.V%Q 0,[%L]",                       0xFFFF7FFF, 0x262F7F90, ARC_MACH_ARCV2, 0, 0, 0, 0},

/*XBFU */
{ (unsigned char *) "xbfu%.f %A,%B,%C%F",                    0xF8FF0000, 0x202D0000, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f %A,%B,%u%F",                    0xF8FF0000, 0x206D0000, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f %#,%B,%K%F",                    0xF8FF0000, 0x20AD0000, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f 0,%B,%C%F",                     0xF8FF003F, 0x202D003E, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f 0,%B,%u%F",                     0xF8FF003F, 0x206D003E, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f%Q %A,%L,%C%F",                  0xFFFF7000, 0x262D7000, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f%Q %A,%L,%u%F",                  0xFFFF7000, 0x266D7000, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f%Q %A,%B,%L%F",                  0xF8FF0FC0, 0x202D0F80, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f%Q %A,%L,%L%F",                  0xFFFF7FC0, 0x262D7F80, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f%Q 0,%L,%C%F",                   0xFFFF703F, 0x262D703E, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f%Q 0,%L,%u%F",                   0xFFFF703F, 0x266D703E, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f%Q 0,%L,%K%F",                   0xFFFF7000, 0x26AD7000, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f%Q 0,%B,%L%F",                   0xF8FF0FFF, 0x202D0FBE, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.f%Q 0,%L,%L%F",                   0xFFFF7FFF, 0x262D7FBE, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.q%.f %#,%B,%C%F",                 0xF8FF0020, 0x20ED0000, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.q%.f %#,%B,%u%F",                 0xF8FF0020, 0x20ED0020, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.q%.f%Q %#,%B,%L%F",               0xF8FF0FE0, 0x20ED0F80, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.q%.f%Q 0,%L,%C%F",                0xFFFF7020, 0x26ED7000, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.q%.f%Q 0,%L,%u%F",                0xFFFF7020, 0x26ED7020, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
{ (unsigned char *) "xbfu%.q%.f%Q 0,%L,%L%F",                0xFFFF7FE0, 0x26ED7F80, ARC_MACH_ARCV2HS, 0, 0, 0, 0},
