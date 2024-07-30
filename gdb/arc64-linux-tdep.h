/* Target dependent code for GNU/Linux ARC.

   Copyright 2024 Free Software Foundation, Inc.

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

#ifndef ARC64_LINUX_TDEP_H
#define ARC64_LINUX_TDEP_H

#include "gdbarch.h"
#include "regset.h"

/* In user_regs_struct structure from include/uapi/asm/ptrace.h all registers
   are declared with "unsigned long" type. That means that registers are dumped
   differently for ARCv3 32-bit and ARCv3 64-bit targets:

     1. For ARCv3 32-bit targets all registers are saved as 32-bit values.
     2. For ARCv3 64-bit targets all registers are saved as 64-bit values
        even if some of them are 32-bit registers (e.g., STATUS32).

   That is why we assume that for ARCv3 64-bit targets all registers are dumped
   as 64-bit values.  */

#define ARC_GREGSET_REGISTERS_NUMBER 40
#define ARC32_GREGSET_REGISTER_SIZE 4
#define ARC64_GREGSET_REGISTER_SIZE 8
#define ARC32_GREGSET_REGISTER_OFFSET(offset) \
	((offset) * ARC32_GREGSET_REGISTER_SIZE)
#define ARC64_GREGSET_REGISTER_OFFSET(offset) \
	((offset) * ARC64_GREGSET_REGISTER_SIZE)

extern const struct regset arc32_linux_gregset;

/* Reads registers from the NT_PRSTATUS data array into the regcache.  */

void arc_linux_supply_gregset (const struct regset *regset,
			       struct regcache *regcache, int regnum,
			       const void *gregs, size_t size);

/* Writes registers from the regcache into the NT_PRSTATUS data array.  */

void arc_linux_collect_gregset (const struct regset *regset,
				const struct regcache *regcache,
				int regnum, void *gregs, size_t size);

#endif /* ARC64_LINUX_TDEP_H */
