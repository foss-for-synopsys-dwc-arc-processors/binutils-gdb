/* Native-dependent code for GNU/Linux ARC.

   Copyright 2020 Free Software Foundation, Inc.

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

#include "defs.h"
#include "frame.h"
#include "inferior.h"
#include "gdbcore.h"
#include "regcache.h"
#include "gdbsupport/gdb_assert.h"
#include "target.h"
#include "linux-nat.h"
#include "nat/gdb_ptrace.h"

#include <stdint.h>
#include <sys/types.h>
#include <sys/param.h>
#include <signal.h>
#include <sys/user.h>
#include <sys/ioctl.h>
#include "gdbsupport/gdb_wait.h"
#include <fcntl.h>
#include <sys/procfs.h>
#include <linux/elf.h>

#include "gregset.h"
#include "arc-tdep.h"
#include "arc-linux-tdep.h"
#include "arch/arc.h"

/* Defines ps_err_e, struct ps_prochandle.  */
#include "gdb_proc_service.h"

/* Linux starting with 4.12 supports NT_ARC_V2 note type, which adds R30,
   R58 and R59 registers, which are specific to ARC HS and aren't
   available in ARC 700.  */
#if defined (NT_ARC_V2) && defined (__ARCHS__)
#define ARC_HAS_V2_REGSET
#endif

class arc_linux_nat_target final : public linux_nat_target
{
public:
  /* Add ARC register access methods.  */
  void fetch_registers (struct regcache *, int) override;
  void store_registers (struct regcache *, int) override;

  const struct target_desc *read_description () override;

  /* Handle threads  */
  void low_prepare_to_resume (struct lwp_info *lp) override;
};

static arc_linux_nat_target the_arc_linux_nat_target;

/* Read general registers from target process via ptrace () into regcache.  */

static void
fetch_gregs (struct regcache *regcache, int regnum)
{
  long tid = regcache->ptid ().lwp ();
  gdb_gregset_t regs;
  struct iovec iov;
  iov.iov_base = &regs;
  iov.iov_len = sizeof (gdb_gregset_t);

  if (ptrace (PTRACE_GETREGSET, tid, NT_PRSTATUS, (void *) &iov) < 0)
    {
      perror_with_name (_("Couldn't get general registers"));
      return;
    }

  supply_gregset (regcache, &regs);
}

#ifdef ARC_HAS_V2_REGSET
/* Read ARC v2 registers from target process via ptrace () into regcache.  */

static void
fetch_v2_regs (struct regcache *regcache, int regnum)
{
  long tid = regcache->ptid ().lwp ();
  bfd_byte buffer[ARC_LINUX_SIZEOF_V2_REGSET];
  struct iovec iov;
  iov.iov_base = &buffer;
  iov.iov_len = ARC_LINUX_SIZEOF_V2_REGSET;

  if (ptrace (PTRACE_GETREGSET, tid, NT_ARC_V2, (void *) &iov) < 0)
    {
      perror_with_name (_("Couldn't get ARC HS registers"));
      return;
    }

  arc_linux_supply_v2_regset (NULL, regcache, -1, buffer, 0);
}
#endif

/* Store general registers from regcache into the it's thread.  */

static void
store_gregs (struct regcache *regcache, int regnum)
{
  long tid = regcache->ptid ().lwp ();
  gdb_gregset_t regs;
  struct iovec iov;
  iov.iov_base = &regs;
  iov.iov_len = sizeof (gdb_gregset_t);

  if (ptrace (PTRACE_GETREGSET, tid, NT_PRSTATUS, (void *) &iov) < 0)
    {
      perror_with_name (_("Couldn't get general registers"));
      return;
    }

  fill_gregset (regcache, &regs, regnum);

  if (ptrace (PTRACE_SETREGSET, tid, NT_PRSTATUS, (void *) &iov) < 0)
    {
      perror_with_name (_("Couldn't write general registers"));
      return;
    }
}

#ifdef ARC_HAS_V2_REGSET
/* Store ARC v2 registers from regcache into the it's thread.  */

static void
store_v2_regs (struct regcache *regcache, int regnum)
{
  long tid = regcache->ptid ().lwp ();
  bfd_byte buffer[ARC_LINUX_SIZEOF_V2_REGSET];
  struct iovec iov;
  iov.iov_base = &buffer;
  iov.iov_len = ARC_LINUX_SIZEOF_V2_REGSET;

  if (ptrace (PTRACE_GETREGSET, tid, NT_ARC_V2, (void *) &iov) < 0)
    {
      perror_with_name (_("Couldn't get ARC HS registers"));
      return;
    }

  arc_linux_collect_v2_regset (NULL, regcache, regnum, buffer, 0);

  if (ptrace (PTRACE_SETREGSET, tid, NT_ARC_V2, (void *) &iov) < 0)
    {
      perror_with_name (_("Couldn't write ARC HS registers"));
      return;
    }
}
#endif

/* Function set to target ops.  */

void
arc_linux_nat_target::fetch_registers (struct regcache *regcache, int regnum)
{
  fetch_gregs (regcache, regnum);
#ifdef ARC_HAS_V2_REGSET
  fetch_v2_regs (regcache, regnum);
#endif
}

/* Function set to target ops.  */

void
arc_linux_nat_target::store_registers (struct regcache *regcache, int regnum)
{
  store_gregs (regcache, regnum);
#ifdef ARC_HAS_V2_REGSET
  store_v2_regs (regcache, regnum);
#endif
}

/* Function exported to proc-service.c.  */

void
fill_gregset (const struct regcache *regcache,
	      gdb_gregset_t *gregsetp, int regno)
{
  arc_linux_collect_gregset (NULL, regcache, regno, gregsetp, 0);
}

/* Function exported to proc-service.c.  */

void
supply_gregset (struct regcache *regcache, const gdb_gregset_t *gregsetp)
{
  arc_linux_supply_gregset (NULL, regcache, -1, gregsetp, 0);
}

/* Function exported to proc-service.c.  ARC doesn't have separate FP
   registers.  */

void
fill_fpregset (const struct regcache *regcache,
	       gdb_fpregset_t *fpregsetp, int regnum)
{
  if (arc_debug)
    debug_printf ("arc-linux-nat: fill_fpregset called.");
  return;
}

/* Function exported to proc-service.c.  ARC doesn't have separate FP
   registers.  */

void
supply_fpregset (struct regcache *regcache, const gdb_fpregset_t *fpregsetp)
{
  if (arc_debug)
    debug_printf ("arc-linux-nat: supply_fpregset called.");
  return;
}

/* Implement the "read_description" method of linux_nat_target.  */

const struct target_desc *
arc_linux_nat_target::read_description ()
{
  /* This is a native target, hence description is hardcoded.  */
#ifdef __ARCHS__
  arc_gdbarch_features features (4, ARC_ISA_ARCV2);
#else
  arc_gdbarch_features features (4, ARC_ISA_ARCV1);
#endif
  return arc_lookup_target_description (features);
}

/* As described in arc_linux_collect_gregset(), we need to write resume-PC
   to ERET.  However by default GDB for native targets doesn't write
   registers if they haven't been changed.  This is a callback called by
   generic GDB, and in this callback we have to rewrite PC value so it
   would force rewrite of register on target.  It seems that the only
   other arch that utilizes this hook is x86/x86-64 for HW breakpoint
   support.  But then, AFAIK no other arch has this stop_pc/eret
   complexity.

   No better way was found, other than this fake write of register value,
   to force GDB into writing register to target.  Is there any?  */

void
arc_linux_nat_target::low_prepare_to_resume (struct lwp_info *lwp)
{
  /* When new processes and threads are created we do not have address
     space for them and call to get_thread_regcache will cause an internal
     error in GDB.  It looks like that checking for last_resume_kind is
     sensible way to determine processes for which we cannot get regcache.
     Ultimately better way would be remove the need for
     low_prepare_to_resume at all.  */
  if (lwp->last_resume_kind == resume_stop)
    return;

  struct regcache *regcache = get_thread_regcache (this, lwp->ptid);
  struct gdbarch *gdbarch = regcache->arch ();

  /* Read current PC value, then write it back.  It is required to call
     invalidate() otherwise GDB will note that new value is equal to old
     value and will skip write.  */
  ULONGEST new_pc;
  regcache_cooked_read_unsigned (regcache, gdbarch_pc_regnum (gdbarch),
				 &new_pc);
  regcache->invalidate (gdbarch_pc_regnum (gdbarch));
  regcache_cooked_write_unsigned (regcache, gdbarch_pc_regnum (gdbarch),
				  new_pc);
}

/* Fetch the thread-local storage pointer for libthread_db.  Note that
   this function is not called from GDB, but is called from libthread_db.
   This is required to debug multithreaded applications with NPTL.  */

ps_err_e
ps_get_thread_area (struct ps_prochandle *ph, lwpid_t lwpid, int idx,
		    void **base)
{
  if (arc_debug >= 2)
    debug_printf ("arc-linux-nat: ps_get_thread_area called");

  if (ptrace (PTRACE_GET_THREAD_AREA, lwpid, NULL, base) != 0)
    return PS_ERR;

  /* IDX is the bias from the thread pointer to the beginning of the
     thread descriptor.  It has to be subtracted due to implementation
     quirks in libthread_db.  */
  *base = (void *) ((char *) *base - idx);

  return PS_OK;
}

/* Suppress warning from -Wmissing-prototypes.  */
void _initialize_arc_linux_nat (void);

void
_initialize_arc_linux_nat (void)
{
  /* Register the target.  */
  linux_target = &the_arc_linux_nat_target;
  add_inf_child_target (&the_arc_linux_nat_target);
}

/* vim: set sts=2 sw=2 ts=8: */
