/* Helper opcode table for the ARC.
   Copyright (C) 1994-2023 Free Software Foundation, Inc.

   Contributed by Claudiu Zissulescu (claziss@synopsys.com)

   This file is part of libopcodes.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.  */

#include "sysdep.h"
#include <stdio.h>
#include "bfd.h"
#include "opcode/arc.h"
#include "opintl.h"
#include "libiberty.h"

/* Include the generic extract/insert functions.  Order is important
   as some of the functions present in the .h may be disabled via
   defines.  */
#include "arc-fxi.h"

/* The flag operands enum. */
#define FLAG(NAME, NAMESTR, CODE, BITS, SHIFT, FAVAIL) \
		F_##NAME,
enum arc_flag_operand_enum {
	F_INVALID = -1,
	F_NULL = 0,
#include "arc-flag.def"
	F_SIZE,
};
#undef FLAG

/* The flag operands name. */
#define FLAG(NAME, NAMESTR, CODE, BITS, SHIFT, FAVAIL) \
		"F_" #NAME,
const char *flag_operand_name[F_SIZE] = {
	"F_NULL",
#include "arc-flag.def"
};
#undef FLAG

/* The flag operands table.

   The format of the table is
   NAME CODE BITS SHIFT FAVAIL.  */
#define FLAG(NAME, NAMESTR, CODE, BITS, SHIFT, FAVAIL) \
  [F_##NAME] = { NAMESTR, CODE, BITS, SHIFT, FAVAIL },
const struct arc_flag_operand arc_flag_operands[F_SIZE] =
{
  [F_NULL] = { 0, 0, 0, 0, 0 },
  #include "arc-flag.def"
};
#undef FLAG

const unsigned arc_num_flag_operands = ARRAY_SIZE (arc_flag_operands);

/* Enum of the flag classes. */
#define FLAG_CLASS(NAME, CLASS, INSERT_FN, EXTRACT_FN, ...) \
	  C_##NAME,
enum arc_flag_class_enum {
  C_INVALID = -1,
  #include "arc-flag-classes.def"
  C_SIZE
};
#undef FLAG_CLASS

/* Table of the flag classes.

   The format of the table is
   CLASS {FLAG_CODE}.  */
#define FLAG_CLASS(NAME, CLASS, INSERT_FN, EXTRACT_FN, ...) \
  [C_##NAME] = { \
    .flag_class = CLASS, \
    .insert = INSERT_FN, \
    .extract = EXTRACT_FN, \
    .flags = { __VA_ARGS__, F_NULL } \
  },
const struct arc_flag_class arc_flag_classes[C_SIZE] =
{
  #include "arc-flag-classes.def"
};
#undef FLAG_CLASS

const unsigned char flags_none[] = { 0 };
const unsigned char flags_f[]    = { C_F };
const unsigned char flags_cc[]   = { C_CC };
const unsigned char flags_ccf[]  = { C_CC, C_F };

/* The operands enum. */
#define ARC_OPERAND(NAME, BITS, SHIFT, RELO, FLAGS, INSERT_FN, EXTRACT_FN) \
  NAME,
enum arc_operand_enum {
  ARC_OPERAND_INVALID = -1,
  UNUSED = 0,
#include "arc-operands.def"
  ARC_OPERAND_SIZE
};
#undef ARC_OPERAND

/* The operands name. */
#define ARC_OPERAND(NAME, BITS, SHIFT, RELO, FLAGS, INSERT_FN, EXTRACT_FN) \
  #NAME,
const char *arc_operand_name[ARC_OPERAND_SIZE] = {
  "UNUSED",
#include "arc-operands.def"
};
#undef ARC_OPERAND
/* The operands table.

   The format of the operands table is:

   BITS SHIFT DEFAULT_RELOC FLAGS INSERT_FUN EXTRACT_FUN.  */
#define ARC_OPERAND(NAME, BITS, SHIFT, RELOC, FLAGS, INSERT_FN, EXTRACT_FN) \
    [NAME] = { \
      .bits = BITS, \
      .shift = SHIFT, \
      .default_reloc = RELOC, \
      .flags = FLAGS, \
      .insert = INSERT_FN, \
      .extract = EXTRACT_FN \
    },
const struct arc_operand arc_operands[ARC_OPERAND_SIZE] =
{
  /* The fields are bits, shift, insert, extract, flags.  The zero
     index is used to indicate end-of-list.  */
  [UNUSED] = { 0, 0, 0, 0, 0, 0 },
#include "arc-operands.def"
};
#undef ARC_OPERAND

const unsigned arc_num_operands = ARRAY_SIZE (arc_operands);

const unsigned arc_Toperand = FKT_T;
const unsigned arc_NToperand = FKT_NT;

const unsigned char arg_none[]		 = { 0 };
const unsigned char arg_32bit_rarbrc[]	 = { RA, RB, RC };
const unsigned char arg_32bit_zarbrc[]	 = { ZA, RB, RC };
const unsigned char arg_32bit_rbrbrc[]	 = { RB, RBdup, RC };
const unsigned char arg_32bit_rarbu6[]	 = { RA, RB, UIMM6_20 };
const unsigned char arg_32bit_zarbu6[]	 = { ZA, RB, UIMM6_20 };
const unsigned char arg_32bit_rbrbu6[]	 = { RB, RBdup, UIMM6_20 };
const unsigned char arg_32bit_rbrbs12[]	 = { RB, RBdup, SIMM12_20 };
const unsigned char arg_32bit_ralimmrc[] = { RA, LIMM, RC };
const unsigned char arg_32bit_rarblimm[] = { RA, RB, LIMM };
const unsigned char arg_32bit_zalimmrc[] = { ZA, LIMM, RC };
const unsigned char arg_32bit_zarblimm[] = { ZA, RB, LIMM };

const unsigned char arg_32bit_rbrblimm[] = { RB, RBdup, LIMM };
const unsigned char arg_32bit_ralimmu6[] = { RA, LIMM, UIMM6_20 };
const unsigned char arg_32bit_zalimmu6[] = { ZA, LIMM, UIMM6_20 };

const unsigned char arg_32bit_zalimms12[]  = { ZA, LIMM, SIMM12_20 };
const unsigned char arg_32bit_ralimmlimm[] = { RA, LIMM, LIMMdup };
const unsigned char arg_32bit_zalimmlimm[] = { ZA, LIMM, LIMMdup };

const unsigned char arg_32bit_rbrc[]   = { RB, RC };
const unsigned char arg_32bit_zarc[]   = { ZA, RC };
const unsigned char arg_32bit_rbu6[]   = { RB, UIMM6_20 };
const unsigned char arg_32bit_zau6[]   = { ZA, UIMM6_20 };
const unsigned char arg_32bit_rblimm[] = { RB, LIMM };
const unsigned char arg_32bit_zalimm[] = { ZA, LIMM };

const unsigned char arg_32bit_limmrc[]   = { LIMM, RC };
const unsigned char arg_32bit_limmu6[]   = { LIMM, UIMM6_20 };
const unsigned char arg_32bit_limms12[]  = { LIMM, SIMM12_20 };
const unsigned char arg_32bit_limmlimm[] = { LIMM, LIMMdup };

const unsigned char arg_32bit_rc[]   = { RC };
const unsigned char arg_32bit_u6[]   = { UIMM6_20 };
const unsigned char arg_32bit_limm[] = { LIMM };

/* List with special cases instructions and the applicable flags.  */
const struct arc_flag_special arc_flag_special_cases[] =
{
  { "b", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	  F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	  F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	  F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ, F_NJ, F_NM,
	  F_NO_T, F_NULL } },
  { "bl", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	   F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	   F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	   F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ,
	   F_NULL } },
  { "br", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	   F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	   F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	   F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ,
	   F_NULL } },
  { "j", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	  F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	  F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	  F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ,
	  F_NULL } },
  { "jl", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	   F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	   F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	   F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ,
	   F_NULL } },
  { "lp", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	   F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	   F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	   F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ,
	   F_NULL } },
  { "set", { F_ALWAYS, F_RA, F_EQUAL, F_ZERO, F_NOTEQUAL, F_NOTZERO, F_POZITIVE,
	    F_PL, F_NEGATIVE, F_MINUS, F_CARRY, F_CARRYSET, F_LOWER, F_CARRYCLR,
	    F_NOTCARRY, F_HIGHER, F_OVERFLOWSET, F_OVERFLOW, F_NOTOVERFLOW,
	    F_OVERFLOWCLR, F_GT, F_GE, F_LT, F_LE, F_HI, F_LS, F_PNZ,
	    F_NULL } },
  { "ld", { F_SIZEB17, F_SIZEW17, F_H17, F_NULL } },
  { "st", { F_SIZEB1, F_SIZEW1, F_H1, F_NULL } }
};

const unsigned arc_num_flag_special = ARRAY_SIZE (arc_flag_special_cases);

/* Relocations.  */
const struct arc_reloc_equiv_tab arc_reloc_equiv[] =
{
  { "sda", "ld", { F_ASFAKE, F_H1, F_NULL },
    BFD_RELOC_ARC_SDA_LDST, BFD_RELOC_ARC_SDA_LDST1 },
  { "sda", "st", { F_ASFAKE, F_H1, F_NULL },
    BFD_RELOC_ARC_SDA_LDST, BFD_RELOC_ARC_SDA_LDST1 },
  { "sda", "ld", { F_ASFAKE, F_SIZEW7, F_NULL },
    BFD_RELOC_ARC_SDA_LDST, BFD_RELOC_ARC_SDA_LDST1 },
  { "sda", "st", { F_ASFAKE, F_SIZEW7, F_NULL },
    BFD_RELOC_ARC_SDA_LDST, BFD_RELOC_ARC_SDA_LDST1 },

  /* Next two entries will cover the undefined behavior ldb/stb with
     address scaling.  */
  { "sda", "ld", { F_ASFAKE, F_SIZEB7, F_NULL },
    BFD_RELOC_ARC_SDA_LDST, BFD_RELOC_ARC_SDA_LDST },
  { "sda", "st", { F_ASFAKE, F_SIZEB7, F_NULL },
    BFD_RELOC_ARC_SDA_LDST, BFD_RELOC_ARC_SDA_LDST},

  { "sda", "ld", { F_ASFAKE, F_NULL },
    BFD_RELOC_ARC_SDA_LDST, BFD_RELOC_ARC_SDA_LDST2 },
  { "sda", "st", { F_ASFAKE, F_NULL },
    BFD_RELOC_ARC_SDA_LDST, BFD_RELOC_ARC_SDA_LDST2},
  { "sda", "ldd", { F_ASFAKE, F_NULL },
    BFD_RELOC_ARC_SDA_LDST, BFD_RELOC_ARC_SDA_LDST2 },
  { "sda", "std", { F_ASFAKE, F_NULL },
    BFD_RELOC_ARC_SDA_LDST, BFD_RELOC_ARC_SDA_LDST2},

  /* Short instructions.  */
  { "sda", 0, { F_NULL }, BFD_RELOC_ARC_SDA16_LD, BFD_RELOC_ARC_SDA16_LD },
  { "sda", 0, { F_NULL }, -SIMM10_A16_7_Sbis, BFD_RELOC_ARC_SDA16_LD1 },
  { "sda", 0, { F_NULL }, BFD_RELOC_ARC_SDA16_LD2, BFD_RELOC_ARC_SDA16_LD2 },
  { "sda", 0, { F_NULL }, BFD_RELOC_ARC_SDA16_ST2, BFD_RELOC_ARC_SDA16_ST2 },

  { "sda", 0, { F_NULL }, BFD_RELOC_ARC_32_ME, BFD_RELOC_ARC_SDA32_ME },
  { "sda", 0, { F_NULL }, BFD_RELOC_ARC_SDA_LDST, BFD_RELOC_ARC_SDA_LDST },

  { "plt", 0, { F_NULL }, BFD_RELOC_ARC_S25H_PCREL,
    BFD_RELOC_ARC_S25H_PCREL_PLT },
  { "plt", 0, { F_NULL }, BFD_RELOC_ARC_S21H_PCREL,
    BFD_RELOC_ARC_S21H_PCREL_PLT },
  { "plt", 0, { F_NULL }, BFD_RELOC_ARC_S25W_PCREL,
    BFD_RELOC_ARC_S25W_PCREL_PLT },
  { "plt", 0, { F_NULL }, BFD_RELOC_ARC_S21W_PCREL,
    BFD_RELOC_ARC_S21W_PCREL_PLT },

  { "plt", 0, { F_NULL }, BFD_RELOC_ARC_32_ME, BFD_RELOC_ARC_PLT32 }
};

const unsigned arc_num_equiv_tab = ARRAY_SIZE (arc_reloc_equiv);

const struct arc_pseudo_insn arc_pseudo_insns[] =
{
  { "push", "st", ".aw", 5, { { RC, 0, 0, 0 }, { BRAKET, 1, 0, 1 },
			      { RB, 1, 28, 2 }, { SIMM9_8, 1, -4, 3 },
			      { BRAKETdup, 1, 0, 4} } },
  { "pop", "ld", ".ab", 5, { { RA, 0, 0, 0 }, { BRAKET, 1, 0, 1 },
			     { RB, 1, 28, 2 }, { SIMM9_8, 1, 4, 3 },
			     { BRAKETdup, 1, 0, 4} } },

  { "brgt", "brlt", NULL, 3, { { RB, 0, 0, 1 }, { RC, 0, 0, 0 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brgt", "brge", NULL, 3, { { RB, 0, 0, 0 }, { UIMM6_8, 0, 1, 1 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brgt", "brlt", NULL, 3, { { RB, 0, 0, 1 }, { LIMM, 0, 0, 0 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brgt", "brlt", NULL, 3, { { LIMM, 0, 0, 1 }, { RC, 0, 0, 0 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brgt", "brge", NULL, 3, { { LIMM, 0, 0, 0 }, { UIMM6_8, 0, 1, 1 },
			       { SIMM9_A16_8, 0, 0, 2 } } },

  { "brhi", "brlo", NULL, 3, { { RB, 0, 0, 1 }, { RC, 0, 0, 0 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brhi", "brhs", NULL, 3, { { RB, 0, 0, 0 }, { UIMM6_8, 0, 1, 1 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brhi", "brlo", NULL, 3, { { RB, 0, 0, 1 }, { LIMM, 0, 0, 0 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brhi", "brlo", NULL, 3, { { LIMM, 0, 0, 1 }, { RC, 0, 0, 0 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brhi", "brhs", NULL, 3, { { LIMM, 0, 0, 0 }, { UIMM6_8, 0, 1, 1 },
			       { SIMM9_A16_8, 0, 0, 2 } } },

  { "brle", "brge", NULL, 3, { { RB, 0, 0, 1 }, { RC, 0, 0, 0 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brle", "brlt", NULL, 3, { { RB, 0, 0, 0 }, { UIMM6_8, 0, 1, 1 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brle", "brge", NULL, 3, { { RB, 0, 0, 1 }, { LIMM, 0, 0, 0 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brle", "brge", NULL, 3, { { LIMM, 0, 0, 1 }, { RC, 0, 0, 0 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brle", "brlt", NULL, 3, { { LIMM, 0, 0, 0 }, { UIMM6_8, 0, 1, 1 },
			       { SIMM9_A16_8, 0, 0, 2 } } },

  { "brls", "brhs", NULL, 3, { { RB, 0, 0, 1 }, { RC, 0, 0, 0 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brls", "brlo", NULL, 3, { { RB, 0, 0, 0 }, { UIMM6_8, 0, 1, 1 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brls", "brhs", NULL, 3, { { RB, 0, 0, 1 }, { LIMM, 0, 0, 0 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brls", "brhs", NULL, 3, { { LIMM, 0, 0, 1 }, { RC, 0, 0, 0 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
  { "brls", "brlo", NULL, 3, { { LIMM, 0, 0, 0 }, { UIMM6_8, 0, 1, 1 },
			       { SIMM9_A16_8, 0, 0, 2 } } },
};

const unsigned arc_num_pseudo_insn =
  sizeof (arc_pseudo_insns) / sizeof (*arc_pseudo_insns);

/* ARC64 pseudo instructions.  */
const struct arc_pseudo_insn arc64_pseudo_insns[] =
{
  { "pushl", "stl", ".aw", 5, { { RC, 0, 0, 0 }, { BRAKET, 1, 0, 1 },
				{ RB, 1, 28, 2 }, { SIMM9_8, 1, -8, 3 },
				{ BRAKETdup, 1, 0, 4} } },
  { "popl", "ldl", ".ab", 5, { { RA, 0, 0, 0 }, { BRAKET, 1, 0, 1 },
			       { RB, 1, 28, 2 }, { SIMM9_8, 1, 8, 3 },
			       { BRAKETdup, 1, 0, 4} } },
};

const unsigned arc64_num_pseudo_insn =
  sizeof (arc64_pseudo_insns) / sizeof (*arc64_pseudo_insns);

const struct arc_aux_reg arc_aux_regs[] =
{
#undef DEF
#define DEF(ADDR, CPU, SUBCLASS, NAME)		\
  { ADDR, CPU, SUBCLASS, #NAME, sizeof (#NAME)-1 },

#include "arc-regs.h"

#undef DEF
};

const unsigned arc_num_aux_regs = ARRAY_SIZE (arc_aux_regs);

/* NOTE: The order of this array MUST be consistent with 'enum
   arc_rlx_types' located in tc-arc.h!  */
const struct arc_opcode arc_relax_opcodes[] =
{
  { NULL, 0x0, 0x0, 0x0, ARITH, NONE, { UNUSED }, { 0 } },

  /* bl_s s13 11111sssssssssss.  */
  { "bl_s", 0x0000F800, 0x0000F800, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, BRANCH, NONE,
    { SIMM13_A32_5_S }, { 0 }},

  /* bl<.d> s25 00001sssssssss10SSSSSSSSSSNRtttt.  */
  { "bl", 0x08020000, 0xF8030000, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, BRANCH, NONE,
    { SIMM25_A32_5 }, { C_D }},

  /* b_s s10 1111000sssssssss.  */
  { "b_s", 0x0000F000, 0x0000FE00, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, BRANCH, NONE,
    { SIMM10_A16_7_S }, { 0 }},

  /* b<.d> s25 00000ssssssssss1SSSSSSSSSSNRtttt.  */
  { "b", 0x00010000, 0xF8010000, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, BRANCH, NONE,
    { SIMM25_A16_5 }, { C_D }},

  /* add_s c,b,u3 01101bbbccc00uuu.  */
  { "add_s", 0x00006800, 0x0000F818, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, ARITH, NONE,
    { RC_S, RB_S, UIMM3_13R_S }, { 0 }},

  /* add<.f> a,b,u6 00100bbb01000000FBBBuuuuuuAAAAAA.  */
  { "add", 0x20400000, 0xF8FF0000, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, ARITH, NONE,
    { RA, RB, UIMM6_20R }, { C_F }},

  /* add<.f> a,b,limm 00100bbb00000000FBBB111110AAAAAA.  */
  { "add", 0x20000F80, 0xF8FF0FC0, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, ARITH, NONE,
    { RA, RB, LIMM }, { C_F }},

  /* ld_s c,b,u7 10000bbbcccuuuuu.  */
  { "ld_s", 0x00008000, 0x0000F800, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, MEMORY, NONE,
    { RC_S, BRAKET, RB_S, UIMM7_A32_11R_S, BRAKETdup }, { 0 }},

  /* ld<.di><.aa><.x><zz> a,b,s9
     00010bbbssssssssSBBBDaaZZXAAAAAA.  */
  { "ld", 0x10000000, 0xF8000000, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, MEMORY, NONE,
    { RA, BRAKET, RB, SIMM9_8R, BRAKETdup },
    { C_ZZ23, C_DI20, C_AA21, C_X25 }},

  /* ld<.di><.aa><.x><zz> a,b,limm 00100bbbaa110ZZXDBBB111110AAAAAA.  */
  { "ld", 0x20300F80, 0xF8380FC0, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, MEMORY, NONE,
    { RA, BRAKET, RB, LIMM, BRAKETdup },
    { C_ZZ13, C_DI16, C_AA8, C_X15 }},

  /* mov_s b,u8 11011bbbuuuuuuuu.  */
  { "mov_s", 0x0000D800, 0x0000F800, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, MEMORY, NONE,
    { RB_S, UIMM8_8R_S }, { 0 }},

  /* mov<.f> b,s12 00100bbb10001010FBBBssssssSSSSSS.  */
  { "mov", 0x208A0000, 0xF8FF0000, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, MEMORY, NONE,
    { RB, SIMM12_20R }, { C_F }},

  /* mov<.f> b,limm 00100bbb00001010FBBB111110RRRRRR.  */
  { "mov", 0x200A0F80, 0xF8FF0FC0, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, MEMORY, NONE,
    { RB, LIMM }, { C_F }},

  /* sub_s c,b,u3 01101bbbccc01uuu.  */
  { "sub_s", 0x00006808, 0x0000F818, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, ARITH, NONE,
    { RC_S, RB_S, UIMM3_13R_S }, { 0 }},

  /* sub<.f> a,b,u6 00100bbb01000010FBBBuuuuuuAAAAAA.  */
  { "sub", 0x20420000, 0xF8FF0000, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, ARITH, NONE,
    { RA, RB, UIMM6_20R }, { C_F }},

  /* sub<.f> a,b,limm 00100bbb00000010FBBB111110AAAAAA.  */
  { "sub", 0x20020F80, 0xF8FF0FC0, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, ARITH, NONE,
    { RA, RB, LIMM }, { C_F }},

  /* mpy<.f> a,b,u6 00100bbb01011010FBBBuuuuuuAAAAAA.  */
  { "mpy", 0x205A0000, 0xF8FF0000, ARC_OPCODE_ARC700 | ARC_OPCODE_ARCv2EM
    | ARC_OPCODE_ARCv2HS, ARITH, MPY6E, { RA, RB, UIMM6_20R }, { C_F }},

  /* mpy<.f> a,b,limm 00100bbb00011010FBBB111110AAAAAA.  */
  { "mpy", 0x201A0F80, 0xF8FF0FC0, ARC_OPCODE_ARC700 | ARC_OPCODE_ARCv2EM
    | ARC_OPCODE_ARCv2HS, ARITH, MPY6E, { RA, RB, LIMM }, { C_F }},

  /* mov<.f><.cc> b,u6 00100bbb11001010FBBBuuuuuu1QQQQQ.  */
  { "mov", 0x20CA0020, 0xF8FF0020, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, MEMORY, NONE,
    { RB, UIMM6_20R }, { C_F, C_CC }},

  /* mov<.f><.cc> b,limm 00100bbb11001010FBBB1111100QQQQQ.  */
  { "mov", 0x20CA0F80, 0xF8FF0FE0, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, MEMORY, NONE,
    { RB, LIMM }, { C_F, C_CC }},

  /* add<.f><.cc> b,b,u6 00100bbb11000000FBBBuuuuuu1QQQQQ.  */
  { "add", 0x20C00020, 0xF8FF0020, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, ARITH, NONE,
    { RB, RBdup, UIMM6_20R }, { C_F, C_CC }},

  /* add<.f><.cc> b,b,limm 00100bbb11000000FBBB1111100QQQQQ.  */
  { "add", 0x20C00F80, 0xF8FF0FE0, ARC_OPCODE_ARC600 | ARC_OPCODE_ARC700
    | ARC_OPCODE_ARCv2EM | ARC_OPCODE_ARCv2HS, ARITH, NONE,
    { RB, RBdup, LIMM }, { C_F, C_CC }}
};

const unsigned arc_num_relax_opcodes = ARRAY_SIZE (arc_relax_opcodes);

/* Return length of an opcode in bytes.  */

int
arc_opcode_len (const struct arc_opcode *opcode)
{
  if (opcode->mask < 0x10000ull)
    return 2;

  if (opcode->mask < 0x100000000ull)
    return 4;

  if (opcode->mask < 0x1000000000000ull)
    return 6;

  return 8;
}
