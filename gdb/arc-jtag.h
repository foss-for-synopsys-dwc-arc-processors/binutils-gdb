/* Target dependent code for ARC processor family, for GDB, the GNU debugger.

   Copyright 2005 Free Software Foundation, Inc.
   Copyright 2009-2012 Synopsys Inc.

   Contributed by Codito Technologies Pvt. Ltd. (www.codito.com) on behalf of
   Synopsys Inc.

   Authors:
      Soam Vasani     <soam.vasani@codito.com>
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
/*     This header file defines some operations provided by the ARC JTAG      */
/*     module.                                                                */
/*                                                                            */
/******************************************************************************/

#ifndef ARC_JTAG_H
#define ARC_JTAG_H

/* ARC header files */
#include "arc-support.h"


typedef enum
{
    CLEAR_USER_BIT,
    RESTORE_USER_BIT
} ARC_Status32Action;


void _initialize_arc_debug(void);


/* operation for clearing/restoring the User bit in the STATUS32 register */
void arc_change_status32(ARC_Status32Action action);


/* operations for reading/writing core/auxiliary registers; these must be used
 * when access to the registers *specifically* via the JTAG i/f is required
 */

Boolean arc_read_jtag_core_register  (ARC_RegisterNumber    hw_regno,
                                      ARC_RegisterContents* contents,
                                      Boolean               warn_on_failure);

Boolean arc_write_jtag_core_register (ARC_RegisterNumber    hw_regno,
                                      ARC_RegisterContents  contents,
                                      Boolean               warn_on_failure);

Boolean arc_read_jtag_aux_register   (ARC_RegisterNumber    hw_regno,
                                      ARC_RegisterContents* contents,
                                      Boolean               warn_on_failure);

Boolean arc_write_jtag_aux_register  (ARC_RegisterNumber    hw_regno,
                                      ARC_RegisterContents  contents,
                                      Boolean               warn_on_failure);

#endif /* ARC_JTAG_H */
/******************************************************************************/
