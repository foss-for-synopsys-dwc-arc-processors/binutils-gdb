/* Target dependent code for the remote server for GNU/Linux ARC.

   Copyright 2014-2016 Free Software Foundation, Inc.

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

#include "server.h"
#include "regdef.h"
#include "linux-low.h"
#include "tdesc.h"

#include <linux/elf.h>
#include <arpa/inet.h>

/* Linux starting with 4.12 supports NT_ARC_V2 note type, which adds R30,
   R58 and R59 registers.  */
#ifdef NT_ARC_V2
#define ARC_HAS_V2_REGSET
#endif

/* Defined in auto-generated files arc-v2-linux.c, arc-arcompact-linux.c.  */
#ifdef __ARC700__
extern void init_registers_arc_arcompact_linux (void);
extern const struct target_desc *tdesc_arc_arcompact_linux;
#else
extern void init_registers_arc_v2_linux (void);
extern const struct target_desc *tdesc_arc_v2_linux;
#endif

static const struct target_desc *
arc_read_description (void)
{
#ifdef __ARC700__
  return tdesc_arc_arcompact_linux;
#else
  return tdesc_arc_v2_linux;
#endif
}

/* Implementation of linux_target_ops method "arch_setup".  */

static void
arc_arch_setup (void)
{
  current_process ()->tdesc = arc_read_description ();
}

/* Implementation of linux_target_ops method "cannot_fetch_register".  */

static int
arc_cannot_fetch_register (int regno)
{
  return regno >= (current_process ()->tdesc->num_registers);
}

/* Implementation of linux_target_ops method "cannot_store_register".  */

static int
arc_cannot_store_register (int regno)
{
  return regno >= (current_process ()->tdesc->num_registers);
}

/* Implementation of linux_target_ops method "breakpoint_at".

   The breakpoint instruction is TRAP_S 1, network function ntohs can be
   used to convert its little-endian form (0x3e78) to the host
   representation, which may be little-endian or big-endian (network
   representation is defined to be little-endian).  */

static int
arc_breakpoint_at (CORE_ADDR where)
{
  uint16_t insn;
  uint16_t breakpoint = ntohs (0x3e78);

  (*the_target->read_memory) (where, (gdb_byte *) &insn, 2);
  return (insn == breakpoint);

}

/* PTRACE_GETREGSET/NT_PRSTATUS and PTRACE_SETREGSET/NT_PRSTATUS work with
   regsets in a struct, "user_regs_struct", defined in the
   linux/arch/arc/include/uapi/asm/ptrace.h header.  This code supports
   ARC Linux ABI v3 and v4.  */

/* Populate a ptrace NT_PRSTATUS regset from a regcache.

   This appears to be a unique approach to populating the buffer, but
   being name, rather than offset based, it is robust to future API
   changes, as there is no need to create a regmap of registers in the
   user_regs_struct.  */

static void
arc_fill_gregset (struct regcache *regcache, void *buf)
{
  struct user_regs_struct *regbuf = (struct user_regs_struct *) buf;

  /* Core registers.  */
  collect_register_by_name (regcache, "r0", &(regbuf->scratch.r0));
  collect_register_by_name (regcache, "r1", &(regbuf->scratch.r1));
  collect_register_by_name (regcache, "r2", &(regbuf->scratch.r2));
  collect_register_by_name (regcache, "r3", &(regbuf->scratch.r3));
  collect_register_by_name (regcache, "r4", &(regbuf->scratch.r4));
  collect_register_by_name (regcache, "r5", &(regbuf->scratch.r5));
  collect_register_by_name (regcache, "r6", &(regbuf->scratch.r6));
  collect_register_by_name (regcache, "r7", &(regbuf->scratch.r7));
  collect_register_by_name (regcache, "r8", &(regbuf->scratch.r8));
  collect_register_by_name (regcache, "r9", &(regbuf->scratch.r9));
  collect_register_by_name (regcache, "r10", &(regbuf->scratch.r10));
  collect_register_by_name (regcache, "r11", &(regbuf->scratch.r11));
  collect_register_by_name (regcache, "r12", &(regbuf->scratch.r12));
  collect_register_by_name (regcache, "r13", &(regbuf->callee.r13));
  collect_register_by_name (regcache, "r14", &(regbuf->callee.r14));
  collect_register_by_name (regcache, "r15", &(regbuf->callee.r15));
  collect_register_by_name (regcache, "r16", &(regbuf->callee.r16));
  collect_register_by_name (regcache, "r17", &(regbuf->callee.r17));
  collect_register_by_name (regcache, "r18", &(regbuf->callee.r18));
  collect_register_by_name (regcache, "r19", &(regbuf->callee.r19));
  collect_register_by_name (regcache, "r20", &(regbuf->callee.r20));
  collect_register_by_name (regcache, "r21", &(regbuf->callee.r21));
  collect_register_by_name (regcache, "r22", &(regbuf->callee.r22));
  collect_register_by_name (regcache, "r23", &(regbuf->callee.r23));
  collect_register_by_name (regcache, "r24", &(regbuf->callee.r24));
  collect_register_by_name (regcache, "r25", &(regbuf->callee.r25));
  collect_register_by_name (regcache, "gp", &(regbuf->scratch.gp));
  collect_register_by_name (regcache, "fp", &(regbuf->scratch.fp));
  collect_register_by_name (regcache, "sp", &(regbuf->scratch.sp));
  collect_register_by_name (regcache, "blink", &(regbuf->scratch.blink));

  /* Loop registers.  */
  collect_register_by_name (regcache, "lp_count", &(regbuf->scratch.lp_count));
  collect_register_by_name (regcache, "lp_start", &(regbuf->scratch.lp_start));
  collect_register_by_name (regcache, "lp_end", &(regbuf->scratch.lp_end));

  /* PC should be written to "return address", instead of stop address.  */
  collect_register_by_name (regcache, "pc", &(regbuf->scratch.ret));

  /* Currently ARC Linux ptrace doesn't allow writes to status32 because
     some of it's bits are kernel mode-only and shoudn't be writable from
     user-space.  Writing status32 from debugger could be useful, though,
     so ability to write non-priviliged bits will be added to kernel
     sooner or later.  */

  /* BTA.  */
  collect_register_by_name (regcache, "bta", &(regbuf->scratch.bta));
}

/* Populate a regcache from a ptrace NT_PRSTATUS regset.  */

static void
arc_store_gregset (struct regcache *regcache, const void *buf)
{
  const struct user_regs_struct *regbuf = (const struct user_regs_struct *) buf;

  /* Core registers.  */
  supply_register_by_name (regcache, "r0", &(regbuf->scratch.r0));
  supply_register_by_name (regcache, "r1", &(regbuf->scratch.r1));
  supply_register_by_name (regcache, "r2", &(regbuf->scratch.r2));
  supply_register_by_name (regcache, "r3", &(regbuf->scratch.r3));
  supply_register_by_name (regcache, "r4", &(regbuf->scratch.r4));
  supply_register_by_name (regcache, "r5", &(regbuf->scratch.r5));
  supply_register_by_name (regcache, "r6", &(regbuf->scratch.r6));
  supply_register_by_name (regcache, "r7", &(regbuf->scratch.r7));
  supply_register_by_name (regcache, "r8", &(regbuf->scratch.r8));
  supply_register_by_name (regcache, "r9", &(regbuf->scratch.r9));
  supply_register_by_name (regcache, "r10", &(regbuf->scratch.r10));
  supply_register_by_name (regcache, "r11", &(regbuf->scratch.r11));
  supply_register_by_name (regcache, "r12", &(regbuf->scratch.r12));
  supply_register_by_name (regcache, "r13", &(regbuf->callee.r13));
  supply_register_by_name (regcache, "r14", &(regbuf->callee.r14));
  supply_register_by_name (regcache, "r15", &(regbuf->callee.r15));
  supply_register_by_name (regcache, "r16", &(regbuf->callee.r16));
  supply_register_by_name (regcache, "r17", &(regbuf->callee.r17));
  supply_register_by_name (regcache, "r18", &(regbuf->callee.r18));
  supply_register_by_name (regcache, "r19", &(regbuf->callee.r19));
  supply_register_by_name (regcache, "r20", &(regbuf->callee.r20));
  supply_register_by_name (regcache, "r21", &(regbuf->callee.r21));
  supply_register_by_name (regcache, "r22", &(regbuf->callee.r22));
  supply_register_by_name (regcache, "r23", &(regbuf->callee.r23));
  supply_register_by_name (regcache, "r24", &(regbuf->callee.r24));
  supply_register_by_name (regcache, "r25", &(regbuf->callee.r25));
  supply_register_by_name (regcache, "gp", &(regbuf->scratch.gp));
  supply_register_by_name (regcache, "fp", &(regbuf->scratch.fp));
  supply_register_by_name (regcache, "sp", &(regbuf->scratch.sp));
  supply_register_by_name (regcache, "blink", &(regbuf->scratch.blink));

  /* Loop registers.  */
  supply_register_by_name (regcache, "lp_count", &(regbuf->scratch.lp_count));
  supply_register_by_name (regcache, "lp_start", &(regbuf->scratch.lp_start));
  supply_register_by_name (regcache, "lp_end", &(regbuf->scratch.lp_end));

  /* PC value is read from stop address.  */
  supply_register_by_name (regcache, "pc", &(regbuf->stop_pc));
  unsigned long pcl = regbuf->stop_pc & ~3L;
  supply_register_by_name (regcache, "pcl", &pcl);

  /* Other auxilliary registers.  */
  supply_register_by_name (regcache, "status32", &(regbuf->scratch.status32));

  /* BTA.  */
  supply_register_by_name (regcache, "bta", &(regbuf->scratch.bta));
}

#ifdef ARC_HAS_V2_REGSET

/* Copy registers from regcache to user_regs_arcv2.  */

static void
arc_fill_v2_regset (struct regcache *regcache, void *buf)
{
  struct user_regs_arcv2 *regbuf = (struct user_regs_arcv2 *) buf;

  collect_register_by_name (regcache, "r30", &(regbuf->r30));
  collect_register_by_name (regcache, "r58", &(regbuf->r58));
  collect_register_by_name (regcache, "r59", &(regbuf->r59));
}

/* Copy registers from user_regs_arcv2 to regcache.  */

static void
arc_store_v2_regset (struct regcache *regcache, const void *buf)
{
  struct user_regs_arcv2 *regbuf = (struct user_regs_arcv2 *) buf;

  supply_register_by_name (regcache, "r30", &(regbuf->r30));
  supply_register_by_name (regcache, "r58", &(regbuf->r58));
  supply_register_by_name (regcache, "r59", &(regbuf->r59));
}

#endif

/* Fetch the thread-local storage pointer for libthread_db.  Note that
   this function is not called from GDB, but is called from libthread_db.

   This is the same function as for other architectures, for example in
   linux-arm-low.c.  */

ps_err_e
ps_get_thread_area (const struct ps_prochandle *ph, lwpid_t lwpid,
		    int idx, void **base)
{
  if (ptrace (PTRACE_GET_THREAD_AREA, lwpid, NULL, base) != 0)
    return PS_ERR;

  /* IDX is the bias from the thread pointer to the beginning of the
     thread descriptor.  It has to be subtracted due to implementation
     quirks in libthread_db.  */
  *base = (void *) ((char *) *base - idx);

  return PS_OK;
}

static struct regset_info arc_regsets[] =
{
  { PTRACE_GETREGSET, PTRACE_SETREGSET, NT_PRSTATUS,
    sizeof (struct user_regs_struct), GENERAL_REGS,
    arc_fill_gregset, arc_store_gregset
  },
#ifdef ARC_HAS_V2_REGSET
  { PTRACE_GETREGSET, PTRACE_SETREGSET, NT_ARC_V2,
    sizeof (struct user_regs_arcv2), GENERAL_REGS,
    arc_fill_v2_regset, arc_store_v2_regset
  },
#endif
  NULL_REGSET
};

static struct regsets_info arc_regsets_info =
{
  arc_regsets, /* regsets */
  0, /* num_regsets */
  NULL, /* disabled regsets */
};

static struct regs_info regs_info =
{
  NULL, /* regset_bitmap */
  NULL, /* usrregs */
  &arc_regsets_info
};

static const struct regs_info *
arc_regs_info (void)
{
  return &regs_info;
}

struct linux_target_ops the_low_target =
{
  arc_arch_setup,
  arc_regs_info,
  arc_cannot_fetch_register,
  arc_cannot_store_register,
  NULL, /* fetch_register  */
  linux_get_pc_32bit,
  linux_set_pc_32bit,
  NULL, /* breakpoint_kind_from_pc  */
  NULL, /* sw_breakpoint_from_kind  */
  NULL, /* get_next_pcs  */
  0,    /* decr_pc_after_break  */
  arc_breakpoint_at,
};

void
initialize_low_arch (void)
{
#ifdef __ARC700__
  init_registers_arc_arcompact_linux ();
#else
  init_registers_arc_v2_linux ();
#endif

  initialize_regsets_info (&arc_regsets_info);
}
