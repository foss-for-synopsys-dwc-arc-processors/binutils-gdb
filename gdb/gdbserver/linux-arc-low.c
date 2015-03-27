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
   Boston, MA 02111-1307, USA.

   --------------------------------------------------------------------------

   The comments within this file are also licensed under under the terms of
   the GNU Free Documentation License as published by the Free Software
   Foundation; either version 1.3 of the License, or (at your option) any
   later version. See the file fdi.texi in the gdb/doc directory for copying
   conditions.

   You should have received a copy of the GNU Free Documentation License along
   with this program. If not, see <http://www.gnu.org/licenses/>.  */

/* -------------------------------------------------------------------------- */
/*!@file
                                                                               
   # ARC Linux gdbserver

   This file defines the implementation of gdbserver for ARC Linux.

   Access to registers via ptrace has changed between Linux 3.2 and Linux 3.9.
   With the new (ABI v3) interface in Linux 3.9, registers are accessed as a
   complete set with PTRACE_GETREGSET and PTRACE_SETREGSET. This file
   implements support only for ABI v3. If you need support for ABI v2, use
   ARC GNU Toolchain 4.8-R3 release.

   ptrace returns regsets in a struct, "user_regs_struct", defined in the
   asm/ptrace.h header. The implementation uses the arc_regsets
   functionality to control the access to registers. */
/* -------------------------------------------------------------------------- */

#include "server.h"
#include "regdef.h"
#include "linux-low.h"

#include <linux/elf.h>
#include <arpa/inet.h>
#include <asm/ptrace.h>
#include <sys/ptrace.h>

/* From include/uapi/asm/ptrace.h in the ARC Linux sources.
 * See user_regs_struct.
 *
 * @todo This is shared with arc-linux-tdep.h, so should be moved to common/
 * directory.
 */
#define BYTES_IN_REGISTER (4)
#define REGISTER_NOT_PRESENT (-1)
#define ARC_NUM_REGS (87)
static int arc_regmap[] =
{
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
  37 * BYTES_IN_REGISTER,	/* r13      */
  36 * BYTES_IN_REGISTER,	/* r14      */
  35 * BYTES_IN_REGISTER,	/* r15      */
  34 * BYTES_IN_REGISTER,	/* r16      */
  33 * BYTES_IN_REGISTER,	/* r17      */
  32 * BYTES_IN_REGISTER,	/* r18      */
  31 * BYTES_IN_REGISTER,	/* r19      */
  30 * BYTES_IN_REGISTER,	/* r20      */
  29 * BYTES_IN_REGISTER,	/* r21      */
  28 * BYTES_IN_REGISTER,	/* r22      */
  27 * BYTES_IN_REGISTER,	/* r23      */
  26 * BYTES_IN_REGISTER,	/* r24      */
  25 * BYTES_IN_REGISTER,	/* r25      */
  9 * BYTES_IN_REGISTER,	/* r26 (gp) */
  8 * BYTES_IN_REGISTER,	/* fp       */
  23 * BYTES_IN_REGISTER,	/* sp       */
  REGISTER_NOT_PRESENT,  	/* ilink1   */
  REGISTER_NOT_PRESENT,  	/* ilink2   */
  7 * BYTES_IN_REGISTER,	/* blink    */

  REGISTER_NOT_PRESENT,  	/* r32      */
  REGISTER_NOT_PRESENT,  	/* r33      */
  REGISTER_NOT_PRESENT,  	/* r34      */
  REGISTER_NOT_PRESENT,  	/* r35      */
  REGISTER_NOT_PRESENT,  	/* r36      */
  REGISTER_NOT_PRESENT,  	/* r37      */
  REGISTER_NOT_PRESENT,  	/* r38      */
  REGISTER_NOT_PRESENT,  	/* r39      */
  REGISTER_NOT_PRESENT,  	/* r40      */
  REGISTER_NOT_PRESENT,  	/* r41      */
  REGISTER_NOT_PRESENT,  	/* r42      */
  REGISTER_NOT_PRESENT,  	/* r43      */
  REGISTER_NOT_PRESENT,  	/* r44      */
  REGISTER_NOT_PRESENT,  	/* r45      */
  REGISTER_NOT_PRESENT,  	/* r46      */
  REGISTER_NOT_PRESENT,  	/* r47      */
  REGISTER_NOT_PRESENT,  	/* r48      */
  REGISTER_NOT_PRESENT,  	/* r49      */
  REGISTER_NOT_PRESENT,  	/* r50      */
  REGISTER_NOT_PRESENT,  	/* r51      */
  REGISTER_NOT_PRESENT,  	/* r52      */
  REGISTER_NOT_PRESENT,  	/* r53      */
  REGISTER_NOT_PRESENT,  	/* r54      */
  REGISTER_NOT_PRESENT,  	/* r55      */
  REGISTER_NOT_PRESENT,  	/* r56      */
  REGISTER_NOT_PRESENT,  	/* r57      */
  REGISTER_NOT_PRESENT,  	/* r58      */
  REGISTER_NOT_PRESENT,  	/* r59      */
  4 * BYTES_IN_REGISTER,	/* lp_count */
  REGISTER_NOT_PRESENT,  	/* reserved */
  REGISTER_NOT_PRESENT,  	/* limm     */
  REGISTER_NOT_PRESENT,  	/* pcl      */

  39 * BYTES_IN_REGISTER,	/* stop_pc  */
  2 * BYTES_IN_REGISTER,	/* lp_start */
  3 * BYTES_IN_REGISTER,	/* lp_end   */
  5 * BYTES_IN_REGISTER,	/* status32 */
  REGISTER_NOT_PRESENT,  	/* st32_l1  */
  REGISTER_NOT_PRESENT,  	/* st32_l2  */
  REGISTER_NOT_PRESENT,  	/* irq_lv12 */
  REGISTER_NOT_PRESENT,  	/* irq_lev  */
  REGISTER_NOT_PRESENT,  	/* irq_hint */
  6 * BYTES_IN_REGISTER,	/* ret      */
  REGISTER_NOT_PRESENT,  	/* erbta    */
  REGISTER_NOT_PRESENT,  	/* erstatus */
  REGISTER_NOT_PRESENT,  	/* ecr      */
  38 * BYTES_IN_REGISTER,	/* efa      */
  REGISTER_NOT_PRESENT,  	/* icause1  */
  REGISTER_NOT_PRESENT,  	/* icause2  */
  REGISTER_NOT_PRESENT,  	/* ienable  */
  REGISTER_NOT_PRESENT,  	/* itrigger */
  1 * BYTES_IN_REGISTER,	/* bta      */
  REGISTER_NOT_PRESENT,  	/* bta_l1   */
  REGISTER_NOT_PRESENT,  	/* bta_l2   */
  REGISTER_NOT_PRESENT,  	/* irq pulse*/
  REGISTER_NOT_PRESENT,  	/* irq pend */

  /* 24 * BYTES_IN_REGISTER,	orig_r8  */
};

/* -------------------------------------------------------------------------- */
/*			Externally defined functions.			      */
/* -------------------------------------------------------------------------- */

/*! Defined in auto-generated file arc-reg.c. */
extern void init_registers_arc (void);
extern const struct target_desc *tdesc_arc;


/* -------------------------------------------------------------------------- */
/*			       Target functions				      */
/*									      */
/* Presented in the order they are used in the_low_target.		      */
/* -------------------------------------------------------------------------- */

/*! Return target description.
 *
 *  @todo This function should return appropriate tdesc (ARCompact or ARC v2),
 *  depending on what target it is run on.
 */
static const struct target_desc *
arc_read_description (void)
{
  return tdesc_arc;
}	/* arc_read_description () */


static void
arc_arch_setup (void)
{
  current_process ()->tdesc = arc_read_description ();
}


/*! Can a register be read?

    We can only write the core registers excluding ilink1, ilink2, the
    extension registers, reserved register and limm registers along with
    the lp_start, lp_end, status32 and efa aux registers.

    @note The EFA register is a bit odd, since it is a privileged register,
          but it will help deal with breakpoints in delay slots.

    @todo This is not terribly efficient, but that probably doesn't matter. If
          it ever did matter, we should use the init function to build a table
          of whether regs can be read or written, then this function is just a
          table lookup.

    @param[in] regno  Number of reg to check.
    @return           Non-zero if register cannot be read, zero otherwise. */
static int
arc_cannot_fetch_register (int regno)
{
  return (regno >= ARC_NUM_REGS || regno < 0 || arc_regmap[regno] == -1);
}	/* arc_cannot_fetch_register () */


/*! Can a register be written?

    We can only write the core registers excluding ilink1, ilink2, the
    extension registers, reserved register, limm and PCL registers along with
    the lp_start and lp_end aux registers.

    @todo This is not terribly efficient, but that probably doesn't matter. If
          it ever did matter, we should use the init function to build a table
          of whether regs can be read or written, then this function is just a
          table lookup.

    @param[in] regno  Number of reg to check.
    @return           Non-zero if register cannot be written, zero otherwise. */
static int
arc_cannot_store_register (int regno)
{
  return (regno >= ARC_NUM_REGS || regno < 0 || arc_regmap[regno] == -1);
}	/* arc_cannot_store_register () */


/*! Get the PC from the register cache.

    @param[in] regcache  Register cache
    @return              The value of the PC. */
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
    @param[in]  pc        Value to write to the PC. */
static void
arc_set_pc (struct regcache *regcache, CORE_ADDR pc)
{
  unsigned long newpc = (unsigned long) pc;

  supply_register_by_name (regcache, "pc", &newpc);

}	/* arc_set_pc () */


/*! Determine if we have a breakpoint at an address.

    The breakpoint instruction is TRAP 1. We can use the network function
    ntohs to convert from its little-endian form (0x3e78) to the host
    representation, which may be little-endian or big-endian (remember network
    representation is defined to be little-endian).

    @param[in] where  The address to look at.
    @return           Non-zero (TRUE) if there is a breakpoint at the address,
                      zero (FALSE) otherwise. */
static int
arc_breakpoint_at (CORE_ADDR where)
{
  uint16_t insn;
  uint16_t breakpoint = ntohs (0x3e78);

  (*the_target->read_memory) (where, (unsigned char *) &insn, 2);
  return insn == breakpoint;

}	/* arc_breakpoint_at () */


/* -------------------------------------------------------------------------- */
/*			Register set access functions.			      */
/*									      */
/* Only for ARC ABI v3. Presented in the order they are used in		      */
/* arc_regsets.							      */
/* -------------------------------------------------------------------------- */

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
  /* ilink1 not currently supported. */
  /* ilink2 not currently supported. */
  collect_register_by_name (regcache, "blink", &(regbuf->scratch.blink));
  /* Extension core regs 32-59 not currently supported. */
  collect_register_by_name (regcache, "lp_count", &(regbuf->scratch.lp_count));
  /* reserved, limm and pcl not currently supported. */
  /* If you write the PC, that means the return address. */
  collect_register_by_name (regcache, "pc", &(regbuf->scratch.ret));
  /* Auxilliary registers */
  collect_register_by_name (regcache, "lp_start", &(regbuf->scratch.lp_start));
  collect_register_by_name (regcache, "lp_end", &(regbuf->scratch.lp_end));
  /* status32 not writable. */
  /* status32_l1 not currently supported. */
  /* status32_l2 not currently supported. */
  /* aux_irq_lv12 not currently supported. */
  /* aux_irq_lev not currently supported. */
  /* aux_irq_hint not currently supported. */
  /* eret not currently supported. */
  /* erbta not currently supported. */
  /* erstatus not currently supported. */
  /* ecr not currently supported. */
  /* efa not writable. */
  /* icause1 not currently supported. */
  /* icause2 not currently supported. */
  /* aux_ienable not currently supported. */
  /* aux_itrigger not currently supported. */
  /* bta not currently supported. */
  /* bta_l1 not currently supported. */
  /* bta_l2 not currently supported. */
  /* aux_irq_pulse_cancel not currently supported. */
  /* aux_irq_pending not currently supported. */

}	/* arc_fill_gregset () */


/*! Populate a regcache from a ptrace NT_PRSTATUS regset.

    We know the regset buffer supplied must therefore be a struct
    user_regs_struct.

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
  /* ilink1 not currently supported. */
  /* ilink2 not currently supported. */
  supply_register_by_name (regcache, "blink", &(regbuf->scratch.blink));
  /* Extension core regs 32-59 not currently supported. */
  supply_register_by_name (regcache, "lp_count", &(regbuf->scratch.lp_count));
  /* limm, reserved and pcl not currently supported. */
  /* If you read the PC, that means the stop_pc address. */
  supply_register_by_name (regcache, "pc", &(regbuf->stop_pc));
  /* Auxilliary registers */
  supply_register_by_name (regcache, "lp_start", &(regbuf->scratch.lp_start));
  supply_register_by_name (regcache, "lp_end", &(regbuf->scratch.lp_end));
  supply_register_by_name (regcache, "status32", &(regbuf->scratch.status32));
  /* status32_l1 not currently supported. */
  /* status32_l2 not currently supported. */
  /* aux_irq_lv12 not currently supported. */
  /* aux_irq_lev not currently supported. */
  /* aux_irq_hint not currently supported. */
  /* eret not currently supported. */
  /* erbta not currently supported. */
  /* erstatus not currently supported. */
  /* ecr not currently supported. */
  supply_register_by_name (regcache, "efa", &(regbuf->efa));
  /* icause1 not currently supported. */
  /* icause2 not currently supported. */
  /* aux_ienable not currently supported. */
  /* aux_itrigger not currently supported. */
  /* bta not currently supported. */
  /* bta_l1 not currently supported. */
  /* bta_l2 not currently supported. */
  /* aux_irq_pulse_cancel not currently supported. */
  /* aux_irq_pending not currently supported. */

}	/* arc_store_gregset () */


/* Fetch the thread-local storage pointer for libthread_db. Note that this
 * function is not called from GDB, but is called from libthread_db.
 *
 * This is the same function as in arc-linux-nat.c */
ps_err_e
ps_get_thread_area (const struct ps_prochandle *ph, lwpid_t lwpid, int idx,
                    void **base)
{
    if (ptrace (PTRACE_GET_THREAD_AREA, lwpid, NULL, base) != 0)
      return PS_ERR;

    /* IDX is the bias from the thread pointer to the beginning of the thread
     * descriptor.  It has to be subtracted due to implementation quirks in
     * libthread_db.  */
    *base = (void *) ((char *)*base - idx);

    return PS_OK;
} /* ps_get_thread_area */


/* -------------------------------------------------------------------------- */
/*		   Global variables defining the interface		      */
/*									      */
/* target_regsets to define how to get registers (with ABI v3) and	      */
/* the_low_target to define the debug interface.			      */
/* -------------------------------------------------------------------------- */

/*! Define how we set/get different regsets (ABI v3 only).

    For ARC ABI v3 we only have support for NT_PRSTATUS, which will return all
    the registers in struct user_regs_struct. For ARC ABI v2, we must still
    define target_regsets, but with no entries. */
static struct regset_info arc_regsets[] =
{
  { .get_request    = PTRACE_GETREGSET,
    .set_request    = PTRACE_SETREGSET,
    .nt_type        = NT_PRSTATUS,
    .size           = sizeof (struct user_regs_struct),
    .type           = GENERAL_REGS,
    .fill_function  = arc_fill_gregset,
    .store_function = arc_store_gregset },
  { .get_request    = 0,		/* End marker */
    .set_request    = 0,
    .nt_type        = 0,
    .size           = -1,
    .type           = -1,
    .fill_function  = NULL,
    .store_function = NULL }
};

static struct regsets_info arc_regsets_info =
{
  arc_regsets, /* regsets */
  0, /* num_regsets */
  NULL, /* disabled regsets */
};

static struct usrregs_info arc_usrregs_info =
{
  ARC_NUM_REGS,
  arc_regmap, /* arc_regmap is empty for now. */
};

static struct regs_info regs_info =
{
  NULL, /* regset_bitmap */
  &arc_usrregs_info,
  &arc_regsets_info
};

static const struct regs_info *
arc_regs_info (void)
{
  return &regs_info;
}

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
  .regs_info                        = arc_regs_info,
  .cannot_fetch_register            = arc_cannot_fetch_register,
  .cannot_store_register            = arc_cannot_store_register,
  .fetch_register                   = NULL,
  .get_pc                           = arc_get_pc,
  .set_pc                           = arc_set_pc,
  .breakpoint                       = NULL,
  .breakpoint_len                   = 2,
  .breakpoint_reinsert_addr         = NULL,
  .decr_pc_after_break              = 0,
  .breakpoint_at                    = arc_breakpoint_at,
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

void
initialize_low_arch (void)
{
  init_registers_arc ();

  initialize_regsets_info (&arc_regsets_info);
}
