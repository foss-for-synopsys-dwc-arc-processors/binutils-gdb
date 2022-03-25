/* Target dependent code for GNU/Linux ARC.

   Copyright 2023 Free Software Foundation, Inc.

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

/* GDB header files.  */
#include "defs.h"
#include "linux-tdep.h"
#include "objfiles.h"
#include "opcode/arc.h"
#include "osabi.h"
#include "solib-svr4.h"
#include "disasm.h"

/* ARC header files.  */
#include "opcodes/arc-dis.h"
#include "arc64-tdep.h"
#include "arch/arc.h"

/* Print an "arc-linux" debug statement.  */

#define arc_linux_debug_printf(fmt, ...) \
  debug_prefixed_printf_cond (arc_debug, "arc-linux", fmt, ##__VA_ARGS__)

/* Implement the "cannot_fetch_register" gdbarch method.  */

static int
arc_linux_cannot_fetch_register (struct gdbarch *gdbarch, int regnum)
{
  /* Assume that register is readable if it is unknown.  */
  switch (regnum)
    {
    case ARC_ILINK_REGNUM:
    case ARC_RESERVED_1_REGNUM:
    case ARC_RESERVED_2_REGNUM:
    case ARC_LIMM_REGNUM:
      return true;
    }
  return (regnum > ARC_BLINK_REGNUM) && (regnum < ARC_RESERVED_1_REGNUM);
}

/* Implement the "cannot_store_register" gdbarch method.  */

static int
arc_linux_cannot_store_register (struct gdbarch *gdbarch, int regnum)
{
  /* Assume that register is writable if it is unknown.  */
  switch (regnum)
    {
    case ARC_ILINK_REGNUM:
    case ARC_RESERVED_1_REGNUM:
    case ARC_RESERVED_2_REGNUM:
    case ARC_LIMM_REGNUM:
    case ARC_PCL_REGNUM:
      return true;
    }
  return (regnum > ARC_BLINK_REGNUM) && (regnum < ARC_RESERVED_1_REGNUM);
}

/* For ARC Linux, breakpoints use the 16-bit TRAP_S 1 instruction, which
   is 0x3e78 (little endian) or 0x783e (big endian).  */

static const gdb_byte arc_linux_trap_s_be[] = { 0x78, 0x3e };
static const gdb_byte arc_linux_trap_s_le[] = { 0x3e, 0x78 };
static const int trap_size = 2;   /* Number of bytes to insert "trap".  */

/* Implement the "breakpoint_kind_from_pc" gdbarch method.  */

static int
arc_linux_breakpoint_kind_from_pc (struct gdbarch *gdbarch, CORE_ADDR *pcptr)
{
  return trap_size;
}

/* Implement the "sw_breakpoint_from_kind" gdbarch method.  */

static const gdb_byte *
arc_linux_sw_breakpoint_from_kind (struct gdbarch *gdbarch,
				   int kind, int *size)
{
  gdb_assert (kind == trap_size);
  *size = kind;
  return ((gdbarch_byte_order (gdbarch) == BFD_ENDIAN_BIG)
	  ? arc_linux_trap_s_be
	  : arc_linux_trap_s_le);
}

/* Check for an atomic sequence of instructions beginning with an
   LLOCK instruction and ending with a SCOND instruction.

   These patterns are hand coded in libc's (glibc and uclibc). Take
   a look at [1] for instance:

   main+14: llock   r2,[r0]
   main+18: brne.nt r2,0,main+30
   main+22: scond   r3,[r0]
   main+26: bne     main+14
   main+30: mov_s   r0,0

   If such a sequence is found, attempt to step over it.
   A breakpoint is placed at the end of the sequence.

   This function expects the INSN to be a "llock(d)" instruction.

   [1]
   https://cgit.uclibc-ng.org/cgi/cgit/uclibc-ng.git/tree/libc/ \
     sysdeps/linux/arc/bits/atomic.h#n46
   */

static std::vector<CORE_ADDR>
handle_atomic_sequence (arc_instruction insn, disassemble_info *di)
{
  const int atomic_seq_len = 24;    /* Instruction sequence length.  */
  std::vector<CORE_ADDR> next_pcs;

  /* Sanity check.  */
  gdb_assert (insn.insn_class == LLOCK);

  /* Data size we are dealing with: LLOCK vs. LLOCKD  */
  arc_ldst_data_size llock_data_size_mode = insn.data_size_mode;
  /* Indicator if any conditional branch is found in the sequence.  */
  bool found_bc = false;
  /* Becomes true if "LLOCK(D) .. SCOND(D)" sequence is found.  */
  bool is_pattern_valid = false;

  for (int insn_count = 0; insn_count < atomic_seq_len; ++insn_count)
    {
      arc_insn_decode (arc_insn_get_linear_next_pc (insn),
		       di, arc_delayed_print_insn, &insn);

      if (insn.insn_class == BRCC)
	{
	  /* If more than one conditional branch is found, this is not
	     the pattern we are interested in.  */
	  if (found_bc)
	    break;
	  found_bc = true;
	  continue;
	}

      /* This is almost a happy ending.  */
      if (insn.insn_class == SCOND)
	{
	  /* SCOND should match the LLOCK's data size.  */
	  if (insn.data_size_mode == llock_data_size_mode)
	    is_pattern_valid = true;
	  break;
	}
    }

  if (is_pattern_valid)
    {
      /* Get next instruction after scond(d).  There is no limm.  */
      next_pcs.push_back (insn.address + insn.length);
    }

  return next_pcs;
}

/* Implement the "software_single_step" gdbarch method.  */

static std::vector<CORE_ADDR>
arc_linux_software_single_step (struct regcache *regcache)
{
  struct gdbarch *gdbarch = regcache->arch ();
  struct gdb_non_printing_memory_disassembler dis (gdbarch);

  /* Read current instruction.  */
  struct arc_instruction curr_insn;
  arc_insn_decode (regcache_read_pc (regcache), dis.disasm_info (),
		   arc_delayed_print_insn, &curr_insn);

  if (curr_insn.insn_class == LLOCK)
    return handle_atomic_sequence (curr_insn, dis.disasm_info ());

  CORE_ADDR next_pc = arc_insn_get_linear_next_pc (curr_insn);
  std::vector<CORE_ADDR> next_pcs;

  /* For instructions with delay slots, the fall thru is not the
     instruction immediately after the current instruction, but the one
     after that.  */
  if (curr_insn.has_delay_slot)
    {
      struct arc_instruction next_insn;
      arc_insn_decode (next_pc, dis.disasm_info (), arc_delayed_print_insn,
		       &next_insn);
      next_pcs.push_back (arc_insn_get_linear_next_pc (next_insn));
    }
  else
    next_pcs.push_back (next_pc);

  ULONGEST status32;
  regcache_cooked_read_unsigned (regcache, gdbarch_ps_regnum (gdbarch),
				 &status32);

  if (curr_insn.is_control_flow)
    {
      CORE_ADDR branch_pc = arc_insn_get_branch_target (curr_insn);
      if (branch_pc != next_pc)
	next_pcs.push_back (branch_pc);
    }

  /* Is this a delay slot?  Then next PC is in BTA register.  */
  if ((status32 & ARC_STATUS32_DE_MASK) != 0)
    {
      ULONGEST bta;
      regcache_cooked_read_unsigned (regcache, ARC_BTA_REGNUM, &bta);
      next_pcs.push_back (bta);
    }

  return next_pcs;
}

/* Implement the "skip_solib_resolver" gdbarch method.

   See glibc_skip_solib_resolver for details.  */

static CORE_ADDR
arc_linux_skip_solib_resolver (struct gdbarch *gdbarch, CORE_ADDR pc)
{
  /* For uClibc 0.9.26+.

     An unresolved PLT entry points to "__dl_linux_resolve", which calls
     "_dl_linux_resolver" to do the resolving and then eventually jumps to
     the function.

     So we look for the symbol `_dl_linux_resolver', and if we are there,
     gdb sets a breakpoint at the return address, and continues.  */
  struct bound_minimal_symbol resolver
    = lookup_minimal_symbol ("_dl_linux_resolver", NULL, NULL);

  if (arc_debug)
    {
      if (resolver.minsym != nullptr)
	{
	  CORE_ADDR res_addr = resolver.value_address ();
	  arc_linux_debug_printf ("pc = %s, resolver at %s",
				  print_core_address (gdbarch, pc),
				  print_core_address (gdbarch, res_addr));
	}
      else
	arc_linux_debug_printf ("pc = %s, no resolver found",
				print_core_address (gdbarch, pc));
    }

  if (resolver.minsym != nullptr && resolver.value_address () == pc)
    {
      /* Find the return address.  */
      return frame_unwind_caller_pc (get_current_frame ());
    }
  else
    {
      /* No breakpoint required.  */
      return 0;
    }
}

/* Initialization specific to Linux environment.  */

static void
arc64_linux_init_osabi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  arc64_gdbarch_tdep *tdep = gdbarch_tdep<arc64_gdbarch_tdep> (gdbarch);

  arc_linux_debug_printf ("GNU/Linux OS/ABI initialization.");

  /* If we are using Linux, we have in uClibc
     (libc/sysdeps/linux/arc/bits/setjmp.h):

     typedef int __jmp_buf[13+1+1+1];    //r13-r25, fp, sp, blink

     Where "blink" is a stored PC of a caller function.
   */
  tdep->jb_pc = 15;

  linux_init_abi (info, gdbarch, 0);

  /* Set up target dependent GDB architecture entries.  */
  set_gdbarch_cannot_fetch_register (gdbarch, arc_linux_cannot_fetch_register);
  set_gdbarch_cannot_store_register (gdbarch, arc_linux_cannot_store_register);
  set_gdbarch_breakpoint_kind_from_pc (gdbarch,
				       arc_linux_breakpoint_kind_from_pc);
  set_gdbarch_sw_breakpoint_from_kind (gdbarch,
				       arc_linux_sw_breakpoint_from_kind);
  set_gdbarch_fetch_tls_load_module_address (gdbarch,
					     svr4_fetch_objfile_link_map);
  set_gdbarch_software_single_step (gdbarch, arc_linux_software_single_step);
  set_gdbarch_skip_trampoline_code (gdbarch, find_solib_trampoline_target);
  set_gdbarch_skip_solib_resolver (gdbarch, arc_linux_skip_solib_resolver);

  /* GNU/Linux uses SVR4-style shared libraries...  */
  set_solib_svr4_fetch_link_map_offsets (gdbarch,
					 (arc64_isa_reg_size (gdbarch) == 4
					 ? linux_ilp32_fetch_link_map_offsets
					 : linux_lp64_fetch_link_map_offsets));
}

/* Suppress warning from -Wmissing-prototypes.  */
extern initialize_file_ftype _initialize_arc64_linux_tdep;

void
_initialize_arc64_linux_tdep ()
{
  gdbarch_register_osabi (bfd_arch_arc64, 0, GDB_OSABI_LINUX,
			  arc64_linux_init_osabi);
}
