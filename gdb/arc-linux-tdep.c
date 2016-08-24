/* Target dependent code for ARC processor family, for GDB, the GNU debugger.

   Copyright 2005 Free Software Foundation, Inc.
   Copyright 2009-2013 Synopsys Inc.

   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com> on behalf of
   Synopsys Inc.
   Contributed by Codito Technologies Pvt. Ltd. (www.codito.com) on behalf of
   Synopsys Inc.

   Authors: 
      Jeremy Bennett       <jeremy.bennett@embecosm.com>
      Soam Vasani          <soam.vasani@codito.com>
      Ramana Radhakrishnan <ramana.radhakrishnan@codito.com> 
      Richard Stuckey      <richard.stuckey@arc.com>

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
#include "osabi.h"
#include "regcache.h"
#include "inferior.h"
#include "reggroups.h"
#include "solib-svr4.h"
#include "block.h"
#include "regset.h"
#include "dis-asm.h"
#include "opcode/arc.h"
#include "opcodes/arc-dis.h"

/* ARC header files */
#include "arc-tdep.h"


/* -------------------------------------------------------------------------- */
/*                               local data                                   */
/* -------------------------------------------------------------------------- */

/* Linux specific values */
#define ARC_NR_PSEUDO_REGS      6
#define ARC_NR_REGS             39

#define STATUS32_L            0x00000100


/* Default breakpoint instruction used for ARC700 Linux */
static const unsigned char breakpoint_instruction[] = { 0x3e, 0x78 };
static const unsigned char be_breakpoint_instruction[] = { 0x78, 0x3e };


/* this array holds the object code of two instructions:
 *
 * mov r8,nr_sigreturn
 * swi
 */
static const gdb_byte arc_sigtramp_insns[] = { 0x8a, 0x20, 0xc1, 0x1d,
  0x6f, 0x22, 0x3f, 0x00
};

#define SIGTRAMP_INSNS_LENGTH     sizeof(arc_sigtramp_insns)


/* N.B. the array size is specified in the declaration so that the compiler
 *      will warn of "excess elements in array initializer" if there is a
 *      mismatch (but not of too few elements, unfortunately!).
 */
static const char *register_names[ARC_NR_REGS + ARC_NR_PSEUDO_REGS] = {
  "r0", "r1", "r2", "r3", "r4", "r5", "r6",
  "r7", "r8", "r9", "r10", "r11", "r12", "r13",
  "r14", "r15", "r16", "r17", "r18", "r19", "r20",
  "r21", "r22", "r23", "r24", "r25", "r26",

  "bta",
  "lp_start",
  "lp_end",
  "lp_count",
  "status32",
  "blink",
  "fp",
  "sp",
  "efa",

  /* linux-only registers */
  "ret",
  "orig_r8",
  "pc",				// stop pc

  /* pseudo-regs */
  "ilink1",
  "ilink2",
  "eret",
  "status_l1",
  "status_l2",
  "erstatus"
};


/* Mapping between the general-purpose registers in `struct sigcontext' format
 * and GDB's register cache layout.
 *
 * arc_linux_sc_reg_offset[i] is the sigcontext offset of GDB regnum `i'.
 */

/* From <asm/sigcontext.h>.  */
static const int arc_linux_sc_reg_offset[ARC_NR_REGS] = {
  23 * BYTES_IN_REGISTER,	/* r0       */
  22 * BYTES_IN_REGISTER,	/* r1       */
  21 * BYTES_IN_REGISTER,	/* r2       */
  20 * BYTES_IN_REGISTER,	/* r3       */
  19 * BYTES_IN_REGISTER,	/* r4       */
  18 * BYTES_IN_REGISTER,	/* r5       */
  17 * BYTES_IN_REGISTER,	/* r6       */
  16 * BYTES_IN_REGISTER,	/* r7       */
  15 * BYTES_IN_REGISTER,	/* r8       */
  14 * BYTES_IN_REGISTER,	/* r9       */
  13 * BYTES_IN_REGISTER,	/* r10      */
  12 * BYTES_IN_REGISTER,	/* r11      */
  11 * BYTES_IN_REGISTER,	/* r12      */
  REGISTER_NOT_PRESENT,		/* r13      */
  REGISTER_NOT_PRESENT,		/* r14      */
  REGISTER_NOT_PRESENT,		/* r15      */
  REGISTER_NOT_PRESENT,		/* r16      */
  REGISTER_NOT_PRESENT,		/* r17      */
  REGISTER_NOT_PRESENT,		/* r18      */
  REGISTER_NOT_PRESENT,		/* r19      */
  REGISTER_NOT_PRESENT,		/* r20      */
  REGISTER_NOT_PRESENT,		/* r21      */
  REGISTER_NOT_PRESENT,		/* r22      */
  REGISTER_NOT_PRESENT,		/* r23      */
  REGISTER_NOT_PRESENT,		/* r24      */
  REGISTER_NOT_PRESENT,		/* r25      */
  10 * BYTES_IN_REGISTER,	/* r26      */
  2 * BYTES_IN_REGISTER,	/* bta      */
  3 * BYTES_IN_REGISTER,	/* lp_start */
  4 * BYTES_IN_REGISTER,	/* lp_end   */
  5 * BYTES_IN_REGISTER,	/* lp_count */
  6 * BYTES_IN_REGISTER,	/* status32 */
  8 * BYTES_IN_REGISTER,	/* blink    */
  9 * BYTES_IN_REGISTER,	/* fp       */
  1 * BYTES_IN_REGISTER,	/* sp       */
  REGISTER_NOT_PRESENT,		/* efa      */
  7 * BYTES_IN_REGISTER,	/* ret      */
  REGISTER_NOT_PRESENT,		/* orig_r8  */
  REGISTER_NOT_PRESENT		/* stop_pc  */
};


/* arcompact_linux_core_reg_offsets[i] is the offset in the .reg section of GDB
 * regnum i.
 *
 * From include/asm-arc/user.h in the ARC Linux sources.
 */

static const int arcompact_linux_core_reg_offsets[ARC_NR_REGS] = {
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
  39 * BYTES_IN_REGISTER,	/* r13      */
  38 * BYTES_IN_REGISTER,	/* r14      */
  37 * BYTES_IN_REGISTER,	/* r15      */
  36 * BYTES_IN_REGISTER,	/* r16      */
  35 * BYTES_IN_REGISTER,	/* r17      */
  34 * BYTES_IN_REGISTER,	/* r18      */
  33 * BYTES_IN_REGISTER,	/* r19      */
  32 * BYTES_IN_REGISTER,	/* r20      */
  31 * BYTES_IN_REGISTER,	/* r21      */
  30 * BYTES_IN_REGISTER,	/* r22      */
  29 * BYTES_IN_REGISTER,	/* r23      */
  28 * BYTES_IN_REGISTER,	/* r24      */
  27 * BYTES_IN_REGISTER,	/* r25      */
  9 * BYTES_IN_REGISTER,	/* r26      */
  1 * BYTES_IN_REGISTER,	/* bta      */
  2 * BYTES_IN_REGISTER,	/* lp_start */
  3 * BYTES_IN_REGISTER,	/* lp_end   */
  4 * BYTES_IN_REGISTER,	/* lp_count */
  5 * BYTES_IN_REGISTER,	/* status32 */
  7 * BYTES_IN_REGISTER,	/* blink    */
  8 * BYTES_IN_REGISTER,	/* fp       */
  25 * BYTES_IN_REGISTER,	/* sp       */
  REGISTER_NOT_PRESENT,		/* efa      */
  6 * BYTES_IN_REGISTER,	/* ret      */
  24 * BYTES_IN_REGISTER,	/* orig_r8  */
  40 * BYTES_IN_REGISTER,	/* stop_pc  */
};


/* -------------------------------------------------------------------------- */
/*                               external functions                           */
/* -------------------------------------------------------------------------- */

/* FIXME: this should be in a header file! */

extern struct arcDisState arcAnalyzeInstr (bfd_vma address,
					   disassemble_info * info);


/* -------------------------------------------------------------------------- */
/*                               forward declarations                         */
/* -------------------------------------------------------------------------- */

static int arc_linux_binutils_reg_to_regnum (struct gdbarch *gdbarch,
					     int reg);


/* -------------------------------------------------------------------------- */
/*                               local macros                                 */
/* -------------------------------------------------------------------------- */

#define PRINT(regnum) \
    default_print_registers_info (gdbarch, file, frame, regnum, all)


/* -------------------------------------------------------------------------- */
/*                               local functions                              */
/* -------------------------------------------------------------------------- */

/* Returns TRUE if the instruction at PC is a branch (of any kind).
 *   *fall_thru is set to the address of the next insn.
 *   *target    is set to the branch target.
 */
static int
next_pc (CORE_ADDR pc, CORE_ADDR * fall_thru, CORE_ADDR * target)
{
  struct regcache *regcache = get_current_regcache ();
  struct disassemble_info di;
  struct arcDisState instr;
  int two_targets = FALSE;

  /* Why on earth do we need to do this each time we call next_pc! */
  arc_initialize_disassembler (gdbarch, &di);

  /* so what is the instruction at the given pc? */
  instr = arcAnalyzeInstr (pc, &di);

  /* by default, the next instruction is the one immediately after the one at pc */
  *fall_thru = pc + instr.instructionLen;

  DEBUG
    ("--- next_pc(%x) = %x, isBranch = %d, tcnt = %d [%x], flow = %s (%d), "
     "reg for indirect jump = %d, nullifyMode = %s\n", (unsigned int) pc,
     (unsigned int) *fall_thru, instr.isBranch, instr.tcnt, instr.targets[0],
     (instr.flow == direct_jump
      || instr.flow == direct_call) ? "direct" : "indirect", instr.flow,
     instr.register_for_indirect_jump,
     ((instr.nullifyMode ==
       (char) BR_exec_always) ? "delay slot" : "no delay"));

  /* OK, it's a branch */
  if ((int) instr.isBranch)
    {
      two_targets = TRUE;

      /* if it's a direct jump or call, the destination address is encoded in
       * the instruction, so we got it by disassembling the instruction;
       * otherwise, it's an indirect jump to the address held in the register
       * named in the instruction, so we must read that register
       */
      if (instr.flow == direct_jump || instr.flow == direct_call)
	*target = (CORE_ADDR) instr.targets[0];
      else
	regcache_cooked_read_unsigned (regcache,
				       arc_linux_binutils_reg_to_regnum
				       (current_gdbarch,
					instr.register_for_indirect_jump),
				       target);

      /* for instructions with delay slots, the fall thru is not the instruction
       * immediately after the branch instruction, but the one after that
       */
      if (instr.nullifyMode == (char) BR_exec_always)
	{
	  struct arcDisState instr_d = arcAnalyzeInstr (*fall_thru, &di);

	  *fall_thru += instr_d.instructionLen;
	}
    }


  /* zero-overhead loops:
   *    if (STATUS32[L] == 0 && next_pc == lp_end && lp_count > 1)
   *        next_pc = lp_start;
   */
  {
    unsigned int lp_end, lp_start, lp_count, status32;

    regcache_cooked_read_unsigned (regcache, ARC_LP_START_REGNUM, &lp_start);
    regcache_cooked_read_unsigned (regcache, ARC_LP_END_REGNUM, &lp_end);
    regcache_cooked_read_unsigned (regcache, ARC_LP_COUNT_REGNUM, &lp_count);
    regcache_cooked_read_unsigned (regcache, ARC_STATUS32_REGNUM, &status32);

    if (!(status32 & STATUS32_L) && *fall_thru == lp_end && lp_count > 1)
      {
	/* the instruction is in effect a jump back to the start of the loop */
	two_targets = TRUE;
	*target = lp_start;
      }
  }

  return two_targets;
}


/* Extract the register values found in the ABI GREGSET, storing their values in
 * regcache.
 */
static void
arcompact_linux_supply_gregset (struct regcache *regcache,
				int regnum, const void *gregs, size_t size)
{
  const bfd_byte *buf = gregs;
  unsigned int reg;

  for (reg = 0; reg < ELEMENTS_IN_ARRAY (arcompact_linux_core_reg_offsets);
       reg++)
    {
      if (arcompact_linux_core_reg_offsets[reg] != REGISTER_NOT_PRESENT)
	regcache_raw_supply (regcache,
			     (int) reg,
			     buf + arcompact_linux_core_reg_offsets[reg]);
    }
}


/* Return whether the frame preceding next_frame corresponds to a GNU/Linux
 * sigtramp routine.
 */
static int
is_linux_sigtramp (struct frame_info *next_frame)
{
  /* find the PC for that previous frame */
  CORE_ADDR pc = frame_pc_unwind (next_frame);
  gdb_byte buf[SIGTRAMP_INSNS_LENGTH];

  /* read the memory at that PC (this gives us the code without any s/w
   * breakpoints that may have been set in it)
   */
  if (!safe_frame_unwind_memory
      (next_frame, pc, buf, (int) SIGTRAMP_INSNS_LENGTH))
    /* failed to unwind frame */
    return FALSE;

  /* is that code the sigtramp instruction sequence? */
  if (memcmp (buf, arc_sigtramp_insns, SIGTRAMP_INSNS_LENGTH) == 0)
    return TRUE;

  /* no - look one instruction earlier in the code... */
  if (!safe_frame_unwind_memory
      (next_frame, pc - 4, buf, (int) SIGTRAMP_INSNS_LENGTH))
    /* failed to unwind frame */
    return FALSE;

  if (memcmp (buf, arc_sigtramp_insns, SIGTRAMP_INSNS_LENGTH) == 0)
    return TRUE;

  return FALSE;
}


/* Assuming next_frame is a frame following a GNU/Linux sigtramp
 * routine, return the address of the associated sigcontext structure.
 */
static CORE_ADDR
linux_sigcontext_addr (struct frame_info *next_frame)
{
  gdb_byte buf[4];

  frame_unwind_register (next_frame, ARC_SP_REGNUM, buf);

  return (CORE_ADDR) extract_unsigned_integer (buf, 4);
}


/* Returns 0, 1, or -1:
 *    0 means the register is not in the group.
 *    1 means the register is in the group.
 *   -1 means the tdep has nothing to say about this register and group.
 */
static int
register_reggroup_p (int regnum, struct reggroup *group)
{
  if (system_reggroup)
    {
      if (regnum == ARC_ORIG_R8_REGNUM ||
	  regnum == ARC_EFA_REGNUM ||
	  regnum == ARC_ERET_REGNUM || regnum == ARC_ERSTATUS_REGNUM)
	return 1;
    }
  else if (group == general_reggroup)
    {
      if (regnum == ARC_RET_REGNUM)
	return 0;

      return (regnum == ARC_STATUS32_REGNUM) ? 0 : 1;
    }

  /* let the caller sort it out! */
  return -1;
}


/* -------------------------------------------------------------------------- */
/*                       local functions called from gdb                      */
/* -------------------------------------------------------------------------- */

/* The Linux kernel stores only one of (ilink1, ilink2, eret). This is stored
 * in the ret "register".  ilink1 is stored when the kernel has been entered
 * because of a level 1 interrupt, etc.
 *
 * Same story for (status_l1, status_l2, erstatus).
 *
 * This disambiguity has been fixed by adding orig_r8 to pt_regs.
 *
 * FIXME: what is pt_regs????
 *
 * It will take the following values -
 *    1. if an exception of any kind occurs then orig_r8 >= 0
 *    2. Interrupt level 1 : orig == -1
 *    3. Interrupt level 2 : orig == -2
 *
 * Registers whose value we don't know are given the value zero.
 *
 * The only pseudo-registers are:
 *
 *     ARC_ILINK1_REGNUM
 *     ARC_ILINK2_REGNUM
 *     ARC_ERET_REGNUM
 *     ARC_STATUS32_L1_REGNUM
 *     ARC_STATUS32_L2_REGNUM
 *     ARC_ERSTATUS_REGNUM
 */
static void
arc_linux_pseudo_register_read (struct gdbarch *gdbarch,
				struct regcache *regcache,
				int gdb_regno, gdb_byte * buf)
{
  unsigned int *contents = (unsigned int *) buf;
  unsigned int status32, ret;
  int orig_r8;

  regcache_cooked_read (regcache, ARC_ORIG_R8_REGNUM, (gdb_byte *) & orig_r8);

  if (gdb_regno == ARC_ILINK1_REGNUM ||
      gdb_regno == ARC_ILINK2_REGNUM || gdb_regno == ARC_ERET_REGNUM)
    {
      regcache_cooked_read (regcache, ARC_RET_REGNUM, (gdb_byte *) & ret);

      if (gdb_regno == ARC_ILINK1_REGNUM)
	*contents = ((orig_r8 == -1) ? ret : 0);
      else if (gdb_regno == ARC_ILINK2_REGNUM)
	*contents = ((orig_r8 == -2) ? ret : 0);
      else			// (gdb_regno == ARC_ERET_REGNUM)
	*contents = ((orig_r8 >= 0) ? ret : 0);

    }
  else if (gdb_regno == ARC_STATUS32_L1_REGNUM ||
	   gdb_regno == ARC_STATUS32_L2_REGNUM ||
	   gdb_regno == ARC_ERSTATUS_REGNUM)
    {
      regcache_cooked_read (regcache, ARC_STATUS32_REGNUM,
			    (gdb_byte *) & status32);

      if (gdb_regno == ARC_STATUS32_L1_REGNUM)
	*contents = ((orig_r8 == -1) ? status32 : 0);
      else if (gdb_regno == ARC_STATUS32_L2_REGNUM)
	*contents = ((orig_r8 == -2) ? status32 : 0);
      else			// (gdb_regno == ARC_ERSTATUS_REGNUM)
	*contents = ((orig_r8 >= 0) ? status32 : 0);
    }
  else
    internal_error (__FILE__, __LINE__,
		    _("%s: bad pseudo register number (%d)"), __FUNCTION__,
		    gdb_regno);
}


static void
arc_linux_pseudo_register_write (struct gdbarch *gdbarch,
				 struct regcache *regcache,
				 int gdb_regno, const gdb_byte * buf)
{
  /* none of our pseudo-regs are writable */
  internal_error (__FILE__, __LINE__,
		  _("%s: pseudo-registers are unwritable"), __FUNCTION__);
}


/*
 * mapping from binutils/gcc register number to GDB register number ("regnum")
 *
 * N.B. registers such as ARC_FP_REGNUM, ARC_SP_REGNUM, etc., actually have
 *      different GDB register numbers in the arc-elf32 and arc-linux-uclibc
 *      configurations of the ARC gdb.
 *
 *      IS THIS TRUE??????
 */
static int
arc_linux_binutils_reg_to_regnum (struct gdbarch *gdbarch, int reg)
{
  /* from gcc/config/arc/arc.h */

  if (reg >= 0 && reg <= 26)
    return reg;
  else if (reg == ARC_ABI_FRAME_POINTER)	/* fp */
    return ARC_FP_REGNUM;
  else if (reg == ARC_ABI_STACK_POINTER)	/* sp */
    return ARC_SP_REGNUM;
  else if (reg == 29)		/* ilink1 */
    return ARC_ILINK1_REGNUM;
  else if (reg == 30)		/* ilink2 */
    return ARC_ILINK2_REGNUM;
  else if (reg == 31)		/* blink */
    return ARC_BLINK_REGNUM;
  else if (IS_EXTENSION_CORE_REGISTER (reg))	/* reserved */
    ;
  else if (reg == 60)		/* lp_count */
    return ARC_LP_COUNT_REGNUM;
#if 0
  else if (reg == 61)		/* reserved */
    ;
  else if (reg == 62)		/* no such register */
    ;
  else if (reg == 63)		/* PCL */
    ;
#endif

  warning (_("unmapped register #%d encountered"), reg);
  return -1;
}


/*
 * print registers in the correct order.
 *
 * Why not have the regnums in the right order in the first place?
 * Because some of the registers have to be pseudo-registers because of
 * the way the kernel is written, and because gdb assumes that
 * pseudo-registers have regnums greater than real register regnums.
 */
static void
arc_linux_print_registers_info (struct gdbarch *gdbarch,
				struct ui_file *file,
				struct frame_info *frame, int regnum, int all)
{
  if (regnum >= 0)
    PRINT (regnum);
  else				/* if regnum < 0, print all registers */
    {
      int i;

      /* r0 .. r26 */
      for (i = 0; i <= 26; i++)
	PRINT (i);

      PRINT (ARC_FP_REGNUM);
      PRINT (ARC_SP_REGNUM);
      PRINT (ARC_ILINK1_REGNUM);
      PRINT (ARC_ILINK2_REGNUM);
      PRINT (ARC_BLINK_REGNUM);
      PRINT (ARC_LP_COUNT_REGNUM);

      /* now the aux registers */

      PRINT (ARC_BTA_REGNUM);
      PRINT (ARC_LP_START_REGNUM);
      PRINT (ARC_LP_END_REGNUM);
      PRINT (ARC_EFA_REGNUM);
      PRINT (ARC_ERET_REGNUM);
      PRINT (ARC_STATUS32_L1_REGNUM);
      PRINT (ARC_STATUS32_L2_REGNUM);
      PRINT (ARC_ERSTATUS_REGNUM);

      /* show the pc */
      PRINT (ARC_STOP_PC_REGNUM);
    }
}


/* return the name of the given register */
static const char *
arc_linux_register_name (struct gdbarch *gdbarch, int gdb_regno)
{
  gdb_assert (ELEMENTS_IN_ARRAY (register_names) ==
	      (unsigned int) (ARC_NR_REGS + ARC_NR_PSEUDO_REGS));

  /* Oh, for a proper language with array bounds checking, like Ada... */
  gdb_assert (0 <= gdb_regno
	      && gdb_regno < (int) ELEMENTS_IN_ARRAY (register_names));

  return register_names[gdb_regno];
}


/* determine whether the given register is read-only */
static int
arc_linux_cannot_store_register (struct gdbarch *gdbarch, int gdb_regno)
{
  if (gdb_regno == ARC_EFA_REGNUM ||
      gdb_regno == ARC_ERET_REGNUM ||
      gdb_regno == ARC_STATUS32_L1_REGNUM ||
      gdb_regno == ARC_STATUS32_L2_REGNUM ||
      gdb_regno == ARC_ERSTATUS_REGNUM ||
      gdb_regno == ARC_ILINK1_REGNUM || gdb_regno == ARC_ILINK2_REGNUM)
    {
      /* No warning should be printed.  arc_cannot_store_register being
         called does not imply that someone is actually writing to regnum.  */

      /* warning(_("writing to read-only register: %s"), gdbarch_register_name(gdbarch, gdb_regno)); */
      return 1;
    }

  return 0;
}


/* this is called with insert_breakpoints_p = 1 before single-stepping and
   with insert_breakpoints_p = 0 after the step */

/*      Makis in 6.8 this is used to add breakpoints only and not remove them so remove 
        functionality for now. This needs monitoring in case we see problems. 
        This code is now completely removed as it break the way the higher layers are
        using breakpoints. It now uses insert_single_step_breakpoint() function this code 
        needs to be validated */

static int
arc_linux_software_single_step (struct frame_info *frame)
{
  CORE_ADDR fall_thru, branch_target;
  CORE_ADDR pc = read_pc ();
  int two_breakpoints = next_pc (pc, &fall_thru, &branch_target);

  insert_single_step_breakpoint (fall_thru);

  if (two_breakpoints)
    {
      if ((pc != branch_target) && (fall_thru != branch_target))
	insert_single_step_breakpoint (branch_target);
    }

  return 1;			// returns always true for now
}


/* Set the program counter for process PTID to PC.  */
static void
arc_linux_write_pc (struct regcache *regcache, CORE_ADDR pc)
{
  regcache_cooked_write_unsigned (regcache, ARC_PC_REGNUM, pc);

  /* We must be careful with modifying the program counter.  If we
   * just interrupted a system call, the kernel might try to restart
   * it when we resume the inferior.  On restarting the system call,
   * the kernel will try backing up the program counter even though it
   * no longer points at the system call.  This typically results in a
   * SIGSEGV or SIGILL.  We can prevent this by writing `-1' in the
   * "orig_r8" pseudo-register.
   *
   * Note that "orig_r8" is saved when setting up a dummy call frame.
   * This means that it is properly restored when that frame is
   * popped, and that the interrupted system call will be restarted
   * when we resume the inferior on return from a function call from
   * within GDB.  In all other cases the system call will not be
   * restarted.
   */

  // FIXME: why -3 and not -1? -3 does not appear to be a defined valued for
  //        orig_r8 (i.e. -2, -1 or >= 0) - perhaps it means "none of these"?
  regcache_cooked_write_signed (regcache, ARC_ORIG_R8_REGNUM, -3);
}


/* See the comments for SKIP_SOLIB_RESOLVER at the top of infrun.c.
 *
 * This is called on every single step through the PLT and runtime resolver.
 *
 * This function:
 *    1) decides whether a PLT has sent us into the linker to resolve
 *       a function reference, and
 *    2) if so, tells us where to set a temporary breakpoint that will
 *       trigger when the dynamic linker is done.
 */
static CORE_ADDR
arc_linux_skip_solib_resolver (struct gdbarch *gdbarch, CORE_ADDR pc)
{
  /* For uClibc 0.9.26.
   *
   *   An unresolved PLT entry points to "__dl_linux_resolve", which calls
   *   "__dl_linux_resolver" to do the resolving and then eventually jumps to
   *   the function.
   *
   *   So we look for the symbol `_dl_linux_resolver', and if we are there,
   *   gdb sets a breakpoint at the return address, and continues.
   */

  /* lookup_minimal_symbol didn't work, for some reason.  */
  struct symbol *resolver = lookup_symbol_global ("_dl_linux_resolver", 0,
						  0
						  /* Makis: Warning added this as API changed in 6.8 */
						  , VAR_DOMAIN, 0);

  DEBUG ((resolver == NULL) ? "--- %s : pc = %x, no resolver found"
	 : "--- %s : pc = %x, resolver at %x\n",
	 __FUNCTION__,
	 (unsigned int) pc,
	 (unsigned int) ((resolver == NULL) ? 0 :
			 BLOCK_START (SYMBOL_BLOCK_VALUE (resolver))));

  if ((resolver != NULL)
      && (BLOCK_START (SYMBOL_BLOCK_VALUE (resolver))) == pc)
    /* find the return address */
    return frame_pc_unwind (get_current_frame ());

  /* no breakpoint required */
  return 0;
}


/* Call the right architecture variant's supply_gregset function.  For now, we
 * have only ARCompact.
 */
static void
arc_linux_supply_gregset (const struct regset *regset,
			  struct regcache *regcache,
			  int regnum, const void *gregs, size_t size)
{
  arcompact_linux_supply_gregset (regcache, regnum, gregs, size);
}


/* Functions for handling core files.
 * The first element is a parameter to pass the rest of the functions.  We
 * don't need it.
 * supply_gregset is for reading the core file.
 * collect_regset, which we haven't defined, would be for writing the core
 * file.
 */

static const struct regset *
arc_linux_regset_from_core_section (struct gdbarch *core_arch,
				    const char *sect_name, size_t sect_size)
{
  static const struct regset arc_linux_gregset = {
    NULL,			// descr
    arc_linux_supply_gregset,	// supply_regset
    NULL,			// collect_regset
    NULL			// arch
  };

  if (strcmp (sect_name, ".reg") == 0)
    return &arc_linux_gregset;

  return NULL;
}


/* initialize for this ABI */
static void
arc_linux_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Fill in target-dependent info in ARC-private structure. */

  tdep->is_sigtramp = is_linux_sigtramp;
  tdep->sigcontext_addr = linux_sigcontext_addr;
  tdep->sc_reg_offset = arc_linux_sc_reg_offset;
  tdep->sc_num_regs = ELEMENTS_IN_ARRAY (arc_linux_sc_reg_offset);
  tdep->pc_regnum_in_sigcontext = ARC_RET_REGNUM;

  if (info.byte_order == BFD_ENDIAN_BIG)
    tdep->breakpoint_instruction = be_breakpoint_instruction;
  else
    tdep->breakpoint_instruction = breakpoint_instruction;
  tdep->breakpoint_size = (unsigned int) sizeof (breakpoint_instruction);

  tdep->register_reggroup_p = register_reggroup_p;

  tdep->lowest_pc = 0x74;	// FIXME: why this?
  tdep->processor_variant_info = NULL;

  /* Pass target-dependent info to gdb. */

  /* ARC_NR_REGS and ARC_NR_PSEUDO_REGS are defined in the tm.h configuration file */
  set_gdbarch_pc_regnum (gdbarch, ARC_STOP_PC_REGNUM);
  set_gdbarch_num_regs (gdbarch, ARC_NR_REGS);
  set_gdbarch_num_pseudo_regs (gdbarch, ARC_NR_PSEUDO_REGS);
  set_gdbarch_print_registers_info (gdbarch, arc_linux_print_registers_info);
  set_gdbarch_register_name (gdbarch, arc_linux_register_name);
  set_gdbarch_cannot_store_register (gdbarch,
				     arc_linux_cannot_store_register);
  set_gdbarch_dwarf2_reg_to_regnum (gdbarch,
				    arc_linux_binutils_reg_to_regnum);

  set_gdbarch_decr_pc_after_break (gdbarch, 0);
  set_gdbarch_software_single_step (gdbarch, arc_linux_software_single_step);
  set_gdbarch_write_pc (gdbarch, arc_linux_write_pc);
  set_gdbarch_pseudo_register_read (gdbarch, arc_linux_pseudo_register_read);
  set_gdbarch_pseudo_register_write (gdbarch,
				     arc_linux_pseudo_register_write);
  set_gdbarch_regset_from_core_section (gdbarch,
					arc_linux_regset_from_core_section);
  set_gdbarch_skip_solib_resolver (gdbarch, arc_linux_skip_solib_resolver);

  /* GNU/Linux uses SVR4-style shared libraries. */
  set_solib_svr4_fetch_link_map_offsets (gdbarch,
					 svr4_ilp32_fetch_link_map_offsets);
}


/* -------------------------------------------------------------------------- */
/*                               externally visible functions                 */
/* -------------------------------------------------------------------------- */

void
_initialize_arc_linux_tdep (void)
{
  /* register a handler with gdb for the Linux O/S ABI variant for the ARC
   * processor architecture, providing an initialization function;
   *
   * 'bfd_arch_arc' is an enumeration value specifically denoting the ARC
   *                architecture
   */
  gdbarch_register_osabi (bfd_arch_arc, 0,	// machine (irrelevant)
			  GDB_OSABI_LINUX, arc_linux_init_abi);
}
