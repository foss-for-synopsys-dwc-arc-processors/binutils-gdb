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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   --------------------------------------------------------------------------

   The comments within this file are also licensed under under the terms of
   the GNU Free Documentation License as published by the Free Software
   Foundation; either version 1.3 of the License, or (at your option) any
   later version. See the file fdi.texi in the gdb/doc directory for copying
   conditions.

   You should have received a copy of the GNU Free Documentation License along
   with this program. If not, see <http://www.gnu.org/licenses/>.  */

/* -------------------------------------------------------------------------- */
/*!@mainpage GNU Debugger for the Synopsys ARC Architecture
  
   ## Stack Frame Layout:                                

   This shows the layout of the stack frame for the general case of a
   function call; a given function might not have a variable number of
   arguments or local variables, or might not save any registers, so it would
   not have the corresponding frame areas.  Additionally, a leaf function
   (i.e. one which calls no other functions) does not need to save the
   contents of the BLINK register (which holds its return address), and a
   function might not have a frame pointer.
                                                                               
   @note The stack grows downward, so SP points below FP in memory; SP always
         points to the last used word on the stack, not the first one.

   @verbatim                                                                               
                      |                       |   |                            
                      |      arg word N       |   | caller's                   
                      |           :           |   | frame                      
                      |      arg word 10      |   |                            
                      |      arg word 9       |   |                            
          old SP ---> |-----------------------| --                             
                      |   var arg word 8      |   |                            
                      |           :           |   |                            
                      |   var arg word P+1    |   |                            
                      |-----------------------|   |                            
                      |                       |   |                            
                      |      callee-saved     |   |                            
                      |        registers      |   |                            
                      |                       |   |                            
                      |-----------------------|   |                            
                      |      saved blink (*)  |   |                            
                      |-----------------------|   | callee's                   
                      |      saved FP         |   | frame                      
              FP ---> |-----------------------|   |                            
                      |                       |   |                            
                      |         local         |   |                            
                      |       variables       |   |                            
                      |                       |   |                            
                      |       register        |   |                            
                      |      spill area       |   |                            
                      |                       |   |                            
                      |     outgoing args     |   |                            
                      |                       |   |                            
              SP ---> |-----------------------| --                             
                      |                       |                                
                      |         unused        |                                
                      |                       |                                
                                  |                                            
                                  |                                            
                                  V                                            
                              downwards                                        
   @endverbatim

   (*) if saved; blink may not be saved in leaf functions.
                                                                               
   The list of arguments to be passed to a function is considered to be a
   sequence of _N_ words (as though all the parameters were stored in order in
   memory with each parameter occupying an integral number of words).  Words
   1..8 are passed in registers 0..7; if the function has more than 8 words of
   arguments then words 9..@em N are passed on the stack in the caller's frame.
                                                                               
   If the function has a variable number of arguments, e.g. it has a form such
   as

      function(p1, p2, ...);
                                                                               
   and _P_ words are required to hold the values of the named parameters
   (which are passed in registers 0..@em P -1), then the remaining 8 - _P_
   words passed in registers _P_..7 are spilled into the top of the frame so
   that the anonymous parameter words occupy a continous region.
                                                                               
   ## Build Configuration:

   The ARC gdb may be built in two different configurations, according to 
   the nature of the target that it is to debug:                          
                                                                               
   arc-tdep.[ch] provides operations which are common to both configurations.
   Operations which are specific to one, or which have different variants in
   each configuration, are provided by the other files.

   ### arc-elf32-gdb

   For debugging 'bare-metal' builds of user code (i.e. built with newlib)
                                                                               
   ARC-specific files:                                              
   - arc-tdep.[ch]                                               
   - arc-elf-tdep.[ch]                                           
   - arc-aux-registers.[ch]                                      
   - arc-board.[ch]                                              
                                                                               
   ### arc-linux-uclibc-gdb

   For deugging user mode Linux applications, via communication to the remote
   gdbserver process, running on Linux for ARC700
                                                                               
   ARC-specific files
   - arc-tdep.[ch]                                               
   - arc-linux-tdep.[ch]
                                                                               
   ## Doxygen commenting

   [Doxygen](http://www.doxygen.org/) format comments are used throughout,
   allowing machine generated documentation to be generated from those
   comments. All comments are licensed under the GNU Free Documentation
   License (GFDL). */

/* -------------------------------------------------------------------------- */
/*!@file
                                                                               
   # ARC General Target Dependent Code

   This file provides support for the ARC processor family's target
   dependencies.  In particular, it has knowledge of the processor ABI.
                                                                               
   See the Synopsys DesignWare ARC Instruction Set Architecture and ABI
   manuals for more details. */
/* -------------------------------------------------------------------------- */

/* system header files */
#include <string.h>
#include <stdio.h>
#include <ctype.h>

/* gdb header files */
#include "defs.h"
#include "arch-utils.h"
#include "dis-asm.h"
#include "frame.h"
#include "frame-base.h"
#include "frame-unwind.h"
#include "inferior.h"
#include "regcache.h"
#include "reggroups.h"
#include "trad-frame.h"
#include "dwarf2-frame.h"
#include "gdbcore.h"
#include "observer.h"
#include "osabi.h"
#include "gdbcmd.h"
#include "block.h"
#include "dictionary.h"
#include "language.h"
#include "demangle.h"
#include "objfiles.h"

#include "target-descriptions.h"

/* ARC header files */
#include "opcode/arc.h"
#include "opcodes/arc-dis-old.h"
#include "opcodes/arc-ext.h"
#include "opcodes/arcompact-dis.h"
#include "arc-tdep.h"

/* Default target descriptions. */
#include "features/arc/compatible-v2.c"
#include "features/arc/compatible-arcompact.c"

/* -------------------------------------------------------------------------- */
/*                               local types                                  */
/* -------------------------------------------------------------------------- */

/*! The frame unwind cache for the ARC. */
struct arc_unwind_cache
{
  /*! BLINK save location offset from previous SP (-ve value) */
  int blink_save_offset_from_prev_sp;

  /*! The stack pointer at the time this frame was created; i.e. the caller's
      stack pointer when this function was called.  It is used to identify this
      frame. */
  CORE_ADDR prev_sp;

  /*! The frame base (as held in FP).

      @note This is NOT the address of the lowest word in the frame! */
  CORE_ADDR frame_base;

  /*! Change in SP from previous SP (-ve value)

      This is computed by scanning the prologue of the function: initially 0,
      it is updated for each instruction which changes SP (either explicitly
      by a subtraction from SP or implicitly by a push operation), so at each
      point in the prologue it gives the difference between the previous SP
      (i.e. before the function was called) and the current SP at that point;
      at the end of the prologue it holds the total change in SP, i.e. the
      size of the frame. */
  LONGEST delta_sp;

  /*! offset of old stack pointer from frame base (+ve value) */
  LONGEST old_sp_offset_from_fp;

  /*! Is this a leaf function? */
  int is_leaf;

  /*! Is there a frame pointer? */
  int uses_fp;

  /*! Offsets for each register in the stack frame */
  struct trad_frame_saved_reg *saved_regs;

  /*! Mask of which registers are saved. */
  unsigned int saved_regs_mask;
};


/* -------------------------------------------------------------------------- */
/*		     Externally visible data defined here		      */
/* -------------------------------------------------------------------------- */

/*! Global debug flag */
int arc_debug;


/* -------------------------------------------------------------------------- */
/* Static data used only here.                                                */
/* -------------------------------------------------------------------------- */

/* The list of available "set arc ..." and "show arc ..." commands.  */
static struct cmd_list_element *setarccmdlist = NULL;
static struct cmd_list_element *showarccmdlist = NULL;

/* XML target descriptions features. */
static const char * const
  core_base_v2_feature_name = "org.gnu.gdb.arc.core.v2";
static const char * const
  core_reduced_v2_feature_name = "org.gnu.gdb.arc.core-reduced.v2";
static const char * const
  core_base_arcompact_feature_name = "org.gnu.gdb.arc.core.arcompact";
static const char * const
  aux_base_v2_feature_name = "org.gnu.gdb.arc.aux-minimal";
static const char * const
  aux_compatible_feature_name = "org.gnu.gdb.arc.aux-compatible";

/* XML target description known registers. */
static const struct arc_reginfo const core_base_v2_reginfo[] =
{
  {"r0",       TRUE, TRUE, TRUE,  TRUE},
  {"r1",       TRUE, TRUE, TRUE,  TRUE},
  {"r2",       TRUE, TRUE, TRUE,  TRUE},
  {"r3",       TRUE, TRUE, TRUE,  TRUE},
  {"r4",       TRUE, TRUE, TRUE,  TRUE},
  {"r5",       TRUE, TRUE, TRUE,  TRUE},
  {"r6",       TRUE, TRUE, TRUE,  TRUE},
  {"r7",       TRUE, TRUE, TRUE,  TRUE},
  {"r8",       TRUE, TRUE, TRUE,  TRUE},
  {"r9",       TRUE, TRUE, TRUE,  TRUE},
  {"r10",      TRUE, TRUE, TRUE,  TRUE},
  {"r11",      TRUE, TRUE, TRUE,  TRUE},
  {"r12",      TRUE, TRUE, TRUE,  TRUE},
  {"r13",      TRUE, TRUE, TRUE,  TRUE},
  {"r14",      TRUE, TRUE, TRUE,  TRUE},
  {"r15",      TRUE, TRUE, TRUE,  TRUE},
  {"r16",      TRUE, TRUE, TRUE,  TRUE},
  {"r17",      TRUE, TRUE, TRUE,  TRUE},
  {"r18",      TRUE, TRUE, TRUE,  TRUE},
  {"r19",      TRUE, TRUE, TRUE,  TRUE},
  {"r20",      TRUE, TRUE, TRUE,  TRUE},
  {"r21",      TRUE, TRUE, TRUE,  TRUE},
  {"r22",      TRUE, TRUE, TRUE,  TRUE},
  {"r23",      TRUE, TRUE, TRUE,  TRUE},
  {"r24",      TRUE, TRUE, TRUE,  TRUE},
  {"r25",      TRUE, TRUE, TRUE,  TRUE},
  {"gp",       TRUE, TRUE, TRUE,  TRUE},
  {"fp",       TRUE, TRUE, TRUE,  TRUE},
  {"sp",       TRUE, TRUE, TRUE,  TRUE},
  {"ilink",    TRUE, TRUE, FALSE, FALSE},
  {"r30",      TRUE, TRUE, TRUE,  TRUE},
  {"blink",    TRUE, TRUE, TRUE,  TRUE},
  {"r32",      TRUE, TRUE, FALSE, FALSE},
  {"r33",      TRUE, TRUE, FALSE, FALSE},
  {"r34",      TRUE, TRUE, FALSE, FALSE},
  {"r35",      TRUE, TRUE, FALSE, FALSE},
  {"r36",      TRUE, TRUE, FALSE, FALSE},
  {"r37",      TRUE, TRUE, FALSE, FALSE},
  {"r38",      TRUE, TRUE, FALSE, FALSE},
  {"r39",      TRUE, TRUE, FALSE, FALSE},
  {"r40",      TRUE, TRUE, FALSE, FALSE},
  {"r41",      TRUE, TRUE, FALSE, FALSE},
  {"r42",      TRUE, TRUE, FALSE, FALSE},
  {"r43",      TRUE, TRUE, FALSE, FALSE},
  {"r44",      TRUE, TRUE, FALSE, FALSE},
  {"r45",      TRUE, TRUE, FALSE, FALSE},
  {"r46",      TRUE, TRUE, FALSE, FALSE},
  {"r47",      TRUE, TRUE, FALSE, FALSE},
  {"r48",      TRUE, TRUE, FALSE, FALSE},
  {"r49",      TRUE, TRUE, FALSE, FALSE},
  {"r50",      TRUE, TRUE, FALSE, FALSE},
  {"r51",      TRUE, TRUE, FALSE, FALSE},
  {"r52",      TRUE, TRUE, FALSE, FALSE},
  {"r53",      TRUE, TRUE, FALSE, FALSE},
  {"r54",      TRUE, TRUE, FALSE, FALSE},
  {"r55",      TRUE, TRUE, FALSE, FALSE},
  {"r56",      TRUE, TRUE, FALSE, FALSE},
  {"r57",      TRUE, TRUE, FALSE, FALSE},
  {"accl",     TRUE, TRUE, FALSE, FALSE},
  {"acch",     TRUE, TRUE, FALSE, FALSE},
  {"lp_count", TRUE, TRUE, TRUE,  TRUE},
  {"reserved", FALSE,FALSE,FALSE, FALSE},
  {"limm",     FALSE,FALSE,FALSE, FALSE},
  {"pcl",      TRUE, FALSE,TRUE,  FALSE},
};

static const struct arc_reginfo const aux_base_v2_reginfo[] =
{
  {"pc",       TRUE, TRUE, TRUE, TRUE},
  {"lp_start", TRUE, TRUE, TRUE, TRUE},
  {"lp_end",   TRUE, TRUE, TRUE, TRUE},
  {"status32", TRUE, TRUE, TRUE, TRUE},
};

static const struct arc_reginfo const core_base_arcompact_reginfo[] =
{
  {"r0",       TRUE, TRUE, TRUE,  TRUE},
  {"r1",       TRUE, TRUE, TRUE,  TRUE},
  {"r2",       TRUE, TRUE, TRUE,  TRUE},
  {"r3",       TRUE, TRUE, TRUE,  TRUE},
  {"r4",       TRUE, TRUE, TRUE,  TRUE},
  {"r5",       TRUE, TRUE, TRUE,  TRUE},
  {"r6",       TRUE, TRUE, TRUE,  TRUE},
  {"r7",       TRUE, TRUE, TRUE,  TRUE},
  {"r8",       TRUE, TRUE, TRUE,  TRUE},
  {"r9",       TRUE, TRUE, TRUE,  TRUE},
  {"r10",      TRUE, TRUE, TRUE,  TRUE},
  {"r11",      TRUE, TRUE, TRUE,  TRUE},
  {"r12",      TRUE, TRUE, TRUE,  TRUE},
  {"r13",      TRUE, TRUE, TRUE,  TRUE},
  {"r14",      TRUE, TRUE, TRUE,  TRUE},
  {"r15",      TRUE, TRUE, TRUE,  TRUE},
  {"r16",      TRUE, TRUE, TRUE,  TRUE},
  {"r17",      TRUE, TRUE, TRUE,  TRUE},
  {"r18",      TRUE, TRUE, TRUE,  TRUE},
  {"r19",      TRUE, TRUE, TRUE,  TRUE},
  {"r20",      TRUE, TRUE, TRUE,  TRUE},
  {"r21",      TRUE, TRUE, TRUE,  TRUE},
  {"r22",      TRUE, TRUE, TRUE,  TRUE},
  {"r23",      TRUE, TRUE, TRUE,  TRUE},
  {"r24",      TRUE, TRUE, TRUE,  TRUE},
  {"r25",      TRUE, TRUE, TRUE,  TRUE},
  {"gp",       TRUE, TRUE, TRUE,  TRUE},
  {"fp",       TRUE, TRUE, TRUE,  TRUE},
  {"sp",       TRUE, TRUE, TRUE,  TRUE},
  {"ilink1",   TRUE, TRUE, FALSE, FALSE},
  {"ilink2",   TRUE, TRUE, FALSE, FALSE},
  {"blink",    TRUE, TRUE, TRUE,  TRUE},
  {"r32",      TRUE, TRUE, FALSE, FALSE},
  {"r33",      TRUE, TRUE, FALSE, FALSE},
  {"r34",      TRUE, TRUE, FALSE, FALSE},
  {"r35",      TRUE, TRUE, FALSE, FALSE},
  {"r36",      TRUE, TRUE, FALSE, FALSE},
  {"r37",      TRUE, TRUE, FALSE, FALSE},
  {"r38",      TRUE, TRUE, FALSE, FALSE},
  {"r39",      TRUE, TRUE, FALSE, FALSE},
  {"r40",      TRUE, TRUE, FALSE, FALSE},
  {"r41",      TRUE, TRUE, FALSE, FALSE},
  {"r42",      TRUE, TRUE, FALSE, FALSE},
  {"r43",      TRUE, TRUE, FALSE, FALSE},
  {"r44",      TRUE, TRUE, FALSE, FALSE},
  {"r45",      TRUE, TRUE, FALSE, FALSE},
  {"r46",      TRUE, TRUE, FALSE, FALSE},
  {"r47",      TRUE, TRUE, FALSE, FALSE},
  {"r48",      TRUE, TRUE, FALSE, FALSE},
  {"r49",      TRUE, TRUE, FALSE, FALSE},
  {"r50",      TRUE, TRUE, FALSE, FALSE},
  {"r51",      TRUE, TRUE, FALSE, FALSE},
  {"r52",      TRUE, TRUE, FALSE, FALSE},
  {"r53",      TRUE, TRUE, FALSE, FALSE},
  {"r54",      TRUE, TRUE, FALSE, FALSE},
  {"r55",      TRUE, TRUE, FALSE, FALSE},
  {"r56",      TRUE, TRUE, FALSE, FALSE},
  {"r57",      TRUE, TRUE, FALSE, FALSE},
  {"r58",     TRUE, TRUE, FALSE, FALSE},
  {"r59",     TRUE, TRUE, FALSE, FALSE},
  {"lp_count", TRUE, TRUE, TRUE,  TRUE},
  {"reserved", FALSE,FALSE,FALSE, FALSE},
  {"limm",     FALSE,FALSE,FALSE, FALSE},
  {"pcl",      TRUE, FALSE,TRUE,  FALSE},
};

static const struct arc_reginfo const aux_compatible_reginfo[] =
{
  {"status32_l1",          TRUE, TRUE, FALSE, FALSE},
  {"status32_l2",          TRUE, TRUE, FALSE, FALSE},
  {"aux_irq_lv12",         TRUE, TRUE, FALSE, FALSE},
  {"aux_irq_lev",          TRUE, TRUE, FALSE, FALSE},
  {"aux_irq_hint",         TRUE, TRUE, FALSE, FALSE},
  {"eret",                 TRUE, TRUE, FALSE, FALSE},
  {"erbta",                TRUE, TRUE, FALSE, FALSE},
  {"erstatus",             TRUE, TRUE, FALSE, FALSE},
  {"ecr",                  TRUE, TRUE, FALSE, FALSE},
  {"efa",                  TRUE, TRUE, FALSE, FALSE},
  {"icause1",              TRUE, FALSE,FALSE, FALSE},
  {"icause2",              TRUE, FALSE,FALSE, FALSE},
  {"aux_ienable",          TRUE, TRUE, FALSE, FALSE},
  {"aux_itrigger",         TRUE, TRUE, FALSE, FALSE},
  {"bta",                  TRUE, TRUE, FALSE, FALSE},
  {"bta_l1",               TRUE, TRUE, FALSE, FALSE},
  {"bta_l2",               TRUE, TRUE, FALSE, FALSE},
  {"aux_irq_pulse_cancel", FALSE,TRUE, FALSE, FALSE},
  {"aux_irq_pending",      TRUE, FALSE,FALSE, FALSE},
};

/* -------------------------------------------------------------------------- */
/*                               local functions                              */
/* -------------------------------------------------------------------------- */

/*! Round up a number of bytes to a whole number of words

    @todo BYTES_IN_WORD should be some form of architectural paramter, not a
          magic constant.

    @param[in] gdbarch  Current GDB architecture.
    @param[in] bytes    Number of bytes to round up.
    @return             Number of bytes rounded up to a whole number of
                        words. */
static int
arc_round_up_to_words (struct gdbarch *gdbarch, unsigned int  bytes)
{
  return ((bytes + BYTES_IN_WORD - 1)	/ BYTES_IN_WORD) * BYTES_IN_WORD;

}	/* arc_round_up_to_words () */


/* Functions to be used with disassembling the prologue and update the frame
   info.  The *FI macros are to update the frame info and the ACT macros are
   to actually do the action on a corresponding match. */

/*! Update frame info for "push blink".

    The frame info changes by changing the decrementing the delta_sp and
    setting the leaf function flag to be False (if this function prologue is
    saving blink then it must be going to call another function - so it can
    not be a leaf!); also the offset of the blink register save location from
    the previous value of sp is recorded.  This will eventually used to
    compute the address of the save location:

      <blink saved address> = <prev sp> + <blink offset from prev sp>

    The addition (+=) below is because the sp offset and the instruction
    offset are negative - so incrementing the sp offset by the instruction
    offset is actually making the sp offset more negative, correctly
    reflecting that SP is moving further down the downwards-growing stack.

    @param[out] info  Frame unwind cache to be updated.
    @param[in]  offset  Offset of the new frame. */
static void
arc_push_blink (struct arc_unwind_cache *info, int offset)
{
  info->delta_sp += offset;
  info->blink_save_offset_from_prev_sp = (int) info->delta_sp;
  info->is_leaf = FALSE;

}	/* arc_push_blink () */


/*! Do we need to update frame info for "push blink".

    We already know we have a push instruction, so we just need to check if
    the operand starts with "blink".

    @param[out] info   Frame unwind cache to be updated if non-NULL.
    @param[in]  state  Instruction state to analyse.
    @return            Non-zero (true) if this was "push blink". Zero (false)
                       otherwise. */
static int
arc_is_push_blink_fi (struct arc_unwind_cache *info, struct arcDisState *state)
{
  if (strstr (state->operandBuffer, "blink") == state->operandBuffer)
    {
      if (info)
	{
	  arc_push_blink (info, state->_offset);
	}
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}	/* arc_is_push_blink_fi () */


/*! Do we need to update frame info for "push fp".

    We already know we have a push instruction, so we just need to check if
    the operand starts with "fp".

    At the point that that FP is pushed onto the stack (so saving the dynamic
    link chain pointer to the previous frame), at the address that will be the
    base of the new frame, we know the offset of SP from the previous SP - so
    the offset of the old SP from the new frame base is known (the -ve
    delta_sp is negated to give the +ve old_sp_offset_from_fp).

    @param[out] info   Frame unwind cache to be updated if non-NULL.
    @param[in]  state  Instruction state to analyse.
    @return            Non-zero (true) if this was "push fp". Zero (false)
                       otherwise. */
static int
arc_is_push_fp_fi (struct arc_unwind_cache *info, struct arcDisState *state)
{
  if (strstr (state->operandBuffer, "fp") == state->operandBuffer)
    {
      if (info)
	{
	  info->delta_sp += state->_offset;
	  info->old_sp_offset_from_fp = -info->delta_sp;
	}
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}	/* arc_is_push_fp_fi () */


/*! Do we need to update frame info for "mov fp,sp".

    @param[out] info   Frame unwind cache to be updated if non-NULL.
    @param[in]  state  Instruction state to analyse.
    @return            Non-zero (true) if this was "mov[_s] fp,sp". Zero (false)
                       otherwise. */
static int
arc_is_update_fp_fi (struct arc_unwind_cache *info, struct arcDisState *state)
{
  if (((0 == strcmp(state->instrBuffer, "mov")) || (0 == strcmp(state->instrBuffer, "mov_s")))
      && (strstr (state->operandBuffer, "fp,sp") == state->operandBuffer))
    {
      if (info)
	{
	  info->uses_fp = TRUE;
	}
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}	/* arc_update_fp_act () */

	  
/*! Do we need to update frame info for "sub sp,sp" of various forms.

    @note Could be sub or sub.s and could be "sub.s sp,sp,const"

    @param[out] info   Frame unwind cache to be updated if non-NULL.
    @param[in]  state  Instruction state to analyse.
    @return            Non-zero (true) if this was "push fp". Zero (false)
                       otherwise. */
static int
arc_is_sub_sp_fi (struct arc_unwind_cache *info, struct arcDisState *state)
{
  if (((0 == strcmp(state->instrBuffer, "sub"))
       || (0 == strcmp(state->instrBuffer, "sub_s")))
      && (strstr (state->operandBuffer, "sp,sp") == state->operandBuffer))
    {
      if (info)
	{
	  /* Eat up sp,sp to just leave (possible) constant. */
	  int immediate = atoi(state->operandBuffer + 6);
	  info->delta_sp -= immediate;
	}
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}	/* arc_is_sub_sp_fi () */


/*! Dump the frame info

    Used for internal debugging only.

    @param[in] gdbarch         GDB architecture to which this relates.
    @param[in] message         Text to include with the output
    @param[in] info            Frame info to dump
    @param[in] addresses_known Non-zero (TRUE) if have saved address, zero
                               (FALSE) if have saved offset. */  
static void
arc_print_frame_info (struct gdbarch *gdbarch,
		      char *message,
		      struct arc_unwind_cache *info,
		      int addresses_known)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
  unsigned int i;

  fprintf_unfiltered (gdb_stdlog, "-------------------\n");
  fprintf_unfiltered (gdb_stdlog, "%s (info = %p)\n", message, info);
  fprintf_unfiltered (gdb_stdlog, "prev_sp               = %s\n",
		      print_core_address (target_gdbarch, info->prev_sp));
  fprintf_unfiltered (gdb_stdlog, "frame_base            = %s\n",
		      print_core_address (target_gdbarch, info->frame_base));
  fprintf_unfiltered (gdb_stdlog, "blink offset          = %d\n",
		      info->blink_save_offset_from_prev_sp);
  fprintf_unfiltered (gdb_stdlog, "delta_sp              = %d\n",
		      (int) info->delta_sp);
  fprintf_unfiltered (gdb_stdlog, "old_sp_offset_from_fp = %d\n",
		      (int) info->old_sp_offset_from_fp);
  fprintf_unfiltered (gdb_stdlog, "is_leaf = %d, uses_fp = %d\n",
		      info->is_leaf, info->uses_fp);

  for (i = ARC_FIRST_CALLEE_SAVED_REGNUM; i <= ARC_LAST_CALLEE_SAVED_REGNUM; i++)
    {
      if (info->saved_regs_mask & (1 << i))
	fprintf_unfiltered (gdb_stdlog, "saved register R%02d %s %s\n",
			    i, (addresses_known) ? "address" : "offset",
			    phex (info->saved_regs[i].addr, BYTES_IN_ADDRESS));
    }
  fprintf_unfiltered (gdb_stdlog, "-------------------\n");

}	/* arc_print_frame_info () */


/*! Give name of instruction operand type.

    Used for internal debugging only.

    @param[in] value  The instruction type.
    @result           Textual representation of the operand type */
static const char *
arc_debug_operand_type (enum ARC_Debugger_OperandType value)
{
  switch (value)
    {
    case ARC_LIMM:           return "LIMM";
    case ARC_SHIMM:          return "SHIMM";
    case ARC_REGISTER:       return "REGISTER";
    case ARCOMPACT_REGISTER: return "COMPACT REGISTER";
    case ARC_UNDEFINED:      return "UNDEFINED";
    default:                 return "?";
    }
}	/*! arc_debug_operand_type () */


/*! Dump the instruction state.

    Used for internal debugging only.

    @parma[in] state  Instruction state to dump. */
static void
arc_print_insn_state (struct arcDisState state)
{
  fprintf_unfiltered (gdb_stdlog, "---------------------------------\n");
  fprintf_unfiltered (gdb_stdlog, "Instruction Length %d\n",
		      state.instructionLen);
  fprintf_unfiltered (gdb_stdlog, "Opcode [0x%x] : Cond [%x]\n",
		      state._opcode, state._cond);
  fprintf_unfiltered (gdb_stdlog, "Words 1 [%lx] : 2 [%lx]\n", state.words[0],
		      state.words[1]);
  fprintf_unfiltered (gdb_stdlog, "Ea present [%x] : memload [%x]\n",
		      state._ea_present, state._mem_load);
  fprintf_unfiltered (gdb_stdlog, "Load Length [%d]:\n", state._load_len);
  fprintf_unfiltered (gdb_stdlog, "Address Writeback [%d]\n",
		      state._addrWriteBack);
  fprintf_unfiltered (gdb_stdlog, "EA reg1 is [%x] offset [%x]\n",
		      state.ea_reg1, state._offset);
  fprintf_unfiltered (gdb_stdlog, "EA reg2 is [%x]\n", state.ea_reg2);
  fprintf_unfiltered (gdb_stdlog, "Instr   buffer is %s\n",
		      state.instrBuffer);
  fprintf_unfiltered (gdb_stdlog, "Operand buffer is %s\n",
		      state.operandBuffer);
  fprintf_unfiltered (gdb_stdlog, "SourceType is %s\n",
		      arc_debug_operand_type (state.sourceType));
  fprintf_unfiltered (gdb_stdlog, "Source operand is %u\n", state.source_operand.registerNum);	/* All fields of union
												   have same type */
  fprintf_unfiltered (gdb_stdlog, "Flow is %d\n", state.flow);
  fprintf_unfiltered (gdb_stdlog, "Branch is %d\n", state.isBranch);
  fprintf_unfiltered (gdb_stdlog, "---------------------------------\n");

}	/* arc_print_insn_state () */


/*! Wrapper for the target_read_memory function.

    Interface shim

    @param[in]  memaddr  Address on target to read from
    @param[out] myaddr   Buffer to read into
    @param[in]  length   Number of bytes to read
    @param[in]  info     Unused.
    @result              Zero on success, error code otherwise. */
static int
arc_read_memory_for_disassembler (bfd_vma memaddr, bfd_byte *myaddr,
				  unsigned int length,
				  struct disassemble_info *info) /* unused */
{
  return target_read_memory ((CORE_ADDR) memaddr, (gdb_byte *) myaddr,
			     (int) length);

}	/* arc_read_memory_for_disassembler () */


/*! Utility function to create a new frame cache structure

    @note The implementations has changed since GDB 6.8, since we are now
          provided with the address of THIS frame, rather than the NEXT frame.

    @param[in] this_frame  Frame for which cache is to be created.
    @return                The new frame cache. */
static struct arc_unwind_cache *
arc_create_cache (struct frame_info *this_frame)
{
  struct arc_unwind_cache *cache =
    FRAME_OBSTACK_ZALLOC (struct arc_unwind_cache);

  /* Zero all fields.  */
  cache->blink_save_offset_from_prev_sp = 0;
  cache->prev_sp = 0;
  cache->frame_base = 0;
  cache->delta_sp = 0;
  cache->old_sp_offset_from_fp = 0;
  cache->is_leaf = FALSE;
  cache->uses_fp = FALSE;

  /* allocate space for saved register info */
  cache->saved_regs = trad_frame_alloc_saved_regs (this_frame);

  return cache;

}	/* arc_create_cache () */


/*! Return the base address of the frame

    For ARC, the base address is the frame pointer

    @note The implementations has changed since GDB 6.8, since we are now
          provided with the address of THIS frame, rather than the NEXT frame.

    @param[in] this_frame      The current stack frame.
    @param[in] prologue_cache  Any cached prologue for THIS function.
    @return                    The frame base address */
static CORE_ADDR
arc_frame_base_address (struct frame_info  *this_frame,
			 void              **prologue_cache) 
{
  struct gdbarch *gdbarch = get_frame_arch (this_frame);
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  return  (CORE_ADDR) get_frame_register_unsigned (this_frame, ARC_FP_REGNUM);

}	/* arc_frame_base_address() */


/*! Compute THIS frame's stack pointer and base pointer.

    This is also the frame's ID's stack address.

    @note This function has changed from GDB 6.8. It now takes a reference to
          THIS frame, not the NEXT frame.

    @param[out] info        Frame unwind cache to be populated.
    @param[in]  this_frame  Frame info for THIS frame. */
static void
arc_find_this_sp (struct arc_unwind_cache * info,
		  struct frame_info *this_frame)
{
  struct gdbarch *gdbarch;
  struct gdbarch_tdep *tdep;

  ARC_ENTRY_DEBUG ("this_frame = %p", this_frame)

  gdbarch = get_frame_arch (this_frame);
  tdep = gdbarch_tdep (gdbarch);

  /* if the frame has a frame pointer */
  if (info->uses_fp)
    {
      ULONGEST this_base;
      unsigned int i;

      /* The SP was moved to the FP. This indicates that a new frame
       * was created. Get THIS frame's FP value by unwinding it from
       * the next frame. The old contents of FP were saved in the location
       * at the base of this frame, so this also gives us the address of
       * the FP save location.
       */
      this_base = arc_frame_base_address (this_frame, NULL);
      info->frame_base = (CORE_ADDR) this_base;
      info->saved_regs[ARC_FP_REGNUM].addr = (LONGEST) this_base;

      /* The previous SP is the current frame base + the difference between
       * that frame base and the previous SP.
       */
      info->prev_sp =
	info->frame_base + (CORE_ADDR) info->old_sp_offset_from_fp;

      for (i = ARC_FIRST_CALLEE_SAVED_REGNUM; i <= ARC_LAST_CALLEE_SAVED_REGNUM; i++)
	{
	  /* If this register has been saved, add the previous stack pointer
	   * to the offset from the previous stack pointer at which the
	   * register was saved, so giving the address at which it was saved.
	   */
	  if (info->saved_regs_mask & (1 << i))
	    {
	      info->saved_regs[i].addr += info->prev_sp;

	      if (arc_debug)
		{
		  /* This is a really useful debugging aid: we can debug a
		     test program which loads known values into the
		     callee-saved registers, then calls another function
		     which uses those registers (and hence must save them)
		     then hits a breakpoint; traversing the stack chain
		     (e.g. with the 'where' command) should then execute
		     this code, and we should see those known values being
		     dumped, so showing that we have got the right addresses
		     for the save locations! */
		  unsigned int contents;
		  fprintf_unfiltered (gdb_stdlog, "saved R%02d is at %s\n", i,
				      phex (info->saved_regs[i].addr,
					    BYTES_IN_ADDRESS));
				   

		  if (target_read_memory
		      ((CORE_ADDR) info->saved_regs[i].addr,
		       (gdb_byte *) & contents, BYTES_IN_REGISTER) == 0)
		    {
		      fprintf_unfiltered (gdb_stdlog,
					  "saved R%02d contents: 0x%0x\n", i,
					  contents);
		    }
		}
	    }
	}
    }
  else
    {
      int sp_regnum = gdbarch_sp_regnum (gdbarch);
      CORE_ADDR this_sp =
	(CORE_ADDR) get_frame_register_unsigned (this_frame, sp_regnum);

      /* The previous SP is this frame's SP plus the known difference between
       * the previous SP and this frame's SP (the delta_sp is negated as it is
       * a negative quantity).
       */
      info->prev_sp = (CORE_ADDR) (this_sp + (ULONGEST) (-info->delta_sp));

      /* Assume that the FP is this frame's SP */
      info->frame_base = (CORE_ADDR) this_sp;
    }

  /* if the function owning this frame is not a leaf function */
  if (!info->is_leaf)
    {
      /* Usually blink is saved above the callee save registers and below the
       * space created for variable arguments. The quantity
       *
       *          info->blink_save_offset_from_prev_sp
       *
       * is negative, so adding it to the the previous SP gives the address of
       * a location further down the stack from that SP.
       */
      info->saved_regs[ARC_BLINK_REGNUM].addr =
	(LONGEST) (info->prev_sp + info->blink_save_offset_from_prev_sp);
    }
}	/* arc_find_prev_sp () */


/*! Is register callee-saved.

    Determine whether the given register, which is being saved by a function
    prologue on the stack at a known offset from the current SP, is a
    callee-saved register.

    If it is, the information in the frame unwind cache is updated.

    @param[in] gdbarch  GDB architecture
    @param[in] reg      Register to be considered
    @param[in] offset   Offset where the register is saved.
    @param[in] info     Frame info for THIS frame.
    @return             Non-zero (TRUE) if callee-saved, zero (FALSE)
                        otherwise. */
static int
arc_is_callee_saved (struct gdbarch *gdbarch,
		     unsigned int reg,
		     int offset,
		     struct arc_unwind_cache *info)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  if (ARC_FIRST_CALLEE_SAVED_REGNUM <= reg && reg <= ARC_LAST_CALLEE_SAVED_REGNUM)
    {
      if (arc_debug)
	{
	  fprintf_unfiltered (gdb_stdlog, "register R%02u saved\n", reg);
	}

      if (info)
	{
	  /* We can not determine the address of the location in the stack
	   * frame in which the register was saved, as we do not (yet) know
	   * the frame or stack pointers for the frame; so the most we can do
	   * is to record the offset from the old SP of that location, which
	   * we can compute as we know the offset of SP from the old SP, and
	   * the offset of the location from SP (which is the offset in the
	   * store instruction).
	   *
	   * N.B. the stack grows downward, so the store offset is positive,
	   *      but the delta-SP is negative, so the save offset is also
	   *      negative.
	   *
	   *                               |            |
	   *                old sp ------> |------------|
	   *              /                |            |  \
	   *              :                |            |  :
	   *              :                |            |  :    -ve
	   *              :                |            |  : save offset
	   *              :                |------------|  :
	   *      -ve     :                |  save loc  |  /
	   *    delta sp  :                |------------| <--- store address
	   *              :            /   |            |
	   *              :     +ve    :   |            |
	   *              :    store   :   |            |
	   *              :    offset  :   |            |
	   *              \            \   |            |
	   *                sp' ---------> |            |
	   *                               |            |
	   *                               |            |
	   *                               |------------| <---- frame base
	   *                               |            |
	   *                               |            |
	   *                               |            |
	   *                               |     |      |
	   *                                     |
	   *                                     V
	   *                                 downwards
	   *
	   * where sp' is the stack pointer at the current point in the code
	   */

	  info->saved_regs[reg].addr = info->delta_sp + offset;

	  /* We now know that this register has been saved, so set the
	   * corresponding bit in the save mask.
	   */
	  info->saved_regs_mask |= (1 << reg);

	  if (arc_debug)
	    {
	      arc_print_frame_info (gdbarch, "after callee register save",
				    info, FALSE);
	    }

	  return TRUE;
	}
    }

  return FALSE;

}	/* arc_is_callee_saved () */


/*! Is disassembled instruction in prologue?

    Determine whether the given disassembled instruction may be part of a
    function prologue.

    If it is, the information in the frame unwind cache may be updated.

    @param[in] gdbarch  Current architecture.
    @param[in] info     Frame cache for THIS frame
    @param[in] instr    Instruction to consider.
    @result Non-zero (TRUE) if instr is in prologue, zero (FALSE)
                     otherwise. */
static int
arc_is_in_prologue (struct gdbarch *gdbarch,
                    struct arc_unwind_cache * info,
                    struct arcDisState *instr)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Might be a push or a pop */
  if (instr->_opcode == 0x3)
    {
      if (instr->_addrWriteBack != (char) 0)
	{
	  /* This is a st.a  */
	  /* Value of ea_reg1 is an architecture register number, while
	   * ARC_SP_REGNUM is GDB regnum, so in general they cannot be
	   * compared, however to simplify code we impose a restriction that
	   * for core registers regnum is always equal to architectural number.
	   * */
	  if (instr->ea_reg1 == gdbarch_sp_regnum (gdbarch))
	    {
	      if (instr->_offset == -4)
		{
		  /* This is a push something at SP */
		  /* Is it a push of the blink? */
		  if (arc_is_push_blink_fi (info, instr))
		    {
		      return TRUE;
		    }

		  /* Is it a push for fp? */
		  if (arc_is_push_fp_fi (info, instr))
		    {
		      return TRUE;
		    }
		}
	      else
		{
		  if (instr->sourceType == ARC_REGISTER)
		    {
		      /* st.a <reg>, [sp,<offset>] */

		      if (arc_is_callee_saved (gdbarch,
			   instr->source_operand.registerNum,
                           instr->_offset, info))
			{
			  /* this is a push onto the stack, so change
			     delta_sp */
			  info->delta_sp += instr->_offset;
			  return TRUE;
			}
		    }
		}
	    }
	}
      else
	{
	  if (instr->sourceType == ARC_REGISTER)
	    {
	      /* Is this a store of some register onto the stack using the
	       * stack pointer?
	       */
	      if (instr->ea_reg1 == gdbarch_sp_regnum (gdbarch))
		{
		  /* st <reg>, [sp,offset] */

		  if (arc_is_callee_saved (gdbarch,
		       instr->source_operand.registerNum, instr->_offset,
		       info))
		    /* this is NOT a push onto the stack, so do not change
		       delta_sp */
		    return TRUE;
		}

	      /* Is this the store of some register on the stack using the
	       * frame pointer? We check for argument registers getting saved
	       * and restored.
	       */
	      if (instr->ea_reg1 == ARC_FP_REGNUM)
		{
		  int regnum = instr->source_operand.registerNum;
		  if (ARC_FIRST_ARG_REGNUM <= regnum && regnum <= ARC_LAST_ARG_REGNUM)
		    {
		      /* Saving argument registers. Don't set the bits in the
		       * saved mask, just skip.
		       */
		      return TRUE;
		    }
		}
	    }
	}
    }

  else if (instr->_opcode == 0x4
       || (instr->_opcode == 0x8 && arc_mach_is_arcv2(gdbarch)))
    {
      /* A major opcode 0x4 instruction */
      /* We are usually interested in a mov or a sub */
      /* ARC v2 uses mov_s instruction in prologue, major opcode is 0x8 */
      if (arc_is_update_fp_fi (info, instr)
	  || arc_is_sub_sp_fi (info, instr))
	{
	  return TRUE;
	}
    }

  else if (instr->_opcode == 0x18)
    {
      /* sub_s sp,sp,constant */
      if (arc_is_sub_sp_fi (info, instr))
	{
	  return TRUE;
	}

      /* push_s blink */
      if (strcmp (instr->instrBuffer, "push_s") == 0)
	{
	  if (strcmp (instr->operandBuffer, "blink") == 0)
	    {
	      if (info)
		{
		  /* SP is decremented by the push_s instruction (before it
		   * stores blink at the stack location addressed by SP)
		   */
		  arc_push_blink (info, -BYTES_IN_REGISTER);
		}
	      return TRUE;
	    }
	}
      else if (strcmp (instr->instrBuffer, "st_s") == 0)
	{
	  unsigned int reg;
	  int offset;

	  if (sscanf (instr->operandBuffer, "r%u,[sp,%d]", &reg, &offset) ==
	      2)
	    {
	      /* st_s <reg>,[sp,<offset>] */

	      if (arc_is_callee_saved (gdbarch, reg, offset, info))
		/* this is NOT a push onto the stack, so do not change
		   delta_sp */
		return TRUE;
	    }
	}
    }

  return FALSE;

}	/* arc_is_in_prologue () */


/*! Scan the prologue.

    Scan the prologue and update the corresponding frame cache for the frame
    unwinder for unwinding frames without debug info. In such a situation GDB
    attempts to parse the prologue for this purpose. This currently would
    attempt to parse the prologue generated by our gcc 2.95 compiler (we
    should support Metaware generated binaries at some suitable point of
    time).

    This function is called with:
       entrypoint : the address of the functon entry point
       this_frame : THIS frame to be filled in (if need be)
       info       : the existing cached info.

    Returns: the address of the first instruction after the prologue.

    This function is called by our unwinder as well as from
    arc_skip_prologue () in the case that it cannot detect the end of the
    prologue.

    'this_frame' and 'info' are NULL if this function is called from
    arc_skip_prologue in an attempt to discover the end of the prologue.  In
    this case we don't fill in the 'info' structure that is passed in.

    @todo.
       1. Support 32 bit normal frames generated by GCC 2.95
       2. Support 16 and 32 bit mixed frames generated by GCC 2.95
       3. Support 32 bit normal variadic function frames by GCC 2.95
       4. Support 32 bit normal frames from GCC 3.4.x with variadic args
       5. Support 16 and 32 bit normal frames from GCC 3.4.x with variadic args
       6. Support 16 and 32 bit mixed frames generated by GCC 3.4.x
       7. Support Metaware generated prologues
            (The difference is in the use of thunks to identify the saving and
             restoring of callee saves: may have to do some hackery even in
             next_pc, since the call is going to create its own set of problems
             with our stack setup).

    We attempt to use the disassembler interface from the opcodes library to do
    our disassembling.

    The usual 32 bit normal gcc -O0 prologue looks like this:

    Complete Prologue for all GCC frames (Cases #1 to #6 in TODOs above):

       sub  sp, sp, limm         ; space for variadic arguments
       st.a blink, [sp,-4]       ; push blink (if not a leaf function)
                                 ; - decrements sp
       sub  sp, sp , limm        ; (optional space creation for callee saves)
       st   r13, [sp]            ; push of first callee saved register
       st   r14, [sp,4]          ; push of next callee saved register
       ...
       st.a fp , [sp,-4]         ; push fp (if fp has to be saved)
                                 ; - decrements sp
       mov  fp , sp              ; set the current frame up correctly
       sub  sp , sp , #immediate ; create space for local vars on the stack

    @note This function has changed from GDB 6.8. It now takes a reference to
          THIS frame, not the NEXT frame.

    @param[in] entrypoint  Function entry point where prologue starts
    @param[in] gdbarch     Current architecture. May be NULL in which case
                           this_frame _must_ be defined.
    @param[in] this_frame  Frame info for THIS frame. May be NULL, in which
                           case gdbarch _must_ be defined.
    @param[in] info        Frame cache
    @return                Address of first instruction after prologue. */
static CORE_ADDR
arc_scan_prologue (CORE_ADDR entrypoint,
		   struct gdbarch *gdbarch,
		   struct frame_info *this_frame,
		   struct arc_unwind_cache *info)
{
  struct gdbarch_tdep *tdep;
  CORE_ADDR prologue_ends_pc;
  CORE_ADDR final_pc;
  struct disassemble_info di;

  ARC_ENTRY_DEBUG ("this_frame = %p, info = %p", this_frame, info)

  if (!gdbarch)
    {
      /* We were called from arc_frame_cache, which we know should have
	 this_frame defined. Otherwise we were called form arc_skip_prologue,
	 which passes in the gdbarch. */
      gdb_assert (this_frame);
      gdbarch = get_frame_arch (this_frame);
    }

  tdep = gdbarch_tdep (gdbarch);

  /* An arbitrary limit on the length of the prologue. If this_frame is NULL
     this means that there was no debug info and we are called from
     arc_skip_prologue; otherwise, if we know the frame, we can find the pc
     within the function.

     The maximum prologue length is computed on the 3 instructions before and
     after callee saves, and max number of saves; assume each is 4-byte inst.

     N.B. That pc will usually be after the end of the prologue, but it could
          actually be within the prologue (i.e. execution has halted within
          the prologue, e.g. at a breakpoint); in that case, do NOT go beyond
          that pc, as the instructions at the pc and after have not been
          executed yet, so have had no effect! */
  prologue_ends_pc = entrypoint;
  final_pc = (this_frame)
    ? get_frame_pc (this_frame)
    : entrypoint + 4 * (6 + ARC_LAST_CALLEE_SAVED_REGNUM -
	ARC_FIRST_CALLEE_SAVED_REGNUM + 2);

  if (info)
    {
      /* Assume that the function is a leaf function until we find out
       * that it is not (i.e. when we find the 'push blink' instruction
       * in the prologue).
       */
      info->is_leaf = TRUE;

      /* no registers known to be saved, as yet */
      info->saved_regs_mask = 0;
    }

  /* Initializations to use the opcodes library. */
  arc_initialize_disassembler (gdbarch, &di);

  if (arc_debug)
    {
      fprintf_unfiltered (gdb_stdlog, "Prologue PC: %s\n",
			  print_core_address (gdbarch, prologue_ends_pc));
      fprintf_unfiltered (gdb_stdlog, "Final    PC: %s\n",
			  print_core_address (gdbarch, final_pc));
    }

  /* look at each instruction in the prologue */
  while (prologue_ends_pc < final_pc)
    {
      struct arcDisState current_instr =
	arcAnalyzeInstr (prologue_ends_pc, &di);

      if (arc_debug)
	{
	  arc_print_insn_state (current_instr);
	}

      /* if this instruction is in the prologue, fields in the info will be
       * updated, and the saved registers mask may be updated
       */
      if (!arc_is_in_prologue (gdbarch, info, &current_instr))
	{
	  /* Found a instruction that is not in the prologue */
	  if (arc_debug)
	    {
	      fprintf_unfiltered (gdb_stdlog, "End of Prologue reached \n");
	    }
	  break;
	}

      prologue_ends_pc += current_instr.instructionLen;
    }

  /* Means we were not called from arc_skip_prologue */
  if (!((this_frame == NULL) && (info == NULL)))
    {
      if (arc_debug)
	{
	  arc_print_frame_info (gdbarch, "after prologue", info, FALSE);
	}

      arc_find_this_sp (info, this_frame);

      /* The PC is found in blink (the actual register or located on the
	 stack). */
      info->saved_regs[ARC_PC_REGNUM] = info->saved_regs[ARC_BLINK_REGNUM];

      if (arc_debug)
	{
	  arc_print_frame_info (gdbarch, "after previous SP found", info, TRUE);
	}
    }

  return prologue_ends_pc;

}	/* arc_scan_prologue () */


/*! Get return value of a function.

    Get the return value of a function from the registers/memory used to
    return it, according to the convention used by the ABI.

    @param[in]  gdbarch   Our GDB architecture
    @param[in]  type      Returned value's type
    @param[in]  regcache  Register cache to get values from.
    @param[out] valbuf    Buffer for the returned value. */
static void
arc_extract_return_value (struct gdbarch *gdbarch, struct type *type,
			  struct regcache *regcache, gdb_byte *valbuf)
{
  unsigned int len = TYPE_LENGTH (type);
  const struct gdbarch_tdep * const tdep = gdbarch_tdep (gdbarch);

  ARC_ENTRY_DEBUG ("")

  if (len <= BYTES_IN_REGISTER)
    {
      ULONGEST val;

      /* Get the return value from one register. */
      regcache_cooked_read_unsigned (regcache, ARC_R0_REGNUM, &val);
      store_unsigned_integer (valbuf, (int) len,
			      gdbarch_byte_order (gdbarch), val);

      if (arc_debug)
	{
	  fprintf_unfiltered (gdb_stdlog, "returning %s\n",
			      phex (val, BYTES_IN_REGISTER));
	}
    }
  else if (len <= BYTES_IN_REGISTER * 2)
    {
      ULONGEST low, high;

      /* Get the return value from two registers. */
      regcache_cooked_read_unsigned (regcache, ARC_R0_REGNUM,
				     &low);
      regcache_cooked_read_unsigned (regcache, ARC_R1_REGNUM,
				     &high);

      store_unsigned_integer (valbuf, BYTES_IN_REGISTER,
			      gdbarch_byte_order (gdbarch), low);
      store_unsigned_integer (valbuf + BYTES_IN_REGISTER,
			      (int) len - BYTES_IN_REGISTER,
			      gdbarch_byte_order (gdbarch), high);

      if (arc_debug)
	{
	  fprintf_unfiltered (gdb_stdlog, "returning 0x%s%s\n",
			      phex (high, BYTES_IN_REGISTER), 
			      phex (low, BYTES_IN_REGISTER));
	}
    }
  else
    error (_("%s: type length %u too large"), __FUNCTION__, len);

}	/* arc_extract_value () */


/*! Store the return value of a function.

    Store the return value of a function into the registers/memory used to
    return it, according to the convention used by the ABI.

    @param[in]  gdbarch   Our GDB architecture
    @param[in]  type      Returned value's type
    @param[out] regcache  Register cache to put values in.
    @param[in]  valbuf    Buffer with the value to return. */
static void
arc_store_return_value (struct gdbarch *gdbarch, struct type *type,
			struct regcache *regcache, const gdb_byte * valbuf)
{
  unsigned int len = TYPE_LENGTH (type);
  const struct gdbarch_tdep * const tdep = gdbarch_tdep (gdbarch);

  ARC_ENTRY_DEBUG ("")

  if (len <= BYTES_IN_REGISTER)
    {
      ULONGEST val;

      /* Put the return value into one register. */
      val = extract_unsigned_integer (valbuf, (int) len,
				      gdbarch_byte_order (gdbarch));
      regcache_cooked_write_unsigned (regcache, ARC_R0_REGNUM, val);

      if (arc_debug)
	{
	  fprintf_unfiltered (gdb_stdlog, "storing 0x%s\n",
			      phex (val, BYTES_IN_REGISTER));
	}
    }
  else if (len <= BYTES_IN_REGISTER * 2)
    {
      ULONGEST low, high;

      /* Put the return value into  two registers. */
      low = extract_unsigned_integer (valbuf, BYTES_IN_REGISTER,
				      gdbarch_byte_order (gdbarch));
      high =
	extract_unsigned_integer (valbuf + BYTES_IN_REGISTER,
				  (int) len - BYTES_IN_REGISTER,
				  gdbarch_byte_order (gdbarch));

      regcache_cooked_write_unsigned (regcache, ARC_R0_REGNUM,
				      low);
      regcache_cooked_write_unsigned (regcache, ARC_R1_REGNUM,
				      high);

      if (arc_debug)
	{
	  fprintf_unfiltered (gdb_stdlog, "storing 0x%s%s\n",
			      phex (high, BYTES_IN_REGISTER), 
			      phex (low, BYTES_IN_REGISTER));
	}
    }
  else
    error (_("arc_store_return_value: type length too large."));

}	/* arc_store_return_value () */


/* -------------------------------------------------------------------------- */
/*		   ARC specific GDB architectural functions		      */
/*									      */
/* Functions are listed in the order they are used in arc_gdbarch_init.       */
/* -------------------------------------------------------------------------- */

/*! Return the virtual frame pointer.

   GDB and the GNU tool chain is increasingly vague about the use of a "frame
   pointer" (FP). With the ARC tool GCC, the FP (r2) is used to point to the
   middle of the current stack frame, just below the saved FP and before local
   variables, register spill area and outgoing args.  However for optimization
   levels above O2 and in any case in leaf functions, the frame pointer is
   usually not set at all. The exception being when handling nested functions.

   We use this function to return a "virtual" frame pointer, marking the start
   of the current stack frame as a register-offset pair.  If the FP is not
   being used, then it should return SP, with an offset of the frame size.

   The current implementation doesn't actually know the frame size, nor
   whether the FP is actually being used, so for now we just return SP and an
   offset of zero. This is no worse than other architectures, but is needed to
   avoid assertion failures.

   @todo Can we determine the frame size to get a correct offset?

   @param[in]  gdbarch     The GDB architecture being used.
   @param[in]  pc          Program counter where we need the virtual FP.
   @param[out] reg_ptr     The base register used for the virtual FP.
   @param[out] offset_ptr  The offset used for the virtual FP.                */
/*----------------------------------------------------------------------------*/
static void
arc_virtual_frame_pointer (struct gdbarch *gdbarch,
			    CORE_ADDR       pc,
			    int            *reg_ptr,
			    LONGEST        *offset_ptr)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
  *reg_ptr    = gdbarch_sp_regnum (gdbarch);
  *offset_ptr = 0;

}	/* arc_virtual_frame_pointer () */


/*! Return the frame ID for a dummy stack frame

    Tear down a dummy frame created by arc_push_dummy_call(). This data has
    to be constructed manually from the data in our hand.

    The stack pointer and program counter can be obtained from the frame info.

    @note The implementations has changed since GDB 6.8, since we are now
          provided with the address of THIS frame, rather than the NEXT frame.

    @param[in] gdbarch     The architecture to use
    @param[in] this_frame  Information about this frame
    @return                Frame ID of this frame */
static struct frame_id
arc_dummy_id (struct gdbarch *gdbarch, struct frame_info *this_frame)
{
  return frame_id_build (get_frame_sp (this_frame), get_frame_pc (this_frame));

}	/* arc_dummy_id () */


/*! Push stack frame for a dummy call.

    @note Any arguments are already in target byte order. We just need to
          store them!

    @param[in] gdbarch        Current gdbarch.
    @param[in] function       Function to call.
    @param[in] regcache       Current register cache
    @param[in] bp_addr        Return address where breakpoint must be placed.
    @param[in] nargs          Number of arguments to the function
    @param[in] args           The arguments values (in target byte order)
    @param[in] sp             Current value of SP.
    @param[in] struct_return  Non-zero (TRUE) if structures are returned by
                              the function. 
    @param[in] struct_addr    Hidden address for returning a struct.
    @return                   SP of new frame. */
static CORE_ADDR
arc_push_dummy_call (struct gdbarch *gdbarch,
		     struct value *function,
		     struct regcache *regcache,
		     CORE_ADDR bp_addr,
		     int nargs,
		     struct value **args,
		     CORE_ADDR sp, int struct_return, CORE_ADDR struct_addr)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
  int arg_reg = ARC_FIRST_ARG_REGNUM;

  ARC_ENTRY_DEBUG ("nargs = %d", nargs)

  /* Push the return address. */
  regcache_cooked_write_unsigned (regcache, ARC_BLINK_REGNUM, bp_addr);

  /* Are we returning a value using a structure return instead of a normal
     value return? If so, struct_addr is the address of the reserved space for
     the return structure to be written on the stack, and that address is
     passed to that function as a hidden first argument.

     @todo Ramana: What about 4 byte structures returned in R0 as claimed by
           Metaware? */
  if (struct_return)
    {
      /* pass the return address in the first argument register */
      regcache_cooked_write_unsigned (regcache, arg_reg, struct_addr);

      if (arc_debug)
	{
	  fprintf_unfiltered (gdb_stdlog,
			      "struct return address %s passed in R%d",
			      print_core_address (gdbarch, struct_addr),
			      arg_reg);
	}

      arg_reg++;
    }

  if (nargs > 0)
    {
      unsigned int total_space = 0;
      gdb_byte *memory_image;
      gdb_byte *data;
      int i;

      /* How much space do the arguments occupy in total?

         @note Must round each argument's size up to an integral number of
               words. */
      for (i = 0; i < nargs; i++)
	{
	  unsigned int len = TYPE_LENGTH (value_type (args[i]));
	  unsigned int space = arc_round_up_to_words (gdbarch, len);

	  total_space += space;

	  if (arc_debug)
	    {
	      fprintf_unfiltered (gdb_stdlog, "arg %d: %d bytes -> %u\n", i,
				  len, arc_round_up_to_words (gdbarch, len));
	    }
	}

      /* Allocate a buffer to hold a memory image of the arguments. */
      memory_image = XCALLOC (total_space, gdb_byte);
      if (memory_image == NULL)
	{
	  /* could not do the call! */
	  return 0;
	}

      /* Now copy all of the arguments into the buffer, correctly aligned */
      data = memory_image;
      for (i = 0; i < nargs; i++)
	{
	  unsigned int len = TYPE_LENGTH (value_type (args[i]));
	  unsigned int space = arc_round_up_to_words (gdbarch, len);

	  (void) memcpy (data, value_contents (args[i]), (size_t) len);
	  if (arc_debug)
	    fprintf_unfiltered (gdb_stdlog,
				"copying arg %d, val 0x%08x, len %d into mem\n",
				i, * ((int *) value_contents (args[i])), len);
	    
	  data += space;
	}

      /* Now load as much as possible of the memory image into registers. */
      data = memory_image;
      while (arg_reg <= ARC_LAST_ARG_REGNUM)
	{
	  if (arc_debug)
	    {
	      fprintf_unfiltered (gdb_stdlog,
				  "passing 0x%02x%02x%02x%02x in register R%d\n",
				  data[0], data[1], data[2], data[3], arg_reg);
	    }

	  /* Note we don't use write_unsigned here, since that would convert
	     the byte order, but we are already in the correct byte order! */
	  regcache_cooked_write (regcache, arg_reg, data);

	  data += BYTES_IN_REGISTER;
	  total_space -= BYTES_IN_REGISTER;

	  /* if all the data is now in registers */
	  if (total_space == 0)
	    break;

	  arg_reg++;
	}

      /* If there is any data left, push it onto the stack (in a single write
	 operation). */
      if (total_space > 0)
	{
	  if (arc_debug)
	    {
	      fprintf_unfiltered (gdb_stdlog, "passing %d bytes on stack\n",
				  total_space);
	    }

	  sp -= total_space;
	  write_memory (sp, data, (int) total_space);
	}

      xfree (memory_image);
    }

  /* Finally, update the SP register. */
  regcache_cooked_write_unsigned (regcache, gdbarch_sp_regnum (gdbarch), sp);

  return sp;

}	/* arc_push_dummy_call () */


/*! Push dummy call return code sequence.

    We don't actually push any code. We just identify where a breakpoint can
    be inserted to which we are can return and the resume address where we
    should be called.

    ARC does not necessarily have an executable stack, so we can't put the
    return breakpoint there. Instead we put it at the entry point fo the
    function. This means the SP is unchanged.

    @note For ARC this is new for GDB 7.5. The GDB 6.8 implementation used the
          old call_dummy_location, whose use is now deprecated. Fro simplicity
          we have just lifted the code that call_dummy_location associated
          with using the entry point (AT_ENTRY_POINT) for dummy return.

    @param[in]  gdbarch     Current GDB architecture
    @param[in]  sp          Current stack pointer
    @param[in]  funaddr     Address of the function to be called.
    @param[in]  args        Args to pass.
    @param[in]  nargs       Number of args to pass.
    @param[in]  value_type  Type of value returned?
    @param[out] real_pc     Resume address when the function is called.
    @param[out] bp_addr     Address where breakpoint should be set.
    @param[in]  regcache    Register cache for current frame.
    @return                 The updated stack pointer. */
static CORE_ADDR
arc_push_dummy_code (struct gdbarch *gdbarch, CORE_ADDR sp, CORE_ADDR funaddr,
		     struct value **args, int nargs, struct type *value_type,
		     CORE_ADDR *real_pc, CORE_ADDR *bp_addr,
		     struct regcache *regcache)
{
  *real_pc = funaddr;
  *bp_addr = entry_point_address ();
  return sp;
    
}	/* arc_push_dummy_code *() */


/*! Print floating point registers.

    This supports the "info float" command.

    The ARC architecture does not have floating point registers as such, but
    the software FPU allows registers and pairs of registers to be used to
    hold FP values, and this function allows the general registers to be
    displayed as floating point values.

    We print the core general and general extension registers, both as single
    precision FP, and as double precision pairs. We assume no aux register
    constains FP values.

    @todo This is a placeholder. We need to write code (lift ideas from
          default_print_register_info).

    @todo We need to be cleverer about dealing with extension core registers
          and auxilliary registers, based on what the architecture tdep
          structure has to say.

    @todo We should consider whether we ought to define a set of pseudo regs
          for FP values.

    @param[in] gdbarch  The current GDB architecture.
    @param[in] file     The GDB file handle to which to write.
    @param[in] frame    The current stack frame.
    @param[in] args     Any arguments given to the info float command. */
static void
arc_print_float_info (struct gdbarch *gdbarch, struct ui_file *file,
		      struct frame_info *frame, const char *args)
{
  fputs_filtered ("Core registers may hold values for use by the soft FPU.\n",
		  file);

}	/* arc_print_float_info () */


/* Get a longjmp target.

   We've just landed at a longjmp breakpoint. Detemine the address the longjmp
   will jump to.

   We need to use the frame info to get the register pointing to the jmp_buf,
   then extract the PC from that.

   Since jmp_buf is the first argument to longjmp () it will be in r0. Where
   we then go depends on the OS. If we are using Linux, we have in uClibc
   (libc/sysdeps/linux/arc/bits/setjmp.h):

   /verbatim
   typedef int __jmp_buf[13+1+1+1];    //r13-r25, fp, sp, blink
   /endverbatim

   If we are using newlib, we have in libc/include/machine/setjmp.h:

   /verbatim
   #ifdef __arc__
   #define _JBLEN 25 // r13-r30,blink,lp_count,lp_start,lp_end,mlo,mhi,status32
   #endif
   /endverbatim

   We don't have full information on which library are using, but it is
   reasonable to assume that if we have GDB_OSABI_LINUX, we are using uClibc,
   and otherwise newlib.

   @param[in]  frame  Frame info for THIS frame.
   @param[out] pc     Address longjmp will jump to.
   @return            Non-zero (TRUE) if we found the target, zero (FALSE)
                      otherwise. */
static int
arc_get_longjmp_target (struct frame_info *frame, CORE_ADDR *pc)
{
  CORE_ADDR jb_addr;
  struct gdbarch *gdbarch = get_frame_arch (frame);
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
  enum bfd_endian byte_order = gdbarch_byte_order (gdbarch);
  int  element_size = gdbarch_ptr_bit (gdbarch) / TARGET_CHAR_BIT;
  void *buf = alloca (element_size);
  enum gdb_osabi osabi = gdbarch_osabi (gdbarch);
  /* todo: Either this whole function should be extracted to target-dependent
   * level, or we need to receive offset dynamically. For example from the
   * valid OS_ABI. */
  int  pc_offset = (GDB_OSABI_LINUX == osabi)
    ? ARC_UCLIBC_JB_PC * element_size
    : ARC_NEWLIB_JB_PC * element_size;

  jb_addr = get_frame_register_unsigned (frame, ARC_FIRST_ARG_REGNUM);

  if (target_read_memory (jb_addr + pc_offset, buf, element_size))
    {
      return  0;		/* Failed to read from buf */
    }
  else
    {
      *pc = extract_unsigned_integer (buf, element_size, byte_order);
      return 1;
    }
}	/* arc_get_longjmp_target () */


/*! Determine how a result of particular type is returned.

    Return the convention used by the ABI for returning a result of the given
    type from a function; it may also be required to:
   
    1. set the return value (this is for the situation where the debugger user
       has issued a "return <value>" command to request immediate return from
       the current function with the given result; or
   
    2. get the return value ((this is for the situation where the debugger
       user has executed a "call <function>" command to execute the specified
       function in the target program, and that function has a non-void result
       which must be returned to the user.

    @param[in] gdbarch  Current GDB architecture
    @param[in] function  The function being returned form (unused).
    @param[in] valtype   The type of the value to return.
    @param[in] regcache  Register cache for the current frame.
    @param[in] readbuf   If non-NULL get the return value into the buffer
    @param[in] writebuf  If non-NULL set the return value from the buffer
    @return              The return convention used. */
static enum return_value_convention
arc_return_value (struct gdbarch *gdbarch,
		  struct value *function,
		  struct type *valtype,
		  struct regcache *regcache,
		  gdb_byte *readbuf, const gdb_byte * writebuf)
{
  /* If the return type is a struct, or a union, or would occupy more than two
     registers, the ABI uses the "struct return convention": the calling
     function passes a hidden first parameter to the callee (in R0).  That
     parameter is the address at which the value being returned should be
     stored.  Otherwise, the result is returned in registers. */
  int is_struct_return = (TYPE_CODE (valtype) == TYPE_CODE_STRUCT ||
			  TYPE_CODE (valtype) == TYPE_CODE_UNION ||
			  TYPE_LENGTH (valtype) > 2 * BYTES_IN_REGISTER);

  ARC_ENTRY_DEBUG ("readbuf = %p, writebuf = %p", readbuf, writebuf)

  if (writebuf != NULL)
    {
      /* Case 1. GDB should not ask us to set a struct return value: it should
                 know the struct return location and write the value there
                 itself. */
      gdb_assert (!is_struct_return);
      arc_store_return_value (gdbarch, valtype, regcache, writebuf);
    }
  else if (readbuf != NULL)
    {
      /* Case 2. GDB should not ask us to get a struct return value: it should
	         know the struct return location and read the value from there
	         itself. */
      gdb_assert (!is_struct_return);
      arc_extract_return_value (gdbarch, valtype, regcache, readbuf);
    }

  return is_struct_return
    ? RETURN_VALUE_STRUCT_CONVENTION
    : RETURN_VALUE_REGISTER_CONVENTION;

}	/* arc_return_value () */


/*! Skip the prologue for the function at pc.

    This is done by checking from the line information read from the DWARF, if
    possible; otherwise, we scan the function prologue to find its end.

    @param[in] gdbarch  Current GDB architecture
    @param[in] pc       PC somewhere in the prologue.
    @return             Address of first instruction after prologue. */
static CORE_ADDR
arc_skip_prologue (struct gdbarch *gdbarch, CORE_ADDR pc)
{
  CORE_ADDR func_addr, func_end = 0;
  const char *func_name;

  ARC_ENTRY_DEBUG ("")

  /* If we're in a dummy frame, don't even try to skip the prologue. */
  if (deprecated_pc_in_call_dummy (gdbarch, pc))
    {
      return pc;
    }

  /* See what the symbol table says. */
  if (find_pc_partial_function (pc, &func_name, &func_addr, &func_end))
    {
      /* Found a function. */
      CORE_ADDR postprologue_pc = skip_prologue_using_sal(gdbarch, func_addr);

      if (postprologue_pc)
          return postprologue_pc;
    }

  /* Find the address of the first instruction after the prologue by scanning
     through it - no other information is needed, so pass NULL for the other
     parameters.  */
  return arc_scan_prologue (pc, gdbarch, NULL, NULL);

}	/* arc_skip_prologue () */


/*! Unwind the program counter.

    @param[in] next_frame  NEXT frame from which the PC in THIS frame should be
                           unwound.
    @return                The value of the PC in THIS frame. */
static CORE_ADDR
arc_unwind_pc (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  int pc_regnum = gdbarch_pc_regnum (gdbarch);
  CORE_ADDR pc =
    (CORE_ADDR) frame_unwind_register_unsigned (next_frame, pc_regnum);

  if (arc_debug)
    {
      fprintf_unfiltered (gdb_stdlog, "unwind PC: %s\n",
			  print_core_address (gdbarch, pc));
    }

  return pc;

}	/* arc_unwind_pc () */


/*! Unwind the stack pointer.

    @param[in] next_frame  NEXT frame from which the SP in THIS frame should be
                           unwound.
    @return                The value of the SP in THIS frame. */
static CORE_ADDR
arc_unwind_sp (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  int sp_regnum = gdbarch_sp_regnum (gdbarch);
  CORE_ADDR sp =
    (CORE_ADDR) frame_unwind_register_unsigned (next_frame, sp_regnum);

  if (arc_debug)
    {
      fprintf_unfiltered (gdb_stdlog, "unwind SP: %s\n",
			  print_core_address (gdbarch, sp));
    }

  return (CORE_ADDR) sp;

}	/* arc_unwind_sp () */


/*! Adjust the stack pointer to align frame.

    @param[in] gdbarch  Current GDB architecture
    @param[in] sp       SP to align.
    @return             Aligned SP. */
static CORE_ADDR
arc_frame_align (struct gdbarch *gdbarch, CORE_ADDR sp)
{
  int  bpw = gdbarch_ptr_bit (gdbarch) / TARGET_CHAR_BIT;
  return sp & ~(((CORE_ADDR) bpw) - 1);

}	/* arc_frame_align () */


/* Skip the code for a trampoline.

   @todo Needs writing. For now we just return the PC.

   @param[in] frame  Frame info for current frame.
   @param[in] pc     PC at start of trampoline code.
   @return           Address of start of function proper. */
static CORE_ADDR
arc_skip_trampoline_code (struct frame_info *frame, CORE_ADDR pc)
{
  if (arc_debug)
    {
      fprintf_unfiltered (gdb_stdlog,
			  "Attempt to skip trampoline code at %s.\n",
			  print_core_address (get_frame_arch (frame), pc));
    }
  return pc;

}	/* arc_skip_trampoline_code () */


/*! Frame unwinder for normal frames.

    @note This function has changed from GDB 6.8. It now takes a reference to
          THIS frame, not the NEXT frame.

    @param[in]     this_frame  Frame info for THIS frame.
    @param[in,out] this_cache  Frame cache for THIS frame, created if necessary.
    @return                    The frame cache (new or existing) */
static struct arc_unwind_cache *
arc_frame_cache (struct frame_info *this_frame, void **this_cache)
{
  struct gdbarch *gdbarch;
  struct gdbarch_tdep *tdep;

  ARC_ENTRY_DEBUG ("")

  gdbarch = get_frame_arch (this_frame);
  tdep = gdbarch_tdep (gdbarch);

  if ((*this_cache) == NULL)
    {
        CORE_ADDR  entrypoint =
	  (CORE_ADDR) get_frame_register_unsigned (this_frame, gdbarch_pc_regnum (gdbarch));
        struct arc_unwind_cache *cache = arc_create_cache (this_frame);

        /* return the newly-created cache */
        *this_cache = cache;

        /* Prologue analysis does the rest... Currently our prologue scanner
	   does not support getting input for the frame unwinder. */
        (void) arc_scan_prologue (entrypoint, NULL, this_frame, cache);
    }

    return *this_cache;

}	/* arc_frame_cache () */


/*! Get the frame_id of a normal frame.

    @note There seemed to be a bucket load of irrelevant code about stopping
          backtraces in the old code, which we've stripped out.

    @note This function has changed from GDB 6.8. It now takes a reference to
          THIS frame, not the NEXT frame.

    @param[in]     this_frame  Frame info for THIS frame.
    @param[in,out] this_cache  Frame cache for THIS frame, created if
                               necessary.
    @param[out]    this_id     Frame id for THIS frame. */
static void
arc_frame_this_id (struct frame_info *this_frame,
		   void **this_cache, struct frame_id *this_id)
{
  struct gdbarch *gdbarch;
  struct gdbarch_tdep *tdep;
  CORE_ADDR stack_addr;
  CORE_ADDR code_addr;
  ARC_ENTRY_DEBUG ("")

  gdbarch = get_frame_arch (this_frame);
  tdep = gdbarch_tdep (gdbarch);

  stack_addr = arc_frame_cache (this_frame, this_cache)->frame_base;

  /* There are 4 possible situation which decide how frame_id->code_addr is
   * evaluated:
   *   1) function is compiled with option -g. Then frame_id will be created in
   *      dwarf_* function and not in this function. NB: even if target binary
   *      is compiled with -g, some std functions like __start and _init are
   *      not, so they still will follow one of the following choices.
   *   2) function is compiled without -g and binary hasn't been stripped in any
   *      way. In this case GDB still has enough information to evaluate frame
   *      code_addr properly. This case is covered by call to get_frame_func().
   *   3) binary has been striped with option -g (strip debug symbols). In this
   *      case there is still enough symbols for get_frame_func() to work
   *      properly, so this case is also covered by it.
   *   4) binary has been striped with option -s (strip all symbols). In this
   *      case GDB cannot get function start address properly, so we return
   *      current PC value instead.
   */
  code_addr = get_frame_func(this_frame);
  if (!code_addr)
    code_addr = get_frame_register_unsigned(this_frame, gdbarch_pc_regnum (gdbarch));

  *this_id = frame_id_build (stack_addr, code_addr);

}	/* arc_frame_this_id () */


/*! Unwind a register from a normal frame.

    Given a pointer to the THIS frame, return the details of a register in the
    PREVIOUS frame.

    @note This function has changed from GDB 6.8. It now takes a reference to
          THIS frame, not the NEXT frame. It returns it results via a
          structure, not its argument list.

    @param[in] this_frame  The stack frame under consideration
    @param[in] this_cache  Any cached prologue associated with THIS frame,
                           which may therefore tell us about registers in the
			   PREVIOUS frame. 
    @param[in] regnum      The register of interest in the PREVIOUS frame
    @return                 A value structure representing the register. */
static struct value *
arc_frame_prev_register (struct frame_info *this_frame,
			 void **this_cache,
			 int regnum)
{
  struct gdbarch *gdbarch = get_frame_arch (this_frame);
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
  struct arc_unwind_cache *info = arc_frame_cache (this_frame, this_cache);

  ARC_ENTRY_DEBUG ("regnum %d", regnum)

  /* @todo The old GDB 6.8 code noted that if we are asked to unwind the PC,
           then we need to return blink instead: the saved value of PC points
           into this frame's function's prologue, not the next frame's
           function's resume location.

           Is this still true? Do we need the following code. */
  if (regnum == gdbarch_pc_regnum (gdbarch))
    {
      regnum = ARC_BLINK_REGNUM;
    }
  
  if (arc_debug)
    {
      fprintf_unfiltered (gdb_stdlog, "-*-*-*\n Regnum = %d\n", regnum);
    }

  /* @todo. The old GDB 6.8 code noted that SP is generally not saved to the
            stack, but this frame is identified by next_frame's stack pointer
            at the time of the call. The value was already reconstructed into
            prev_sp.

            The old code explicitly set *lvalp to not_lval and stored a value
            in the buffer . Do we need to do something special for SP? */
  return trad_frame_get_prev_register (this_frame, info->saved_regs, regnum);

}	/* arc_frame_prev_register () */


/*! Identify some properties of particular registers for the DWARF unwinder.

    @param[in]  gdbarch  Current GDB architecture
    @param[in]  regnum   Register or interest
    @param[out] reg      DWARF register info.
    @param[in]  info     Frame info for this frame (unused). */
static void
arc_dwarf2_frame_init_reg (struct gdbarch *gdbarch,
			   int regnum,
			   struct dwarf2_frame_state_reg *reg,
			   struct frame_info *info)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  if (regnum == gdbarch_pc_regnum (gdbarch))
    reg->how = DWARF2_FRAME_REG_RA;	/* The return address column. */
  else if (regnum == gdbarch_sp_regnum (gdbarch))
    reg->how = DWARF2_FRAME_REG_CFA;	/* The call frame address. */

}	/* arc_dwarf2_frame_init_reg () */


/*! Signal trampoline frame unwinder.
 
    Allow frame unwinding to happen from within signal handlers.

    @note This function has changed from GDB 6.8. It now takes a reference to
          THIS frame, not the NEXT frame.

    @param[in]     this_frame  Frame info for THIS frame.
    @param[in,out] this_cache  Frame cache for THIS frame, created if necessary.
    @return                    The frame cache (new or existing) */
static struct arc_unwind_cache *
arc_sigtramp_frame_cache (struct frame_info *this_frame, void **this_cache)
{
  ARC_ENTRY_DEBUG ("")

  if (*this_cache == NULL)
    {
      struct gdbarch_tdep *tdep = gdbarch_tdep (get_frame_arch (this_frame));
      struct arc_unwind_cache *cache = arc_create_cache (this_frame);

      *this_cache = cache;

      /* get the stack pointer and use it as the frame base */
      cache->frame_base = arc_frame_base_address (this_frame, NULL);

      /* If the ARC-private target-dependent info has a table of offsets of
         saved register contents within a O/S signal context structure. */
      if (tdep->sc_reg_offset)
	{
	  /* find the address of the sigcontext structure */
	  CORE_ADDR addr = tdep->sigcontext_addr (this_frame);
	  unsigned int i;

	  /* For each register, if its contents have been saved within the
	    sigcontext structure, determine the address of those contents. */
	  for (i = 0; i < tdep->sc_num_regs; i++)
	    {
	      if (tdep->sc_reg_offset[i] != REGISTER_NOT_PRESENT)
		{
		  cache->saved_regs[i].addr =
		    (LONGEST) (addr + tdep->sc_reg_offset[i]);
		}
	    }
	}
    }
  return *this_cache;

}	/* arc_sigtramp_frame_cache () */


/*! Get the frame_id of a signal handler frame.

    @note This function has changed from GDB 6.8. It now takes a reference to
          THIS frame, not the NEXT frame.

    @param[in]     this_frame  Frame info for THIS frame.
    @param[in,out] this_cache  Frame cache for THIS frame, created if
                               necessary.
    @param[out]    this_id     Frame id for THIS frame. */
static void
arc_sigtramp_frame_this_id (struct frame_info *this_frame,
			    void **this_cache, struct frame_id *this_id)
{
  struct gdbarch *gdbarch;
  struct gdbarch_tdep *tdep;
  CORE_ADDR stack_addr;
  CORE_ADDR code_addr;
  ARC_ENTRY_DEBUG ("")

  gdbarch = get_frame_arch (this_frame);
  tdep = gdbarch_tdep (gdbarch);

  stack_addr = arc_sigtramp_frame_cache (this_frame, this_cache)->frame_base;
  code_addr = get_frame_register_unsigned (this_frame, gdbarch_pc_regnum (gdbarch));
  *this_id = frame_id_build (stack_addr, code_addr);

}	/* arc_sigtramp_frame_this_id () */


/*! Get a register from a signal handler frame.

    Given a pointer to the THIS frame, return the details of a register in the
    PREVIOUS frame.

    @todo The old version of this used to look for the PC in the "ret"
          register, since that was where it would be found for a
          signal. However we no longer have this - we rely on the GDB server
          to give us the correct value of the PC.

    @note This function has changed from GDB 6.8. It now takes a reference to
          THIS frame, not the NEXT frame. It returns it results via a
          structure, not its argument list.

    @param[in] this_frame  The stack frame under consideration
    @param[in] this_cache  Any cached prologue associated with THIS frame,
                           which may therefore tell us about registers in the
			   PREVIOUS frame. 
    @param[in] regnum      The register of interest in the PREVIOUS frame
    @return                 A value structure representing the register. */
static struct value *
arc_sigtramp_frame_prev_register (struct frame_info *this_frame,
				  void **this_cache,
				  int regnum)
{
  /* Make sure we've initialized the cache. */
  struct arc_unwind_cache *info =
    arc_sigtramp_frame_cache (this_frame, this_cache);

  ARC_ENTRY_DEBUG ("")

  return trad_frame_get_prev_register (this_frame, info->saved_regs, regnum);

}	/* arc_sigtramp_frame_prev_register () */


/*! Frame sniffer for signal handler frame.

    Only recognize a frame if we have a sigcontext_addr hander in the target
    dependency.

    @note This function has changed from GDB 6.8. It now takes a reference to
          THIS frame, not the NEXT frame.

    @param[in] this_frame  Frame info for THIS frame.

    @return Non-zero (TRUE) if this frame is accepted, zero (FALSE)
    otherwise. */
static int
arc_sigtramp_frame_sniffer (const struct frame_unwind *self,
			   struct frame_info *this_frame,
			   void **this_cache)
{
  struct gdbarch_tdep *tdep;

  ARC_ENTRY_DEBUG ("")

  tdep = gdbarch_tdep (get_frame_arch (this_frame));

  /* If we have a sigcontext_addr handler, then just use the default frame
     sniffer. */
  if ((tdep->sigcontext_addr != NULL) &&
      (tdep->is_sigtramp != NULL) && tdep->is_sigtramp (this_frame))
    {
      return default_frame_sniffer (self, this_frame, this_cache);
    }
  else
    {
      return FALSE;
    }
}	/* arc_sigtramp_frame_sniffer () */


/*! Structure defining the ARC ordinary frame unwind functions

    Since we are the fallback unwinder, we use the default frame sniffer,
    which always accepts the frame. */
static const struct frame_unwind arc_frame_unwind = {
  .type          = NORMAL_FRAME,
  .stop_reason   = default_frame_unwind_stop_reason,
  .this_id       = arc_frame_this_id,
  .prev_register = arc_frame_prev_register,
  .unwind_data   = NULL,
  .sniffer       = default_frame_sniffer,
  .dealloc_cache = NULL,
  .prev_arch     = NULL
};


/*! Structure defining the ARC signal frame unwind functions

    We use a custom sniffer, since we must only accept this frame in the right
    context. */
static const struct frame_unwind arc_sigtramp_frame_unwind = {
  .type          = SIGTRAMP_FRAME,
  .stop_reason   = default_frame_unwind_stop_reason,
  .this_id       = arc_sigtramp_frame_this_id,
  .prev_register = arc_sigtramp_frame_prev_register,
  .unwind_data   = NULL,
  .sniffer       = arc_sigtramp_frame_sniffer,
  .dealloc_cache = NULL,
  .prev_arch     = NULL
};


/*! Function identifying the frame base sniffers for normal frames.

    @param[in] this_frame  Frame info for THIS frame. */
static const struct frame_base *
arc_frame_base_sniffer (struct frame_info *this_frame)
{
  static const struct frame_base fb =
    {
      .unwind      = &arc_frame_unwind,
      .this_base   = arc_frame_base_address,
      .this_locals = arc_frame_base_address,
      .this_args   = arc_frame_base_address
    };

  return &fb;

}	/* arc_frame_base_sniffer () */


/*! Function identifying the frame base sniffers for signal frames.

    @param[in] this_frame  Frame info for THIS frame. */
static const struct frame_base *
arc_sigtramp_frame_base_sniffer (struct frame_info *this_frame)
{
  static const struct frame_base fb =
    {
      .unwind      = &arc_sigtramp_frame_unwind,
      .this_base   = arc_frame_base_address,
      .this_locals = arc_frame_base_address,
      .this_args   = arc_frame_base_address
    };

  return &fb;

}	/* arc_sigtramp_frame_base_sniffer () */

/*! Initialize GDB

    The functions set here are generic to *all* versions of GDB for ARC. The
    set functions are generally presented in the order they appear in
    gdbarch.h. For details, see the comments in that header file.

    @param[in] info    Information about the architecture from BFD.
    @param[in] arches  Linked list of prev GDB architectures (unused).
    @return            A newly created GDB architecture. */
static struct gdbarch *
arc_gdbarch_init (struct gdbarch_info info, struct gdbarch_list *arches)
{
  struct gdbarch_tdep *tdep;
  struct gdbarch *gdbarch;
  const struct target_desc *tdesc = info.target_desc;
  struct tdesc_arch_data *tdesc_data = NULL;
  int num_regs = 0;
  const struct tdesc_feature *feature;
  int valid_p = 1;
  int i;
  /* Filled while parsing tdesc. */
  struct arc_reginfo *reginfo = NULL;

  /* Depending on whether this is ARCompact or ARCv2 we will assigned different
   * default registers sets (which will differ in exactly two core registers).
   * GDB will also refuse to accept register feature from invalid ISA - v2
   * features can be used only with v2 ARChitecture.  registers of invalid
   * architecture.  We read bfd_arch_info, which looks like to be a safe bet
   * here, as it looks like it is always initialized even when we don't pass
   * any elf file to GDB at all (it uses default arch in this case). Also GDB
   * will call this function multiple times, and if XML target description file
   * contains architecture specifications, then GDB will set this architecture
   * to info.bfd_arch_info, overriding value from ELF file if they are
   * different. That means that, where matters, this value is always our best
   * guess on what CPU we are debugging. It has been noted that that
   * architecture specified in tdesc file has higher precedence over ELF and
   * even "set architecture" - that is, using "set architecture" command will
   * have no effect when tdesc has "arch" tag.
  */
  const int is_arcv2 = (info.bfd_arch_info->mach == bfd_mach_arc_arcv2);
  int is_reduced_rf;
  const struct arc_reginfo const * core_reginfo;
  const char * core_feature_name;

  /* If target doesn't provide us description - use default one. */
  if (!tdesc_has_registers (tdesc))
    {
      if (is_arcv2)
	{
	  tdesc = tdesc_compatible_v2;
	  if (arc_debug)
	    fprintf_unfiltered (gdb_stdlog, "Using default register set for ARC v2.\n");
	}
      else
	{
	  tdesc = tdesc_compatible_arcompact;
	  if (arc_debug)
	    fprintf_unfiltered (gdb_stdlog, "Using default register set for ARCompact.\n");
	}
    }
  else
    {
      if (arc_debug)
	fprintf_unfiltered (gdb_stdlog, "Using provided register set.\n");
    }
  gdb_assert (tdesc);

  /* Now we can search for base registers. Depending on situation that might be
   * core registers or compatible registers. Core registers can be either full
   * or reduced. Summary:
   * - core-baseline.v2 + aux-baseline.v2
   * - core-reduced.v2 + aux-baseline.v2
   * - core-baseline.arcompact + aux-baseline.arcompcact
   * - compat.v2
   * - compat.v1
   * NB: It is interely feaseble to have ARCompact with reduced core regs, but
   * we ignore that because GCC doesn't support that and at the same time this
   * architecture is obsolete.
   */
  feature = tdesc_find_feature (tdesc, core_base_v2_feature_name);
  if (feature)
    {
      /* Confirm that register and architecture match, to prevent accidents in
       * some situations. This code will trigger an error if:
       *   1. XML tdesc doesn't specify arch explicitly, registers are for arch
       *   X, but ELF specifies arch Y.
       *   2. XML tdesc specifies arch X, but contains registers for arch Y.
       * It will not protect from case where XML or ELF specify arch X,
       * registers are for the same arch X, but the real target is arch Y. To
       * detect this case we need to check IDENTITY register.
       */
      if (!is_arcv2)
	{
	  fprintf_unfiltered (gdb_stdlog, "Error: ARC v2 target description "
	      "supplied for non-ARCv2 target.\n");
	  return NULL;
	}

      is_reduced_rf = FALSE;
      core_feature_name = core_base_v2_feature_name;
      core_reginfo = core_base_v2_reginfo;
    }
  else
    {
      feature = tdesc_find_feature (tdesc, core_reduced_v2_feature_name);
      if (feature)
	{
	  if (!is_arcv2)
	    {
	      fprintf_unfiltered (gdb_stdlog, "Error: ARC v2 target description "
		  "supplied for non-ARCv2 target.\n");
	      return NULL;
	    }

	  is_reduced_rf = TRUE;
	  core_feature_name = core_reduced_v2_feature_name;
	  core_reginfo = core_base_v2_reginfo;
	}
      else
        {
	  feature = tdesc_find_feature (tdesc, core_base_arcompact_feature_name);
	  if (feature)
	    {
	      if (is_arcv2)
		{
		  fprintf_unfiltered (gdb_stdlog, "Error: ARCompact target description "
		      "supplied for non-ARCompact target.\n");
		  return NULL;
		}

	      is_reduced_rf = FALSE;
	      core_feature_name = core_base_arcompact_feature_name;
	      core_reginfo = core_base_arcompact_reginfo;
	    }
	  else
	    {
	      fprintf_unfiltered (gdb_stdlog, "Error: Couldn't find core "
		  "register feature in supplied target description.");
	      return NULL;
	    }
	}
    }

  tdesc_data = tdesc_data_alloc ();

  gdb_assert (feature);
  gdb_assert (valid_p);

  for (i = 0; i < 64; i++)
    {
      /* R61 and R62 do never exist in real hardware, however have to check for
       * them to preserve compatibility with old gdbserver which reserve a slot
       * for them in g/G-packet. */

      /* If rf16, then skip extra registers. */
      if (is_reduced_rf && ((i >= 4 && i <= 9) || (i >= 16 && i <= 25)))
        continue;

      valid_p = tdesc_numbered_register (feature, tdesc_data, i,
          core_reginfo[i].name);

      /* - Ignore errors in extension registers - they are optional.
       * - Ignore missing ILINK because it doesn't make sense for Linux targets.
       * - Ignore missing ILINK2 when architecture is ARCompact, because it
       *   doesn't make sense for Linux targets.
       * In theory those optional registers should be in separate features, but
       * that's just crazy - features would be tiny and numerous and would be
       * make for complex maintanence, especially since regnums of different
       * features would interleve.
       *   */
      if (!valid_p && (i <= 28 || i == 31 || i == 60 || i == 63 ||
	    (i == 30 && is_arcv2)))
        {
          fprintf_unfiltered (gdb_stdlog, "Error: Cannot find required "
	  "register `%s' in feature `%s'.\n",
	  core_reginfo[i].name, core_feature_name);
          tdesc_data_cleanup (tdesc_data);
          return NULL;
        }
    }

  num_regs = i;

  /* Mandatory AUX registeres are intentionally few and are common between
   * ARCompact and ARC v2, so same code can be used for both. */
  feature = tdesc_find_feature (tdesc, aux_base_v2_feature_name);
  if (!feature)
    {
      fprintf_unfiltered (gdb_stdlog, "Error: Cannot find required feature "
          "`%s' in supplied target description.\n", aux_base_v2_feature_name);
      tdesc_data_cleanup (tdesc_data);
      return NULL;
    }

  for (i = 0; i < ARRAY_SIZE (aux_base_v2_reginfo); i++)
    {
      valid_p = tdesc_numbered_register (feature, tdesc_data, \
	  num_regs + i, aux_base_v2_reginfo[i].name);
      /* LP_registers are optional */
      if (!valid_p && (i + num_regs != ARC_LP_START_REGNUM ) &&
	  (i + num_regs != ARC_LP_END_REGNUM))
	{
	  fprintf_unfiltered (gdb_stdlog, "Error: Cannot find required register "
	      "`%s' in feature `%s'.\n",
	      aux_base_v2_reginfo[i].name, tdesc_feature_name (feature));
	  tdesc_data_cleanup (tdesc_data);
	  return NULL;
	}
    }

  /* Copy both core and AUX reginfo at once. */
  reginfo = xmemdup (core_reginfo,
      sizeof (struct arc_reginfo) * num_regs,
      sizeof (struct arc_reginfo) * (num_regs + i));
  memcpy (&(reginfo[num_regs]), aux_base_v2_reginfo,
      sizeof (struct arc_reginfo) * i);

  num_regs += i;

  /* Check for compatible AUX registers. */
  feature = tdesc_find_feature (tdesc, aux_compatible_feature_name);
  if (feature)
    {
      for (i = 0; i < ARRAY_SIZE (aux_compatible_reginfo); i++)
	{
	  valid_p = tdesc_numbered_register (feature, tdesc_data, \
	      num_regs + i, aux_compatible_reginfo[i].name);
	  if (!valid_p)
	    {
	      fprintf_unfiltered (gdb_stdlog, "Error: Cannot find required register "
		  "`%s' in feature `%s'.\n",
		  aux_compatible_reginfo[i].name, tdesc_feature_name (feature));
	      tdesc_data_cleanup (tdesc_data);
	      return NULL;
	    }
	}

      /* realloc will do free (reginfo), so we shouldn't do that. */
      reginfo = xrealloc (reginfo, sizeof (struct arc_reginfo) * (num_regs + i));
      num_regs += i;
    }

  /* Determine which OSABI we have. A different version of this function is
     linked in for each GDB target. Must do this before we allocate the
     gdbarch, since it is copied into the gdbarch! */
  info.osabi = arc_get_osabi ();

  /* Allocate the ARC-private target-dependent information structure, and the
     GDB target-independent information structure. */
  tdep = xmalloc (sizeof (struct gdbarch_tdep));
  memset (tdep, 0, sizeof (*tdep));
  tdep->reginfo = reginfo;
  tdep->reginfo_sz = num_regs;
  gdbarch = gdbarch_alloc (&info, tdep);

  /* gdbarch setup. */
  /* Default gdbarch_bits_big_endian suffices. */
  set_gdbarch_short_bit (gdbarch, 16);
  set_gdbarch_int_bit (gdbarch, 32);
  set_gdbarch_long_bit (gdbarch, 32);
  set_gdbarch_long_long_bit (gdbarch, 64);
  set_gdbarch_long_long_align_bit (gdbarch, 32);
  /* No need for half_bit, since half precision FP is not supported. */
  set_gdbarch_float_bit (gdbarch, 32);
  set_gdbarch_float_format (gdbarch, floatformats_ieee_single);
  set_gdbarch_double_bit (gdbarch, 64);
  set_gdbarch_double_format (gdbarch, floatformats_ieee_double);
  /* No need for long_double, since quad precison FP is not supported. */
  set_gdbarch_ptr_bit (gdbarch, 32);
  /* Default gdbarch_addr_bit suffices (same as gdbarch_ptr_bit) */
  /* No need for gdbarch_dwarf2_addr_size */
  set_gdbarch_char_signed (gdbarch, 0);	/* Default unsigned chars */
  /* No need for read_pc, since PC is normal register */
  /* write_pc is target dependent: no for linux, exists for elf32 */
  set_gdbarch_virtual_frame_pointer (gdbarch, arc_virtual_frame_pointer);
  /* No need for special pseudo register read/write. */
  /* tdesc_use_registers expects gdbarch_num_regs to return number of registers
   * parsed by gdbarch_init, and then it will add all of the remaining
   * registers and will increase number of registers. */
  set_gdbarch_num_regs (gdbarch, tdep->reginfo_sz);
  set_gdbarch_num_pseudo_regs (gdbarch, 0);
  /* We don't use Agent Expressions here (only MIPS does it seems) */
  set_gdbarch_sp_regnum (gdbarch, ARC_SP_REGNUM);
  set_gdbarch_pc_regnum (gdbarch, ARC_PC_REGNUM);
  set_gdbarch_ps_regnum (gdbarch, ARC_STATUS32_REGNUM);
  set_gdbarch_fp0_regnum (gdbarch, -1);		/* No FPU registers */
  /* Don't try to convert STAB, ECOFF or SDB regnums. We don't really support
     these debugging formats, and if used assume regnums are the same. */
  /* No need to convert DWARF register numbers, since they are now the same
     (this is a change from GDB 6.8 for ARC). */
  /* gdbarch_register_name will be set bytdesc_use_registers. */
  /* gdbarch_register_type will be set bytdesc_use_registers. */
  set_gdbarch_dummy_id (gdbarch, arc_dummy_id);
  /* No need for deprecated_fp_regnum */
  set_gdbarch_push_dummy_call (gdbarch, arc_push_dummy_call);
  /* call_dummy_location obsoleted by push_dummy_code */
  set_gdbarch_push_dummy_code (gdbarch, arc_push_dummy_code);
  /* Use default_print_registers_info. */
  set_gdbarch_print_float_info (gdbarch, arc_print_float_info);
  /* No vector registers need printing. */
  /* Default gdbarch_register_sim_regno suffices */
  /* Which registers can be fetched and stored is target specific. */
  set_gdbarch_get_longjmp_target (gdbarch, arc_get_longjmp_target);
  set_gdbarch_believe_pcc_promotion (gdbarch, 1);
  /* No need for gdbarch_convert_register_p, gdbarch_register_to_value or
     gdbarch_value_to_register, since values are represented the same in
     memory and registers. */
  /* No need for gdbarch_value_from_register, since there is no special
     treatment of values from registers. */
  /* No need for gdbarch_pointer_to_address or gdbarch_address_to_pointer,
     since pointers and addresses are the same thing for ARC. */
  /* No special conversion need between integers and addresses. */
  set_gdbarch_return_value (gdbarch, arc_return_value);
  /* No special treatment of return values stored in hidden first params. */
  set_gdbarch_skip_prologue (gdbarch, arc_skip_prologue);
  /* Nothing special for skipping main prologue */
  set_gdbarch_inner_than (gdbarch, core_addr_lessthan);
  /* gdbarch_breakpoint_from_pc is target specific. */
  /* No need for gdbarch_remote_breakpoint_from_pc, since all breakpoints are
     client side memory breakpoints. */
  /* No need for gdbarch_adjust_breakpoint_address. */
  /* Default gdbarch_memory_insert_breakpoint and
     gdbarch_memory_remove_breakpoint suffice. */
  /* ARC 600 is a special case for decr_pc, it is handled in arc-elf-tdep.c */
  set_gdbarch_decr_pc_after_break (gdbarch, 0);
  /* Default gdbarch_remote_register_number suffices. */
  /* Whether to support TLS is target specific (yes for Linux, no for ELF) */
  /* We don't need to skip any args when printing frame local args. */
  set_gdbarch_unwind_pc (gdbarch, arc_unwind_pc);
  set_gdbarch_unwind_sp (gdbarch, arc_unwind_sp);
  /* We can't work out how many frame args (only the VAX can) */
  set_gdbarch_frame_align (gdbarch, arc_frame_align);
  /* Don't need gdbarch_stabs_argument_has_addr. */
  /* Default red zone suffices. */
  /* Default conversion from function pointer to address suffices. */
  /* No need to remove or smash address bits. */
  /* Whether we need software single-step is target specific (yes for Linux,
     no for ELF). */
  /* We can't single step through a delay slot */
  set_gdbarch_print_insn (gdbarch, ARCompact_decodeInstr);
  set_gdbarch_skip_trampoline_code (gdbarch, arc_skip_trampoline_code);
  /* Whether we need to skip the shared object resolver is target specific
     (yes for Linux, no for ELF). */
  /* Don't need to know if we are in the epilogue. */
  /* Don't need to make special msymbols for ELF of COFF. */
  set_gdbarch_cannot_step_breakpoint (gdbarch, 1);
  set_gdbarch_have_nonsteppable_watchpoint (gdbarch, 1);
  /* No special address classes. */
  /* Default gdbarch_register_reggroup_p suffices. */
  /* No need for fetch_pointer_argument (Objective C support only) */
  /* Core file handling is target specific (yes for Linux, no for ELF). */
  /* No special handling needed for C++ vtables. */
  /* No special code to skip permanent breakpoints. */
  set_gdbarch_max_insn_length (gdbarch, 4);
  /* @todo Currently we don't support displaced stepping. */
  /* No need for instruction relocation or overlay support. */
  /* No special handling of STABS static vars needed. */
  /* No process recording (for reverse execution?) needed. */
  /* No signal translation needed. */
  /* No architecture specific symbol information. */
  /* @todo We don't yet catch syscalls. */
  /* No support for SystemTap. */
  /* No gobal shared object list or breakpoints. */
  /* @todo Should ELF report it has a shared address space? Probably not,
           since it is a single thread. */
  /* No fast tracepoint support. */
  /* No special charset handling. */
  /* No alternative file extensions for shared objects. */
  /* Not a DOS-based file system. */
  /* No bytecode handling needed. */
  /* No special handling of "info proc" needed. */
  /* No special global symbol search of objfiles needed. */

  /* Frame unwinders and sniffers. We use DWARF2 if it's available, for which
     we set up a register initialization function. Then we have ARC specific
     unwinders and sniffers for signal frames and then ordinary frames. */
  dwarf2_frame_set_init_reg (gdbarch, arc_dwarf2_frame_init_reg);
  dwarf2_append_unwinders (gdbarch);
  frame_unwind_append_unwinder (gdbarch, &arc_sigtramp_frame_unwind);
  frame_unwind_append_unwinder (gdbarch, &arc_frame_unwind);
  frame_base_append_sniffer (gdbarch, dwarf2_frame_base_sniffer);
  frame_base_append_sniffer (gdbarch, arc_sigtramp_frame_base_sniffer);
  frame_base_append_sniffer (gdbarch, arc_frame_base_sniffer);
  
  /* Put OS specific stuff into gdbarch. This can override any of the generic
     ones specified above. */
  arc_gdbarch_osabi_init (gdbarch);

  tdesc_use_registers (gdbarch, tdesc, tdesc_data);

  return gdbarch;			/* Newly created architecture. */

}	/* arc_gdbarch_init () */


/*! Dump out the target specific information.

    @param[in] gdbarch  Current GDB architecture
 */
static void
arc_dump_tdep (struct gdbarch *gdbarch, struct ui_file *file)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  fprintf_unfiltered (file, "arc_dump_tdep: is_sigtramp = %p\n",
		      tdep->is_sigtramp);
  fprintf_unfiltered (file, "arc_dump_tdep: sigcontext_addr = %p\n",
		      tdep->sigcontext_addr);
  fprintf_unfiltered (file, "arc_dump_tdep: sc_reg_offset = %p\n",
		      tdep->sc_reg_offset);
  fprintf_unfiltered (file, "arc_dump_tdep: sc_num_regs = %d\n",
		      tdep->sc_num_regs);
  fprintf_unfiltered (file, "arc_dump_tdep: reginfo_sz = %zd\n",
		      tdep->reginfo_sz);
}	/* arc_dump_tdep () */


/* -------------------------------------------------------------------------- */
/*			 Externally visible functions                         */
/* -------------------------------------------------------------------------- */

/*
    @param[in] gdbarch  Current GDB architecture
*/
void
arc_initialize_disassembler (struct gdbarch *gdbarch, 
			     struct disassemble_info *info)
{
  /* N.B. this type cast is not strictly correct: the return types differ! */
  init_disassemble_info (info, gdb_stderr,
			 (fprintf_ftype) fprintf_unfiltered);
  info->arch = gdbarch_bfd_arch_info (gdbarch)->arch;
  info->mach = gdbarch_bfd_arch_info (gdbarch)->mach;
  info->endian = gdbarch_byte_order (gdbarch);
  info->read_memory_func = arc_read_memory_for_disassembler;
}


/*! Warn about plain "set arc". */
static void
set_arc_command (char *args, int from_tty)
{
  printf_unfiltered (_("\
\"set arc\" must be followed by an apporpriate subcommand.\n"));
  help_list (setarccmdlist, "set arc ", all_commands, gdb_stdout);
}


/*! Warn about plain "show arc". */
static void
show_arc_command (char *args, int from_tty)
{
  cmd_show_list (showarccmdlist, from_tty, "");
}

/* this function is called from gdb */
void
_initialize_arc_tdep (void)
{
  /* register the ARC processor architecture with gdb, providing an
   * initialization function and a dump function;
   *
   * 'bfd_arch_arc' is an enumeration value specifically denoting the ARC
   *                architecture
   */
  gdbarch_register (bfd_arch_arc, arc_gdbarch_init, arc_dump_tdep);

  initialize_tdesc_compatible_v2 ();
  initialize_tdesc_compatible_arcompact ();

  /* register ARC-specific commands with gdb */

  /* Add root prefix command for all "set arc"/"show arc" commands.  */
  add_prefix_cmd ("arc", no_class, set_arc_command,
		  _("Various ARC-specific commands."),
		  &setarccmdlist, "set arc ", 0, &setlist);

  add_prefix_cmd ("arc", no_class, show_arc_command,
		  _("Various ARC-specific commands."),
		  &showarccmdlist, "show arc ", 0, &showlist);

  /* Debug internals for ARC GDB.  */
  add_setshow_zinteger_cmd ("arc", class_maintenance,
			    &arc_debug,
			    _("Set ARC specific debugging."),
			    _("Show ARC specific debugging."),
			    _("Non-zero enables ARC specific debugging."),
			    NULL,
			    NULL,
			    &setdebuglist,
			    &showdebuglist);
}	/* _initialize_arc_tdep () */

/* vim: set sts=2 shiftwidth=2 ts=8: */
