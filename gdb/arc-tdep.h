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

   ### Simulator register numbers

   The built-in CGEN simulator uses a register number/register type pair to
   identify registers. For the core register type, the numbering is the same
   as for GDB.

   For the auxilliary registers, the numbering follows the ARC architecture
   numbering, so we must provide a mapping (the simulator has an API call to
   which we hook in).

   @todo This mapping should be provide via the XML file.

   ## ABI related processor details

   - r0  .. r7 are the registers used to pass arguments in function calls
   - r13 .. r26 are the callee-saved registers
   - when a return value is stored in registers it is in either R0 or in the
     pair (R0,R1).

   
   ### Other comments

   We'll eventually use Franck Jullien's OpenRISC GDB trick, of only accessing
   the core registers using G/g packets, requiring aux registers to be
   accessed using P/p packets. That way a G packet need not be too large.


   However, in the short term, we are only supporting a modest number of
   fixed aux regs, so we just use the G packet.                               */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Opella ARC600 register numbering.                                          */
/* -------------------------------------------------------------------------- */

#define OA6_R0                         0
#define OA6_R25                       25
#define OA6_GP                        26
#define OA6_FP                        27
#define OA6_SP                        28
#define OA6_ILINK1                    29
#define OA6_ILINK2                    30
#define OA6_BLINK                     31
#define OA6_LP_COUNT                  32
#define OA6_PCL                       33
#define OA6_AUX_STATUS                34
#define OA6_AUX_SEMAPHORE             35
#define OA6_AUX_LP_START              36
#define OA6_AUX_LP_END                37
#define OA6_AUX_IDENTITY              38
#define OA6_AUX_DEBUG                 39
#define OA6_AUX_PC                    40
#define OA6_AUX_STATUS32              41
#define OA6_AUX_STATUS32_L1           42
#define OA6_AUX_STATUS32_L2           43
#define OA6_AUX_COUNT0                44
#define OA6_AUX_CONTROL0              45
#define OA6_AUX_LIMIT0                46
#define OA6_AUX_INT_VECTOR_BASE       47
#define OA6_AUX_AUX_MACMODE           48
#define OA6_AUX_AUX_IRQ_LV12          49
#define OA6_AUX_COUNT1                50
#define OA6_AUX_CONTROL1              51
#define OA6_AUX_LIMIT1                52
#define OA6_AUX_AUX_IRQ_LEV           53
#define OA6_AUX_AUX_IRQ_HINT          54
#define OA6_AUX_IC_IVIC               55
#define OA6_AUX_IC_CTRL               56
#define OA6_AUX_DC_IVDC               57
#define OA6_AUX_DC_CTRL               58
#define OA6_AUX_AMV0                  59
#define OA6_AUX_AMM0                  60
#define OA6_AUX_AC0                   61
#define OA6_BCR_DCCM_BASE_BUILD       63
#define OA6_BCR_CRC_BASE_BUILD        64
#define OA6_BCR_DVBF_BUILD            65
#define OA6_BCR_TEL_INSTR_BUILD       66
#define OA6_BCR_MEMSUBSYS             68
#define OA6_BCR_VECBASE_AC_BUILD      69
#define OA6_BCR_P_BASE_ADDRESS        70
#define OA6_BCR_RF_BUILD              75
#define OA6_BCR_MMU_BUILD             76
#define OA6_BCR_ARCANGEL_BUILD        77
#define OA6_BCR_DCACHE_BUILD          79
#define OA6_BCR_MADI_BUILD            80
#define OA6_BCR_DCCM_BUILD            81
#define OA6_BCR_TIMER_BUILD           82
#define OA6_BCR_AP_BUILD              83
#define OA6_BCR_ICACHE_BUILD          84
#define OA6_BCR_ICCM_BUILD            85
#define OA6_BCR_DSPRAM_BUILD          86
#define OA6_BCR_MAC_BUILD             87
#define OA6_BCR_MULTIPLY_BUILD        88
#define OA6_BCR_SWAP_BUILD            99
#define OA6_BCR_NORM_BUILD            90
#define OA6_BCR_MINMAX_BUILD          91
#define OA6_BCR_BARREL_BUILD          92

#define OA6_NUM_CORE_REGS    (OA6_PCL + 1)
#define OA6_NUM_REGS         (OA6_BCR_BARREL_BUILD + 1)
#define OA6_NUM_PSEUDO_REGS   0

/* -------------------------------------------------------------------------- */
/* Opella ARC700 register numbering.                                          */
/* -------------------------------------------------------------------------- */

#define OA7_R0                         0
#define OA7_R25                       25
#define OA7_GP                        26
#define OA7_FP                        27
#define OA7_SP                        28
#define OA7_ILINK1                    29
#define OA7_ILINK2                    30
#define OA7_BLINK                     31
#define OA7_LP_COUNT                  32
#define OA7_PCL                       33
#define OA7_AUX_STATUS                34
#define OA7_AUX_LP_START              35
#define OA7_AUX_LP_END                36
#define OA7_AUX_IDENTITY              37
#define OA7_AUX_DEBUG                 38
#define OA7_AUX_PC                    39
#define OA7_AUX_STATUS32              40
#define OA7_AUX_STATUS32_L1           41
#define OA7_AUX_STATUS32_L2           42
#define OA7_AUX_COUNT0                43
#define OA7_AUX_CONTROL0              44
#define OA7_AUX_LIMIT0                45
#define OA7_AUX_INT_VECTOR_BASE       46
#define OA7_AUX_AUX_MACMODE           47
#define OA7_AUX_AUX_IRQ_LV12          48
#define OA7_AUX_COUNT1                49
#define OA7_AUX_CONTROL1              50
#define OA7_AUX_LIMIT1                51
#define OA7_AUX_AUX_IRQ_LEV           52
#define OA7_AUX_AUX_IRQ_HINT          53
#define OA7_AUX_ERET                  54
#define OA7_AUX_ERBTA                 55
#define OA7_AUX_ERSTATUS              56
#define OA7_AUX_ECR                   57
#define OA7_AUX_EFA                   58
#define OA7_AUX_ICAUSE1               59
#define OA7_AUX_ICAUSE2               60
#define OA7_AUX_AUX_IENABLE           61
#define OA7_AUX_AUX_ITRIGGER          62
#define OA7_AUX_XPU                   63
#define OA7_AUX_BTA                   64
#define OA7_AUX_BTA_L1                65
#define OA7_AUX_BTA_L2                66
#define OA7_AUX_AUX_IRQ_PULSE_CANCEL  67
#define OA7_AUX_AUX_IRQ_PENDING       68
#define OA7_AUX_IC_IVIC               69
#define OA7_AUX_IC_CTRL               70
#define OA7_AUX_DC_IVDC               71
#define OA7_AUX_DC_CTRL               72
#define OA7_AUX_AMV0                  73
#define OA7_AUX_AMM0                  74
#define OA7_AUX_AC0                   75
#define OA7_BCR_DCCM_BASE_BUILD       77
#define OA7_BCR_CRC_BASE_BUILD        78
#define OA7_BCR_BTA_LINK_BUILD        79
#define OA7_BCR_DVBF_BUILD            80
#define OA7_BCR_TEL_INSTR_BUILD       81
#define OA7_BCR_MEMSUBSYS             83
#define OA7_BCR_VECBASE_AC_BUILD      84
#define OA7_BCR_P_BASE_ADDRESS        85
#define OA7_BCR_MMU_BUILD             91
#define OA7_BCR_ARCANGEL_BUILD        92
#define OA7_BCR_DCACHE_BUILD          94
#define OA7_BCR_MADI_BUILD            95
#define OA7_BCR_DCCM_BUILD            96
#define OA7_BCR_TIMER_BUILD           97
#define OA7_BCR_AP_BUILD              98
#define OA7_BCR_ICACHE_BUILD          99
#define OA7_BCR_ICCM_BUILD           100
#define OA7_BCR_DSPRAM_BUILD         101
#define OA7_BCR_MAC_BUILD            102
#define OA7_BCR_MULTIPLY_BUILD       103
#define OA7_BCR_SWAP_BUILD           104
#define OA7_BCR_NORM_BUILD           105
#define OA7_BCR_MINMAX_BUILD         106
#define OA7_BCR_BARREL_BUILD         107

#define OA7_NUM_CORE_REGS    (OA7_PCL + 1)
#define OA7_NUM_REGS         (OA7_BCR_BARREL_BUILD + 1)
#define OA7_NUM_PSEUDO_REGS   0

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
/*! Number of pseudo registers. */
#define ARC_NUM_PSEUDO_REGS 0

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


/* Enumeration of possible Opella targets */
enum arc_opella_target {
  ARC600,
  ARC700,
  NONE,
  INVALID
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
  
  /* Opella JTAG target. */
  enum arc_opella_target opella_target;

  /* Register mapping stuff (for Opella) */
  int  num_core_regs;
  int  num_regs;
  int  num_pseudo_regs;
  int  first_arg_regnum;
  int  last_arg_regnum;
  int  first_callee_saved_regnum;
  int  last_callee_saved_regnum;
  int  pc_regnum;
  int  fp_regnum;
  int  sp_regnum;
  int  ps_regnum;
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

#endif /* ARC_TDEP_H */
/******************************************************************************/
