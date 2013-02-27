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
#include "regdef.h"
#include "linux-low.h"

#include <elf.h>
#include <linux/ptrace.h>

/*! This struct will eventually be provided in asm/ptrace.h in the 3.8 Linux
    kernel with library ABI v3. For now we provide it conditionally.

    The meaning of orig_r0 is lost in the mists of time. For the meaning of
    orig_r8, see the comments on the variable orig_r8 below. */
#ifdef ARC_LEGACY_PTRACE_ABI
struct user_regs_struct {

  struct scratch {
    long int pad;
    long int bta;	/* bta_l1, bta_l2, erbta */
    long int lp_start;
    long int lp_end;
    long int lp_count;
    long int status32;	/* status32_l1, status32_l2, erstatus */
    long int ret;	/* ilink1, ilink2 or eret */
    long int blink;
    long int fp;
    long int gp;	/* gp */
    long int r12;
    long int r11;
    long int r10;
    long int r9;
    long int r8;
    long int r7;
    long int r6;
    long int r5;
    long int r4;
    long int r3;
    long int r2;
    long int r1;
    long int r0;
    long int sp;	/* user/kernel sp depending on where we came from  */
    long int orig_r0;
    long int orig_r8;
  } scratch;
  struct callee {
    long int pad;
    long int r25;
    long int r24;
    long int r23;
    long int r22;
    long int r21;
    long int r20;
    long int r19;
    long int r18;
    long int r17;
    long int r16;
    long int r15;
    long int r14;
    long int r13;
  } callee;
  long int efa;		/* break pt addr, for break points in delay slots */
  long int stop_pc;	/* give dbg stop_pc directly after checking orig_r8 */
};
#endif

/*! Register to deal with PTRACE overlay.

    Three of the ptrace register slots (ret, bta and status32) have different
    meanings depending on whether we are in an exception, a level 1 interrupt
    or a level 2 interrupt. The meanings are determined by the orig_r8
    register:
   
    >= 0 means any form of exception (e.g. a breakpoint)
       - bta is erbta
       - status32 is erstatus32
       - ret is eret
    -1 means level 1 interrupt
       - bta is bta_l1
       - status32 is status32_l1
       - ret is ilink1
    -2 means level 2 interrupt
       - bta is bta_l2
       - status32 is status32_l2
       - ret is ilink1

    Any other value is an error.

    The value of orig_r8 is updated whenever we collect the PR_STATUS
    regset. The default value assumes we are in an exception, since for
    gdbserver that is most likely.

    @todo Should the default be an erroneous value like -3? */
static long int orig_r8 = 0;

/*! Number of registers. */
static long int arc_num_regs;

/*! Defined in auto-generated file arc-reg.c. */
extern void init_registers_arc (void);


/*! Set up the ARC architecture.

    New function for GDB 7.x. Initialize the ARC architecture.

    For now it just initializes the register cache and number of registers.
    But in the future expect it to configure the aux registers from the XML
    file. */
static void
arc_arch_setup (void)
{
  /* The auto generated register initialization. */
  init_registers_arc ();

  /* Work out how many registers we have. */
  arc_num_regs = register_cache_size() / sizeof (struct reg);
  the_low_target.num_regs = arc_num_regs;

}	/* arc_arch_setup () */


/*! Can a register be written?

    The only register in the general set that cannot be written is EFA.

    @param[in] regno  Number of reg to check.

    @return  Non-zero if register cannot be written, zero otherwise. */
static int
arc_cannot_store_register (int regno)
{
  /* We can write every register except efa. */
  return (regno < 0)
    || (regno == find_regno ("efa"))
    || (regno >= arc_num_regs);

}	/* arc_cannot_store_register () */


/*! Can a register be read?

    All registers in the general set can be written.

    @param[in] regno  Number of reg to check.

    @return  Non-zero if register cannot be read, zero otherwise. */
static int
arc_cannot_fetch_register (int regno)
{
  return (regno < 0) || (regno >= arc_num_regs);

}	/* arc_cannot_fetch_register () */


/*! Get the PC from the register cache.

    @param[in] regcache  Register cache

    @return  The value of the PC. */
static CORE_ADDR
arc_get_pc (struct regcache *regcache)
{
  unsigned long pc;
  collect_register_by_name (regcache, "pc", &pc);
  if (debug_threads)
    fprintf (stderr, "pc is %08lx\n", pc);
  return (CORE_ADDR) pc;

}	/* arc_get_pc () */


/*! Set the PC in the register cache.

    @param[out] regcache  Register cache
    @param[in]  pc        value to write to the PC.

    To set the PC, we actually don't write the stop_pc (which has no
    effect). Instead we overwrite the return address, which in turn depends on
    the value of orig_r8 to determine which return address matters. */
static void
arc_set_pc (struct regcache *regcache, CORE_ADDR pc)
{
  unsigned long newpc = (unsigned long) pc;

  /* Determin which return address to write */
  if (orig_r8 >= 0)
    {
      /* Exception */
      supply_register_by_name (regcache, "eret", &newpc);
    }
  else if (-1 == orig_r8)
    {
      /* Level 1 interrupt */
      supply_register_by_name (regcache, "ilink1", &newpc);
    }
  else if (-2 == orig_r8)
    {
      /* Level 2 interrupt */
      supply_register_by_name (regcache, "ilink2", &newpc);
    }
  else
    {
      /* Error. */
      fprintf (stderr, "ERROR: arc_set_pc: orig_r8 is %ld: ignored.\n",
	       orig_r8);
    }
}	/* arc_set_pc () */


/*! Populate a ptrace NT_PRSTATUS regset from a regcache.

    We know the buffer regset supplied must therefore be a struct
    user_regs_struct.

    @note This appears to be a unique approach to populating the buffer, but
          being name, rather than offset based, it is robust to future API
          changes. It is appropriate with the new Linux PTRACE_GETREGSET and
          PTRACE_SETREGSET functionality. Since this function should only be
          called when we are in user interaction with the client, performance
          is not critical.

    @param[in]  regcache  Register cache supplying the values.
    @param[out] buf       ptrace buffer to be filled. */
static void
arc_fill_gregset (struct regcache *regcache, void *buf)
{
  struct user_regs_struct *regbuf = buf;

  /* Collect all the unique registers by name. */
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
  /* ilink1 depedent on orig_r8 - see below. */
  /* ilink2 depedent on orig_r8 - see below. */
  collect_register_by_name (regcache, "blink", &(regbuf->scratch.blink));
  /* Extension core regs 32-59 not currently supported. */
  collect_register_by_name (regcache, "lp_count", &(regbuf->scratch.lp_count));
  /* limm and pcl not currently supported. */
  /* Auxilliary registers */
  collect_register_by_name (regcache, "pc", &(regbuf->stop_pc));
  /* status32 not currently supported. */
  /* bta depedent on orig_r8 - see below. */
  /* ecr not currently supported. */
  /* icause1 not currently supported. */
  /* icause2 not currently supported. */
  /* status32_l1 depedent on orig_r8 - see below. */
  /* status32_l2 depedent on orig_r8 - see below. */
  /* eret depedent on orig_r8 - see below. */
  /* erbta depedent on orig_r8 - see below. */
  /* erstatus depedent on orig_r8 - see below. */
  /* aux_irq_lv12 not currently supported. */
  /* aux_irq_lev not currently supported. */
  /* aux_irq_hint not currently supported. */
  /* aux_ienable not currently supported. */
  /* aux_itrigger not currently supported. */
  /* aux_irq_pulse_cancel not currently supported. */
  /* aux_irq_pending not currently supported. */
  collect_register_by_name (regcache, "lp_start", &(regbuf->scratch.lp_start));
  collect_register_by_name (regcache, "lp_end", &(regbuf->scratch.lp_end));
  collect_register_by_name (regcache, "efa", &(regbuf->efa));
  /* bta_l1 depedent on orig_r8 - see below. */
  /* bta_l2 depedent on orig_r8 - see below. */

  /* Three registers in ptrace map to multiple GDB registers, depending on the
     value of orig_r8. */
  if (orig_r8 >= 0)
    {
      /* Exception */
      collect_register_by_name (regcache, "erbta", &(regbuf->scratch.bta));
      collect_register_by_name (regcache, "erstatus32",
				&(regbuf->scratch.status32));
      collect_register_by_name (regcache, "eret", &(regbuf->scratch.ret));
    }
  else if (-1 == orig_r8)
    {
      /* Level 1 interrupt */
      collect_register_by_name (regcache, "bta_l1", &(regbuf->scratch.bta));
      collect_register_by_name (regcache, "status32_l1",
				&(regbuf->scratch.status32));
      collect_register_by_name (regcache, "ilink1", &(regbuf->scratch.ret));
    }
  else if (-2 == orig_r8)
    {
      /* Level 2 interrupt */
      collect_register_by_name (regcache, "bta_l2", &(regbuf->scratch.bta));
      collect_register_by_name (regcache, "status32_l2",
				&(regbuf->scratch.status32));
      collect_register_by_name (regcache, "ilink2", &(regbuf->scratch.ret));
    }
  else
    {
      /* Error. */
      fprintf (stderr, "ERROR: arc_fill_gregset: orig_r8 is %ld: ignored.\n",
	       orig_r8);
    }
}	/* arc_fill_gregset () */


/*! Populate a regcache from a ptrace NT_PRSTATUS regset.

    We know the regset buffer supplied must therefore be a struct
    user_regs_struct.

    We update the orig_r8 register with a new value to be used when
    determining the use of bta, status32 and ret fields.

    @note This appears to be a unique approach to populating the regcache, but
          being name, rather than offset based, it is robust to future API
          changes. It is appropriate with the new Linux PTRACE_GETREGSET and
          PTRACE_SETREGSET functionality. Since this function should only be
          called when we are in user interaction with the client, performance
          is not critical.

    @param[in]  regcache  Register cache supplying the values.
    @param[out] buf       ptrace buffer to be filled. */
static void
arc_store_gregset (struct regcache *regcache, const void *buf)
{
  const struct user_regs_struct *regbuf = buf;

  /* Supply all the unique registers by name. */
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
  /* ilink1 depedent on orig_r8 - see below. */
  /* ilink2 depedent on orig_r8 - see below. */
  supply_register_by_name (regcache, "blink", &(regbuf->scratch.blink));
  /* Extension core regs 32-59 not currently supported. */
  supply_register_by_name (regcache, "lp_count", &(regbuf->scratch.lp_count));
  /* limm and pcl not currently supported. */
  /* Auxilliary registers */
  supply_register_by_name (regcache, "pc", &(regbuf->stop_pc));
  /* status32 not currently supported. */
  /* bta depedent on orig_r8 - see below. */
  /* ecr not currently supported. */
  /* icause1 not currently supported. */
  /* icause2 not currently supported. */
  /* status32_l1 depedent on orig_r8 - see below. */
  /* status32_l2 depedent on orig_r8 - see below. */
  /* eret depedent on orig_r8 - see below. */
  /* erbta depedent on orig_r8 - see below. */
  /* erstatus depedent on orig_r8 - see below. */
  /* aux_irq_lv12 not currently supported. */
  /* aux_irq_lev not currently supported. */
  /* aux_irq_hint not currently supported. */
  /* aux_ienable not currently supported. */
  /* aux_itrigger not currently supported. */
  /* aux_irq_pulse_cancel not currently supported. */
  /* aux_irq_pending not currently supported. */
  supply_register_by_name (regcache, "lp_start", &(regbuf->scratch.lp_start));
  supply_register_by_name (regcache, "lp_end", &(regbuf->scratch.lp_end));
  supply_register_by_name (regcache, "efa", &(regbuf->efa));
  /* bta_l1 depedent on orig_r8 - see below. */
  /* bta_l2 depedent on orig_r8 - see below. */

  /* Update orig_r8 from the ptrace structure. */
  orig_r8 = regbuf->scratch.orig_r8;

  /* Three registers in ptrace map to multiple GDB registers, depending on the
     value of orig_r8. */
  if (orig_r8 >= 0)
    {
      /* Exception */
      supply_register_by_name (regcache, "erbta", &(regbuf->scratch.bta));
      supply_register_by_name (regcache, "erstatus32",
				&(regbuf->scratch.status32));
      supply_register_by_name (regcache, "eret", &(regbuf->scratch.ret));
    }
  else if (-1 == orig_r8)
    {
      /* Level 1 interrupt */
      supply_register_by_name (regcache, "bta_l1", &(regbuf->scratch.bta));
      supply_register_by_name (regcache, "status32_l1",
				&(regbuf->scratch.status32));
      supply_register_by_name (regcache, "ilink1", &(regbuf->scratch.ret));
    }
  else if (-2 == orig_r8)
    {
      /* Level 2 interrupt */
      supply_register_by_name (regcache, "bta_l2", &(regbuf->scratch.bta));
      supply_register_by_name (regcache, "status32_l2",
				&(regbuf->scratch.status32));
      supply_register_by_name (regcache, "ilink2", &(regbuf->scratch.ret));
    }
  else
    {
      /* Error. */
      fprintf (stderr, "ERROR: arc_store_gregset: orig_r8 is %ld: ignored.\n",
	       orig_r8);
    }
}	/* arc_store_gregset () */


/*! Define how we set/get different regsets.

    For ARC we only have support for NT_PRSTATUS, which will return all the
    registers in struct user_regs_struct. */
struct regset_info target_regsets[] = {
  { PTRACE_GETREGSET, PTRACE_SETREGSET, NT_PRSTATUS,
    sizeof (struct user_regs_struct), GENERAL_REGS,
    arc_fill_gregset, arc_store_gregset },
  { 0, 0, 0, -1, -1, NULL, NULL }
};


/*! Define all the ARC specific interface functions.

    For a description of each entry see linux-low.h. We set all elements, even
    though most are not used, so we are likely to trigger an error on any API
    change.

    @note. We have to initialize with constants, so we can't use a variable
           for num_regs. We set it to zero here, and put the correct value in
           during the init function.

    @note. regmap is used only if access to individual registers is possible
           rather than just using regsets. By setting regset_bitmap to NULL we
           indicate on regsets are used, so we need not define regmap.

    @note. The ARC client relies exclusively on software breakpoints, even
           for single step, so will set breakpoints by using memory
           read/write. So we do not need the breakpoint functions. */
struct linux_target_ops the_low_target = {
  .arch_setup                       = arc_arch_setup,
  .num_regs                         = 0,	/* Set later during init. */
  .regmap                           = NULL,
  .regset_bitmap                    = NULL,
  .cannot_fetch_register            = arc_cannot_fetch_register,
  .cannot_store_register            = arc_cannot_store_register,
  .fetch_register                   = NULL,
  .get_pc                           = arc_get_pc,
  .set_pc                           = arc_set_pc,
  .breakpoint                       = NULL,
  .breakpoint_len                   = 0,
  .breakpoint_reinsert_addr         = NULL,
  .decr_pc_after_break              = 0,
  .breakpoint_at                    = NULL,
  .insert_point                     = NULL,
  .remove_point                     = NULL,
  .stopped_by_watchpoint            = NULL,
  .stopped_data_address             = NULL,
  .collect_ptrace_register          = NULL,
  .supply_ptrace_register           = NULL,
  .siginfo_fixup                    = NULL,
  .new_process                      = NULL,
  .new_thread                       = NULL,
  .prepare_to_resume                = NULL,
  .process_qsupported               = NULL,
  .supports_tracepoints             = NULL,
  .get_thread_area                  = NULL,
  .install_fast_tracepoint_jump_pad = NULL,
  .emit_ops                         = NULL,
  .get_min_fast_tracepoint_insn_len = NULL
};
