/* Target dependent code for ARC processor family, for GDB, the GNU debugger.

   Copyright 2009 Free Software Foundation, Inc.
   Copyright 2009-2012 Synopsys Inc.

   Contributed by  ARC International (www.arc.com), now part of Synopsys Inc.

   Authors:
      Phil Barnard    <phil.barnard@arc.com>
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
/*     This header file defines operations for controlling an ARC target      */
/*     board.                                                                 */
/*                                                                            */
/*     These operations are:                                                  */
/*        1) configuring ("blasting") an FPGA target with the contents of an  */
/*           XBF file;                                                        */
/*        2) checking whether a target has been so configured; and            */
/*        3) setting the clock frequency of the target.                       */
/*                                                                            */
/* Notes:                                                                     */
/*     The arc_blast_board function implements an ARC-specific command; hence */
/*     its 'args' parameter contains data entered by the debugger user, which */
/*     must be checked for validity.                                          */
/*                                                                            */
/******************************************************************************/

#ifndef ARC_BOARD_H
#define ARC_BOARD_H

/* ARC header files */
#include "arc-support.h"


typedef enum
{
  INACCESSIBLE,
  CONFIGURED,
  UNCONFIGURED
} FPGA_Status;


void arc_blast_board (char *args, int from_tty);

void arc_reset_board (void);

FPGA_Status arc_is_FPGA_configured (void);


#endif /* ARC_BOARD_H */
/******************************************************************************/
