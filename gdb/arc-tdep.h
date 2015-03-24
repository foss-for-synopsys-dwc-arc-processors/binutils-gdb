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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   --------------------------------------------------------------------------

   The comments within this file are also licensed under under the terms of
   the GNU Free Documentation License as published by the Free Software
   Foundation; either version 1.3 of the License, or (at your option) any
   later version. See the file fdi.texi in the gdb/doc directory for copying
   conditions.

   You should have received a copy of the GNU Free Documentation License along
   with this program. If not, see <http://www.gnu.org/licenses/>.  */

/* -------------------------------------------------------------------------- */

#ifndef ARC_TDEP_H
#define ARC_TDEP_H

/* -------------------------------------------------------------------------- */
/*!@file 
   # ARC General Target Dependant Header for GDB
 
   Definitions specific to the architecture, but not any particular OS.

   ## Register numbering

   Details of GDB core register and auxilliary register numbering should
   really be in the XML file.

   ### GDB register numbers

   Not all are visible in user space, which is all the Linux version of the
   tool chain can see. For each we show the access as:

   - __r__: readable by user, kernel or JTAG debugger
   - __R__: readable by kernel or JTAG debugger
   - __w__: writable by user, kernel or JTAG debugger
   - __W__: writable by kernel or JTAG debugger
   - __G__: writable by JTAG debugger

   ### Core register set.

   We use the direct address number for the core registers (r0 through r63).
   That makes for simpler code of GDB, since GDB has some operations on
   registers depending on their purpose (SP, PC, argument registers, callee
   saved registers, return value registers...), and those operations are much
   easier to implement when register numbers are fixed even if some registers
   in between do not exist, like with extension core registers.

   `enum` constants are defined for named registers and some important ones
   (first arg, last arg, etc), but not for undistinguished, or extension core
   registers.

   ABI usage of core general registers, all having rw access:
     Register     Use                     16bit instr access    16 reg file
   - r0  .. r3:   arguments               +                     +
   - r4  .. r7:   arguments
   - r8  .. r9:   temp regs
   - r10 .. r11:  temp regs                                     +
   - r12:         temp reg                +                     +
   - r13 .. r15:  callee-saved regs       +                     +
   - r16 .. r25:  callee-saved regs
   - when a return value is stored in registers it is in either R0 or in the
     pair (R0,R1).

   NB: PRM for ARCompact and ARC v2 give different designations for r12-r15
   registers, which causes some discrepancy between documents. However all
   Synopsys tools (GDB, GCC, MetaWare, etc) follow designation given here.

   ### Auxiliary registers.

   These are the sequential register numbers by which these are known in GDB.
   Four registers have fixed numbers: PC, STATUS32, LP_START and LP_END. For PC
   and STATUS32 that is because those are special registers, assigning them
   permanent regnum makes GDB code simpler. LP_ registers got stuck in between
   in the old-style compatible register set, and to allow same code path to be
   used for both new register sets and old one, those registers have been
   allowed to stay in between. Besides they are pretty important so in most
   cases we would like them to be available anyway, although technically they
   are optional.

   ### Simulator register numbers

   The built-in CGEN simulator uses a register number/register type pair to
   identify registers. For the core register type, the numbering is the same
   as for GDB.

   For the auxilliary registers, the numbering follows the ARC architecture
   numbering, so we must provide a mapping (the simulator has an API call to
   which we hook in).
*/
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/* Simulator aux reg numbers                                                  */
/* -------------------------------------------------------------------------- */

#define ARC_AUX_LP_START_SIM_REGNUM              0x002
#define ARC_AUX_LP_END_SIM_REGNUM                0x003
#define ARC_AUX_STATUS32_SIM_REGNUM              0x00a
#define ARC_AUX_STATUS32_L1_SIM_REGNUM           0x00b
#define ARC_AUX_STATUS32_L2_SIM_REGNUM           0x00c
#define ARC_AUX_AUX_IRQ_LV12_SIM_REGNUM          0x043
#define ARC_AUX_AUX_IRQ_LEV_SIM_REGNUM           0x200
#define ARC_AUX_AUX_IRQ_HINT_SIM_REGNUM          0x201
#define ARC_AUX_ERET_SIM_REGNUM                  0x400
#define ARC_AUX_ERBTA_SIM_REGNUM                 0x401
#define ARC_AUX_ERSTATUS_SIM_REGNUM              0x402
#define ARC_AUX_ECR_SIM_REGNUM                   0x403
#define ARC_AUX_EFA_SIM_REGNUM                   0x404
#define ARC_AUX_ICAUSE1_SIM_REGNUM               0x40a
#define ARC_AUX_ICAUSE2_SIM_REGNUM               0x40b
#define ARC_AUX_AUX_IENABLE_SIM_REGNUM           0x40c
#define ARC_AUX_AUX_ITRIGGER_SIM_REGNUM          0x40d
#define ARC_AUX_BTA_SIM_REGNUM                   0x412
#define ARC_AUX_BTA_L1_SIM_REGNUM                0x413
#define ARC_AUX_BTA_L2_SIM_REGNUM                0x414
#define ARC_AUX_AUX_IRQ_PULSE_CANCEL_SIM_REGNUM  0x415
#define ARC_AUX_AUX_IRQ_PENDING_SIM_REGNUM       0x416


/* -------------------------------------------------------------------------- */
/* GDB register numbering                                                     */
/* -------------------------------------------------------------------------- */

/* Certain limitations are imposed on GDB register numbers to simplify logic
 * in the GDB. Those limitations applie to both ARCompact and ARC v2.
 *   1. ARC can have up to 64 core registers, and each one of them has same GDB
 *   regnum as an architectural number. So R0 always has regnum 0, LP_COUNT
 *   always has regnum 60.
 *   2. PC always has regnum 64. That register is mandatory.
 *   3. LP_START and LP_END has regnums 65 and 66 respectively, those registers
 *   are optional, and those register numbers shall not be occupied by other
 *   registers when LP_START and LP_END are not present.
 *   4. STATUS32 always has regnum 67.
 */
enum arc_regnum
{
  /* Core registers. */
  ARC_R0_REGNUM       = 0,
  ARC_R1_REGNUM       = 1,
  ARC_R7_REGNUM       = 7,
  ARC_R13_REGNUM      = 13,
  ARC_R25_REGNUM      = 25,
  ARC_GP_REGNUM,
  ARC_FP_REGNUM,
  ARC_SP_REGNUM,
  ARC_ILINK_REGNUM,
  ARC_R30_REGNUM,
  ARC_BLINK_REGNUM,
  ARC_LP_COUNT_REGNUM = 60,
  ARC_RESERVED_REGNUM,
  ARC_LIMM_REGNUM,
  ARC_PCL_REGNUM,
  /* AUX registers */
  ARC_PC_REGNUM,
  ARC_LP_START_REGNUM,
  ARC_LP_END_REGNUM,
  ARC_STATUS32_REGNUM,

  /* Additional ABI constants */
  ARC_FIRST_ARG_REGNUM = ARC_R0_REGNUM,
  ARC_LAST_ARG_REGNUM = ARC_R7_REGNUM,
  ARC_FIRST_CALLEE_SAVED_REGNUM = ARC_R13_REGNUM,
  ARC_LAST_CALLEE_SAVED_REGNUM  = ARC_R25_REGNUM,
};

/* Assign regnums to compatible register feature. */
enum arc_compat_regnum
{
  ARC_COMPATIBLE_STATUS32_L1_REGNUM = ARC_STATUS32_REGNUM + 1,
  ARC_COMPATIBLE_STATUS32_L2_REGNUM,
  ARC_COMPATIBLE_AUX_IRQ_LV12_REGNUM,
  ARC_COMPATIBLE_AUX_IRQ_LEV_REGNUM,
  ARC_COMPATIBLE_AUX_IRQ_HINT_REGNUM,
  ARC_COMPATIBLE_ERET_REGNUM,
  ARC_COMPATIBLE_ERBTA_REGNUM,
  ARC_COMPATIBLE_ERSTATUS_REGNUM,
  ARC_COMPATIBLE_ECR_REGNUM,
  ARC_COMPATIBLE_EFA_REGNUM,
  ARC_COMPATIBLE_ICAUSE1_REGNUM,
  ARC_COMPATIBLE_ICAUSE2_REGNUM,
  ARC_COMPATIBLE_AUX_IENABLE_REGNUM,
  ARC_COMPATIBLE_AUX_ITRIGGER_REGNUM,
  ARC_COMPATIBLE_BTA_REGNUM,
  ARC_COMPATIBLE_BTA_L1_REGNUM,
  ARC_COMPATIBLE_BTA_L2_REGNUM,
  ARC_COMPATIBLE_AUX_IRQ_PULSE_CANCEL_REGNUM,
  ARC_COMPATIBLE_AUX_IRQ_PENDING_REGNUM,
};

/* -------------------------------------------------------------------------- */
/* ABI constants and macros                                                   */
/* -------------------------------------------------------------------------- */

/*! Offset (in words) of PC in uClibc jmp_buf structure for longjmp () */
#define ARC_UCLIBC_JB_PC  15
/*! Offset (in words) of PC in Newlib jmp_buf structure for longjmp () */
#define ARC_NEWLIB_JB_PC  19

/* -------------------------------------------------------------------------- */
/* Useful constants                                                           */
/* -------------------------------------------------------------------------- */

#define BYTES_IN_REGISTER  4
#define BYTES_IN_WORD      4
#define BYTES_IN_ADDRESS  (BYTES_IN_REGISTER)

#define REGISTER_NOT_PRESENT   (-1)   /* special value for sc_reg_offset[reg] */


/* -------------------------------------------------------------------------- */
/* Debug support                                                              */
/* -------------------------------------------------------------------------- */

/*! Debug a function entry point.

    @todo. The use of ##__VA_ARGS__ is a GCC extension. */
#define ARC_ENTRY_DEBUG(fmt, ...)					\
  if (arc_debug)							\
    {									\
      fprintf_unfiltered (gdb_stdlog, "--- entered %s (" fmt ")\n",	\
                          __FUNCTION__, ##__VA_ARGS__);			\
    }


/* -------------------------------------------------------------------------- */
/* Globally visible datatypes                                                 */
/* -------------------------------------------------------------------------- */

/* Register information. */
struct arc_reginfo
{
  char * name;
  /* Readable by baremetal debugger. */
  uint8_t readable;
  /* Writable by baremetal debugger. */
  uint8_t writable;
  /* Readable by userspace debugger. */
  uint8_t user_readable;
  /* Writable by userspace debugger. */
  uint8_t user_writable;
};

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
  
  struct arc_reginfo *reginfo;
  /* reginfo_sz is useful in cannot_(store|fetch), where gdbarch_num_regs might
   * be greater than amount of registers in reginfo. */
  size_t reginfo_sz;
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
extern void arc_gdbarch_osabi_init (struct gdbarch *gdbarch);


/* Inline functions */
static inline int
arc_mach_is_arc600(struct gdbarch *gdbarch)
{
    return gdbarch_bfd_arch_info (gdbarch)->mach == bfd_mach_arc_arc600 ||
	gdbarch_bfd_arch_info (gdbarch)->mach == bfd_mach_arc_arc601;
}

static inline int
arc_mach_is_arc700(struct gdbarch *gdbarch)
{
    return gdbarch_bfd_arch_info (gdbarch)->mach == bfd_mach_arc_arc700;
}

static inline int
arc_mach_is_arcv2(struct gdbarch *gdbarch)
{
    return gdbarch_bfd_arch_info (gdbarch)->mach == bfd_mach_arc_arcv2;
}

#endif /* ARC_TDEP_H */

/* vim: set sts=2 shiftwidth=2 ts=8: */
