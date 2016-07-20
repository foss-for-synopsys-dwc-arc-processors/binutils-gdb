/* Target dependent code for GNU/Linux ARC.

   Copyright 2014-2016 Free Software Foundation, Inc.
   Contributed by Synopsys Inc.

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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef ARC_LINUX_TDEP_H
#define ARC_LINUX_TDEP_H

#include "gdbarch.h"
#include "regset.h"

/* There are 40 registers in Linux user_regs_struct, although some of them are
 * now just a mere paddings, kept to maintain binary compatibility with older
 * tools. */
#define ARC_LINUX_SIZEOF_GREGSET (40 * BYTES_IN_REGISTER)

/* Reads registers from NT_PRSTATUS data array into the regcache. */
void arc_linux_supply_gregset (	const struct regset *regset,
				struct regcache *regcache,
				int regnum,
				const void *gregs,
				size_t size);

/* Writes registers from regcache into the NT_PRSTATUS data array. */
void arc_linux_collect_gregset (const struct regset *regset,
				const struct regcache *regcache,
				int regnum,
				void *gregs,
				size_t size);

#endif // ARC_LINUX_TDEP_H

/* vim: set sts=2 shiftwidth=2 ts=8: */
