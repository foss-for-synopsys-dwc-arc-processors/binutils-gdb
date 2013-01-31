/* Target dependent code for ARC processor family, for GDB, the GNU debugger.

   Copyright 2009 Free Software Foundation, Inc.
   Copyright 2009-2012 Synopsys Inc.

   Contributed by ARC International (www.arc.com), now part of Synopsys Inc.

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
/*     This header file defines an enumeration type for representing the      */
/*     architectural version of an ARC processor, and associated functions.   */
/*                                                                            */
/******************************************************************************/

#ifndef ARC_ARCHITECTURE_H
#define ARC_ARCHITECTURE_H

/* gdb header files */
#include "gdbarch.h"
#include "bfd/bfd-in2.h"

/* ARC header files */
#include "arc-support.h"


typedef enum arc_processor_version
{
  NO_ARCHITECTURE,
  ARC700,
  ARC600,
  A5,
  A4,
  UNSUPPORTED_ARCHITECTURE
} ARC_ProcessorVersion;


ARC_ProcessorVersion arc_get_architecture (ARC_RegisterNumber identity_regnum);

void arc_update_architecture (ARC_RegisterNumber identity_regnum);

void arc_check_architecture (struct gdbarch *gdbarch, bfd * objfile_bfd);

ARC_ProcessorVersion arc_version (const char *arch);

const char *arc_version_image (ARC_ProcessorVersion version);


extern ARC_ProcessorVersion ARC_processor;

#endif /* ARC_ARCHITECTURE_H */
/******************************************************************************/
