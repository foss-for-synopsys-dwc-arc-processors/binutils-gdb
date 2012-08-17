/******************************************************************************/
/*                                                                            */
/* Outline:                                                                   */
/*     This header file defines register numbers for the arc-elf32            */
/*     configuration of the ARC gdb.                                          */
/*                                                                            */
/******************************************************************************/

#ifndef ARC_TM_EMBED_H
#define ARC_TM_EMBED_H

#include "gdbarch.h"
#include "arc-jtag-tdep.h"
#include "arc-aux-registers.h"


#define CONFIG_OSABI        GDB_OSABI_UNKNOWN

#define CONFIG_INIT_TDEP    (void) arc_jtag_initialize (gdbarch, arches);


/* These are hardware register numbers (i.e. NOT gdb register numbers). */
enum arc700_jtag_regnums
{
    /* Regnums 0 .. 26 are R0 .. R26 */

    ARC_FP_REGNUM = 27,
    ARC_SP_REGNUM,
    ARC_ILINK1_REGNUM,
    ARC_ILINK2_REGNUM,
    ARC_BLINK_REGNUM,

    /* Extension core regs are R32 .. R59 inclusive.  */

    ARC_LP_COUNT_REGNUM = 60,

    /* 61 is reserved, 62 is not a real register.  */
    ARC_PCL_REGNUM = 63,

   /* end marker: this is not a register, but its integer value gives the number
    * of registers
    */
    ARC_REG_END_MARKER
};


#define ARC_NR_PSEUDO_REGS      0
#define ARC_NR_REGS             (int) (arc_core_register_count(gdbarch) + \
                                       arc_aux_register_count (gdbarch))

#endif /* ARC_TM_EMBED_H */
/******************************************************************************/
