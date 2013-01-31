/* Target dependent code for ARC processor family, for GDB, the GNU debugger.

   Copyright 2009 Free Software Foundation, Inc.

   Contributed by ARC International (www.arc.com)

   Authors:
      Richard Stuckey <richard.stuckey@arc.com>

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

/******************************************************************************/
/*                                                                            */
/* Outline:                                                                   */
/*     This header file defines the initialization function for this module.  */
/*                                                                            */
/*     All the facilities of this module are accessed via information stored  */
/*     in the gdbarch structure by this function.                             */
/*                                                                            */
/******************************************************************************/

#ifndef ARC_JTAG_TDEP_H
#define ARC_JTAG_TDEP_H

/* gdb header files */
#include "gdbarch.h"

/* ARC header files */
#include "arc-aux-registers.h"
#include "arc-architecture.h"


// complete structure definition here
struct arc_variant_info
{
    ARC_ProcessorVersion processor_version;
    ARC_RegisterInfo     registers;
};


struct gdbarch *arc_jtag_initialize (struct gdbarch*      gdbarch,
                                     struct gdbarch_list* arches);

void _initialize_arc_jtag_tdep (void);

void arc_check_pc_defined(struct gdbarch* gdbarch);

#endif /* ARC_JTAG_TDEP_H */
/******************************************************************************/
