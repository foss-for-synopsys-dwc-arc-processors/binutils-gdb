/* ARC instruction defintions.
   Copyright (C) 2021 Free Software Foundation, Inc.

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

/* Flags.  */
#define FL_NONE { 0 }
#define FL_CC   { C_FPCC }

/* Arguments.  */
#define ARG_NONE       { 0 }
#define ARG_64FP_3OP   { FA, FB, FC, FD }
#define ARG_128FP_3OP  { FDA, FDB, FDC, FDD }
#define ARG_64FP_2OP   { FA, FB, FC }
#define ARG_64FP_CMP   { FB, FC }
#define ARG_128FP_2OP  { FDA, FDB, FDC }
#define ARG_64FP_1OP   { FA, FC }
#define ARG_64FP_SOP   { FA, FB }
#define ARG_128FP_SOP  { FDA, FDB }

#define ARG_64FP_CVI2F { FA, FRB }
#define ARG_64FP_CVF2I { FRD, FC }

/* Macros to help generating floating point pattern instructions.  */
/* Define FP_TOP */
#define FIELDS1(word) (word & 0x1F)
#define FIELDS2(word) (((word & 0x07) << 24) | (((word >> 3) & 0x03) << 12))
#define FIELDS3(word) ((word & 0x1F) << 19)
#define FIELDD(word)  ((word & 0x1F) << 6)
#define FIELDTOP(word) (((word & 0x01) << 5) | ((word >> 1) & 0x07) << 16)
#define FIELDP(word)  ((word & 0x03) << 14)
#define MASK_32BIT(VAL) (0xffffffff & (VAL))

#define INSNFP3OP(TOPF, P)					\
  ((0x1C << 27) | FIELDTOP (TOPF) | FIELDP (P) | (1 << 11))
#define MINSNFP3OP							\
  (MASK_32BIT (~(FIELDS1 (31) | FIELDS2 (31) | FIELDS3 (31) | FIELDD (31))))

/* Define FP_DOP */
#define FIELDDOP(ops) ((ops & 0x1f) << 16)

#define INSNFP2OP(DOPF, P)					\
  ((0x1C << 27) | FIELDDOP (DOPF) | FIELDP (P) | (1 << 5))
#define MINSNFP2OP						\
  (MASK_32BIT (~(FIELDS2 (31) | FIELDS1 (31) | FIELDD (31))))

/* Define FP_CVF2F */
/* 0x1c | fs2[2:0] | 0 1 1 0 - - | cvtf[1:0] | - - | fs2[4:3] | 0 | fd | 1 | u4 u3 1 0 u0 */
#define FIELDCVTF(WORD) ((WORD & 0x03) << 16)
#define FIELDU0(BIT) (BIT & 0x01)
#define FIELDU1(BIT) (BIT & 0x02)
#define FIELDU3(BIT) (BIT & 0x08)
#define FIELDU4(BIT) (BIT & 0x10)

#define FP_CVF2F_MACHINE(CVTF, BIT)					\
  ((0x1C << 27) | (0x03 << 21) | FIELDCVTF (CVTF)			\
   | (1 << 5) | (1 << 2) |  FIELDU0(BIT) | FIELDU3(BIT) | FIELDU4(BIT))
#define MFP_CVF2F (MASK_32BIT (~(FIELDS2 (31) | FIELDD (31))))

/* Define FP_RND */
#define FP_RND_MACHINE(CVTF, BIT)					\
((0x1C << 27) | (0x03 << 21) | FIELDCVTF (CVTF) | (1 << 5) | (0x03 << 1) \
 | FIELDU3(BIT))
#define MFP_RND (MASK_32BIT (~(FIELDS2 (31) | FIELDD (31))))

/* Define FP_CVF2I */
#define FP_CVF2I_MACHINE(CVTF, BIT) ((0x1C << 27) | (0x03 << 21) | FIELDCVTF (CVTF) \
			     | (1 << 5) | 1 | FIELDU3(BIT) | FIELDU1(BIT))
#define MFP_CVF2I (MASK_32BIT (~(FIELDS2 (31) | FIELDD (31))))

/* Define FMVVF2I */
#define FM_VVF2I(CVTF, BIT) ((0x1C << 27) | (0x03 << 21) | FIELDCVTF (CVTF) \
			     | (1 << 5) | 1 << 4 | 1)
#define MFM_VVF2I (MASK_32BIT (~(FIELDS2 (31) | FIELDD (31))))

/* Define FP_SOP */
#define FP_SOP_MACHINE(SOPF, P)						\
  ((0x1C << 27) | (0x02 << 21) | FIELDCVTF (SOPF) | FIELDP (P) | (1 << 5))
#define MFP_SOP_MACHINE (MASK_32BIT (~(FIELDS1 (31) | FIELDD (31))))

/* Define FP_COP */
#define FP_COP_MACHINE(COPF, P)						\
  ((0x1C << 27) | (0x09 << 19) | FIELDCVTF (COPF) | FIELDP (P) | (1 << 5))
#define MFP_COP_MACHINE \
  (MASK_32BIT (~(FIELDS1 (31) | FIELDD (31) | FIELDS2(31))))

/* Define FP_ZOP */
#define INSNFPZOP(COPF)						\
  ((0x1C << 27) | (0x07 << 20) | FIELDCVTF (COPF) | (1 << 5))

/* Define FP_VMVI */
#define INSNFPVMVI(WMVF, P)						\
  ((0x1C << 27) | (0x05 << 20) | FIELDCVTF (WMVF) | FIELDP (P) | (1 << 5))
#define MINSNFPCOP (MASK_32BIT (~(FIELDS1 (31) | FIELDD (31) | FIELDS2(31))))

/* Define FP_VMVR */
#define INSNFPVMVR(VMVF, P) \
  ((0x1C << 27) | (0x01 << 23) | FIELDCVTF (WMVF) | FIELDP (P) | (1 << 5))
#define MINSNFPVMVR (MASK_32BIT (~(FIELDS1 (31) | FIELDD (31) | FIELDS2(31))))

/* Define FP_CVI2F */
#define INSNFPCVI2F(CVTF, BIT) ((0x1C << 27) | (0x07 << 21) | FIELDCVTF (CVTF) \
				| (1 << 5) | FIELDU3(BIT) | FIELDU1(BIT))
#define MINSNFPCVI2F (MASK_32BIT (~(FIELDS2 (31) | FIELDD (31))))

/* Define FMVI2F */
#define INSNFMVI2F(CVTF, BIT) ((0x1C << 27) | (0x07 << 21) | FIELDCVTF (CVTF) \
			       | (1 << 5) | (1 << 4))
#define MINSNFMVI2F (MASK_32BIT (~(FIELDS2 (31) | FIELDD (31))))

/* Define FMVF2I */
#define INSNFMVF2I(CVTF, BIT) ((0x1C << 27) | (0x03 << 21) | FIELDCVTF (CVTF) \
			       | (1 << 5) | (1 << 4) | (1))
#define MINSNFMVF2I (MASK_32BIT (~(FIELDS2 (31) | FIELDD (31))))

/* Define FP_LOAD */
#define FP_LOAD_ENCODING(SIZE)  (0x1C << 27 | ((SIZE & 0x03) << 1))
#define MSK_FP_LOAD (MASK_32BIT (~(FIELDB (63) | FIELDD (31) | (0x03 << 3) \
				   | (0x1FF << 15))))

#define FP_LSYM_ENCODING(SIZE)  (0x1C << 27 | ((SIZE & 0x03) << 1) | FIELDB(62))
#define MSK_FP_SYM  (MASK_32BIT (~(FIELDD (31))))

/* Define FP_STORE */
#define FP_STORE_ENCODING(SIZE)  ((0x1C << 27) | ((SIZE & 0x03) << 1) | (1))
#define MSK_FP_STORE (MASK_32BIT (~(FIELDB (63) | FIELDD (31) | (0x03 << 3) \
				   | (0x1FF << 15))))
#define FP_SSYM_ENCODING(SIZE)  (0x1C << 27 | ((SIZE & 0x03) << 1) \
				 | FIELDB(62) | (1))

/* FP Load/Store.  */
#define FP_LOAD(NAME,SIZE)						\
  { #NAME, FP_LOAD_ENCODING(SIZE), MSK_FP_LOAD, ARC_OPCODE_ARC64, LOAD,	\
    NONE, { FA, BRAKET, RB, SIMM9_8, BRAKETdup }, { C_AA27 } },		\
  { #NAME, FP_LSYM_ENCODING(SIZE), MSK_FP_SYM, ARC_OPCODE_ARC64, LOAD,	\
    NONE, { FA, BRAKET, LIMM, BRAKETdup }, FL_NONE },

#define FP_STORE(NAME,SIZE)						\
  { #NAME, FP_STORE_ENCODING(SIZE), MSK_FP_STORE, ARC_OPCODE_ARC64, STORE, \
    NONE, { FA, BRAKET, RB, SIMM9_8, BRAKETdup }, { C_AA27 } },		\
  { #NAME, FP_SSYM_ENCODING(SIZE), MSK_FP_SYM, ARC_OPCODE_ARC64, LOAD,	\
    NONE, { FA, BRAKET, LIMM, BRAKETdup }, FL_NONE },

/* Macros used to generate conversion instructions.  */
#define FMVF2I_INSN(NAME, CPU, CLASS, SCLASS, OPS, BIT, ARG)		\
  { NAME, INSNFMVF2I (OPS, BIT), MINSNFMVF2I, CPU, CLASS,		\
    SCLASS, ARG, FL_NONE },

#define FMVF2I(NAME, OPS, BIT)				    \
  FMVF2I_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, OPS,   \
	       BIT, ARG_64FP_CVF2I)

#define FMVI2F_INSN(NAME, CPU, CLASS, SCLASS, OPS, BIT, ARG)		\
  { NAME, INSNFMVI2F (OPS, BIT), MINSNFMVI2F, CPU, CLASS,		\
    SCLASS, ARG, FL_NONE },

#define FMVI2F(NAME, OPS, BIT)				   \
  FMVI2F_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, OPS,  \
	       BIT, ARG_64FP_CVI2F)

#define FP_RND_INSN(NAME, CPU, CLASS, SCLASS, OPS, BIT, ARG)		\
  { NAME, FP_RND_MACHINE (OPS, BIT), MFP_RND, CPU, CLASS,		\
    SCLASS, ARG, FL_NONE },

#define FP_RND(NAME, OPS, BIT)				   \
  FP_RND_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, OPS,  \
	       BIT, ARG_64FP_1OP)

#define FP_CVF2F_INSN(NAME, CPU, CLASS, SCLASS, OPS, BIT, ARG)		\
  { NAME, FP_CVF2F_MACHINE (OPS, BIT), MFP_CVF2F, CPU, CLASS,		\
    SCLASS, ARG, FL_NONE },

#define FP_CVF2F(NAME, OPS, BIT)				   \
  FP_CVF2F_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, OPS,	   \
		 BIT, ARG_64FP_1OP)

#define FP_CVF2I_INSN(NAME, CPU, CLASS, SCLASS, OPS, BIT, ARG)		\
  { NAME, FP_CVF2I_MACHINE (OPS, BIT), MFP_CVF2I, CPU, CLASS,		\
    SCLASS, ARG, FL_NONE },

#define FP_CVF2I(NAME, OPS, BIT)				   \
  FP_CVF2I_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, OPS,	   \
		 BIT, ARG_64FP_CVF2I)

#define FP_CVI2F_INSN(NAME, CPU, CLASS, SCLASS, OPS, BIT, ARG)		\
  { NAME, INSNFPCVI2F (OPS, BIT), MINSNFPCVI2F, CPU, CLASS,		\
    SCLASS, ARG, FL_NONE },

#define FP_CVI2F(NAME, OPS, BIT)				   \
  FP_CVI2F_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, OPS,	   \
		 BIT, ARG_64FP_CVI2F)

/* Macro to generate 1 operand extension instruction.  */
#define FP_SOP_INSN(NAME, CPU, CLASS, SCLASS, OPS, PRC, ARG)		\
  { NAME, FP_SOP_MACHINE (OPS, PRC), MFP_SOP_MACHINE, CPU, CLASS, SCLASS, \
    ARG, FL_NONE },

#define FP_SOP(NAME, OPS, PRECISION)				   \
  FP_SOP_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, SOPF_ ## OPS, \
	       P_ ## PRECISION, ARG_64FP_SOP)

#define FP_SOP_D(NAME, OPS, PRECISION)				    \
  FP_SOP_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, SOPF_ ## OPS, \
	       P_ ## PRECISION, ARG_128FP_SOP)

/* Macro to generate 2 operand extension instruction.  */
#define FP_DOP_INSN(NAME, CPU, CLASS, SCLASS, OPS, PRC, ARG)	\
  { NAME, INSNFP2OP (OPS, PRC), MINSNFP2OP, CPU, CLASS, SCLASS,	\
    ARG, FL_NONE },

#define FP_DOP(NAME, OPS, PRECISION)				   \
  FP_DOP_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, DOPF_ ## OPS, \
	       P_ ## PRECISION, ARG_64FP_2OP)

#define FP_DOPC_INSN(NAME, CPU, CLASS, SCLASS, OPS, PRC, ARG)		\
  { NAME, INSNFP2OP (OPS, PRC) | FIELDD (0), MINSNFP2OP, CPU,		\
    CLASS, SCLASS, ARG, FL_NONE },

#define FP_DOP_C(NAME, OPS, PRECISION)				   \
  FP_DOPC_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, DOPF_ ## OPS, \
		P_ ## PRECISION, ARG_64FP_CMP)

#define FP_DOP_D(NAME, OPS, PRECISION)				     \
  FP_DOP_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, DOPF_ ## OPS, \
	       P_ ## PRECISION, ARG_128FP_2OP)

/* Macro to generate 3 operand generic instruction.  */
#define FP_TOP_INSN(NAME, CPU, CLASS, SCLASS, TOPF, P, ARG)		\
  { NAME, INSNFP3OP (TOPF, P),  MINSNFP3OP,  CPU, CLASS, SCLASS,	\
    ARG, FL_NONE },

#define FP_TOP(NAME, OPS, PRECISION)					\
  FP_TOP_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, TOPF_ ## OPS,	\
	       P_ ## PRECISION, ARG_64FP_3OP)

#define FP_TOP_D(NAME, OPS, PRECISION)				    \
  FP_TOP_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, TOPF_ ## OPS, \
	       P_ ## PRECISION, ARG_128FP_3OP)

/* Conditional mov instructions.  */
#define FP_COP_INSN(NAME, CPU, CLASS, SCLASS, OPS, PRC, ARG)		\
  { NAME, FP_COP_MACHINE (OPS, PRC), MFP_COP_MACHINE, CPU, CLASS, SCLASS, \
    ARG, FL_CC },

#define FP_COP(NAME, OPS, PRECISION)					\
  FP_COP_INSN (#NAME, ARC_OPCODE_ARC64, FLOAT, NONE, COPF_ ## OPS,	\
	       P_ ## PRECISION, ARG_64FP_SOP)

FP_TOP (fhmadd , FMADD , HALF)
FP_TOP (fhmsub , FMSUB , HALF)
FP_TOP (fhnmadd, FNMADD, HALF)
FP_TOP (fhnmsub, FNMSUB, HALF)

FP_TOP (fsmadd , FMADD , SINGLE)
FP_TOP (fsmsub , FMSUB , SINGLE)
FP_TOP (fsnmadd, FNMADD, SINGLE)
FP_TOP (fsnmsub, FNMSUB, SINGLE)

FP_TOP (fdmadd , FMADD , DOUBLE)
FP_TOP (fdmsub , FMSUB , DOUBLE)
FP_TOP (fdnmadd, FNMADD, DOUBLE)
FP_TOP (fdnmsub, FNMSUB, DOUBLE)


/* Vectors*/
FP_TOP (vfhmadd , VFMADD , HALF)
FP_TOP (vfhmsub , VFMSUB , HALF)
FP_TOP (vfhnmadd, VFNMADD, HALF)
FP_TOP (vfhnmsub, VFNMSUB, HALF)
FP_TOP (vfhmadds , VFMADDS , HALF)
FP_TOP (vfhmsubs , VFMSUBS , HALF)
FP_TOP (vfhnmadds, VFNMADDS, HALF)
FP_TOP (vfhnmsubs, VFNMSUBS, HALF)

FP_TOP (vfsmadd , VFMADD , SINGLE)
FP_TOP (vfsmsub , VFMSUB , SINGLE)
FP_TOP (vfsnmadd, VFNMADD, SINGLE)
FP_TOP (vfsnmsub, VFNMSUB, SINGLE)
FP_TOP (vfsmadds , VFMADDS , SINGLE)
FP_TOP (vfsmsubs , VFMSUBS , SINGLE)
FP_TOP (vfsnmadds, VFNMADDS, SINGLE)
FP_TOP (vfsnmsubs, VFNMSUBS, SINGLE)

FP_TOP_D (vfdmadd , VFMADD , DOUBLE)
FP_TOP_D (vfdmsub , VFMSUB , DOUBLE)
FP_TOP_D (vfdnmadd, VFNMADD, DOUBLE)
FP_TOP_D (vfdnmsub, VFNMSUB, DOUBLE)
FP_TOP_D (vfdmadds , VFMADDS , DOUBLE)
FP_TOP_D (vfdmsubs , VFMSUBS , DOUBLE)
FP_TOP_D (vfdnmadds, VFNMADDS, DOUBLE)
FP_TOP_D (vfdnmsubs, VFNMSUBS, DOUBLE)

/* 2OPS */
FP_DOP (fhadd  , FADD  , HALF)
FP_DOP (fhsub  , FSUB  , HALF)
FP_DOP (fhmul  , FMUL  , HALF)
FP_DOP (fhdiv  , FDIV  , HALF)
FP_DOP (fhmin  , FMIN  , HALF)
FP_DOP (fhmax  , FMAX  , HALF)
FP_DOP (fhsgnj , FSGNJ , HALF)
FP_DOP (fhsgnjn, FSGNJN, HALF)
FP_DOP (fhsgnjx, FSGNJX, HALF)

FP_DOP (fsadd  , FADD  , SINGLE)
FP_DOP (fssub  , FSUB  , SINGLE)
FP_DOP (fsmul  , FMUL  , SINGLE)
FP_DOP (fsdiv  , FDIV  , SINGLE)
FP_DOP (fsmin  , FMIN  , SINGLE)
FP_DOP (fsmax  , FMAX  , SINGLE)
FP_DOP (fssgnj , FSGNJ , SINGLE)
FP_DOP (fssgnjn, FSGNJN, SINGLE)
FP_DOP (fssgnjx, FSGNJX, SINGLE)

FP_DOP (fdadd  , FADD  , DOUBLE)
FP_DOP (fdsub  , FSUB  , DOUBLE)
FP_DOP (fdmul  , FMUL  , DOUBLE)
FP_DOP (fddiv  , FDIV  , DOUBLE)
FP_DOP (fdmin  , FMIN  , DOUBLE)
FP_DOP (fdmax  , FMAX  , DOUBLE)
FP_DOP (fdsgnj , FSGNJ , DOUBLE)
FP_DOP (fdsgnjn, FSGNJN, DOUBLE)
FP_DOP (fdsgnjx, FSGNJX, DOUBLE)

FP_DOP_C (fhcmp , FCMP , HALF)
FP_DOP_C (fhcmpf, FCMPF, HALF)
FP_DOP_C (fscmp , FCMP , SINGLE)
FP_DOP_C (fscmpf, FCMPF, SINGLE)
FP_DOP_C (fdcmp , FCMP , DOUBLE)
FP_DOP_C (fdcmpf, FCMPF, DOUBLE)

/* Vectors */
FP_DOP (vfhadd , VFADD , HALF)
FP_DOP (vfhsub , VFSUB , HALF)
FP_DOP (vfhmul , VFMUL , HALF)
FP_DOP (vfhdiv , VFDIV , HALF)
FP_DOP (vfhadds, VFADDS, HALF)
FP_DOP (vfhsubs, VFSUBS, HALF)
FP_DOP (vfhmuls, VFMULS, HALF)
FP_DOP (vfhdivs, VFDIVS, HALF)

FP_DOP (vfsadd , VFADD , SINGLE)
FP_DOP (vfssub , VFSUB , SINGLE)
FP_DOP (vfsmul , VFMUL , SINGLE)
FP_DOP (vfsdiv , VFDIV , SINGLE)
FP_DOP (vfsadds, VFADDS, SINGLE)
FP_DOP (vfssubs, VFSUBS, SINGLE)
FP_DOP (vfsmuls, VFMULS, SINGLE)
FP_DOP (vfsdivs, VFDIVS, SINGLE)

FP_DOP_D (vfdadd , VFADD , DOUBLE)
FP_DOP_D (vfdsub , VFSUB , DOUBLE)
FP_DOP_D (vfdmul , VFMUL , DOUBLE)
FP_DOP_D (vfddiv , VFDIV , DOUBLE)
FP_DOP_D (vfdadds, VFADDS, DOUBLE)
FP_DOP_D (vfdsubs, VFSUBS, DOUBLE)
FP_DOP_D (vfdmuls, VFMULS, DOUBLE)
FP_DOP_D (vfddivs, VFDIVS, DOUBLE)

FP_SOP (fhsqrt, FSQRT, HALF)
FP_SOP (fssqrt, FSQRT, SINGLE)
FP_SOP (fdsqrt, FSQRT, DOUBLE)
FP_SOP (vfhsqrt, VFSQRT, HALF)
FP_SOP (vfssqrt, VFSQRT, SINGLE)
FP_SOP_D (vfdsqrt, VFSQRT,DOUBLE)

FP_COP (fhmov, FMOV, HALF)
FP_COP (fsmov, FMOV, SINGLE)
FP_COP (fdmov, FMOV, DOUBLE)
FP_COP (vfhmov, VFMOV, HALF)
FP_COP (vfsmov, VFMOV, SINGLE)
FP_COP (vfdmov, VFMOV, DOUBLE)

FP_CVI2F (fuint2s, FUINT2S, 0x00)
FP_CVI2F (fuint2d, FUINT2D, 0x00)
FP_CVI2F (ful2s,   FUL2S,   0x00)
FP_CVI2F (ful2d,   FUL2D,   0x00)

FP_CVF2I (fs2uint, FS2UINT, 0x01)
FP_CVF2I (fs2ul,   FS2UL,   0x01)
FP_CVF2I (fd2uint, FD2UINT, 0x01)
FP_CVF2I (fd2ul,   FD2UL,   0x01)

FP_CVI2F (fint2s, FINT2S, 0x02)
FP_CVI2F (fint2d, FINT2D, 0x02)
FP_CVI2F (fl2s,   FL2S,   0x02)
FP_CVI2F (fl2d,   FL2D,   0x02)

FP_CVF2I (fs2int, FS2INT, 0x03)
FP_CVF2I (fs2l,   FS2L,   0x03)
FP_CVF2I (fd2int, FD2INT, 0x03)
FP_CVF2I (fd2l,   FD2L,   0x03)

FP_CVF2F (fs2d, FS2D, 0x04)
FP_CVF2F (fd2s, FD2S, 0x04)

FP_RND (fsrnd, FSRND, 0x06)
FP_RND (fdrnd, FDRND, 0x06)

FP_CVF2I (fs2uint_rz,  F2UINT_RZ,  0x09)
FP_CVF2I (fs2ul_rz,   FS2UL_RZ,   0x09)
FP_CVF2I (fd2uint_rz, FD2UINT_RZ, 0x09)
FP_CVF2I (fd2ul_rz,   FD2UL_RZ,   0x09)

FP_CVF2I (fs2int_rz,  FSINT_RZ,  0x0B)
FP_CVF2I (fs2l_rz,   FS2L_RZ,   0x0B)
FP_CVF2I (fd2int_rz, FD2INT_RZ, 0x0B)
FP_CVF2I (fd2l_rz,   FD2L_RZ,   0x0B)

FP_RND (fsrnd_rz, FSRND_RZ, 0x0E)
FP_RND (fdrnd_rz, FDRND_RZ, 0x0E)

FMVI2F (fmvi2s, FMVI2S, 0x10)
FMVI2F (fmvl2d, FMVL2D, 0x10)

FMVF2I (fmvs2i, FMVS2I, 0x11)
FMVF2I (fmvd2l, FMVD2L, 0x11)

FP_CVF2F (fs2h, FS2H, 0x14)
FP_CVF2F (fh2s, FH2S, 0x15)
FP_CVF2F (fs2h_rz, FS2H_RZ, 0x1C)

FP_LOAD (fld16, 0x02)
FP_LOAD (fld32, 0x00)
FP_LOAD (fld64, 0x01)
FP_LOAD (fld128, 0x03)

FP_STORE (fst16, 0x02)
FP_STORE (fst32, 0x00)
FP_STORE (fst64, 0x01)
FP_STORE (fst128, 0x03)
