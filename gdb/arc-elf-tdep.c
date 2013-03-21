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
#include "arch-utils.h"

/* ARC header files */
#include "arc-tdep.h"

/* ARC simulator header files */
#include "sim/arc/arc-sim-registers.h"


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
/* Functions are listed in the order they are used in arc_elf_init_abi.       */
/* -------------------------------------------------------------------------- */

/*! Determine whether a register can be read.

    An ELF target can see any register visible via the JTAG debug interface.

    @todo We'll need a more complex interface once the aux registers are
          defined via XML.

    @param[in] gdbarch  The current GDB architecture.
    @param[in] regnum   The register of interest.
    @return             Non-zero (TRUE) if we _cannot_ read the register,
                        false otherwise. */
static int
arc_elf_cannot_fetch_register (struct gdbarch *gdbarch, int regnum)
{
  /* Default is to be able to read regs, pick out the others explicitly. */
  switch (regnum)
    {
    case ARC_RESERVED_REGNUM:
    case ARC_LIMM_REGNUM:
      return 1;				/* Never readable. */

    default:
      return 0;				/* Readable via JTAG. */
    }
}	/* arc_elf_cannot_fetch_register () */


/*! Determine whether a register can be written.

    An ELF target can see any register visible via the JTAG debug interface.

    @todo We'll need a more complex interface once the aux registers are
          defined via XML.

    @param[in] gdbarch  The current GDB architecture.
    @param[in] regnum   The register of interest.
    @return             Non-zero (TRUE) if we _cannot_ write the register,
                        false otherwise. */
static int
arc_elf_cannot_store_register (struct gdbarch *gdbarch, int regnum)
{
  /* Default is to be able to write regs, pick out the others explicitly. */
  switch (regnum)
    {
    case ARC_RESERVED_REGNUM:
    case ARC_LIMM_REGNUM:
    case ARC_PCL_REGNUM:
      return 1;				/* Never writable. */

    default:
      return 0;				/* Writable via JTAG. */
    }
}	/* arc_elf_cannot_store_register () */


/*! Map GDB registers to ARC simulator registers

    The ARC CGEN based simulator has its own register numbering. This function
    provides the necessary mapping

    The simulator does not have a simple numbering. Rather registers are known
    by a class and a number.

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

	case ARC_AUX_LP_START_REGNUM:
	  *sim_regnum = ARC_AUX_LP_START_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_LP_END_REGNUM:
	  *sim_regnum = ARC_AUX_LP_END_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_STATUS32_REGNUM:
	  *sim_regnum = ARC_AUX_STATUS32_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_STATUS32_L1_REGNUM:
	  *sim_regnum = ARC_AUX_STATUS32_L1_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_STATUS32_L2_REGNUM:
	  *sim_regnum = ARC_AUX_STATUS32_L2_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_AUX_IRQ_LV12_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_IRQ_LV12_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_AUX_IRQ_LEV_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_IRQ_LEV_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_AUX_IRQ_HINT_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_IRQ_HINT_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_ERET_REGNUM:
	  *sim_regnum = ARC_AUX_ERET_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_ERBTA_REGNUM:
	  *sim_regnum = ARC_AUX_ERBTA_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_ERSTATUS_REGNUM:
	  *sim_regnum = ARC_AUX_ERSTATUS_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_ECR_REGNUM:
	  *sim_regnum = ARC_AUX_ECR_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_EFA_REGNUM:
	  *sim_regnum = ARC_AUX_EFA_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_ICAUSE1_REGNUM:
	  *sim_regnum = ARC_AUX_ICAUSE1_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_ICAUSE2_REGNUM:
	  *sim_regnum = ARC_AUX_ICAUSE2_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_AUX_IENABLE_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_IENABLE_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_AUX_ITRIGGER_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_ITRIGGER_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_BTA_REGNUM:
	  *sim_regnum = ARC_AUX_BTA_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_BTA_L1_REGNUM:
	  *sim_regnum = ARC_AUX_BTA_L1_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_BTA_L2_REGNUM:
	  *sim_regnum = ARC_AUX_BTA_L2_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_AUX_IRQ_PULSE_CANCEL_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_IRQ_PULSE_CANCEL_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	case ARC_AUX_AUX_IRQ_PENDING_REGNUM:
	  *sim_regnum = ARC_AUX_AUX_IRQ_PENDING_SIM_REGNUM;
	  *reg_class  = ARC_AUX_REGISTER;
	  break;

	default:
	  *sim_regnum  = -1;
	  *reg_class = ARC_UNKNOWN_REGISTER;
	}
    }
}	/* arc_elf_sim_map () */


/* -------------------------------------------------------------------------- */
/*                               externally visible functions                 */
/* -------------------------------------------------------------------------- */

/*! Function to determine the OSABI variant.

    Every target variant must define this appropriately.

    @return  The OSABI variant. */
enum gdb_osabi
arc_get_osabi (void)
{
  return GDB_OSABI_LINUX;

}	/* arc_get_osabi () */


/*! Function to initialize for this target variant.

    Every target variant must define this appropriately.

    @param[in,out] gdbarch  The gdbarch we are initializing. */
void
arc_gdbarch_osabi_init (struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Fill in target-dependent info in ARC-private structure. */
  tdep->is_sigtramp = NULL;
  tdep->sigcontext_addr = NULL;
  tdep->sc_reg_offset = NULL;
  tdep->sc_num_regs = 0;

  /* Set up target dependent GDB architecture entries. */
  set_gdbarch_cannot_fetch_register (gdbarch, arc_elf_cannot_fetch_register);
  set_gdbarch_cannot_store_register (gdbarch, arc_elf_cannot_store_register);

  /* Provide the built-in simulator with a function that it can use to map
     from gdb register numbers to h/w register numbers */
  arc_set_register_mapping (&arc_elf_sim_map);

}	/* arc_gdbarch_osabi_init () */
