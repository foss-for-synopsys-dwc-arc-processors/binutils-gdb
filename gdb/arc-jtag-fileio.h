/* Target dependent code for ARC processor family, for GDB, the GNU debugger.

   Copyright 2009 Free Software Foundation, Inc.
   Copyright 2009-2012 Synopsys Inc.

   Contributed by ARC International (www.arc.com), now part of Synopsys Inc.

   Author: 
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
/*     This header file defines facilities for intercepting I/O (and other)   */
/*     operations attempted on a JTAG target and performing them on the host, */
/*     using a RPC (Remote Procedure Call) mechanism.                         */
/*                                                                            */
/******************************************************************************/

#ifndef ARC_JTAG_FILEIO
#define ARC_JTAG_FILEIO

/* ARC header files */
#include "arc-support.h"


typedef enum
{
    INTERCEPTION_RESUME,
    INTERCEPTION_HALT,
    INTERCEPTION_EXIT
} Action;


typedef enum
{
    INTERCEPTION_RESET,
    INTERCEPTION_ON,
    INTERCEPTION_OFF
} Interception;


void arc_set_jtag_interception(Interception state);

Action arc_check_interception_breakpoint(ARC_RegisterNumber pc_regnum,
                                         int*               exitcode);

#endif /* ARC_JTAG_FILEIO */
/******************************************************************************/
