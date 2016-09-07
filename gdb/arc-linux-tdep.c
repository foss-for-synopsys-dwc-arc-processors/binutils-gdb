/* Target dependent code for ARC processor family, for GDB, the GNU debugger.

   Copyright 2005 Free Software Foundation, Inc.
   Copyright 2009-2015 Synopsys Inc.

   Contributor Anton Kolesov <Anton.Kolesov@synopsys.com>
   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com> on behalf of
   Synopsys Inc.
   Contributed by Codito Technologies Pvt. Ltd. (www.codito.com) on behalf of
   Synopsys Inc.

   Authors: 
      Jeremy Bennett       <jeremy.bennett@embecosm.com>
      Soam Vasani          <soam.vasani@codito.com>
      Ramana Radhakrishnan <ramana.radhakrishnan@codito.com> 
      Richard Stuckey      <richard.stuckey@arc.com>
      Anton Kolesov        <Anton.Kolesov@synopsys.com>

   This file is part of GDB.
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
  
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
  
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/******************************************************************************/
/*                                                                            */
/* Outline:                                                                   */
/*     This module provides support for the ARC processor family's target     */
/*     dependencies which are specific to the arc-linux-uclibc configuration  */
/*     of the ARC gdb.                                                        */
/*                                                                            */
/******************************************************************************/

/* gdb header files */
#include "defs.h"
#include "gdbarch.h"
#include "frame.h"
#include "osabi.h"
#include "regcache.h"
#include "inferior.h"
#include "reggroups.h"
#include "solib-svr4.h"
#include "block.h"
#include "regset.h"
#include "dis-asm.h"
#include "opcode/arc.h"
#include "exceptions.h"
/* lookup_minimal_symbol */
#include "minsyms.h"
/* Not used directly, but BMSYMBOL_VALUE_ADDRESS macro expansion depends on it. */
#include "objfiles.h"
/* BMSYMBOL_VALUE_ADDRESS */
#include "symtab.h"
/* delete_single_step_breakpoints */
#include "gdbthread.h"
/* linux_init_abi */
#include "linux-tdep.h"

/* ARC header files */
#include "arc-tdep.h"
#include "arc-linux-tdep.h"


/* -------------------------------------------------------------------------- */
/*                               local data                                   */
/* -------------------------------------------------------------------------- */

/*! Mapping between the general-purpose registers in `struct sigcontext' format
    and GDB's register cache layout. It should match current target
    description, currently it is aligned to the "compatible" register layout.

    arc_linux_sc_reg_offset[i] is the sigcontext offset of GDB regnum `i'.
	
	At the moment of this writing sigcontext is the same as user_regs_struct
	used for core dumps. The only difference is that sigcontext uses only a
	subset of registers from user_regs_struct, namely "scratch" part.*/

/* From <include/uapi/asm/sigcontext.h> and <include/uapi/asm/ptrace.h>. */
static const int arc_linux_sc_reg_offset[] = {
  22 * BYTES_IN_REGISTER,	/* r0       */
  21 * BYTES_IN_REGISTER,	/* r1       */
  20 * BYTES_IN_REGISTER,	/* r2       */
  19 * BYTES_IN_REGISTER,	/* r3       */
  18 * BYTES_IN_REGISTER,	/* r4       */
  17 * BYTES_IN_REGISTER,	/* r5       */
  16 * BYTES_IN_REGISTER,	/* r6       */
  15 * BYTES_IN_REGISTER,	/* r7       */
  14 * BYTES_IN_REGISTER,	/* r8       */
  13 * BYTES_IN_REGISTER,	/* r9       */
  12 * BYTES_IN_REGISTER,	/* r10      */
  11 * BYTES_IN_REGISTER,	/* r11      */
  10 * BYTES_IN_REGISTER,	/* r12      */
  REGISTER_NOT_PRESENT,  	/* r13      */
  REGISTER_NOT_PRESENT,  	/* r14      */
  REGISTER_NOT_PRESENT,  	/* r15      */
  REGISTER_NOT_PRESENT,  	/* r16      */
  REGISTER_NOT_PRESENT,  	/* r17      */
  REGISTER_NOT_PRESENT,  	/* r18      */
  REGISTER_NOT_PRESENT,  	/* r19      */
  REGISTER_NOT_PRESENT,  	/* r20      */
  REGISTER_NOT_PRESENT,  	/* r21      */
  REGISTER_NOT_PRESENT,  	/* r22      */
  REGISTER_NOT_PRESENT,  	/* r23      */
  REGISTER_NOT_PRESENT,  	/* r24      */
  REGISTER_NOT_PRESENT,  	/* r25      */
  9 * BYTES_IN_REGISTER,	/* r26 (gp) */
  8 * BYTES_IN_REGISTER,	/* fp       */
  23 * BYTES_IN_REGISTER,	/* sp       */
  REGISTER_NOT_PRESENT,  	/* ilink1   */
  REGISTER_NOT_PRESENT,  	/* ilink2   */
  7 * BYTES_IN_REGISTER,	/* blink    */

  REGISTER_NOT_PRESENT,  	/* r32      */
  REGISTER_NOT_PRESENT,  	/* r33      */
  REGISTER_NOT_PRESENT,  	/* r34      */
  REGISTER_NOT_PRESENT,  	/* r35      */
  REGISTER_NOT_PRESENT,  	/* r36      */
  REGISTER_NOT_PRESENT,  	/* r37      */
  REGISTER_NOT_PRESENT,  	/* r38      */
  REGISTER_NOT_PRESENT,  	/* r39      */
  REGISTER_NOT_PRESENT,  	/* r40      */
  REGISTER_NOT_PRESENT,  	/* r41      */
  REGISTER_NOT_PRESENT,  	/* r42      */
  REGISTER_NOT_PRESENT,  	/* r43      */
  REGISTER_NOT_PRESENT,  	/* r44      */
  REGISTER_NOT_PRESENT,  	/* r45      */
  REGISTER_NOT_PRESENT,  	/* r46      */
  REGISTER_NOT_PRESENT,  	/* r47      */
  REGISTER_NOT_PRESENT,  	/* r48      */
  REGISTER_NOT_PRESENT,  	/* r49      */
  REGISTER_NOT_PRESENT,  	/* r50      */
  REGISTER_NOT_PRESENT,  	/* r51      */
  REGISTER_NOT_PRESENT,  	/* r52      */
  REGISTER_NOT_PRESENT,  	/* r53      */
  REGISTER_NOT_PRESENT,  	/* r54      */
  REGISTER_NOT_PRESENT,  	/* r55      */
  REGISTER_NOT_PRESENT,  	/* r56      */
  REGISTER_NOT_PRESENT,  	/* r57      */
  REGISTER_NOT_PRESENT,  	/* r58      */
  REGISTER_NOT_PRESENT,  	/* r59      */
  4 * BYTES_IN_REGISTER,	/* lp_count */
  REGISTER_NOT_PRESENT,  	/* reserved */
  REGISTER_NOT_PRESENT,  	/* limm     */
  REGISTER_NOT_PRESENT,  	/* pcl      */

  REGISTER_NOT_PRESENT,  	/* stop_pc  */
  2 * BYTES_IN_REGISTER,	/* lp_start */
  3 * BYTES_IN_REGISTER,	/* lp_end   */
  5 * BYTES_IN_REGISTER,	/* status32 */
  REGISTER_NOT_PRESENT,  	/* st32_l1  */
  REGISTER_NOT_PRESENT,  	/* st32_l2  */
  REGISTER_NOT_PRESENT,  	/* irq_lv12 */
  REGISTER_NOT_PRESENT,  	/* irq_lev  */
  REGISTER_NOT_PRESENT,  	/* irq_hint */
  6 * BYTES_IN_REGISTER,	/* ret      */
  REGISTER_NOT_PRESENT,  	/* erbta    */
  REGISTER_NOT_PRESENT,  	/* erstatus */
  REGISTER_NOT_PRESENT,  	/* ecr      */
  REGISTER_NOT_PRESENT,  	/* efa      */
  REGISTER_NOT_PRESENT,  	/* icause1  */
  REGISTER_NOT_PRESENT,  	/* icause2  */
  REGISTER_NOT_PRESENT,  	/* ienable  */
  REGISTER_NOT_PRESENT,  	/* itrigger */
  1 * BYTES_IN_REGISTER,	/* bta      */
  REGISTER_NOT_PRESENT,  	/* bta_l1   */
  REGISTER_NOT_PRESENT,  	/* bta_l2   */
  REGISTER_NOT_PRESENT,  	/* irq pulse*/
  REGISTER_NOT_PRESENT,  	/* irq pend */
};


/* arc_linux_core_reg_offsets[i] is the offset in the .reg section of GDB
 * regnum i. It should match current target description, currently it is
 * aligned to the "compatible" register layout.
 *
 * From include/uapi/asm/ptrace.h in the ARC Linux sources.
 */

static const int arc_linux_core_reg_offsets[] = {
  22 * BYTES_IN_REGISTER,	/* r0       */
  21 * BYTES_IN_REGISTER,	/* r1       */
  20 * BYTES_IN_REGISTER,	/* r2       */
  19 * BYTES_IN_REGISTER,	/* r3       */
  18 * BYTES_IN_REGISTER,	/* r4       */
  17 * BYTES_IN_REGISTER,	/* r5       */
  16 * BYTES_IN_REGISTER,	/* r6       */
  15 * BYTES_IN_REGISTER,	/* r7       */
  14 * BYTES_IN_REGISTER,	/* r8       */
  13 * BYTES_IN_REGISTER,	/* r9       */
  12 * BYTES_IN_REGISTER,	/* r10      */
  11 * BYTES_IN_REGISTER,	/* r11      */
  10 * BYTES_IN_REGISTER,	/* r12      */
  37 * BYTES_IN_REGISTER,	/* r13      */
  36 * BYTES_IN_REGISTER,	/* r14      */
  35 * BYTES_IN_REGISTER,	/* r15      */
  34 * BYTES_IN_REGISTER,	/* r16      */
  33 * BYTES_IN_REGISTER,	/* r17      */
  32 * BYTES_IN_REGISTER,	/* r18      */
  31 * BYTES_IN_REGISTER,	/* r19      */
  30 * BYTES_IN_REGISTER,	/* r20      */
  29 * BYTES_IN_REGISTER,	/* r21      */
  28 * BYTES_IN_REGISTER,	/* r22      */
  27 * BYTES_IN_REGISTER,	/* r23      */
  26 * BYTES_IN_REGISTER,	/* r24      */
  25 * BYTES_IN_REGISTER,	/* r25      */
  9 * BYTES_IN_REGISTER,	/* r26 (gp) */
  8 * BYTES_IN_REGISTER,	/* fp       */
  23 * BYTES_IN_REGISTER,	/* sp       */
  REGISTER_NOT_PRESENT,  	/* ilink1   */
  REGISTER_NOT_PRESENT,  	/* ilink2   */
  7 * BYTES_IN_REGISTER,	/* blink    */

  REGISTER_NOT_PRESENT,  	/* r32      */
  REGISTER_NOT_PRESENT,  	/* r33      */
  REGISTER_NOT_PRESENT,  	/* r34      */
  REGISTER_NOT_PRESENT,  	/* r35      */
  REGISTER_NOT_PRESENT,  	/* r36      */
  REGISTER_NOT_PRESENT,  	/* r37      */
  REGISTER_NOT_PRESENT,  	/* r38      */
  REGISTER_NOT_PRESENT,  	/* r39      */
  REGISTER_NOT_PRESENT,  	/* r40      */
  REGISTER_NOT_PRESENT,  	/* r41      */
  REGISTER_NOT_PRESENT,  	/* r42      */
  REGISTER_NOT_PRESENT,  	/* r43      */
  REGISTER_NOT_PRESENT,  	/* r44      */
  REGISTER_NOT_PRESENT,  	/* r45      */
  REGISTER_NOT_PRESENT,  	/* r46      */
  REGISTER_NOT_PRESENT,  	/* r47      */
  REGISTER_NOT_PRESENT,  	/* r48      */
  REGISTER_NOT_PRESENT,  	/* r49      */
  REGISTER_NOT_PRESENT,  	/* r50      */
  REGISTER_NOT_PRESENT,  	/* r51      */
  REGISTER_NOT_PRESENT,  	/* r52      */
  REGISTER_NOT_PRESENT,  	/* r53      */
  REGISTER_NOT_PRESENT,  	/* r54      */
  REGISTER_NOT_PRESENT,  	/* r55      */
  REGISTER_NOT_PRESENT,  	/* r56      */
  REGISTER_NOT_PRESENT,  	/* r57      */
  REGISTER_NOT_PRESENT,  	/* r58      */
  REGISTER_NOT_PRESENT,  	/* r59      */
  4 * BYTES_IN_REGISTER,	/* lp_count */
  REGISTER_NOT_PRESENT,  	/* reserved */
  REGISTER_NOT_PRESENT,  	/* limm     */
  REGISTER_NOT_PRESENT,  	/* pcl      */

  39 * BYTES_IN_REGISTER,	/* stop_pc  */
  2 * BYTES_IN_REGISTER,	/* lp_start */
  3 * BYTES_IN_REGISTER,	/* lp_end   */
  5 * BYTES_IN_REGISTER,	/* status32 */
  REGISTER_NOT_PRESENT,  	/* st32_l1  */
  REGISTER_NOT_PRESENT,  	/* st32_l2  */
  REGISTER_NOT_PRESENT,  	/* irq_lv12 */
  REGISTER_NOT_PRESENT,  	/* irq_lev  */
  REGISTER_NOT_PRESENT,  	/* irq_hint */
  6 * BYTES_IN_REGISTER,	/* ret      */
  REGISTER_NOT_PRESENT,  	/* erbta    */
  REGISTER_NOT_PRESENT,  	/* erstatus */
  REGISTER_NOT_PRESENT,  	/* ecr      */
  38 * BYTES_IN_REGISTER,	/* efa      */
  REGISTER_NOT_PRESENT,  	/* icause1  */
  REGISTER_NOT_PRESENT,  	/* icause2  */
  REGISTER_NOT_PRESENT,  	/* ienable  */
  REGISTER_NOT_PRESENT,  	/* itrigger */
  1 * BYTES_IN_REGISTER,	/* bta      */
  REGISTER_NOT_PRESENT,  	/* bta_l1   */
  REGISTER_NOT_PRESENT,  	/* bta_l2   */
  REGISTER_NOT_PRESENT,  	/* irq pulse*/
  REGISTER_NOT_PRESENT,  	/* irq pend */

  /* 24 * BYTES_IN_REGISTER,	orig_r8  */
};


/* -------------------------------------------------------------------------- */
/*                               local functions                              */
/* -------------------------------------------------------------------------- */


/*! Extracts the result of the last condition checking from status32 register by
    condition code.

  @param[in] condition_code	It must be a condition code of the last
				condition that was checked and its result was
				stored in status32 register, otherwise this
				function may return the wrong value.
  @param[in] status32		Status32 register's value.
  @return  The result of condition checking if given condition code exists,
	   otherwise throws the assertion error.*/
static int
arc_linux_is_condition_true (ULONGEST status32, int condition_code)
{
  int z_flag, n_flag, c_flag, v_flag;

  gdb_assert (condition_code >= 0 && condition_code <= 15);

  z_flag = status32 & ARC_REG_STATUS32_Z;
  n_flag = status32 & ARC_REG_STATUS32_N;
  c_flag = status32 & ARC_REG_STATUS32_C;
  v_flag = status32 & ARC_REG_STATUS32_V;

  switch (condition_code)
    {
    /* Always (unconditional branch/jump instruction). */
    case 0:
      return TRUE;

    /* Zero (equals). */
    case 1:
      return z_flag;

    /* Non-Zero (not equals). */
    case 2:
      return !z_flag;

    /* Positive. */
    case 3:
      return !n_flag;

    /* Negative. */
    case 4:
      return n_flag;

    /* carry set, lower than (unsigned). */
    case 5:
      return c_flag;

    /* Carry clear, higher or same (unsigned). */
    case 6:
      return !c_flag;

    /* Over-flow set. */
    case 7:
      return v_flag;

    /* Over-flow clear. */
    case 8:
      return !v_flag;

    /* Greater than (signed). */
    case 9:
      return (n_flag && v_flag && !z_flag) || (!n_flag && !v_flag && !z_flag);

    /* Greater than or equal to (signed). */
    case 10:
      return (n_flag && v_flag) || (!n_flag && !v_flag);

    /* Less than (signed). */
    case 11:
      return (n_flag && !v_flag) || (!n_flag && v_flag);

    /* Less than or equal to (signed). */
    case 12:
      return (z_flag) || (n_flag && !v_flag) || (!n_flag && v_flag);

    /* Higher than (unsigned). */
    case 13:
      return (!c_flag) && (!z_flag);

    /* Lower than or same (unsigned). */
    case 14:
      return (c_flag) || (z_flag);

    /* Positive non-zero. */
    case 15:
      return (!n_flag) && (!z_flag);

    }

  /* Next line is used to supress warning about the return value. It is
     unreachable during normal execution which does not cause the assertion
     error, see code above to understand why. */
  return -1;

}    /* arc_linux_is_condition_true() */


/*! Checks result of brcc/bbit instruction condition by instruction arguments
    and subopcode.

  @param insn BRcc/BBIT{0,1} instruction to analyze. This function doesn't
              check if insn is indeed a BRcc or BBIT.

  @return Whether condition of this instruction is true or not. */
static int
arc_linux_is_brcc_taken (const struct arc_instruction *insn)
{
  ULONGEST uarg1, uarg2;
  LONGEST arg1, arg2;
  unsigned int subopcode;

  gdb_assert (insn != NULL);

  uarg1 = arc_insn_get_operand_value (insn, 0);
  uarg2 = arc_insn_get_operand_value (insn, 1);
  /* These variables will be used for signed comparison. */
  arg1 = arc_insn_get_operand_value_signed (insn, 0);
  arg2 = arc_insn_get_operand_value_signed (insn, 1);

  /* 32-bit BRcc/BBIT instructions contains they condition in the
     subopcode. 16-bit BRcc supports only EQ and NE, but subopcode values for
     short instruction are identical to those of long instruction. However the
     field in arc_instruction is different. */
  subopcode = ((insn->length == 4) ? insn->subopcode3 :
			    insn->subopcode1);

  gdb_assert (subopcode <= 15);

  if (arc_debug)
    {
      fprintf_unfiltered (gdb_stdlog,
			  " --- arc_linux_is_brcc_taken subopcode = %d,"
			  "arg1 = %s, arg2 = %s, uarg1 = %s, uarg2 = %s\n",
			  subopcode, plongest (arg1), plongest (arg2),
			  pulongest (uarg1), pulongest (uarg2));
    }

  switch (subopcode)
    {
    /* BREQ */
    case 0x0:
    case 0x8:
      return uarg1 == uarg2;

    /* BRNE */
    case 0x1:
    case 0x9:
      return uarg1 != uarg2;

    /* BRLT */
    case 0x2:
    case 0xA:
      return arg1 < arg2;

    /* BRGE */
    case 0x3:
    case 0xB:
      return arg1 >= arg2;

    /* BRLO */
    case 0x4:
    case 0xC:
      return uarg1 < uarg2;

    /* BRHS */
    case 0x5:
    case 0xD:
      return uarg1 >= uarg2;

    /* BBIT0 */
    case 0x6:
    case 0xE:
      return !(uarg1 & (1 << uarg2));

    /* BBIT1 */
    case 0x7:
    case 0xF:
      return (uarg1 & (1 << uarg2));
    }

  /* This line is used to supress warning about the return value. It is
     unreachable during normal execution, because assert will catch the case of
     subopcode > 15. */
  return -1;
}    /* arc_linux_is_brcc_taken() */


/*! Returns the address of the next instruction or the branch
    target if it is a branch and it is taken.

    @param[in]	pc */
static CORE_ADDR
arc_linux_next_pc (CORE_ADDR pc)
{
  struct regcache *regcache = get_current_regcache ();
  struct gdbarch *gdbarch = get_regcache_arch (regcache);
  struct arc_instruction insn;
  int is_loop_enabled;
  ULONGEST status32;
  CORE_ADDR next_pc;

  /* So what is the instruction at the given pc? */
  arc_insn_decode (gdbarch, pc, &insn);

  /* By default, the next instruction is the one immediately after the one at
     pc. */
  next_pc = arc_insn_get_linear_next_pc (&insn);

  /* ZD-loops may be disabled in STATUS32.  */
  regcache_cooked_read_unsigned (regcache, gdbarch_ps_regnum (gdbarch),
				 &status32);
  is_loop_enabled = !(status32 & ARC_REG_STATUS32_L);

  if (arc_debug)
    arc_insn_dump (&insn);

  if (insn.is_control_flow)
    {
      int is_branch_taken = FALSE;
      /* Checking if instruction is brcc or bbit because there is need to
         calculate branch condition manually then. */
      int is_brcc_or_bbit = ((insn.opcode == 0x01) && (insn.subopcode1 == 0x1))
			 || (insn.opcode == 0x1D);
      int is_branch_lpcc = (insn.opcode == 0x04 && insn.subopcode1 == 0x28);

      if (is_brcc_or_bbit)
	{
	  is_branch_taken = arc_linux_is_brcc_taken (&insn);
	}
      /* If branch instruction is not brcc or bbit we have not calculated
	 branch condition yet and should use status32 register for calculating
	 it. */
      else
	{
	  /* Non-conditional jumps and branches will have condition_code == 0,
	     which means "execute always.  */
	  is_branch_taken =
	    arc_linux_is_condition_true (status32, insn.condition_code);
	}

      if (arc_debug)
	{
	  fprintf_unfiltered (gdb_stdlog,
			      "--- arc_linux_next_pc is_brcc_or_bbit = %d, "
			      "is_branch_taken = %d, is_branch_lpcc = %d\n",
			      is_brcc_or_bbit, is_branch_taken,
			      is_branch_lpcc);
	}

      /* If current instruction is LP(cc) and branch is not taken, next
         instruction must be calculated the same way as it would if instruction
         was an another branch or jump and branch was taken. */
      if ((is_branch_taken && !is_branch_lpcc)
	  || (!is_branch_taken && is_branch_lpcc))
	{
	  next_pc = arc_insn_get_branch_target (&insn);
	}
      else
	{
	  /* For instructions with delay slots, the fall thru is not the
	     instruction immediately after the branch instruction, but the one
	     after that. */
	  if (insn.has_delay_slot)
	    {
	      struct arc_instruction insn_d;
	      arc_insn_decode (gdbarch, next_pc, &insn_d);
	      next_pc = arc_insn_get_linear_next_pc (&insn_d);
	    }
	}
    }
  /* Is current instruction the last in a loop body? */
  else if (is_loop_enabled)
    {
      ULONGEST lp_end, lp_start, lp_count;
      regcache_cooked_read_unsigned (regcache, ARC_LP_START_REGNUM,
				     &lp_start);
      regcache_cooked_read_unsigned (regcache, ARC_LP_END_REGNUM, &lp_end);
      regcache_cooked_read_unsigned (regcache, ARC_LP_COUNT_REGNUM,
				     &lp_count);

      if (arc_debug)
	{
	  fprintf_unfiltered (gdb_stdlog,
			      "lp_start = %s, lp_end = %s, lp_count = %s, "
			      "next_pc = %s\n",
			      pulongest (lp_start), pulongest (lp_end),
			      pulongest (lp_count), pulongest (next_pc));
	}
      if (next_pc == lp_end && lp_count > 1)
	{
	  /* The instruction is in effect a jump back to the start of the
	     loop. */
	  next_pc = lp_start;
	}
    }

  return next_pc;
}	/* arc_linux_next_pc () */


/*! Is THIS frame a sigtramp function.

    Does THIS frame correspond to a GNU/Linux sigtramp function? This is the
    case if the PC is either at the start of, or in the middle of the two
    instructions:

    @verbatim
    mov r8,nr_sigreturn
    swi
    @endverbatim

    @note This function has changed from GDB 6.8. It now takes a reference to
          THIS frame, not the NEXT frame.

    @param[in] this_frame  The frame to consider.
    @return                Non-zero (TRUE) if this is a sigtramp frame, zero
                           (FALSE) otherwise. */
static int
arc_linux_is_sigtramp (struct frame_info *this_frame)
{
  static const gdb_byte arc_sigtramp_insns_le[] =
    { 0x8a, 0x20, 0xc2, 0x12,		/* mov  r8,nr_rt_sigreturn */
      0x6f, 0x22, 0x3f, 0x00		/* swi */
    };
  static const gdb_byte arc_sigtramp_insns_be[] =
    { 0x12, 0xc2, 0x20, 0x8a,		/* mov  r8,nr_rt_sigreturn */
      0x00, 0x3f, 0x22, 0x6f		/* swi */
    };

  static const int INSNS_SIZE = sizeof (arc_sigtramp_insns_le);
  struct gdbarch *gdbarch = get_frame_arch (this_frame);
  enum bfd_endian byte_order = gdbarch_byte_order (gdbarch);
  const gdb_byte *arc_sigtramp_insns = byte_order == BFD_ENDIAN_LITTLE
    ? arc_sigtramp_insns_le : arc_sigtramp_insns_be;
  CORE_ADDR pc = get_frame_pc (this_frame);
  gdb_byte buf[sizeof (arc_sigtramp_insns_le)];

  /* Read the memory at the PC. Since we are stopped any breakpoints will
     have been removed (despite the name, this really does take THIS frame). */
  if (!safe_frame_unwind_memory (this_frame, pc, buf, INSNS_SIZE))
    {
      /* failed to unwind frame */
      return FALSE;
    }

  /* Is that code the sigtramp instruction sequence? */
  if (memcmp (buf, arc_sigtramp_insns, INSNS_SIZE) == 0)
    {
      return TRUE;
    }

  /* No - look one instruction earlier in the code... */
  if (!safe_frame_unwind_memory (this_frame, pc - 4, buf, (int) INSNS_SIZE))
    {
      /* failed to unwind frame */
      return FALSE;
    }
  
  return memcmp (buf, arc_sigtramp_insns, INSNS_SIZE) == 0;

}	/* arc_linux_is_sigtramp () */


/*! Get sigcontext of sigtramp frame.

    Assuming THIS frame is a frame following a GNU/Linux sigtramp routine,
    return the address of the associated sigcontext structure.

    That structure can be found in the stack pointer of the frame.

    @note This function has changed from GDB 6.8. It now takes a reference to
          THIS frame, not the NEXT frame.

    @param[in] this_frame  The frame to consider.
    @return                The address of the sigcontext structure. */
static CORE_ADDR
arc_linux_sigcontext_addr (struct frame_info *this_frame)
{
  return (CORE_ADDR) get_frame_sp (this_frame);

}	/* arc_linux_sigcontext_addr () */


/* -------------------------------------------------------------------------- */
/*		   ARC specific GDB architectural functions		      */
/*									      */
/* Functions are listed in the order they are used in arc_linux_init_osabi.   */
/* -------------------------------------------------------------------------- */

/*! Determine whether a register can be read.

    This function relies on tdep->reginfo, since numbers of individual
    registers are not globally same and can change from one run to another.

    A Linux target can only read registers writable in user space and only sees
    a small subset of aux registers and no core extension registers.  This
    information is stored in the tdep->reginfo, but since availability is
    different with baremetal case, this function relies on
    user_readable/user_writable functions.

    @param[in] gdbarch  The current GDB architecture.
    @param[in] regnum   The register of interest.
    @return             Non-zero (TRUE) if we _cannot_ read the register,
                        false otherwise. */
static int
arc_linux_cannot_fetch_register (struct gdbarch *gdbarch, int regnum)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Assume that register is readable if there is no information. */
  if (regnum < tdep->reginfo_sz)
    return !tdep->reginfo[regnum].user_readable;
  else
    return FALSE;
}	/* arc_linux_cannot_store_register () */

/*! Determine whether a register can be written.

    This function relies on tdep->reginfo, since numbers of individual
    registers are not globally same and can change from one run to another.

    A Linux target can only read registers writable in user space and only sees
    a small subset of aux registers and no core extension registers.  This
    information is stored in the tdep->reginfo, but since availability is
    different with baremetal case, this function relies on
    user_readable/user_writable functions.

    @todo We'll need a more complex interface once the aux registers are
          defined via XML.

    @param[in] gdbarch  The current GDB architecture.
    @param[in] regnum   The register of interest.
    @return             Non-zero (TRUE) if we _cannot_ write the register,
                        false otherwise. */
static int
arc_linux_cannot_store_register (struct gdbarch *gdbarch, int regnum)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Assume that register is writable if there is no info. */
  if (regnum < tdep->reginfo_sz)
    return !tdep->reginfo[regnum].user_writable;
  else
    return FALSE;
}	/* arc_linux_cannot_store_register () */


/*! Get breakpoint which is approriate for address at which it is to be set.

    For ARC under Linux, breakpoint uses the 16-bit TRAP_S 1 instruction,
    which is 0x3e78 (little endian) or 0x783e (big endian).

    @todo Surely we should be able to use the same breakpoint instruction for
          both Linux and ELF?

    @param[in]     gdbarch  Current GDB architecture
    @param[in,out] pcptr    Pointer to the PC where we want to place a
                            breakpoint
    @param[out]    lenptr   Number of bytes used by the breakpoint.
    @return                 The byte sequence of a breakpoint instruction. */
static const unsigned char *
arc_linux_breakpoint_from_pc (struct gdbarch *gdbarch, CORE_ADDR * pcptr,
			      int *lenptr)
{
  static const unsigned char breakpoint_instr_be[] = { 0x78, 0x3e };
  static const unsigned char breakpoint_instr_le[] = { 0x3e, 0x78 };

  *lenptr = sizeof (breakpoint_instr_be);
  return (gdbarch_byte_order (gdbarch) == BFD_ENDIAN_BIG)
    ? breakpoint_instr_be
    : breakpoint_instr_le;

}	/* arc_linux_breakpoint_from_pc () */


/*! Single step in software.

    Inserts a breakpoint to the location where the program will end up
    after the current instruction.

    @param[in] frame  The current frame (THIS frame).
    @return           Non-zero (TRUE) if the breakpoints are inserted.
 */
static int
arc_linux_software_single_step (struct frame_info *frame)
{
  struct gdbarch *gdbarch = get_frame_arch (frame);
  struct address_space *aspace = get_frame_address_space (frame);
  CORE_ADDR pc = get_frame_pc (frame);
  CORE_ADDR next_pc = arc_linux_next_pc (pc);
  insert_single_step_breakpoint (gdbarch, aspace, next_pc);

  /* Returns always true for now. */
  return 1;

}	/* arc_linux_software_single_step () */


/*! Find where to put a breakpoint after the resolver.

    See the comments for SKIP_SOLIB_RESOLVER at the top of infrun.c.
 
    This is called on every single step through the PLT and runtime resolver.
   
    This function:
       1) decides whether a PLT has sent us into the linker to resolve a
          function reference, and
       2) if so, tells us where to set a temporary breakpoint that will
          trigger when the dynamic linker is done. */
static CORE_ADDR
arc_linux_skip_solib_resolver (struct gdbarch *gdbarch, CORE_ADDR pc)
{
  /* For uClibc 0.9.26.
   
     An unresolved PLT entry points to "__dl_linux_resolve", which calls
     "__dl_linux_resolver" to do the resolving and then eventually jumps to
     the function.
   
     So we look for the symbol `_dl_linux_resolver', and if we are there, gdb
     sets a breakpoint at the return address, and continues. */
  struct bound_minimal_symbol resolver = lookup_minimal_symbol("_dl_linux_resolver",
          NULL, NULL);

  if (arc_debug)
    {
      if (resolver.minsym)
	{
	  CORE_ADDR res_addr = BMSYMBOL_VALUE_ADDRESS (resolver);
	  fprintf_unfiltered (gdb_stdlog, "--- %s : pc = %s, resolver at %s\n",
			      __FUNCTION__, print_core_address (gdbarch, pc),
			      print_core_address (gdbarch, res_addr));
	}
      else
	{
	  fprintf_unfiltered (gdb_stdlog, "--- %s : pc = %s, no resolver found",
			      __FUNCTION__, print_core_address (gdbarch, pc));
	}
    }

  if (resolver.minsym && BMSYMBOL_VALUE_ADDRESS (resolver) == pc)
    {
      /* find the return address */
      return  gdbarch_unwind_pc (gdbarch, get_current_frame());
    }
  else
    {
      /* no breakpoint required */
      return 0;
    }
}	/* arc_linux_skip_solib_resolver () */


/*! Call the right architecture variant's supply_gregset function.

    For now, we have only ARCompact. */
void
arc_linux_supply_gregset (const struct regset *regset,
			  struct regcache *regcache,
			  int regnum, const void *gregs, size_t size)
{
  const bfd_byte *buf = (const bfd_byte *) gregs;
  unsigned int reg;

  for (reg = 0; reg < ARRAY_SIZE (arc_linux_core_reg_offsets); reg++)
    {
      if (arc_linux_core_reg_offsets[reg] != REGISTER_NOT_PRESENT)
	regcache_raw_supply (regcache,
			     (int) reg,
			     buf + arc_linux_core_reg_offsets[reg]);
    }
}	/* arc_linux_supply_gregset () */


/* Writes registers from regcache into the NT_PRSTATUS data array. */
void
arc_linux_collect_gregset ( const struct regset *regset,
                            const struct regcache *regcache,
                            int regnum,
                            void *gregs,
                            size_t size)
{
  gdb_byte *buf = (gdb_byte *) gregs;
  int reg;

  for (reg = 0; reg < ARRAY_SIZE (arc_linux_core_reg_offsets); reg++)
    {
      /* Skip unexisting registers. regnum == -1 means writing all regs. */
      if ((arc_linux_core_reg_offsets[reg] != REGISTER_NOT_PRESENT) &&
          (regnum == reg || regnum == -1) )
        {
          struct gdbarch *gdbarch = get_regcache_arch (regcache);
          struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
          /* This is a cludge for ARC 700: address where execution has stopped
           * is in pseudo-register STOP_PC, however when continuing execution
           * kernel uses value from ERET register. And because TRAP_S commits,
           * we have that ERET != STOP_PC, so ERET must be overwritten by the
           * GDB, otherwise program will continue at address after the current
           * instruction, which might not be a valid instruction at all. In
           * GDBserver this handled internally, invisible to the GDB client. */
          if (gdbarch_pc_regnum (gdbarch) == reg)
            regcache_raw_collect (regcache, reg,
                buf + arc_linux_core_reg_offsets[ARC_COMPATIBLE_ERET_REGNUM]);
          else if (reg != ARC_COMPATIBLE_ERET_REGNUM)
            regcache_raw_collect (regcache, reg,
                buf + arc_linux_core_reg_offsets[reg]);
          /* reg == ARC_AUX_ERET_REGNUM is ignored. */
        }
    }
} /* arc_linux_collect_gregset () */

/* Linux regset definitions. */
static struct regset arc_linux_gregset = {
  NULL,
  arc_linux_supply_gregset,
  NULL,
};

/* Implement the `iterate_over_regset_sections` gdbarch method.  */
static void
arc_linux_iterate_over_regset_sections (struct gdbarch *gdbarch,
                                        iterate_over_regset_sections_cb *cb,
                                        void *cb_data,
                                        const struct regcache *regcache)
{
  cb (".reg", ARC_LINUX_SIZEOF_GREGSET, &arc_linux_gregset, NULL, cb_data);
}


/* -------------------------------------------------------------------------- */
/*                               externally visible functions                 */
/* -------------------------------------------------------------------------- */

/* Initialization specific to Linux/uClibc environment.  */

static void
arc_linux_init_osabi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  if (arc_debug)
    arc_print ("arc-linux: GNU/Linux OS/ABI initialization.\n");

  /* Fill in target-dependent info in ARC-private structure. */
  tdep->is_sigtramp = arc_linux_is_sigtramp;
  tdep->sigcontext_addr = arc_linux_sigcontext_addr;
  tdep->sc_reg_offset = arc_linux_sc_reg_offset;
  tdep->sc_num_regs = ARRAY_SIZE (arc_linux_core_reg_offsets);

  linux_init_abi (info, gdbarch);

  /* Set up target dependent GDB architecture entries. */
  set_gdbarch_cannot_fetch_register (gdbarch, arc_linux_cannot_fetch_register);
  set_gdbarch_cannot_store_register (gdbarch, arc_linux_cannot_store_register);
  set_gdbarch_breakpoint_from_pc (gdbarch, arc_linux_breakpoint_from_pc);
  set_gdbarch_fetch_tls_load_module_address (gdbarch,
                                             svr4_fetch_objfile_link_map);
  set_gdbarch_software_single_step (gdbarch, arc_linux_software_single_step);
  set_gdbarch_skip_solib_resolver (gdbarch, arc_linux_skip_solib_resolver);
  set_gdbarch_iterate_over_regset_sections
    (gdbarch, arc_linux_iterate_over_regset_sections);
  /* No need for any other GDB architecture core file functions. */

  /* GNU/Linux uses SVR4-style shared libraries, with 32-bit ints, longs and
     pointers (ILP32). */
  set_solib_svr4_fetch_link_map_offsets (gdbarch,
					 svr4_ilp32_fetch_link_map_offsets);

}	/* arc_gdbarch_osabi_init () */

/* Shut up -Wmissing-prototypes.  */
void _initialize_arc_linux_tdep (void);

void
_initialize_arc_linux_tdep (void)
{
  gdbarch_register_osabi (bfd_arch_arc, 0, GDB_OSABI_LINUX,
			  arc_linux_init_osabi);
}

/* vim: set sts=2 shiftwidth=2 ts=8: */
