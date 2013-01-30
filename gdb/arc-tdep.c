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
/*     dependencies.  In particular, it has knowledge of the processor ABI.   */
/*                                                                            */
/*     See                                                                    */
/*                       System V ABI Supplement                              */
/*                               4093-004                                     */
/*                                                                            */
/*     for a complete definition of the ABI.                                  */
/*                                                                            */
/*                                                                            */
/* Stack Frame Layout:                                                        */
/*     This shows the layout of the stack frame for the general case of a     */
/*     function call; a given function might not have a variable number of    */
/*     arguments or local variables, or might not save any registers, so it   */
/*     would not have the corresponding frame areas.  Additionally, a leaf    */
/*     function (i.e. one which calls no other functions) does not need to    */
/*     save the contents of the BLINK register (which holds its return        */
/*     address), and a function might not have a frame pointer.               */
/*                                                                            */
/*     N.B. the stack grows downward, so SP points below FP in memory; SP     */
/*          always points to the last used word on the stack, not the first   */
/*          one.                                                              */
/*                                                                            */
/*                   |                       |   |                            */
/*                   |      arg word N       |   | caller's                   */
/*                   |           :           |   | frame                      */
/*                   |      arg word 10      |   |                            */
/*                   |      arg word 9       |   |                            */
/*       old SP ---> |-----------------------| --                             */
/*                   |   var arg word 8      |   |                            */
/*                   |           :           |   |                            */
/*                   |   var arg word P+1    |   |                            */
/*                   |-----------------------|   |                            */
/*                   |                       |   |                            */
/*                   |      callee-saved     |   |                            */
/*                   |        registers      |   |                            */
/*                   |                       |   |                            */
/*                   |-----------------------|   |                            */
/*                   |      saved blink (*)  |   |                            */
/*                   |-----------------------|   | callee's                   */
/*                   |      saved FP         |   | frame                      */
/*           FP ---> |-----------------------|   |                            */
/*                   |                       |   |                            */
/*                   |         local         |   |                            */
/*                   |       variables       |   |                            */
/*                   |                       |   |                            */
/*                   |       register        |   |                            */
/*                   |      spill area       |   |                            */
/*                   |                       |   |                            */
/*                   |     outgoing args     |   |                            */
/*                   |                       |   |                            */
/*           SP ---> |-----------------------| --                             */
/*                   |                       |                                */
/*                   |         unused        |                                */
/*                   |                       |                                */
/*                               |                                            */
/*                               |                                            */
/*                               V                                            */
/*                           downwards                                        */
/*                                                                            */
/*     The list of arguments to be passed to a function is considered to be a */
/*     sequence of N words (as though all the parameters were stored in order */
/*     in memory with each parameter occupying an integral number of words).  */
/*     Words 1 .. 8 are passed in registers 0 .. 7; if the function has more  */
/*     than 8 words of arguments then words 9 .. N are passed on the stack in */
/*     the caller's frame.                                                    */
/*                                                                            */
/*     If the function has a variable number of arguments, e.g. it has a form */
/*     such as                                                                */
/*                      function(p1, p2, ...);                                */
/*                                                                            */
/*     and P words are required to hold the values of the named parameters    */
/*     (which are passed in registers 0 .. P-1), then the remaining 8 - P     */
/*     words passed in registers P .. 7 are spilled into the top of the frame */
/*     so that the anonymous parameter words occupy a continous region.       */
/*                                                                            */
/*     (*) if saved.                                                          */
/*                                                                            */
/* Build Configuration:                                                       */
/*     The ARC gdb may be built in two different configurations, according to */
/*     the nature of the target that it is to debug:                          */
/*                                                                            */
/*     1) arc-elf32:                                                          */
/*           for debugging 'bare-metal' builds of user code (i.e. built with  */
/*           newlib)                                                          */
/*                                                                            */
/*           ARC-specific modules:                                            */
/*                arc-embed                                                   */
/*                arc-jtag-tdep                                               */
/*                arc-jtag                                                    */
/*                arc-jtag-ops                                                */
/*                arc-jtag-actionpoints                                       */
/*                arc-jtag-fileio                                             */
/*                arc-aux-registers                                           */
/*                arc-architecture                                            */
/*                arc-board                                                   */
/*                                                                            */
/*     2) arc-linux-uclibc:                                                   */
/*           for deugging user mode Linux applications, via communication to  */
/*           the remote gdbserver process, running on Linux for ARC700        */
/*                                                                            */
/*           ARC-specific modules:                                            */
/*                arc-tdep                                                    */
/*                arc-linux-tdep                                              */
/*                                                                            */
/*     Note that the arc-embed.c and arc-tdep.c files are textually identical */
/*     except for the inclusion of a different configuration header file.     */
/*     This is simply a device for building the two different configurations, */
/*     and should be replaced by a better method which avoids duplication of  */
/*     the source.                                                            */
/*                                                                            */
/*     This module (arc-embed/arc-tdep) provides operations which are common  */
/*     to both configurations; operations which are specific to one, or which */
/*     have different variants in each configuration, are provided by the     */
/*     other modules.                                                         */
/*                                                                            */
/******************************************************************************/

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

/* ARC header files */
#include "opcode/arc.h"
#include "opcodes/arc-dis.h"
#include "opcodes/arc-ext.h"
#include "opcodes/arcompact-dis.h"
#include "arc-tdep.h"


/* -------------------------------------------------------------------------- */
/*                               local types                                  */
/* -------------------------------------------------------------------------- */

typedef struct
{
  const char *name;
  CORE_ADDR address;
  int is_argument;
  int is_callee;
  int is_array;
  unsigned int size;
  unsigned int element_size;
} arc_local_var_t;


/* The frame unwind cache for the ARC */

typedef struct
{
  /* BLINK save location offset from previous SP (-ve value) */
  int blink_save_offset_from_prev_sp;

  /* The stack pointer at the time this frame was created; i.e. the
   * caller's stack pointer when this function was called.  It is used
   * to identify this frame.
   */
  CORE_ADDR prev_sp;

  /* The frame base (as held in FP).
   *
   * N.B. this is NOT the address of the lowest word in the frame!
   */
  CORE_ADDR frame_base;

  /* Change in SP from previous SP (-ve value) - this is computed by scanning
   * the prologue of the function: initially 0, it is updated for each
   * instruction which changes SP (either explicitly by a subtraction from SP
   * or implicitly by a push operation), so at each point in the prologue it
   * gives the difference between the previous SP (i.e. before the function
   * was called) and the current SP at that point; at the end of the prologue
   * it holds the total change in SP, i.e. the size of the frame.
   */
  LONGEST delta_sp;

  /* offset of old stack pointer from frame base (+ve value) */
  LONGEST old_sp_offset_from_fp;

  /* Is this a leaf function? */
  int is_leaf;
  /* Is there a frame pointer? */
  int uses_fp;

  /* Offsets for each register in the stack frame */
  struct trad_frame_saved_reg *saved_regs;
  unsigned int saved_regs_mask;
} arc_unwind_cache_t;


/* -------------------------------------------------------------------------- */
/*                               externally visible data                      */
/* -------------------------------------------------------------------------- */

/*! Global debug flag */
int arc_debug;


/* -------------------------------------------------------------------------- */
/*                               local macros                                 */
/* -------------------------------------------------------------------------- */

#define WORD_ALIGNED(addr)         ((addr) & ~(BYTES_IN_WORD - 1))
#define WORDS_OCCUPIED(bytes)      (((bytes) + BYTES_IN_WORD - 1)	\
				    / BYTES_IN_WORD)
#define ROUND_UP_TO_WORDS(bytes)   (WORDS_OCCUPIED(bytes) * BYTES_IN_WORD)



/* Macros to be used with disassembling the prologue and update the frame info.
 * The *FI macros are to update the frame info and the ACT macros are to
 * actually do the action on a corresponding match.
 */

#define IS_INSTRUCTION(insn_name, search_string)	\
  !strcmp(insn_name, search_string)

#define CHECK_OPERAND_STRING_AND_ACT(target_check, search_string, action) \
    if (strstr(target_check, search_string) == target_check)              \
    {                                                                     \
        action;                                                           \
        return TRUE;                                                      \
    }


/* The frame info changes by changing the decrementing the delta_sp and setting
 * the leaf function flag to be False (if this function prologue is saving blink
 * then it must be going to call another function - so it can not be a leaf!);
 * also the offset of the blink register save location from the previous value
 * of sp is recorded.  This will eventually used to compute the address of the
 * save location:
 *
 *         <blink saved address> = <prev sp> + <blink offset from prev sp>
 *
 * The addition (+=) below is because the sp offset and the instruction offset
 * are negative - so incrementing the sp offset by the instruction offset is
 * actually making the sp offset more negative, correctly reflecting that SP
 * is moving further down the downwards-growing stack.
 */

#define PUSH_BLINK(offset)                                           \
    {                                                                \
        info->delta_sp += offset;                                    \
        info->blink_save_offset_from_prev_sp = (int) info->delta_sp; \
        info->is_leaf = FALSE;                                       \
    }

#define PUSH_BLINK_ACT                          \
    do {                                        \
           if (info) PUSH_BLINK(instr->_offset) \
       } while (0);


#define IS_PUSH_BLINK_FI(state) CHECK_OPERAND_STRING_AND_ACT(state->operandBuffer, "blink", PUSH_BLINK_ACT)


/* At the point that that FP is pushed onto the stack (so saving the dynamic
 * link chain pointer to the previous frame), at the address that will be the
 * base of the new frame, we know the offset of SP from the previous SP - so the
 * offset of the old SP from the new frame base is known (the -ve delta_sp is
 * negated to give the +ve old_sp_offset_from_fp).
 */
#define PUSH_FP_ACT					\
  do {							\
    if (info)						\
      {							\
	info->delta_sp += instr->_offset;		\
	info->old_sp_offset_from_fp = -info->delta_sp;	\
      }} while (0);

#define IS_PUSH_FP_FI(state)						\
  CHECK_OPERAND_STRING_AND_ACT(state->operandBuffer, "fp", PUSH_FP_ACT)

#define UPDATE_FP_ACT				      \
  do {						      \
    if (info)					      \
      info->uses_fp = TRUE;			      \
  } while (0);

#define IS_UPDATE_FP_FI(state)						\
  if (IS_INSTRUCTION(state->instrBuffer, "mov"))			\
    {									\
      CHECK_OPERAND_STRING_AND_ACT(state->operandBuffer, "fp,sp",	\
				   UPDATE_FP_ACT);			\
    }

#define UPDATE_STACK_SPACE(state)			\
  do {							\
    if (info) {						\
      /* Eat up sp,sp */				\
      int immediate = atoi(state->operandBuffer + 6);	\
      info->delta_sp -= immediate;			\
    }							\
  } while (0);


#define IS_SUB_SP_FI(state)						\
  if (IS_INSTRUCTION(state->instrBuffer, "sub")				\
      || IS_INSTRUCTION(state->instrBuffer, "sub_s"))			\
    {									\
      CHECK_OPERAND_STRING_AND_ACT(state->operandBuffer, "sp,sp",	\
				   UPDATE_STACK_SPACE(state))		\
    }


/* -------------------------------------------------------------------------- */
/*                               local functions                              */
/* -------------------------------------------------------------------------- */


/*! Dump the frame info

    Used for internal debugging only. */  
static void
arc_print_frame_info (char *message, arc_unwind_cache_t *info,
		      int addresses_known)
{
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

  for (i = ARC_ABI_FIRST_CALLEE_SAVED_REGISTER;
       i < ARC_ABI_LAST_CALLEE_SAVED_REGISTER; i++)
    {
      if (info->saved_regs_mask & (1 << i))
	fprintf_unfiltered (gdb_stdlog, "saved register R%02d %s %s\n",
			    i, (addresses_known) ? "address" : "offset",
			    phex (info->saved_regs[i].addr, BYTES_IN_ADDRESS));
    }
  fprintf_unfiltered (gdb_stdlog, "-------------------\n");

}	/* arc_print_frame_info () */


/*! Text of the instruction state returned by the disassembler.

    Used for internal debugging only. */
static const char *
arc_debug_operand_type (enum ARC_Debugger_OperandType value)
{
  switch (value)
    {
    case ARC_LIMM:
      return "LIMM";
    case ARC_SHIMM:
      return "SHIMM";
    case ARC_REGISTER:
      return "REGISTER";
    case ARCOMPACT_REGISTER:
      return "COMPACT REGISTER";
    case ARC_UNDEFINED:
      return "UNDEFINED";
    }
  return "?";
}


/*! Print the instruction state.

    Used for internal debugging only. */
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


/*! Wrapper for the target_read_memory function. */
static int
arc_read_memory_for_disassembler (bfd_vma memaddr, bfd_byte *myaddr,
				  unsigned int length,
				  struct disassemble_info *info) // unused
{
  return target_read_memory ((CORE_ADDR) memaddr, (gdb_byte *) myaddr,
			     (int) length);

}	/* arc_read_memory_for_disassembler () */


/*! Callback to set the disassembler

    We use the new_objfile observer to trigger this function.

    We wait until an objfile is loaded, since the disassembler can use its
    OBFD to find out what extensions are defined. If we load a new objfile,
    this will get redefined. */
static void
arc_set_disassembler (struct objfile *objfile)
{
  if (objfile)
    {
      set_gdbarch_print_insn (target_gdbarch,
			      arc_get_disassembler (objfile->obfd));
    }
}	/* arc_set_disassembler () */


/*! Simple utility function to create a new frame cache structure

    The implementations has changed since GDB 6.8, since we are now provided
    with the address of THIS frame, rather than the NEXT frame. */
static arc_unwind_cache_t *
arc_create_cache (struct frame_info *this_frame)
{
  arc_unwind_cache_t *cache = FRAME_OBSTACK_ZALLOC (arc_unwind_cache_t);

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


/*! Unwind the program counter.

    @param[in] next_frame  NEXT frame from which the PC in THIS frame should be
                           unwound.
    @return  The value of the PC in THIS frame. */
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
    @return  The value of the SP in THIS frame. */
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


/*! Return the base address of the frame

    The implementations has changed since GDB 6.8, since we are now provided
    with the address of THIS frame, rather than the NEXT frame.

    For ARC, the base address is the frame pointer

    @param[in] this_frame      The current stack frame.
    @param[in] prologue_cache  Any cached prologue for THIS function.

    @return  The frame base address */
static CORE_ADDR
arc_frame_base_address (struct frame_info  *this_frame,
			 void              **prologue_cache) 
{
  return  (CORE_ADDR) get_frame_register_unsigned (this_frame, ARC_FP_REGNUM);

}	/* arc_frame_base_address() */


/*! Compute THIS frame's stack pointer and base pointer.

    This function has changed from GDB 6.8. It now takes a reference to THIS
    frame, not the NEXT frame.

    This is also the frame's ID's stack address. */
static void
arc_find_this_sp (arc_unwind_cache_t * info,
		  struct frame_info *this_frame)
{
  struct gdbarch *gdbarch;

  ARC_ENTRY_DEBUG ("this_frame = %p", this_frame)

  gdbarch = get_frame_arch (this_frame);

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
      info->saved_regs[ARC_FP_REGNUM].addr = (long long) this_base;

      /* The previous SP is the current frame base + the difference between
       * that frame base and the previous SP.
       */
      info->prev_sp =
	info->frame_base + (CORE_ADDR) info->old_sp_offset_from_fp;

      for (i = ARC_ABI_FIRST_CALLEE_SAVED_REGISTER;
	   i < ARC_ABI_LAST_CALLEE_SAVED_REGISTER; i++)
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

    If it is, the information in the frame unwind cache is updated. */
static int
arc_is_callee_saved (unsigned int reg, int offset,
		     arc_unwind_cache_t * info)
{
  if (ARC_ABI_FIRST_CALLEE_SAVED_REGISTER <= reg
      && reg <= ARC_ABI_LAST_CALLEE_SAVED_REGISTER)
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
	      arc_print_frame_info ("after callee register save", info, FALSE);
	    }

	  return TRUE;
	}
    }

  return FALSE;

}	/* arc_is_callee_saved () */


/*! Is disassembled instruction in prologue?

    Determine whether the given disassembled instruction may be part of a
    function prologue.

    If it is, the information in the frame unwind cache may be updated. */
static int
arc_is_in_prologue (arc_unwind_cache_t * info, struct arcDisState *instr)
{
  /* Might be a push or a pop */
  if (instr->_opcode == 0x3)
    {
      if (instr->_addrWriteBack != (char) 0)
	{
	  /* This is a st.a  */
	  if (instr->ea_reg1 == ARC_ABI_STACK_POINTER)
	    {
	      if (instr->_offset == -4)
		{
		  /* This is a push something at SP */
		  /* Is it a push of the blink? */
		  IS_PUSH_BLINK_FI (instr);

		  /* Is it a push for fp? */
		  IS_PUSH_FP_FI (instr);
		}
	      else
		{
		  if (instr->sourceType == ARC_REGISTER)
		    {
		      /* st.a <reg>, [sp,<offset>] */

		      if (arc_is_callee_saved
			  (instr->source_operand.registerNum, instr->_offset,
			   info))
			{
			  /* this is a push onto the stack, so change delta_sp */
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
	      if (instr->ea_reg1 == ARC_ABI_STACK_POINTER)
		{
		  /* st <reg>, [sp,offset] */

		  if (arc_is_callee_saved
		      (instr->source_operand.registerNum, instr->_offset,
		       info))
		    /* this is NOT a push onto the stack, so do not change delta_sp */
		    return TRUE;
		}

	      /* Is this the store of some register on the stack using the
	       * frame pointer? We check for argument registers getting saved
	       * and restored.
	       */
	      if (instr->ea_reg1 == ARC_ABI_FRAME_POINTER)
		{
		  if (IS_ARGUMENT_REGISTER
		      (instr->source_operand.registerNum))
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

  else if (instr->_opcode == 0x4)
    {
      /* A major opcode 0x4 instruction */
      /* We are usually interested in a mov or a sub */
      IS_UPDATE_FP_FI (instr);
      IS_SUB_SP_FI (instr);
    }

  else if (instr->_opcode == 0x18)
    {
      /* sub_s sp,sp,constant */
      IS_SUB_SP_FI (instr);

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
		  PUSH_BLINK (-BYTES_IN_REGISTER)}
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

	      if (arc_is_callee_saved (reg, offset, info))
		/* this is NOT a push onto the stack, so do not change delta_sp */
		return TRUE;
	    }
	}
    }

  return FALSE;

}	/* arc_is_in_prologue () */


/*! Scan the prologue.

    This function has changed from GDB 6.8. It now takes a reference to THIS
    frame, not the NEXT frame.

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
       sub  sp , sp , #immediate ; create space for local vars on the stack */
static CORE_ADDR
arc_scan_prologue (CORE_ADDR entrypoint,
		   struct frame_info *this_frame, arc_unwind_cache_t * info)
{
  struct gdbarch *gdbarch;
  int pc_regnum;
  CORE_ADDR prologue_ends_pc;
  CORE_ADDR final_pc;
  struct disassemble_info di;

  ARC_ENTRY_DEBUG ("this_frame = %p, info = %p", this_frame, info)

  gdbarch = get_frame_arch (this_frame);
  pc_regnum = gdbarch_pc_regnum (gdbarch);

  /* An arbitrary limit on the length of the prologue. If this_frame is NULL
     this means that there was no debug info and we are called from
     arc_skip_prologue; otherwise, if we know the frame, we can find the pc
     within the function.

     N.B. That pc will usually be after the end of the prologue, but it could
          actually be within the prologue (i.e. execution has halted within
          the prologue, e.g. at a breakpoint); in that case, do NOT go beyond
          that pc, as the instructions at the pc and after have not been
          executed yet, so have had no effect! */
  prologue_ends_pc = entrypoint;
  final_pc = (this_frame)
    ? get_frame_register_unsigned (this_frame, pc_regnum)
    : entrypoint + MAX_PROLOGUE_LENGTH;

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
      if (!arc_is_in_prologue (info, &current_instr))
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
	  arc_print_frame_info ("after prologue", info, FALSE);
	}

      arc_find_this_sp (info, this_frame);

      /* The PC is found in blink (the actual register or located on the
	 stack). */
      info->saved_regs[ARC_PC_REGNUM] = info->saved_regs[ARC_BLINK_REGNUM];

      if (arc_debug)
	{
	  arc_print_frame_info ("after previous SP found", info, TRUE);
	}
    }

  return prologue_ends_pc;

}	/* arc_scan_prologue () */


/*! Get return value of a function.

    Get the return value of a function from the registers used to return it,
    according to the convention used by the ABI. */
static void
arc_extract_return_value (struct gdbarch *gdbarch, struct type *type,
			  struct regcache *regcache, gdb_byte * valbuf)
{
  unsigned int len = TYPE_LENGTH (type);

  ARC_ENTRY_DEBUG ("")

  if (len <= BYTES_IN_REGISTER)
    {
      ULONGEST val;

      /* Get the return value from one register. */
      regcache_cooked_read_unsigned (regcache, ARC_ABI_RETURN_REGNUM, &val);
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
      regcache_cooked_read_unsigned (regcache, ARC_ABI_RETURN_LOW_REGNUM,
				     &low);
      regcache_cooked_read_unsigned (regcache, ARC_ABI_RETURN_HIGH_REGNUM,
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


/* This function loads the return value of a function into the registers used to
 * return it, according to the convention used by the ABI.
 */
static void
arc_store_return_value (struct gdbarch *gdbarch, struct type *type,
			struct regcache *regcache, const gdb_byte * valbuf)
{
  unsigned int len = TYPE_LENGTH (type);

  ARC_ENTRY_DEBUG ("")

  if (len <= BYTES_IN_REGISTER)
    {
      ULONGEST val;

      /* Put the return value into one register. */
      val = extract_unsigned_integer (valbuf, (int) len,
				      gdbarch_byte_order (gdbarch));
      regcache_cooked_write_unsigned (regcache, ARC_ABI_RETURN_REGNUM, val);

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

      regcache_cooked_write_unsigned (regcache, ARC_ABI_RETURN_LOW_REGNUM,
				      low);
      regcache_cooked_write_unsigned (regcache, ARC_ABI_RETURN_HIGH_REGNUM,
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

}	/* arc_extract_return_value () */


/* -------------------------------------------------------------------------- */
/*                       local functions called from gdb                      */
/* -------------------------------------------------------------------------- */

/*!  Standard register type for the ARC platform.
 
    It would be builtin_type_uint32 until we consider the DSP extensions. */
static struct type *
arc_register_type (struct gdbarch *gdbarch, int regnum)
{
  return builtin_type (gdbarch)->builtin_uint32;

}	/* arc_register_type () */


/*! Skip the prologue for the function at pc.

    This is done by checking from the line information read from the DWARF, if
    possible; otherwise, we scan the function prologue to find its end. */
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
      struct symbol *sym = lookup_symbol (func_name, NULL, VAR_DOMAIN, NULL);

      if ((sym != NULL) && SYMBOL_LANGUAGE (sym) != language_asm)
	{
	  /* Don't use this trick for assembly source files. */
	  struct symtab_and_line sal = find_pc_line (func_addr, 0);

	  if ((sal.line != 0) && (sal.end < func_end))
	    return sal.end;
	}
    }

  /* Find the address of the first instruction after the prologue by
   * scanning through it - no other information is needed, so pass NULL
   * for the other parameters.
   */
  return arc_scan_prologue (pc, NULL, NULL);

}	/* arc_skip_prologue () */


/*! Frame unwinder for normal frames.

    This function has changed from GDB 6.8. It now takes a reference to THIS
    frame, not the NEXT frame. */
static arc_unwind_cache_t *
arc_frame_cache (struct frame_info *this_frame, void **this_cache)
{
  ARC_ENTRY_DEBUG ("")

  if ((*this_cache) == NULL)
    {
        CORE_ADDR  entrypoint =
	  (CORE_ADDR) get_frame_register_unsigned (this_frame, ARC_PC_REGNUM);
        arc_unwind_cache_t *cache      = arc_create_cache (this_frame);

        /* return the newly-created cache */
        *this_cache = cache;

        /* Prologue analysis does the rest... */
        /* Currently our scan prologue does not support getting input for the
         * frame unwinder.
         */
        (void) arc_scan_prologue (entrypoint, this_frame, cache);
    }

    return *this_cache;

}	/* arc_frame_cache () */


/*! Get the frame_id of a normal frame.

    This function has changed from GDB 6.8. It now takes a reference to THIS
    frame, not the NEXT frame.

    There seemed to be a bucket load of irrelevant code about stopping
    backtraces in the old code, which we've stripped out. */
static void
arc_frame_this_id (struct frame_info *this_frame,
		   void **this_cache, struct frame_id *this_id)
{
  CORE_ADDR stack_addr;
  CORE_ADDR code_addr;
  ARC_ENTRY_DEBUG ("")

  stack_addr = arc_frame_cache (this_frame, this_cache)->frame_base;
  code_addr = get_frame_register_unsigned (this_frame, ARC_PC_REGNUM);
  *this_id = frame_id_build (stack_addr, code_addr);

}	/* arc_frame_this_id () */


/*! Get a register from a normal frame.

    This function has changed from GDB 6.8. It now takes a reference to THIS
    frame, not the NEXT frame. It returns it results via a structure, not its
    argument list.

    Given a pointer to the THIS frame, return the details of a register in the
    PREVIOUS frame.

    @param[in] this_frame  The stack frame under consideration
    @param[in] this_cache  Any cached prologue associated with THIS frame,
                           which may therefore tell us about registers in the
			   PREVIOUS frame. 
    @param[in] regnum      The register of interest in the PREVIOUS frame

    @return  A value structure representing the register. */
static struct value *
arc_frame_prev_register (struct frame_info *this_frame,
			 void **this_cache,
			 int regnum)
{
  arc_unwind_cache_t *info = arc_frame_cache (this_frame, this_cache);

  ARC_ENTRY_DEBUG ("regnum %d", regnum)

  /* @todo The old GDB 6.8 code noted that if we are asked to unwind the PC,
           then we need to return blink instead: the saved value of PC points
           into this frame's function's prologue, not the next frame's
           function's resume location.

           Is this still true? Do we need the following code. */
  if (regnum == ARC_PC_REGNUM)
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


/*! Get breakpoint which is approriate for address at which it is to be set.

    Return whatever is in the ARC-private tdep structure (this has been set up
    according to the correct target / architecture chosen).
   
    Fortunately, the ARC processor does not have separate instruction sets
    (like the ARM's normal 32-bit and 16-bit Thumb instructions), so the bp
    instruction to be used does not depend on the address (although the ARC
    does have both 16- and * 32-bit instructions, they may be freely
    intermixed). */
static const unsigned char *
arc_breakpoint_from_pc (struct gdbarch *gdbarch, CORE_ADDR * pcptr,
			int *lenptr)
{

  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
  *lenptr = (int) tdep->breakpoint_size;
  return tdep->breakpoint_instruction;

}	/* arc_breakpoint_from_pc () */


/*! Identify if a register is in a group.

      0 means the register is not in the group.
      1 means the register is in the group.
     -1 means the tdep has nothing to say about this register and group.

    @todo Should we really raise an internal error if we don't know about
          the group. Surely that is what -1 is for. */
static int
arc_register_reggroup_p (struct gdbarch *gdbarch,
			 int regnum, struct reggroup *group)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
  int tdep_answer = tdep->register_reggroup_p (regnum, group);

  /* if the configuration-specific tdep knows about this register */
  if (tdep_answer != -1)
    return tdep_answer;

  if (group == all_reggroup)
    return 1;

  if (group == save_reggroup || group == restore_reggroup)
    {
      /* don't save/restore read-only registers. */
      return (!gdbarch_cannot_store_register (gdbarch, regnum));
    }

  if (group == system_reggroup)
    {
      if (regnum == ARC_ILINK1_REGNUM || regnum == ARC_ILINK2_REGNUM)
	return 1;

      return 0;
    }

  internal_error (__FILE__, __LINE__, _("bad register group"));
  return -1;

}	/* arc_register_reggroup_p () */


/*! Identify some properties of particular registers for the DWARF unwinder. */
static void
arc_dwarf2_frame_init_reg (struct gdbarch *gdbarch,
			   int regnum,
			   struct dwarf2_frame_state_reg *reg,
			   struct frame_info *info)
{
//  ENTERARGS("Regno no:%d, 0x%x", regnum, (unsigned int) regnum);

  /* The return address column. */
  if (regnum == ARC_PC_REGNUM)
    reg->how = DWARF2_FRAME_REG_RA;

  /* The call frame address. */
  if (regnum == ARC_SP_REGNUM)
    reg->how = DWARF2_FRAME_REG_CFA;

}	/* arc_dwarf2_frame_init_reg () */


/*! Determine how a result of particular type is returned.

    Return the convention used by the ABI for returning a result of the given
    type from a function; it may also be required to:
   
      a) set the return value (this is for the situation where the debugger
         user has issued a "return <value>" command to request immediate
         return from the current function with the given result; or
   
      b) get the return value ((this is for the situation where the debugger
         user has executed a "call <function>" command to execute the
         specified function in the target program, and that function has a
         non-void result which must be returned to the user. */
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

  /* case a) */
  if (writebuf != NULL)
    {
      /* gdb should not ask us to set a struct return value: it should
       * know the struct return location and write the value there itself.
       */
      gdb_assert (!is_struct_return);
      arc_store_return_value (gdbarch, valtype, regcache, writebuf);
    }

  /* case b) */
  if (readbuf != NULL)
    {
      /* gdb should not ask us to get a struct return value: it should
       * know the struct return location and read the value from there
       * itself.
       */
      gdb_assert (!is_struct_return);
      arc_extract_return_value (gdbarch, valtype, regcache, readbuf);
    }

  return (is_struct_return) ? RETURN_VALUE_STRUCT_CONVENTION
    : RETURN_VALUE_REGISTER_CONVENTION;

}	/* arc_return_value () */


/*! Return the frame ID for a dummy stack frame

    The implementations has changed since GDB 6.8, since we are now provided
    with the address of THIS frame, rather than the NEXT frame.

    Tear down a dummy frame created by or32_push_dummy_call(). This data has
    to be constructed manually from the data in our hand.

    The stack pointer and program counter can be obtained from the frame info.

    @param[in] gdbarch     The architecture to use
    @param[in] this_frame  Information about this frame

    @return  Frame ID of this frame */
static struct frame_id
arc_dummy_id (struct gdbarch *gdbarch, struct frame_info *this_frame)
{
  return frame_id_build (get_frame_sp (this_frame), get_frame_pc (this_frame));

}	/* arc_unwind_dummy_id () */


/*! Signal trampoline frame unwinder.
 
    This function has changed from GDB 6.8. It now takes a reference to THIS
    frame, not the NEXT frame.

    Allow frame unwinding to happen from within signal handlers. */
static arc_unwind_cache_t *
arc_sigtramp_frame_cache (struct frame_info *this_frame, void **this_cache)
{
  ARC_ENTRY_DEBUG ("")

  if (*this_cache == NULL)
    {
      struct gdbarch_tdep *tdep = gdbarch_tdep (get_frame_arch (this_frame));
      arc_unwind_cache_t *cache = arc_create_cache (this_frame);

      *this_cache = cache;

      /* get the stack pointer and use it as the frame base */
      cache->frame_base = arc_frame_base_address (this_frame, NULL);

      /* If the ARC-private target-dependent info has a table of offsets of
       * saved register contents within a O/S signal context structure.
       */
      if (tdep->sc_reg_offset)
	{
	  /* find the address of the sigcontext structure */
	  CORE_ADDR addr = tdep->sigcontext_addr (this_frame);
	  unsigned int i;

	  /* For each register, if its contents have been saved within the
	   * sigcontext structure, determine the address of those contents.
	   */
	  for (i = 0; i < tdep->sc_num_regs; i++)
	    if (tdep->sc_reg_offset[i] != REGISTER_NOT_PRESENT)
	      cache->saved_regs[i].addr =
		(LONGEST) (addr + tdep->sc_reg_offset[i]);
	}
    }

  return *this_cache;

}	/* arc_sigtramp_frame_cache () */


/*! Get the frame_id of a signal handler frame.

    This function has changed from GDB 6.8. It now takes a reference to THIS
    frame, not the NEXT frame. */
static void
arc_sigtramp_frame_this_id (struct frame_info *this_frame,
			    void **this_cache, struct frame_id *this_id)
{
  CORE_ADDR stack_addr;
  CORE_ADDR code_addr;
  ARC_ENTRY_DEBUG ("")

  stack_addr = arc_sigtramp_frame_cache (this_frame, this_cache)->frame_base;
  code_addr = get_frame_register_unsigned (this_frame, ARC_PC_REGNUM);
  *this_id = frame_id_build (stack_addr, code_addr);

}	/* arc_sigtramp_frame_this_id () */


/*! Get a register from a signal handler frame.

    This function has changed from GDB 6.8. It now takes a reference to THIS
    frame, not the NEXT frame. It returns it results via a structure, not its
    argument list.

    Given a pointer to the THIS frame, return the details of a register in the
    PREVIOUS frame.

    @param[in] this_frame  The stack frame under consideration
    @param[in] this_cache  Any cached prologue associated with THIS frame,
                           which may therefore tell us about registers in the
			   PREVIOUS frame. 
    @param[in] regnum      The register of interest in the PREVIOUS frame

    @return  A value structure representing the register. */
static struct value *
arc_sigtramp_frame_prev_register (struct frame_info *this_frame,
				  void **this_cache,
				  int regnum)
{
  /* Make sure we've initialized the cache. */
  arc_unwind_cache_t *info = arc_sigtramp_frame_cache (this_frame, this_cache);

  ARC_ENTRY_DEBUG ("")

  /* on a signal, the PC is in ret */
  if (regnum == ARC_PC_REGNUM)
    {
      struct gdbarch_tdep *tdep = gdbarch_tdep (get_frame_arch (this_frame));
      regnum = tdep->pc_regnum_in_sigcontext;
    }

  return trad_frame_get_prev_register (this_frame, info->saved_regs, regnum);

}	/* arc_sigtramp_frame_prev_register () */


/*! Frame sniffer for signal handler frame.

    The implementations has changed since GDB 6.8, since we are now provided
    with the address of THIS frame, rather than the NEXT frame.

    Only recognize a frame if we have a sigcontext_addr hander in the target
    dependency.

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


/*! Structure defining the ARC signal frame unwind functions

    We use a custom sniffer, since we must only accept this frame in the right
    context. */
static const struct frame_unwind arc_sigtramp_frame_unwind = {
  .type          = SIGTRAMP_FRAME,
  .this_id       = arc_sigtramp_frame_this_id,
  .prev_register = arc_sigtramp_frame_prev_register,
  .unwind_data   = NULL,
  .sniffer       = arc_sigtramp_frame_sniffer,
  .dealloc_cache = NULL,
  .prev_arch     = NULL
};


/*! Structure defining the ARC ordinary frame unwind functions

    Since we are the fallback unwinder, we use the default frame sniffer,
    which always accepts the frame. */
static const struct frame_unwind arc_frame_unwind = {
  .type          = NORMAL_FRAME,
  .this_id       = arc_frame_this_id,
  .prev_register = arc_frame_prev_register,
  .unwind_data   = NULL,
  .sniffer       = default_frame_sniffer,
  .dealloc_cache = NULL,
  .prev_arch     = NULL
};


/*! Function identifying the frame base sniffers for signal frames. */
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


/*! Function identifying the frame base sniffers for normal frames. */
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


/*! Push stack frame for a dummy call.

    @param[in] gdbarch        Current gdbarch.
    @param[in] function       Function to call.
    @param[in] regcache       Current register cache
    @param[in] bp_addr        Return address where breakpoint must be placed.
    @param[in] sp             Current value of SP.
    @param[in] struct_return  Non-zero (TRUE) if structures are returned by
                              the function. 
    @param[in] struct_addr    Hidden address for returning a struct. */
static CORE_ADDR
arc_push_dummy_call (struct gdbarch *gdbarch,
		     struct value *function,
		     struct regcache *regcache,
		     CORE_ADDR bp_addr,
		     int nargs,
		     struct value **args,
		     CORE_ADDR sp, int struct_return, CORE_ADDR struct_addr)
{
  int arg_reg = ARC_ABI_FIRST_ARGUMENT_REGISTER;

  ARC_ENTRY_DEBUG ("nargs = %d", nargs)

  /* Push the return address. */
  regcache_cooked_write_unsigned (regcache, ARC_BLINK_REGNUM, bp_addr);

  /* Are we returning a value using a structure return instead of a normal
   * value return? If so, struct_addr is the address of the reserved space
   * for the return structure to be written on the stack, and that address
   * is passed to that function as a hidden first argument.
   */
  /* FIXME:: Ramana :: What about 4 byte structures returned in R0 as
   *                   claimed by Metaware?
   */
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
       * N.B. must round each argument's size up to an integral number of words.
       */
      for (i = 0; i < nargs; i++)
	{
	  unsigned int len = TYPE_LENGTH (value_type (args[i]));
	  unsigned int space = ROUND_UP_TO_WORDS (len);

	  total_space += space;

	  if (arc_debug)
	    {
	      fprintf_unfiltered (gdb_stdlog, "arg %d: %d bytes -> %d\n", i,
				  len, ROUND_UP_TO_WORDS (len));
	    }
	}

      /* Allocate a buffer to hold a memory image of the arguments. */
      memory_image = XCALLOC (total_space, gdb_byte);
      if (memory_image == NULL)
	{
	  /* could not do the call! */
	  return 0;
	}

      /* now copy all of the arguments into the buffer, correctly aligned */
      data = memory_image;
      for (i = 0; i < nargs; i++)
	{
	  unsigned int len = TYPE_LENGTH (value_type (args[i]));
	  unsigned int space = ROUND_UP_TO_WORDS (len);

	  (void) memcpy (data, value_contents (args[i]), (size_t) len);
	  data += space;
	}

      /* Now load as much as possible of the memory image into registers. */
      data = memory_image;
      while (arg_reg <= ARC_ABI_LAST_ARGUMENT_REGISTER)
	{
	  if (arc_debug)
	    {
	      fprintf_unfiltered (gdb_stdlog,
				  "passing 0x%08lX in register R%d\n",
				  *(unsigned long *) data, arg_reg);
	    }

	  regcache_cooked_write_unsigned (regcache,
					  arg_reg, *(unsigned long *) data);

	  data += BYTES_IN_REGISTER;
	  total_space -= BYTES_IN_REGISTER;

	  /* if all the data is now in registers */
	  if (total_space == 0)
	    break;

	  arg_reg++;
	}

      /* If there is any data left, push it onto the stack (in a single write operation). */
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
  regcache_cooked_write_unsigned (regcache, ARC_SP_REGNUM, sp);

  return sp;

}	/* arc_push_dummy_call () */


/* Adjust the SP to align frame. */
static CORE_ADDR
arc_frame_align (struct gdbarch *gdbarch, CORE_ADDR sp)
{
  /* Align to the normal alignment on the stack).  */
  return WORD_ALIGNED (sp);

}	/* arc_frame_align () */


/*! Print info about floating point.

    We don't have one, so just print a suitable message. */
static void
arc_print_float_info (struct gdbarch *gdbarch, struct ui_file *file,
		      struct frame_info *frame, const char *args)
{
  printf_unfiltered (_("Software FPU\n"));
}


/* this initialization function is called by gdb
 *
 * see gdbarch.h for a description of its parameters
 */
static struct gdbarch *
arc_gdbarch_init (struct gdbarch_info info, struct gdbarch_list *arches)
{
  /* Allocate the ARC-private target-dependent information structure, and the
   * gdb target-independent information structure.
   */
  struct gdbarch_tdep *tdep = xmalloc (sizeof (struct gdbarch_tdep));
  struct gdbarch *gdbarch = gdbarch_alloc (&info, tdep);

  memset (tdep, 0, sizeof (*tdep));

  /* Put stuff in gdbarch that is generic to ARC. */

  /* Breakpoint manipulation.  */
  set_gdbarch_breakpoint_from_pc (gdbarch, arc_breakpoint_from_pc);

  /* Characters are unsigned by default */
  set_gdbarch_char_signed (gdbarch, 0);

  set_gdbarch_sp_regnum (gdbarch, ARC_SP_REGNUM);
  set_gdbarch_register_type (gdbarch, arc_register_type);
  set_gdbarch_print_float_info (gdbarch, arc_print_float_info);

  /* Advance PC across function entry code. */
  set_gdbarch_skip_prologue (gdbarch, arc_skip_prologue);

  /* The stack grows downward. */
  set_gdbarch_inner_than (gdbarch, core_addr_lessthan);
  set_gdbarch_unwind_pc (gdbarch, arc_unwind_pc);
  set_gdbarch_unwind_sp (gdbarch, arc_unwind_sp);
  set_gdbarch_dummy_id (gdbarch, arc_dummy_id);
  set_gdbarch_return_value (gdbarch, arc_return_value);

  /* Add the arc register groups.  */
  reggroup_add (gdbarch, general_reggroup);
  reggroup_add (gdbarch, all_reggroup);
  reggroup_add (gdbarch, system_reggroup);
  set_gdbarch_register_reggroup_p (gdbarch, arc_register_reggroup_p);

  set_gdbarch_cannot_step_breakpoint (gdbarch, 1);
  /*set_gdbarch_frame_args_skip (gdbarch, 8); */
  set_gdbarch_frame_align (gdbarch, arc_frame_align);

  /* Dummy Frame handling */
  set_gdbarch_push_dummy_call (gdbarch, arc_push_dummy_call);
  set_gdbarch_call_dummy_location (gdbarch, AT_ENTRY_POINT);

  /* Disassembly. We use an observer, since although only ARCompact is
     supported, if we wait for an object file it will have information about
     extensions to be loaded.

     @todo. Should we use a dummy_disassembler before this. GDB by default
     will trigger gdbabort, but we could give a nicer message. */
  observer_attach_new_objfile (arc_set_disassembler);

  /* Frame unwinders and sniffers. We use DWARF2 if it's available, for which
     we set up a register initialization function. Then we have ARC specific
     unwinders and sniffers for signal frames and ordinary frames. */
  dwarf2_frame_set_init_reg (gdbarch, arc_dwarf2_frame_init_reg);
  dwarf2_append_unwinders (gdbarch);
  frame_unwind_append_unwinder (gdbarch, &arc_sigtramp_frame_unwind);
  frame_unwind_append_unwinder (gdbarch, &arc_frame_unwind);
  frame_base_append_sniffer (gdbarch, dwarf2_frame_base_sniffer);
  frame_base_append_sniffer (gdbarch, arc_sigtramp_frame_base_sniffer);
frame_base_append_sniffer (gdbarch, arc_frame_base_sniffer);
  
  /* Put OS specific stuff into gdbarch. This can override any of the generic
     ones specified above. */
  info.osabi = GDB_OSABI_LINUX;
  gdbarch_init_osabi (info, gdbarch);

  return gdbarch;			/* Newly created architecture. */
}


/*! Dump out the target specific information.

  @todo. Why is this empty! */
static void
arc_dump_tdep (struct gdbarch *gdbarch, struct ui_file *file)
{
}	/* arc_dump_tdep () */


/* -------------------------------------------------------------------------- */
/*			 Externally visible functions                         */
/* -------------------------------------------------------------------------- */

void
arc_initialize_disassembler (struct gdbarch *gdbarch, 
			     struct disassemble_info *info)
{
  // N.B. this type cast is not strictly correct: the return types differ!
  init_disassemble_info (info, gdb_stderr,
			 (fprintf_ftype) fprintf_unfiltered);
  info->arch = gdbarch_bfd_arch_info (gdbarch)->arch;
  info->mach = gdbarch_bfd_arch_info (gdbarch)->mach;
  info->endian = gdbarch_byte_order (gdbarch);
  info->read_memory_func = arc_read_memory_for_disassembler;
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

  /* register ARC-specific commands with gdb */

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
