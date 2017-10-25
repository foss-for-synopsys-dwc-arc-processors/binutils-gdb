/* Copyright (C) 2017-2020 Free Software Foundation, Inc.

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


#include "gdbsupport/common-defs.h"
#include <stdlib.h>

#include "arc.h"

/* Target description features.  */
#include "features/arc/core-v2.c"
#include "features/arc/aux-v2.c"
#include "features/arc/core-v2-linux.c"
#include "features/arc/aux-v2-linux.c"
#include "features/arc/core-arcompact.c"
#include "features/arc/aux-arcompact.c"
#include "features/arc/core-arcompact-linux.c"
#include "features/arc/aux-arcompact-linux.c"

/* See arc.h.  */

target_desc *
arc_create_target_description (arc_sys_type sys_type)
{
  target_desc *tdesc = allocate_target_description ();

  long regnum = 0;

#ifndef IN_PROCESS_AGENT
  if (sys_type == ARC_SYS_TYPE_ARCV2_BMT)
    set_tdesc_architecture (tdesc, "arc:ARCv2");
  else if (sys_type == ARC_SYS_TYPE_ARCV2_LNX)
    /* If this is ARCv2 Linux, then it is ARC HS.  */
    set_tdesc_architecture (tdesc, "arc:HS");
  else
    set_tdesc_architecture (tdesc, "arc:ARC700");

  if (sys_type == ARC_SYS_TYPE_ARCOMPACT_LNX
      || sys_type == ARC_SYS_TYPE_ARCV2_LNX)
    set_tdesc_osabi (tdesc, "GNU/Linux");
#endif

  switch (sys_type)
    {
    case ARC_SYS_TYPE_ARCOMPACT_BMT:
	  regnum = create_feature_arc_core_arcompact (tdesc, regnum);
	  regnum = create_feature_arc_aux_arcompact (tdesc, regnum);
	  break;
    case ARC_SYS_TYPE_ARCOMPACT_LNX:
	  regnum = create_feature_arc_core_arcompact_linux (tdesc, regnum);
	  regnum = create_feature_arc_aux_arcompact_linux (tdesc, regnum);
	  break;
    case ARC_SYS_TYPE_ARCV2_BMT:
	  regnum = create_feature_arc_core_v2 (tdesc, regnum);
	  regnum = create_feature_arc_aux_v2 (tdesc, regnum);
	  break;
    case ARC_SYS_TYPE_ARCV2_LNX:
	  regnum = create_feature_arc_core_v2_linux (tdesc, regnum);
	  regnum = create_feature_arc_aux_v2_linux (tdesc, regnum);
	  break;
    default:
	  gdb_assert(!"Invalid arc_sys_type.");
    }

  return tdesc;
}
