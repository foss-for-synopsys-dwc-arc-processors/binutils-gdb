/* GNU/Linux/ARC specific low level interface, for the remote server for GDB.
   Copyright 1995, 1996, 1998, 1999, 2000, 2001, 2002, 2003, 2004
   Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#include "server.h"
#include "linux-low.h"

#include "../config/arc/tm-linux.h"	/* useful ARC info */
#include <asm/ptrace.h>			/* Linux kernel ptrace reg offsets */


/* arc_regmap[i] is the saved "address" of a register. The map is built in
   GDB order (r0-r26, bta, lp_start, lp_end, lp_count, status32, blink, fp,
   sp, efa, ret, orig_r8, stop_pc) and yields the offset of the register.

   PTRACE doesn't save all registers, but we know that the arrangement is
   that after sp, there are orig_r0, orig_r8, a word of space, then r25-r13
   (in that order) followed by efa and stop_pc. */
static int arc_regmap[] = {
  PT_r0,       PT_r1,       PT_r2,       PT_r3,
  PT_r4,       PT_r5,       PT_r6,       PT_r7,
  PT_r8,       PT_r9,       PT_r10,      PT_r11,
  PT_r12,      PT_sp + 64,  PT_sp + 60,  PT_sp + 56,
  PT_sp + 52,  PT_sp + 48,  PT_sp + 44,  PT_sp + 40,
  PT_sp + 36,  PT_sp + 32,  PT_sp + 28,  PT_sp + 24,
  PT_sp + 20,  PT_sp + 16,  PT_r26,      PT_bta,
  PT_lp_start, PT_lp_end,   PT_lp_count, PT_status32,
  PT_blink,    PT_fp,       PT_sp,       PT_sp + 68,
  PT_ret,      PT_orig_r8,  PT_sp + 72
};


static int
arc_cannot_store_register (int regno)
{
  /* We can write every register except efa. */
  return (regno < 0)
    || (regno == ARC_EFA_REGNUM)
    || (regno >= ARC_NR_REGS);

}	/* arc_cannot_store_register () */


static int
arc_cannot_fetch_register (int regno)
{
  return (regno < 0) || (regno >= ARC_NR_REGS);

}	/* arc_cannot_fetch_register () */


static CORE_ADDR
arc_get_pc ()
{
  unsigned long pc;
  collect_register_by_name ("stop_pc", &pc);
  if (debug_threads)
    fprintf (stderr, "stop pc is %08lx\n", pc);
  return pc;
}

static void
arc_set_pc (CORE_ADDR pc)
{
  unsigned long newpc = pc;
  supply_register_by_name ("ret", &newpc);
}


/* trap_s 1 */
/* FIXME: dependent on target endianness */
static const unsigned short arc_breakpoint = 0x783E;
#define arc_breakpoint_len 2

static int
arc_breakpoint_at (CORE_ADDR where)
{
  unsigned short insn;

  (*the_target->read_memory) (where, (unsigned char *) &insn, arc_breakpoint_len);
  if (insn == arc_breakpoint)
    return 1;

  /* If necessary, recognize more trap instructions here.  GDB only uses the
     one.  */
  return 0;
}


/* We only place breakpoints in empty marker functions, and thread locking
   is outside of the function.  So rather than importing software single-step,
   we can just run until exit.  */
static CORE_ADDR
arc_reinsert_addr ()
{
  unsigned long pc;
  collect_register_by_name ("blink", &pc);
  return pc;
}

struct linux_target_ops the_low_target = {
  ARC_NR_REGS,
  arc_regmap,
  arc_cannot_fetch_register,
  arc_cannot_store_register,
  arc_get_pc,
  arc_set_pc,
  (const unsigned char *) &arc_breakpoint,
  arc_breakpoint_len,
  arc_reinsert_addr,
  0,
  arc_breakpoint_at,
};
