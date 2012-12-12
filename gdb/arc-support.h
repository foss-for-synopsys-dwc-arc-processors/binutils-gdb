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
/*     This header file defines some useful types and constants, and macros   */
/*     for use in debugging.                                                  */
/*                                                                            */
/******************************************************************************/

#ifndef ARC_SUPPORT_H
#define ARC_SUPPORT_H


#define ARC_DEBUG 1

#if ARC_DEBUG
#define DEBUG(...)              if (arc_debug_target) fprintf_unfiltered(gdb_stdlog, __VA_ARGS__)
#define ENTERMSG                DEBUG("--- entered %s:%s()\n",        __FILE__, __FUNCTION__)
#define ENTERARGS(fmt, args...) DEBUG("--- entered %s:%s(" fmt ")\n", __FILE__, __FUNCTION__, args)
#define LEAVEMSG                DEBUG("--- exited  %s:%s()\n",        __FILE__, __FUNCTION__)
#else
#define DEBUG(...)
#define ENTERMSG
#define ENTERARGS(fmt, args...)
#define LEAVEMSG
#endif


/* N.B. it must be possible to build some ARC modules without the rest of gdb so
 *      that they can be exercised by stand-alone test drivers
 */
#ifdef STANDALONE_TEST
#define error(...)                    { printf(__VA_ARGS__); printf("\n"); }
#define warning(...)                  { printf(__VA_ARGS__); printf("\n"); }
#define printf_filtered(...)            printf(__VA_ARGS__)
#define printf_unfiltered(...)          printf(__VA_ARGS__)
#define fprintf_unfiltered(STR, ...)    printf(__VA_ARGS__)
#define internal_error(...)             abort()
#endif


/* useful Boolean type and constants */
typedef int Boolean;

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif


typedef unsigned int           ARC_RegisterNumber;
typedef unsigned int           ARC_RegisterContents;
typedef unsigned int           ARC_Address;
typedef unsigned long long int ARC_Doubleword;
typedef unsigned int           ARC_Word;
typedef unsigned short int     ARC_Halfword;
typedef unsigned char          ARC_Byte;


/* sizes of quantities */
#define BYTES_IN_WORD              4
#define BYTES_IN_REGISTER          4
#define BITS_IN_BYTE               8
#define BITS_IN_WORD              32
#define BITS_IN_ADDRESS           32
#define BITS_IN_REGISTER          32


#define ELEMENTS_IN_ARRAY(arr)           (unsigned int) (sizeof(arr) / sizeof(arr[0]))


/* a global debug flag */
extern Boolean arc_debug_target;

#endif /* ARC_SUPPORT_H */
/******************************************************************************/
