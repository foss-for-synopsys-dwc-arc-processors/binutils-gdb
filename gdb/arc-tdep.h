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
/*		       ARC Architecture Header for GDB                        */
/*		       ===============================                        */
/*                                                                            */
/*  Definitions specific to the architecture, but not any particular OS.      */
/*                                                                            */
/******************************************************************************/

#ifndef ARC_TDEP_H
#define ARC_TDEP_H


/*! Target dependencies.

    This structure holds target-dependent information.
 
    @note This type is used in the target-independent gdb code, but it is
          treated as an opaque (or private) type: the only use of it is by
          pointers to objects of this type (passed as parameters or returned
          as results, or held in other structures); it is only the
          ARC-specific modules that have knowledge of the structure of this
          type and access its fields. */
struct gdbarch_tdep
{
    /* Detect sigtramp.  */
    int (*is_sigtramp) (struct frame_info*);
  
    /* Get address of sigcontext for sigtramp.  */
    CORE_ADDR (*sigcontext_addr) (struct frame_info*);

    /* Offset of registers in `struct sigcontext'. */
    const int*   sc_reg_offset;
    unsigned int sc_num_regs;

    /* In our linux target, gdbarch_pc_regnum points to stop_pc, which is a
       register that is made up by the kernel and does not actually exist.
       stop_pc is NOT saved in the sigcontext; what is saved is the ret
       "register".  Since ret is a linux-only register, its regnum is visible
       only in arc-linux-tdep.c; hence initialize pc_regnum_in_sigcontext in
       arc-linux-tdep.c.  */
    int pc_regnum_in_sigcontext;

    /* Returns 0, 1, or -1:
     *    0 means the register is not in the group.
     *    1 means the register is in the group.
     *   -1 means the tdep has nothing to say about this register and group.
     */
    int (*register_reggroup_p) (int regnum, struct reggroup* group);
  
    /* Breakpoint instruction to be used */
    const unsigned char* breakpoint_instruction;
    unsigned int         breakpoint_size;

    /* For stopping backtraces.  */
    CORE_ADDR lowest_pc;
  
    /* ARC processor variant information (may be NULL). */
    struct arc_variant_info *processor_variant_info;
};


void _initialize_arc_tdep (void);


/* utility functions used by other ARC-specific modules */

void arc_initialize_disassembler(struct gdbarch *gdbarch,
				 struct disassemble_info* info);


/* -------------------------------------------------------------------------- */
/*			    Globally visible data                             */
/* -------------------------------------------------------------------------- */

extern int  arc_debug;

/* -------------------------------------------------------------------------- */
/*			  Globally visible functions                          */
/* -------------------------------------------------------------------------- */

/* From opcodes/arcompact-dis.h. */
extern struct arcDisState arcAnalyzeInstr (bfd_vma address,
					   struct disassemble_info *info);

/* From arc-tdep.c */
extern int arc_debug;

/* From arc-linux.c or arc-elf32.c */
extern enum gdb_osabi arc_get_osabi (void);

#endif /* ARC_TDEP_H */
/******************************************************************************/
