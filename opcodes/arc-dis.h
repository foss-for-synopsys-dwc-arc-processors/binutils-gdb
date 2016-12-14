/* Disassembler structures definitions for the ARC.
   Copyright (C) 1994-2016 Free Software Foundation, Inc.

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

#ifndef ARCDIS_H
#define ARCDIS_H

#ifdef __cplusplus
extern "C" {
#endif

enum ARC_Debugger_OperandType
{
    ARC_UNDEFINED,
    ARC_LIMM,
    ARC_SHIMM,
    ARC_REGISTER,
    ARCOMPACT_REGISTER /* Valid only for the
			  registers allowed in
			  16 bit mode.  */
};

enum Flow
{
  noflow,
  direct_jump,
  direct_call,
  indirect_jump,
  indirect_call,
  invalid_instr
};

enum NullifyMode
{
  BR_exec_when_no_jump,
  BR_exec_always,
  BR_exec_when_jump
};

enum { allOperandsSize = 256 };

struct arcDisState
{
  void *_this;
  int instructionLen;
  void (*err)(void*, const char*);
  const char *(*coreRegName)(void*, int);
  const char *(*auxRegName)(void*, int);
  const char *(*condCodeName)(void*, int);
  const char *(*instName)(void*, int, int, int*);

  unsigned char* instruction;
  unsigned index;
  const char *comm[6]; /* Instr name, cond, NOP, 3 operands.  */

  union
  {
    unsigned int registerNum;
    unsigned int shortimm;
    unsigned int longimm;
  } source_operand;
  enum ARC_Debugger_OperandType sourceType;

  int opWidth;
  int targets[4];
  /* START ARC LOCAL.  */
  unsigned int addresses[4];
  /* END ARC LOCAL.  */
  /* Set as a side-effect of calling the disassembler.
     Used only by the debugger.  */
  enum Flow flow;
  int register_for_indirect_jump;
  int ea_reg1, ea_reg2, _offset;
  int _cond, _opcode;
  unsigned long words[2];
  char *commentBuffer;
  char instrBuffer[40];
  char operandBuffer[allOperandsSize];
  char _ea_present;
  char _addrWriteBack; /* Address writeback.  */
  char _mem_load;
  char _load_len;
  enum NullifyMode nullifyMode;
  unsigned char commNum;
  unsigned char isBranch;
  unsigned char tcnt;
  unsigned char acnt;
};

struct arcDisState
arcAnalyzeInstr (bfd_vma memaddr, struct disassemble_info *);

enum arc_ldst_writeback_mode
  {
    ARC_WRITEBACK_NO = 0,
    ARC_WRITEBACK_AW = 1,
    ARC_WRITEBACK_A = ARC_WRITEBACK_AW,
    ARC_WRITEBACK_AB = 2,
    ARC_WRITEBACK_AS = 3,
  };


enum arc_ldst_data_size
  {
    ARC_SCALING_NONE = 0,
    ARC_SCALING_B = 1,
    ARC_SCALING_H = 2,
    ARC_SCALING_D = 3,
  };


enum arc_condition_code
  {
    ARC_CC_AL = 0x0,
    ARC_CC_RA = ARC_CC_AL,
    ARC_CC_EQ = 0x1,
    ARC_CC_Z = ARC_CC_EQ,
    ARC_CC_NE = 0x2,
    ARC_CC_NZ = ARC_CC_NE,
    ARC_CC_PL = 0x3,
    ARC_CC_P = ARC_CC_PL,
    ARC_CC_MI = 0x4,
    ARC_CC_N = ARC_CC_MI,
    ARC_CC_CS = 0x5,
    ARC_CC_C = ARC_CC_CS,
    ARC_CC_LO = ARC_CC_CS,
    ARC_CC_CC = 0x6,
    ARC_CC_NC = ARC_CC_CC,
    ARC_CC_HS = ARC_CC_CC,
    ARC_CC_VS = 0x7,
    ARC_CC_V = ARC_CC_VS,
    ARC_CC_VC = 0x8,
    ARC_CC_NV = ARC_CC_VC,
    ARC_CC_GT = 0x9,
    ARC_CC_GE = 0xA,
    ARC_CC_LT = 0xB,
    ARC_CC_LE = 0xC,
    ARC_CC_HI = 0xD,
    ARC_CC_LS = 0xE,
    ARC_CC_PNZ = 0xF,
  };

enum arc_operand_kind
  {
    ARC_OPERAND_KIND_UNKNOWN = 0,
    ARC_OPERAND_KIND_REG,
    ARC_OPERAND_KIND_SHIMM,
    ARC_OPERAND_KIND_LIMM
  };

struct arc_insn_operand
{
  /* Operand value as encoded in instruction.  */
  unsigned long value;

  enum arc_operand_kind kind;
};

/* Only LEAVE_S can have this amount of operands.  Other instructions have 3
   operands at most.  */
#define ARC_MAX_OPERAND_COUNT (4)

/* Container for information about instruction.  Provides a higher level access
   to data that is contained in struct arc_opcode.  */

struct arc_instruction
{
  /* Address of this instruction.  */
  bfd_vma address;

  /* Whether this is a valid instruction.  */
  bfd_boolean valid;

  insn_class_t insn_class;

  /* Length (without LIMM).  */
  unsigned int length;

  /* Instruction word as it is, in the host endianness.  */
  unsigned long raw_word;

  /* Is there a LIMM in this instruction?  */
  int limm_p;

  /* Long immediate value.  */
  unsigned long limm_value;

  /* Some ARC instructions have subopcodes nested up to 3 layers.  */
  unsigned int opcode;
  unsigned int subopcode1;
  unsigned int subopcode2;
  unsigned int subopcode3;

  /* Is it a branch/jump instruction?  */
  int is_control_flow;

  /* Whether this instruction has a delay slot.  */
  int has_delay_slot;

  /* Value of condition code field.  */
  enum arc_condition_code condition_code;

  /* Load/store writeback mode.  */
  enum arc_ldst_writeback_mode writeback_mode;

  /* Load/store data size.  */
  enum arc_ldst_data_size data_size_mode;

  /* Amount of operands in instruction.  Note that amount of operands reported
     by opcodes disassembler can be different from the one encoded in the
     instruction.  Notable case is "ld a,[b,offset]", when offset == 0.  In
     this case opcodes disassembler presents this instruction as "ld a,[b]",
     hence there are *two* operands, not three.  OPERANDS_COUNT and OPERANDS
     contain only those explicit operands, hence it is up to invoker to handle
     the case described above based on instruction opcodes.  Another notable
     thing is that in opcodes disassembler representation square brackets (`['
     and `]') are so called fake-operands - they are in the list of operands,
     but do not have any value of they own.  Those "operands" are not present
     in this array.  */
  struct arc_insn_operand operands[ARC_MAX_OPERAND_COUNT];

  unsigned int operands_count;
};

/* Fill INSN with data about instruction at specified ADDR.  */

void arc_insn_decode (bfd_vma addr,
		      struct disassemble_info *di,
		      disassembler_ftype func,
		      struct arc_instruction *insn);

/* Get address of next instruction after INSN, assuming linear execution (no
   taken branches).  If instruction has a delay slot, then returned value will
   point at the instruction in delay slot.  That is - "address of instruction
   + instruction length with LIMM".  */

static inline bfd_vma
arc_insn_get_linear_next_pc (const struct arc_instruction *insn)
{
  /* In ARC long immediate is always 4 bytes.  */
  return (insn->address + insn->length + (insn->limm_p ? 4 : 0));
}

/* Get register with base address of memory operation.  */

int arc_insn_get_memory_base_reg (const struct arc_instruction *insn);

/* Get offset of a memory operation INSN.  */

bfd_vma arc_insn_get_memory_offset (const struct arc_instruction *insn);

/* Various functions that help with checking if given instruction has specified
   [sub]opcode or that it is a particular type of instruction.  */

static inline int
arc_insn_match_op (const struct arc_instruction *insn, unsigned int opcode)
{
  return (insn->opcode == opcode);
}

static inline int
arc_insn_match_subop1 (const struct arc_instruction *insn, unsigned int opcode,
		       unsigned int subopcode1)
{
  return (insn->opcode == opcode && insn->subopcode1 == subopcode1);
}

static inline int
arc_insn_match_subop2 (const struct arc_instruction *insn, unsigned int opcode,
		       unsigned int subopcode1, unsigned int subopcode2)
{
  return (insn->opcode == opcode
	  && insn->subopcode1 == subopcode1
	  && insn->subopcode2 == subopcode2);
}

static inline int
arc_insn_match_subop3 (const struct arc_instruction *insn, unsigned int opcode,
		       unsigned int subopcode1, unsigned int subopcode2,
		       unsigned int subopcode3)
{
  return (insn->opcode == opcode
	  && insn->subopcode1 == subopcode1
	  && insn->subopcode2 == subopcode2
	  && insn->subopcode3 == subopcode3);
}

/* Provide insn_match shortcuts for commonly checked instructions.  There is an
   alternative: use opcode_data->name to check for instruction, but using
   opcodes looks preferably because it is possible that a new encoding can be
   added for an existing instruction, so it will pass the "name" test, however
   it might, for example, has a different set of operands, which will break
   assumptions in current code about the operands.  If instructions are
   detected by their opcodes, then it will be required to update those matching
   instructions and all functions that use them.  */

static inline int
arc_insn_is_enter_s (const struct arc_instruction *insn)
{
  return arc_insn_match_subop2 (insn, 0x18, 0x7, 0x0);
}

static inline int
arc_insn_is_leave_s (const struct arc_instruction *insn)
{
  return arc_insn_match_subop2 (insn, 0x18, 0x6, 0x0);
}

static inline int
arc_insn_is_mov (const struct arc_instruction *insn)
{
  /* mov b,c  */
  return (arc_insn_match_subop1 (insn, 0x04, 0xA)
	  /* mov_s g,h  */
	  || arc_insn_match_subop1 (insn, 0x08, 0x0)
	  /* mov_s h,s3  */
	  || arc_insn_match_subop1 (insn, 0x0E, 0x3)
	  /* mov_s.ne b,h  */
	  || arc_insn_match_subop1 (insn, 0x0E, 0x7)
	  /* mov_s b,u8  */
	  || arc_insn_match_op (insn, 0x1B));
}

static inline int
arc_insn_is_pop_s (const struct arc_instruction *insn)
{
  return (arc_insn_match_subop2 (insn, 0x18, 0x6, 0x1)
	  || arc_insn_match_subop2 (insn, 0x18, 0x6, 0x11));
}

static inline int
arc_insn_is_push_s (const struct arc_instruction *insn)
{
  return (arc_insn_match_subop2 (insn, 0x18, 0x7, 0x1)
	  || arc_insn_match_subop2 (insn, 0x18, 0x7, 0x11));
}

static inline int
arc_insn_is_st (const struct arc_instruction *insn)
{
  /* st c,[b,s9]  */
  return (arc_insn_match_op (insn, 0x03)
	  /* st_s r0,[gp,s11]  */
	  || arc_insn_match_subop1 (insn, 0x0A, 0x2)
	  /* st_s c,[b,u7]  */
	  || arc_insn_match_op (insn, 0x14)
	  /* stb_s c,[b,u7]  */
	  || arc_insn_match_op (insn, 0x15)
	  /* sth_s c,[b,u7]  */
	  || arc_insn_match_op (insn, 0x16)
	  /* st_s b,[sp,u7]  */
	  || arc_insn_match_subop1 (insn, 0x18, 0x2)
	  /* stb_s b,[sp,u7]  */
	  || arc_insn_match_subop1 (insn, 0x18, 0x3));
}

static inline int
arc_insn_is_sub (const struct arc_instruction *insn)
{
  /* sub a,b,c  */
  return (arc_insn_match_subop1 (insn, 0x4, 0x2)
	  /* sub_s c,b,u3  */
	  || arc_insn_match_subop1 (insn, 0x0D, 0x1)
	  /* sub_s b,b,c  */
	  || arc_insn_match_subop1 (insn, 0x0F, 0x2)
	  /* sub_s.ne b,b,b  */
	  || arc_insn_match_subop2 (insn, 0x0F, 0x0, 0x6)
	  /* sub_s b,b,u5  */
	  || arc_insn_match_subop1 (insn, 0x17, 0x3)
	  /* sub_s sp,sp,u7  */
	  || arc_insn_match_subop2 (insn, 0x18, 0x5, 0x1));
}

#ifdef __cplusplus
}
#endif

#endif
