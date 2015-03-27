/* Target dependent code for ARC processor family, for GDB, the GNU debugger.

   Copyright 2014-2015 Synopsys Inc.

   Authors:
      Anton Kolesov <Anton.Kolesov@synopsys.com

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
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include "defs.h"
#include "frame.h"
#include "inferior.h"
#include "gdbcore.h"
#include "regcache.h"
#include "gdb_assert.h"
#include "target.h"
#include "linux-nat.h"

#include <stdint.h>
#include <sys/types.h>
#include <sys/param.h>
#include <signal.h>
#include <sys/user.h>
#include <sys/ioctl.h>
#include "gdb_wait.h"
#include <fcntl.h>
#include <sys/procfs.h>
#include <sys/ptrace.h>
#include <linux/elf.h>

#include "gregset.h"
#include "arc-tdep.h"
#include "arc-linux-tdep.h"

/* Defines ps_err_e, struct ps_prochandle.  */
#include "gdb_proc_service.h"

/* Fetch greg-register(s) from process/thread TID and store value(s) in GDB's
 * register array.  */
static void fetch_gregs (struct regcache *regcache, int regnum);
static void store_gregs (struct regcache *regcache, int regnum);
static void arc_linux_prepare_to_resume (struct lwp_info *lwp);

/* On GNU/Linux, threads are implemented as pseudo-processes, in which
   case we may be tracing more than one process at a time.  In that
   case, inferior_ptid will contain the main process ID and the
   individual thread (process) ID.  get_thread_id () is used to get
   the thread id if it's available, and the process id otherwise.  */
static int
get_thread_id (ptid_t ptid)
{
  int tid = ptid_get_lwp (ptid);
  if (0 == tid)
    tid = ptid_get_pid (ptid);
  return tid;
}

/* Read register from target process via ptrace() into regcache. */
static void
fetch_gregs (struct regcache *regcache, int regnum)
{
  const gdb_gregset_t regs;
  struct iovec iov;
  int tid = get_thread_id (inferior_ptid);

  iov.iov_base = &regs;
  iov.iov_len = sizeof(gdb_gregset_t);

  if (ptrace (PTRACE_GETREGSET, tid, NT_PRSTATUS, (void*)&iov) < 0)
    {
      perror_with_name (_("Couldn't get registers"));
      return;
    }

  supply_gregset (regcache, &regs);
}

/* Store greg-register(s) in GDB's register array into the process/thread
 * specified by TID.  */
static void
store_gregs (struct regcache *regcache, int regnum)
{
  gdb_gregset_t regs;
  struct iovec iov;
  int tid = get_thread_id (inferior_ptid);

  iov.iov_base = &regs;
  iov.iov_len = sizeof(gdb_gregset_t);

  if (ptrace (PTRACE_GETREGSET, tid, NT_PRSTATUS, (void*)&iov) < 0)
    {
      perror_with_name (_("Couldn't get registers"));
      return;
    }

  fill_gregset (regcache, &regs, regnum);

  if (ptrace (PTRACE_SETREGSET, tid, NT_PRSTATUS, (void*)&iov) < 0)
    {
      perror_with_name (_("Couldn't write registers"));
      return;
    }
}

/* Function exported to target ops. */
static void
arc_linux_fetch_inferior_registers (struct target_ops *ops,
				    struct regcache *regcache, int regnum)
{
  fetch_gregs (regcache, regnum);
}

/* Function exported to target ops. */
static void
arc_linux_store_inferior_registers (struct target_ops *ops,
				    struct regcache *regcache, int regnum)
{
  store_gregs (regcache, regnum);
}

void
fill_gregset (const struct regcache *regcache,
	      gdb_gregset_t *gregsetp, int regno)
{
    arc_linux_collect_gregset (NULL, regcache, regno, gregsetp, 0);
}

void
supply_gregset (struct regcache *regcache, const gdb_gregset_t *gregsetp)
{
    arc_linux_supply_gregset (NULL, regcache, -1, gregsetp, 0);
}

void
fill_fpregset (const struct regcache *regcache,
	       gdb_fpregset_t *fpregsetp, int regnum)
{
    /* No FP registers on ARC. */
    if (arc_debug)
      fprintf_unfiltered (gdb_stdlog, "%s() called.", __func__);
    return;
}

void
supply_fpregset (struct regcache *regcache,
		 const gdb_fpregset_t *fpregsetp)
{
    /* No FP registers on ARC. */
    if (arc_debug)
      fprintf_unfiltered (gdb_stdlog, "%s() called.", __func__);
    return;
}

/* As described in arc_linux_collect_gregset(), we need to write resume-PC to
   ERET. However by default GDB for native targets doesn't write registers if
   they haven't been changed. This is a callback called by generic GDB, and in
   this callback we have to rewrite PC value so it would force rewrite of
   register on target. It seems that the only other arch that utilizes this
   hook is x86/x86-64 for HW breakpoint support. But then, AFAIK no other arch
   has this stop_pc/eret complexity.

   I haven't found any other way to force GDB to write register to target,
   other than this fake write of register value. Maybe there is some better
   way? */
static void
arc_linux_prepare_to_resume (struct lwp_info *lwp) {
    ULONGEST new_pc;
    struct regcache *regcache;
    struct gdbarch *gdbarch;

    /* When new processes and threads are created we do not have address space
     * for them and call to get_thread_regcache will cause an internal error in
     * GDB. It looks like that checking for last_resume_kind is sensible way to
     * determine processes for which we cannot get regcache. Ultimately better
     * way would be remote the need for prepare_to_resume at all. */
    if (lwp->last_resume_kind == resume_stop)
	return;

    regcache = get_thread_regcache (lwp->ptid);
    gdbarch = get_regcache_arch (regcache);

    /* Read current PC value, then write it back. It is required to call
       invalidate() otherwise GDB will note that new value is equal to old
       value and will skip write. */
    regcache_cooked_read_unsigned(regcache, gdbarch_pc_regnum(gdbarch),
        &new_pc);
    regcache_invalidate(regcache, gdbarch_pc_regnum (gdbarch));
    regcache_cooked_write_unsigned(regcache, gdbarch_pc_regnum(gdbarch),
	new_pc);
}

/* Fetch the thread-local storage pointer for libthread_db. Note that this
 * function is not called from GDB, but is called from libthread_db. */
ps_err_e
ps_get_thread_area (const struct ps_prochandle *ph, lwpid_t lwpid, int idx,
                    void **base)
{
    if (arc_debug >= 2)
      fprintf_unfiltered (gdb_stdlog, "ps_get_thread_area called");

    if (ptrace (PTRACE_GET_THREAD_AREA, lwpid, NULL, base) != 0)
      return PS_ERR;

    /* IDX is the bias from the thread pointer to the beginning of the thread
     * descriptor.  It has to be subtracted due to implementation quirks in
     * libthread_db.  */
    *base = (void *) ((char *)*base - idx);

    return PS_OK;
} /* ps_get_thread_area */

void _initialize_arc_linux_nat (void);

void
_initialize_arc_linux_nat (void)
{
  struct target_ops *t;
  /* Fill in the generic GNU/Linux methods.  */
  t = linux_target ();
  t->to_fetch_registers = arc_linux_fetch_inferior_registers;
  t->to_store_registers = arc_linux_store_inferior_registers;
  linux_nat_add_target (t);
  linux_nat_set_prepare_to_resume(t, arc_linux_prepare_to_resume);
}

/* vim: set sts=2 shiftwidth=2 ts=8: */
