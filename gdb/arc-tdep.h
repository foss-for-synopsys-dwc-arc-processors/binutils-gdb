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

   Old GDB used to have a completely arbitrary mapping, and that mapping
   differed between ELF32 and LINUX tool chains. In this version we use the
   direct address number for the core registers (r0 through r63).

   `#define` constants are defined for named registers, but not the numbered
   core registers r0 through r25 and the optional extension core registers
   r32 through r59.

   ABI usage of core general registers, all having rw access:
   - r0  .. r3:   args
   - r4  .. r7:   args (32-bit instructions only)
   - r8  .. r9:   temp regs (32 bit instructions only)
   - r10 .. r11:  temp regs (32 bit & reduced instructsion set only)
   - r12 .. r15:  temp regs
   - r16 .. r25:  saved reg

   ### Auxilliary registers.

   These are the sequential register numbers by which these are known in
   GDB.

   @todo For now we hardcode only the key registers. Eventually these should
         be sorted out through XML.

   ## ABI related processor details

   - r0  .. r7 are the registers used to pass arguments in function calls
   - r13 .. r26 are the callee-saved registers
   - when a return value is stored in registers it is in either R0 or in the
     pair (R0,R1).

   ### Other comments

   We'll also use Franck Jullien's OpenRISC GDB trick, of only accessing the
   core registers using G/g packets, requiring aux registers to be accessed
   using P/p packets. That way a G packet need not be too large. */
/* -------------------------------------------------------------------------- */

/* Core register definitions. */
#define ARC_GP_REGNUM               26	/*!< Access __rw__ */
#define ARC_FP_REGNUM               27	/*!< Access __rw__ */
#define ARC_SP_REGNUM               28	/*!< Access __rw__ */
#define ARC_ILINK1_REGNUM           29	/*!< Access __RW__ */
#define ARC_ILINK2_REGNUM           30	/*!< Access __RW__ */
#define ARC_BLINK_REGNUM            31	/*!< Access __rw__ */

/* Extension core registers r32-r59 */
#define ARC_FIRST_EXT_CORE_REGNUM   32	/*!< Access __rw__ */
#define ARC_LAST_EXT_CORE_REGNUM    59	/*!< Access __rw__ */

#define ARC_LP_COUNT_REGNUM         60	/*!< Access __rw__ */
#define ARC_RESERVED_REGNUM         61	/*!< No access */
#define ARC_LIMM_REGNUM             62	/*!< No access */
#define ARC_PCL_REGNUM              63	/*!< Access __r__ */

/*! Stop and resume PC register.

    There is no one register which corresponds to the PC of the address where
    we stopped. Depending on the type of exception, we may have the address of
    the current instruction (TLB or protection exceptions) or the next
    instruction (traps and syscalls) in our hand.

    However this is not a pseudo register, since it has a physical
    representation (actually several) and must be fetched from and restored to
    the target.

    We define one register, which reads the address of the instruction
    on which we stopped and writes the address of the instruction which we
    will next execute. It is up to the server on the target to sort out what
    it does with this value.

    @note This register is distinguished from the auxilliary register PC,
          which is named ARC_AUX_PC_REGNUM.

    @note Previously this was two registers STOP_PC for where we stopped and
          RET for where we want to restart. They are unified here.

    @todo This is still subject to some discussion. This is not yet regarded as
          stable. */
#define ARC_PC_REGNUM               64 /*!< Access __rw__ */

/* Auxilliary registers - subset for GDB. */
#define ARC_AUX_LP_START_REGNUM              65	/*!< Access __rw_ */
#define ARC_AUX_LP_END_REGNUM                66	/*!< Access __rw_ */
#define ARC_AUX_STATUS32_REGNUM              67	/*!< Access __rG__ */
#define ARC_AUX_STATUS32_L1_REGNUM           68	/*!< Access __RW__ */
#define ARC_AUX_STATUS32_L2_REGNUM           69	/*!< Access __RW__ */
#define ARC_AUX_AUX_IRQ_LV12_REGNUM          70	/*!< Access __RW_ */
#define ARC_AUX_AUX_IRQ_LEV_REGNUM           71	/*!< Access __RW_ */
#define ARC_AUX_AUX_IRQ_HINT_REGNUM          72	/*!< Access __RW_ */
#define ARC_AUX_ERET_REGNUM                  73	/*!< Access __RW__ */
#define ARC_AUX_ERBTA_REGNUM                 74	/*!< Access __RW__ */
#define ARC_AUX_ERSTATUS_REGNUM              75	/*!< Access __RW__ */
#define ARC_AUX_ECR_REGNUM                   76	/*!< Access __RW__ */
#define ARC_AUX_EFA_REGNUM                   77	/*!< Access __RW_ */
#define ARC_AUX_ICAUSE1_REGNUM               78	/*!< Access __RW__ */
#define ARC_AUX_ICAUSE2_REGNUM               79	/*!< Access __RW__ */
#define ARC_AUX_AUX_IENABLE_REGNUM           80	/*!< Access __RW_ */
#define ARC_AUX_AUX_ITRIGGER_REGNUM          81	/*!< Access __RW_ */
#define ARC_AUX_BTA_REGNUM                   82	/*!< Access __RW__ */
#define ARC_AUX_BTA_L1_REGNUM                83	/*!< Access __RW_ */
#define ARC_AUX_BTA_L2_REGNUM                84	/*!< Access __RW_ */
#define ARC_AUX_AUX_IRQ_PULSE_CANCEL_REGNUM  85 /*!< Access __RW_ */
#define ARC_AUX_AUX_IRQ_PENDING_REGNUM       86	/*!< Access __RW_ */

/* Some useful counts. */

/*! Maximum number of core registers (i.e. with extension core regs). */
#define ARC_MAX_CORE_REGS  (ARC_PCL_REGNUM + 1)  /*!< Total core regs */
/*! Number of extension core registers. */
#define ARC_EXT_CORE_REGS			\
  (ARC_LAST_EXT_CORE_REGNUM - ARC_FIRST_EXT_CORE_REGNUM + 1)
/*! Number of standard core registers (i.e. without extension core regs). */
#define ARC_STD_CORE_REGS			\
  (ARC_MAX_CORE_REGS - ARC_NUM_EXT_CORE_REGS)

/*! Number of "raw" registers (i.e. core + aux). */
#define ARC_NUM_RAW_REGS    (ARC_AUX_AUX_IRQ_PENDING_REGNUM + 1)
/*! Total "raw" + pseudo registers. */
#define ARC_TOTAL_REGS      (ARC_AUX_AUX_IRQ_PENDING_REGNUM + 1)
/*! Number of pseudo registers. */
#define ARC_NUM_PSEUDO_REGS (ARC_TOTAL_REGS - ARC_NUM_RAW_REGS)

/* -------------------------------------------------------------------------- */
/* ABI constants and macros                                                   */
/* -------------------------------------------------------------------------- */

#define ARC_FIRST_CALLEE_SAVED_REGNUM  13
#define ARC_LAST_CALLEE_SAVED_REGNUM   26

#define ARC_FIRST_ARG_REGNUM            0
#define ARC_LAST_ARG_REGNUM             7

#define ARC_RET_REGNUM                  0
#define ARC_RET_LOW_REGNUM              0
#define ARC_RET_HIGH_REGNUM             1

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

/*! Enum of the various ARC architectures.

    @note A4 and A5 now removed. */
enum arc_processor_version
{
  NO_ARCHITECTURE,
  ARC700,
  ARC600,
  UNSUPPORTED_ARCHITECTURE
};

/*! Enum for type of access allowed to registers */
enum arc_reg_access
{
  READ_ONLY,
  READ_WRITE,
  WRITE_ONLY
};

/*! Struct for definition of ARC core registers. */
struct arc_core_reg_def
{
    int                 gdb_regno;
    uint32_t            mask;
    enum arc_reg_access access;
    int                 exists;
};

/*! struct aux_reg_def is opaque here. */
struct arc_aux_reg_def;

/* this type is essentially private: no access to any of its fields should
 * be performed outside of this module
 */
struct arc_reg_info
{
  enum arc_processor_version processor;
  struct arc_aux_reg_def *aux_registers;
  unsigned int aux_register_count;
  int first_aux_gdb_regno;
  unsigned int max_name_length;
  int PC_number;
  struct arc_core_reg_def core_registers[ARC_MAX_CORE_REGS];
  unsigned int core_register_count;
};

/*! Structure describing an ARC variant. */
struct arc_variant_info
{
  enum arc_processor_version processor_version;
  struct arc_reg_info registers;
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

    /* In our linux target, gdbarch_pc_regnum points to stop_pc, which is a
       register that is made up by the kernel and does not actually exist.
       stop_pc is NOT saved in the sigcontext; what is saved is the ret
       "register".  Since ret is a linux-only register, its regnum is visible
       only in arc-linux-tdep.c; hence initialize pc_regnum_in_sigcontext in
       arc-linux-tdep.c.  */
    int pc_regnum_in_sigcontext;

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
