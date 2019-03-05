# This shell script emits a C file. -*- C -*-
# Copyright (C) 2019 Free Software Foundation, Inc.
#
# Copyright 2019 Synopsys Inc.
#
# This file is part of GLD, the Gnu Linker.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
# MA 02110-1301, USA.

# This file is sourced from elf32.em, and defines extra arcelf
# specific routines.
#
fragment <<EOF

static void
arcelf_before_allocation (void)
{
  /* Call main function; we're just extending it.  */
  gld${EMULATION_NAME}_before_allocation ();

  /* ARC needs two step relaxation.  */
  link_info.relax_pass = 2;
}

EOF

LDEMUL_BEFORE_ALLOCATION=arcelf_before_allocation
