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
#include "opcodes/arc-dis.h"

/* ARC header files */
#include "arc-tdep.h"


/* -------------------------------------------------------------------------- */
/*                               local data                                   */
/* -------------------------------------------------------------------------- */



/* Default breakpoint instruction used for ARC700 Linux */
static const unsigned char breakpoint_instruction[] = { 0x3e, 0x78 };
static const unsigned char be_breakpoint_instruction[] = { 0x78, 0x3e };


/*! this array holds the object code of two instructions:

    mov r8,nr_sigreturn
    swi */
static const gdb_byte arc_sigtramp_insns[] = { 0x8a, 0x20, 0xc1, 0x1d,
  0x6f, 0x22, 0x3f, 0x00
};

#define SIGTRAMP_INSNS_LENGTH     sizeof(arc_sigtramp_insns)


/*! Mapping between the general-purpose registers in `struct sigcontext' format
    and GDB's register cache layout.

    arc_linux_sc_reg_offset[i] is the sigcontext offset of GDB regnum `i'. */

/* From <asm/sigcontext.h>.  */
static const int arc_linux_sc_reg_offset[ARC_NUM_RAW_REGS] = {
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


/* arc_linux_core_reg_offsets[i] is the offset in the .reg section of GDB
 * regnum i.
 *
 * From include/asm-arc/user.h in the ARC Linux sources.
 */

static const int arc_linux_core_reg_offsets[ARC_NUM_RAW_REGS] = {
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
/*                               local functions                              */
/* -------------------------------------------------------------------------- */

/*! Returns TRUE if the instruction at PC is a branch (of any kind).

    @param[out] fall_thru  Set to the address of the next insn.
    @param[out] target     Set to the branch target. */
static int
arc_linux_next_pc (CORE_ADDR pc, CORE_ADDR *fall_thru, CORE_ADDR *target)
{
  struct regcache *regcache = get_current_regcache ();
  struct gdbarch *gdbarch = get_regcache_arch (regcache);
  struct disassemble_info di;
  struct arcDisState instr;
  int two_targets = FALSE;
  ULONGEST  lp_end, lp_start, lp_count, status32;

  /* Why on earth do we need to do this each time we call arc_linux_next_pc! */
  arc_initialize_disassembler (gdbarch, &di);

  /* so what is the instruction at the given pc? */
  instr = arcAnalyzeInstr (pc, &di);

  /* by default, the next instruction is the one immediately after the one at
     pc */
  *fall_thru = pc + instr.instructionLen;

  if (arc_debug)
    {
      fprintf_unfiltered (gdb_stdlog,
			  "--- arc_linux_next_pc (%s) = %s, isBranch = %s, "
			  "tcnt = %d [0x%x],\n"
			  "    flow = %s (%d), reg for indirect jump = %d, "
			  "nullifyMode = %s\n",
			  print_core_address (gdbarch, pc),
			  print_core_address (gdbarch, *fall_thru),
			  instr.isBranch ? "true" : "false", instr.tcnt,
			  instr.targets[0],
			  (instr.flow == direct_jump
			   || instr.flow == direct_call)
			  ? "direct" : "indirect", instr.flow,
			  instr.register_for_indirect_jump,
			  ((instr.nullifyMode == (char) BR_exec_always)
			   ? "delay slot" : "no delay"));
    }

  /* OK, it's a branch */
  if (instr.isBranch)
    {
      two_targets = TRUE;

      /* if it's a direct jump or call, the destination address is encoded in
         the instruction, so we got it by disassembling the instruction;
         otherwise, it's an indirect jump to the address held in the register
         named in the instruction, so we must read that register */
      if (instr.flow == direct_jump || instr.flow == direct_call)
	{
	  *target = (CORE_ADDR) instr.targets[0];
	}
      else
	{
	  ULONGEST val;
	  regcache_cooked_read_unsigned (regcache,
					 instr.register_for_indirect_jump,
					 &val);
	  *target = val;
	}

      /* for instructions with delay slots, the fall thru is not the
         instruction immediately after the branch instruction, but the one
         after that. */
      if (instr.nullifyMode == (char) BR_exec_always)
	{
	  struct arcDisState instr_d = arcAnalyzeInstr (*fall_thru, &di);

	  *fall_thru += instr_d.instructionLen;
	}
    }


  /* zero-overhead loops:

        if (STATUS32[L] == 0 && arc_linux_next_pc == lp_end && lp_count > 1)
            arc_linux_next_pc = lp_start; */
  regcache_cooked_read_unsigned (regcache, ARC_AUX_LP_START_REGNUM, &lp_start);
  regcache_cooked_read_unsigned (regcache, ARC_AUX_LP_END_REGNUM, &lp_end);
  regcache_cooked_read_unsigned (regcache, ARC_LP_COUNT_REGNUM, &lp_count);
  regcache_cooked_read_unsigned (regcache, ARC_AUX_STATUS32_REGNUM, &status32);

  if (!(status32 & 0x00000100) && *fall_thru == lp_end && lp_count > 1)
    {
      /* the instruction is in effect a jump back to the start of the loop */
      two_targets = TRUE;
      *target = lp_start;
    }

  return two_targets;

}	/* arc_linux_next_pc () */


/*! Is the PREV frame a sigtramp function.

    Return whether the frame preceding next_frame corresponds to a GNU/Linux
    sigtramp routine. */
static int
arc_linux_is_sigtramp (struct frame_info *next_frame)
{
  /* find the PC for that previous frame */
  struct gdbarch *gdbarch = get_frame_arch (next_frame);
  CORE_ADDR pc = gdbarch_unwind_pc (gdbarch, next_frame);
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

}	/* arc_linux_is_sigtramp () */


/*! Get sigcontect of sigtramp frame.

    Assuming next_frame is a frame following a GNU/Linux sigtramp routine,
    return the address of the associated sigcontext structure. */
static CORE_ADDR
arc_linux_sigcontext_addr (struct frame_info *next_frame)
{
  return (CORE_ADDR) gdbarch_unwind_sp (get_frame_arch (next_frame),
					next_frame);

}	/* arc_linux_sigcontext_addr () */


/* -------------------------------------------------------------------------- */
/*		   ARC specific GDB architectural functions		      */
/*									      */
/* Functions are listed in the order they are used in arc_linux_init_abi.     */
/* -------------------------------------------------------------------------- */

/*! Single step in software.

    This is called with insert_breakpoints_p = 1 before single-stepping and
    with insert_breakpoints_p = 0 after the step.

    @todo Makis noted in 6.8 that this is used to add breakpoints only and not
          remove them so remove functionality for now. This needs monitoring
          in case we see problems.  This code is now completely removed as it
          break the way the higher layers are using breakpoints. It now uses
          insert_single_step_breakpoint() function this code needs to be
          validated */
static int
arc_linux_software_single_step (struct frame_info *frame)
{
  struct gdbarch *gdbarch = get_frame_arch (frame);
  struct address_space *aspace = get_frame_address_space (frame);
  CORE_ADDR pc = get_frame_pc (frame);
  CORE_ADDR fall_thru, branch_target;
  int two_breakpoints = arc_linux_next_pc (pc, &fall_thru, &branch_target);

  insert_single_step_breakpoint (gdbarch, aspace, fall_thru);

  if (two_breakpoints)
    {
      if ((pc != branch_target) && (fall_thru != branch_target))
	insert_single_step_breakpoint (gdbarch, aspace, branch_target);
    }

  return 1;			/* returns always true for now */

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
     sets a breakpoint at the return address, and continues.

     lookup_minimal_symbol didn't work, for some reason.  */
  struct symbol *resolver = lookup_symbol_global ("_dl_linux_resolver", NULL,
						  VAR_DOMAIN);

  if (arc_debug)
    {
      if (resolver)
	{
	  CORE_ADDR res_addr = BLOCK_START (SYMBOL_BLOCK_VALUE (resolver));
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

  if (resolver && ((BLOCK_START (SYMBOL_BLOCK_VALUE (resolver))) == pc))
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
static void
arc_linux_supply_gregset (const struct regset *regset,
			  struct regcache *regcache,
			  int regnum, const void *gregs, size_t size)
{
  const bfd_byte *buf = gregs;
  unsigned int reg;

  for (reg = 0; reg < ARC_NUM_RAW_REGS; reg++)
    {
      if (arc_linux_core_reg_offsets[reg] != REGISTER_NOT_PRESENT)
	regcache_raw_supply (regcache,
			     (int) reg,
			     buf + arc_linux_core_reg_offsets[reg]);
    }
}	/* arc_linux_supply_gregset () */


/*! Identify functions for handling core files.

    The first element is a parameter to pass the rest of the functions.  We
    don't need it.
    - supply_gregset is for reading the core file.
    - collect_regset, which we haven't defined, would be for writing the core
      file. */
static const struct regset *
arc_linux_regset_from_core_section (struct gdbarch *core_arch,
				    const char *sect_name, size_t sect_size)
{
  static struct regset arc_linux_gregset = {
    .descr          = NULL,
    .supply_regset  = arc_linux_supply_gregset,
    .collect_regset = NULL,
    .arch           = NULL,
  };

  arc_linux_gregset.arch = core_arch;	/* Not const, so not in initializer */

  if (strcmp (sect_name, ".reg") == 0)
    {
      return &arc_linux_gregset;
    }

  return NULL;

}	/* arc_linux_regset_from_core_section () */


/*! Initialize for the Linux ABI */
static void
arc_linux_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Fill in target-dependent info in ARC-private structure. */

  tdep->is_sigtramp = arc_linux_is_sigtramp;
  tdep->sigcontext_addr = arc_linux_sigcontext_addr;
  tdep->sc_reg_offset = arc_linux_sc_reg_offset;
  tdep->sc_num_regs = ARC_NUM_RAW_REGS;
  /* @todo We don't have ARC_RET_REGNUM nay more, what do we use instead? */
  /* tdep->pc_regnum_in_sigcontext = ARC_RET_REGNUM; */

  tdep->breakpoint_instruction = (info.byte_order == BFD_ENDIAN_BIG)
    ? be_breakpoint_instruction
    : breakpoint_instruction;
  tdep->breakpoint_size = (unsigned int) sizeof (breakpoint_instruction);

  tdep->lowest_pc = 0x74;	/* @todo why this? */
  tdep->processor_variant_info = NULL;

  /* Set up target dependent GDB architecture entries. */
  set_gdbarch_fetch_tls_load_module_address (gdbarch,
                                             svr4_fetch_objfile_link_map);
  set_gdbarch_software_single_step (gdbarch, arc_linux_software_single_step);





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

/*! Function to identify the OSABI to be used.

    Every target variant must define this appropriately. */
enum gdb_osabi
arc_get_osabi (void)
{
  return  GDB_OSABI_LINUX;

}	/* arc_get_osabi () */


/*! Linux specific initialization function. */
void
_initialize_arc_linux_tdep (void)
{
  /* register a handler with gdb for the Linux O/S ABI variant for the ARC
   * processor architecture, providing an initialization function;
   *
   * 'bfd_arch_arc' is an enumeration value specifically denoting the ARC
   *                architecture
   */
  gdbarch_register_osabi (bfd_arch_arc, 0,	/* machine (irrelevant) */
			  GDB_OSABI_LINUX, arc_linux_init_abi);
}
