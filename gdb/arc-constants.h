/* Target dependent constants for the ARC processor family

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
/*		       ARC Architecture Header for GDB                        */
/*		       ===============================                        */
/*                                                                            */
/*  Constants specific to the architecture, but not any particular OS.      */
/*                                                                            */
/******************************************************************************/

#ifndef ARC_CONSTANTS_H
#define ARC_CONSTANTS_H


#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

/* -------------------------------------------------------------------------- */
/* Local constants, which should really be in the XML file. */
/* -------------------------------------------------------------------------- */
/* Regsters */
#define ARC_BTA_REGNUM          27
#define ARC_LP_START_REGNUM     28
#define ARC_LP_END_REGNUM       29
#define ARC_LP_COUNT_REGNUM     30
#define ARC_STATUS32_REGNUM     31
#define ARC_BLINK_REGNUM        32
#define ARC_FP_REGNUM           33
#define ARC_SP_REGNUM           34
#define ARC_EFA_REGNUM          35
#define ARC_RET_REGNUM          36
#define ARC_ORIG_R8_REGNUM      37
#define ARC_STOP_PC_REGNUM      38

/* Pseudo-registers */
#define ARC_ILINK1_REGNUM       39
#define ARC_ILINK2_REGNUM       40
#define ARC_ERET_REGNUM         41
#define ARC_STATUS32_L1_REGNUM  42
#define ARC_STATUS32_L2_REGNUM  43
#define ARC_ERSTATUS_REGNUM     44


#define BYTES_IN_REGISTER  4
#define BYTES_IN_WORD      4
#define BYTES_IN_ADDRESS  (BYTES_IN_REGISTER)

/* 3 instructions before and after callee saves, and max number of saves;
   assume each is 4-byte inst. See arc_scan_prologue () for details. */
#define MAX_PROLOGUE_LENGTH   ((6 + (ARC_ABI_LAST_CALLEE_SAVED_REGISTER     \
				     - ARC_ABI_FIRST_CALLEE_SAVED_REGISTER  \
				     + 1)) * 4)


/* Debug support */

/*! Debug a function entry point.

    @todo. The use of ##__VA_ARGS__ is a GCC extension. */
#define ARC_ENTRY_DEBUG(fmt, ...)					\
  if (arc_debug)							\
    {									\
      fprintf_unfiltered (gdb_stdlog, "--- entered %s:%s(" fmt ")\n",	\
                          __FILE__, __FUNCTION__, ##__VA_ARGS__);	\
    }

#define ARC_PC_REGNUM       (gdbarch_pc_regnum       (target_gdbarch))
#define ARC_NUM_REGS        (gdbarch_num_regs        (target_gdbarch))
#define ARC_NUM_PSEUDO_REGS (gdbarch_num_pseudo_regs (target_gdbarch))
#define ARC_TOTAL_REGS      (ARC_NUM_REGS + ARC_NUM_PSEUDO_REGS)


#define ARC_MAX_CORE_REGS                      64
#define ARC_FIRST_EXTENSION_CORE_REGISTER      32
#define ARC_LAST_EXTENSION_CORE_REGISTER       59
#define ARC_NUM_EXTENSION_CORE_REGS            (ARC_LAST_EXTENSION_CORE_REGISTER - ARC_FIRST_EXTENSION_CORE_REGISTER + 1)
#define ARC_NUM_STANDARD_CORE_REGS             (ARC_MAX_CORE_REGS - ARC_NUM_EXTENSION_CORE_REGS)


#define IS_EXTENSION_CORE_REGISTER(hw_regnum)				\
  ((ARC_FIRST_EXTENSION_CORE_REGISTER <= (hw_regnum))			\
   && (hw_regnum) <= ARC_LAST_EXTENSION_CORE_REGISTER)


/* ARC processor ABI-related registers:
 *
 *    R0  .. R7 are the registers used to pass arguments in function calls
 *    R13 .. R26 are the callee-saved registers
 *    when a return value is stored in registers it is in either R0 or in the pair (R0,R1).
 */

#define ARC_ABI_GLOBAL_POINTER                 26
#define ARC_ABI_FRAME_POINTER                  27
#define ARC_ABI_STACK_POINTER                  28

#define ARC_ABI_FIRST_CALLEE_SAVED_REGISTER    13
#define ARC_ABI_LAST_CALLEE_SAVED_REGISTER     26

#define ARC_ABI_FIRST_ARGUMENT_REGISTER         0
#define ARC_ABI_LAST_ARGUMENT_REGISTER          7

#define ARC_ABI_RETURN_REGNUM                   0
#define ARC_ABI_RETURN_LOW_REGNUM               0
#define ARC_ABI_RETURN_HIGH_REGNUM              1

#define IS_ARGUMENT_REGISTER(hw_regnum)         (ARC_ABI_FIRST_ARGUMENT_REGISTER <= (hw_regnum) && (hw_regnum) <= ARC_ABI_LAST_ARGUMENT_REGISTER)


#define REGISTER_NOT_PRESENT   (-1)   /* special value for sc_reg_offset[reg] */

#endif /* ARC_CONSTANTS_H */
/******************************************************************************/
