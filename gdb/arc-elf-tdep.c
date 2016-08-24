/* Target dependent code for ARC arhitecture, for GDB.

   Copyright 2005-2016 Free Software Foundation, Inc.
   Contributed by Synopsys Inc.

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

/* system header files */
#include <string.h>

/* gdb header files */
#include "defs.h"
#include "inferior.h"
#include "gdbcmd.h"
#include "regcache.h"
#include "reggroups.h"
#include "observer.h"
#include "objfiles.h"
#include "osabi.h"
#include "arch-utils.h"
#include "opcode/arc.h"
#include "opcodes/arc-dis.h"

/* ARC header files */
#include "arc-tdep.h"

#ifdef WITH_SIM
/* ARC simulator header files */
#include "sim/arc/arc-sim-registers.h"
#endif


/* -------------------------------------------------------------------------- */
/*                               local types                                  */
/* -------------------------------------------------------------------------- */

typedef struct
{
  struct gdbarch *gdbarch;
  struct ui_file *file;
  struct frame_info *frame;
} PrintData;


/* -------------------------------------------------------------------------- */
/*                               local data                                   */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*		   ARC specific GDB architectural functions		      */
/*									      */
/* Functions are listed in the order they are used in arc_elf_init_osabi.     */
/* -------------------------------------------------------------------------- */

/*! Determine whether a register can be read.

    This function relies on tdep->reginfo, since numbers of individual
    registers are not globally same and can change from one run to another.

    @param[in] gdbarch  The current GDB architecture.
    @param[in] regnum   The register of interest.
    @return             Non-zero (TRUE) if we _cannot_ read the register,
                        false otherwise. */
static int
arc_elf_cannot_fetch_register (struct gdbarch *gdbarch, int regnum)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Assume that register is readable if there is no information. */
  if (regnum < tdep->reginfo_sz)
    return !tdep->reginfo[regnum].readable;
  else
    return FALSE;
}	/* arc_elf_cannot_store_register () */


/*! Determine whether a register can be written.

    This function relies on tdep->reginfo, since numbers of individual
    registers are not globally same and can change from one run to another.

    @param[in] gdbarch  The current GDB architecture.
    @param[in] regnum   The register of interest.
    @return             Non-zero (TRUE) if we _cannot_ write the register,
                        false otherwise. */
static int
arc_elf_cannot_store_register (struct gdbarch *gdbarch, int regnum)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Assume that register is writable if there is no info. */
  if (regnum < tdep->reginfo_sz)
    return !tdep->reginfo[regnum].writable;
  else
    return FALSE;
}	/* arc_elf_cannot_store_register () */


/*! Get breakpoint which is appropriate for address at which it is to be set.

    For ARC ELF, breakpoint uses the 16-bit BRK_S instruction, which is 0x7fff
    (little endian) or 0xff7f (big endian). We used to insert BRK_S even
    instead of 32-bit instructions, which works mostly ok, unless breakpoint is
    inserted into delay slot instruction. In this case if branch is taken BLINK
    value will be set to address of instruction after delay slot, however if we
    replaced 32-bit instruction in delay slot with 16-bit long BRK_S, then
    BLINK value will have an invalid value - it will point to the address after
    the BRK_S (which was there at the moment of branch execution) while it
    should point to the address after the 32-bit long instruction. To avoid
    such issues this function disassembles instruction at target location and
    evaluates it value.

    ARC 600 supports only 16-bit BRK_S.

    NB:  Baremetal GDB uses BRK[_S], while user-space GDB uses TRAP_S. BRK[_S]
    is much better because it doesn't commit unlike TRAP_S, so it can be set in
    delay slots; however it cannot be used in user-mode, hence usage of TRAP_S
    in GDB for user-space.

    @param[in]     gdbarch  Current GDB architecture
    @param[in,out] pcptr    Pointer to the PC where we want to place a
                            breakpoint
    @param[out]    lenptr   Number of bytes used by the breakpoint.
    @return                 The byte sequence of a breakpoint instruction. */
static const unsigned char *
arc_elf_breakpoint_from_pc (struct gdbarch *gdbarch, CORE_ADDR * pcptr,
			    int *lenptr)
{
  static const unsigned char brk_s_be[] = { 0x7f, 0xff };
  static const unsigned char brk_s_le[] = { 0xff, 0x7f };
  static const unsigned char brk_be[] = { 0x25, 0x6f, 0x00, 0x3f };
  static const unsigned char brk_le[] = { 0x6f, 0x25, 0x3f, 0x00 };
  /* Note that BRK for little endian is in middle-endian encoding. */

  struct arc_instruction insn;
  arc_insn_decode (gdbarch, *pcptr, &insn);


  /* Replace 16-bit instruction BRK_S, replace 32-bit instructions with BRK.
   * LIMM is part of instructionLen, so it can be either 4 or 8 bytes. */
  if (insn.length == 4 && !arc_mach_is_arc600(gdbarch))
    {
      *lenptr = sizeof(brk_le);
      return (gdbarch_byte_order (gdbarch) == BFD_ENDIAN_BIG)
	? brk_be : brk_le;
    }
  else
    {
      *lenptr = sizeof(brk_s_le);
      return (gdbarch_byte_order (gdbarch) == BFD_ENDIAN_BIG)
	? brk_s_be : brk_s_le;
    }
}	/* arc_elf_breakpoint_from_pc () */


#ifdef WITH_SIM
/*! Map GDB registers to ARC simulator registers

    The ARC CGEN based simulator has its own register numbering. This function
    provides the necessary mapping

    The simulator does not have a simple numbering. Rather registers are known
    by a class and a number.

    That function will work properly only with ARCompact compatible register
    set. gdbarch is not part of argument list, so it's not possible to get
    information for current architecture (other that horrific global variables.
    Just don't 'set tdesc filename' with 'target sim' and everything should be
    fine.

    @param[in]  gdb_regnum  The GDB register number to map
    @param[out] sim_regnum  The corresponding simulator register
    @param[out] reg_class   The corresponding ARC register class */
static void
arc_elf_sim_map (int                gdb_regnum,
		 int*               sim_regnum,
		 ARC_RegisterClass *reg_class)
{
  if ((0 <= gdb_regnum) && (gdb_regnum <= ARC_LP_COUNT_REGNUM))
    {
      /* All core registers apart from reserved, LIMM and PCL have an
	 identity mapping. */
      *sim_regnum = gdb_regnum;
      *reg_class  = ARC_CORE_REGISTER;
    }
  else
    {
      switch (gdb_regnum)
	{
	case ARC_RESERVED_REGNUM:
	case ARC_LIMM_REGNUM:
	case ARC_PCL_REGNUM:
	  /* Unsupported core registers */
	  *sim_regnum  = -1;
	  *reg_class = ARC_UNKNOWN_REGISTER;
	  break;

	case ARC_PC_REGNUM:
	  /* sim_regnum irrelevant. */
	  *reg_class = ARC_PROGRAM_COUNTER;
	  break;

	case ARC_LP_START_REGNUM:
	  *sim_regnum = ARC_AUX_LP_START_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_LP_END_REGNUM:
	  *sim_regnum = ARC_AUX_LP_END_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_STATUS32_REGNUM:
	  *sim_regnum = ARC_AUX_STATUS32_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_STATUS32_L1_REGNUM:
	  *sim_regnum = ARC_AUX_STATUS32_L1_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_STATUS32_L2_REGNUM:
	  *sim_regnum = ARC_AUX_STATUS32_L2_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_AUX_IRQ_LV12_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_IRQ_LV12_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_AUX_IRQ_LEV_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_IRQ_LEV_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_AUX_IRQ_HINT_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_IRQ_HINT_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_ERET_REGNUM:
	  *sim_regnum = ARC_AUX_ERET_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_ERBTA_REGNUM:
	  *sim_regnum = ARC_AUX_ERBTA_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_ERSTATUS_REGNUM:
	  *sim_regnum = ARC_AUX_ERSTATUS_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_ECR_REGNUM:
	  *sim_regnum = ARC_AUX_ECR_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_EFA_REGNUM:
	  *sim_regnum = ARC_AUX_EFA_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_ICAUSE1_REGNUM:
	  *sim_regnum = ARC_AUX_ICAUSE1_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_ICAUSE2_REGNUM:
	  *sim_regnum = ARC_AUX_ICAUSE2_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_AUX_IENABLE_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_IENABLE_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_AUX_ITRIGGER_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_ITRIGGER_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_BTA_REGNUM:
	  *sim_regnum = ARC_AUX_BTA_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_BTA_L1_REGNUM:
	  *sim_regnum = ARC_AUX_BTA_L1_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_BTA_L2_REGNUM:
	  *sim_regnum = ARC_AUX_BTA_L2_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_AUX_IRQ_PULSE_CANCEL_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_IRQ_PULSE_CANCEL_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_COMPATIBLE_AUX_IRQ_PENDING_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_IRQ_PENDING_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	default:
	  *sim_regnum  = -1;
	  *reg_class = ARC_UNKNOWN_REGISTER;
	}
    }
}	/* arc_elf_sim_map () */
#endif

/*! Writes values of PC register.

    In ARC PC register is a normal register so in most cases setting PC value
    is a straightforward process: debugger just writes PC value. However it
    gets trickier in case when current instruction is an instruction in delay
    slot. In this case CPU will execute instruction at current PC value, then
    will set PC to the current value of BTA register; also current instruction
    cannot be branch/jump and some of the other instruction types. Thus if
    debugger would try to just change PC value in this case, this instruction
    will get executed, but then core will "jump" to the original branch target.

    ARC provides following means to resolve this problem: - BTA register
    contains address where core should jump after executing instruction in
    delay slot - Bit DE in STATUS32 register indicates if current instruction
    is a delay slot instruction. This bit is writable by debug host, which
    allows debug host to prevent core from jumping after the delay slot
    instruction. At also works in another directions: setting this bit will
    make core to treat any current instructions as a delay slot instruction and
    to set PC to the current value of BTA register.

    To workaround issues with changing PC register while in delay slot
    instruction, debugger should check for the STATUS32.DE bit and reset it if
    it is set. No other change is required in this function. Most common case
    where this function might be required is calling inferior functions from
    debugger. Generic GDB logic handles this pretty well: current values of
    registers are stored, value of PC is changed (that is the job of this
    function), after inferior function is executed, GDB restores all registers,
    which also means that core is returned to its original state of being
    halted on delay slot instructions.

    This method is useless for ARC 600, because it doesn't have externally
    exposed BTA register. In the case of ARC 600 it is impossible to restore
    core to it's state in all occasions thus core should never be halted (from
    the perspective of debugger host) in the delay slot. */
static void
arc_elf_write_pc (struct regcache *regcache, CORE_ADDR new_pc)
{
    int de_bit;
    ULONGEST status32;
    struct gdbarch *gdbarch = get_regcache_arch(regcache);

    if (arc_debug)
      debug_printf ("arc-elf: Writing PC. New value=%s\n",
		    paddress (gdbarch, new_pc));

    regcache_cooked_write_unsigned (regcache, gdbarch_pc_regnum (gdbarch), new_pc);

    regcache_cooked_read_unsigned (regcache, gdbarch_ps_regnum (gdbarch), &status32);

    /* Mask for DE bit is 0x40 */
    if (status32 & 0x40)
      {
	if (arc_debug)
	  {
	    debug_printf ("arc-elf: Changing PC while in delay slot. Will "
			  "reset STATUS32.DE bit to zero. Value of STATUS32 "
			  "register is 0x%s\n",
			  phex (status32, BYTES_IN_REGISTER));
	  }

	/* Reset bit and write to the cache */
	status32 &= ~0x40;
	regcache_cooked_write_unsigned (regcache, gdbarch_ps_regnum (gdbarch), status32);
      }
}


/* -------------------------------------------------------------------------- */
/*                               externally visible functions                 */
/* -------------------------------------------------------------------------- */

/* Initialization specific to baremetal environment.  */

void
arc_elf_init_osabi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  if (arc_debug)
    debug_printf ("arc-elf: Baremetal OS/ABI initialization.\n");

  /* Fill in target-dependent info in ARC-private structure. */
  tdep->is_sigtramp = NULL;
  tdep->sigcontext_addr = NULL;
  tdep->sc_reg_offset = NULL;
  tdep->sc_num_regs = 0;

  /* Set up target dependent GDB architecture entries. */
  set_gdbarch_cannot_fetch_register (gdbarch, arc_elf_cannot_fetch_register);
  set_gdbarch_cannot_store_register (gdbarch, arc_elf_cannot_store_register);
  set_gdbarch_breakpoint_from_pc (gdbarch, arc_elf_breakpoint_from_pc);
  set_gdbarch_write_pc(gdbarch, arc_elf_write_pc);

  /* On ARC 600 BRK_S instruction advances PC, unlike other ARC cores. */
  if (arc_mach_is_arc600 (gdbarch))
    set_gdbarch_decr_pc_after_break (gdbarch, 2);

#ifdef WITH_SIM
  /* Provide the built-in simulator with a function that it can use to map
     from gdb register numbers to h/w register numbers */
  arc_set_register_mapping (&arc_elf_sim_map);
#endif

}	/* arc_gdbarch_osabi_init () */

/* vim: set sts=2 shiftwidth=2 ts=8: */
