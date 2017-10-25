/* Copyright (C) 2017 Free Software Foundation, Inc.

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


#include "common-defs.h"
#include <stdlib.h>

#include "arc.h"

/* Target description features.  */
#include "features/arc/core-v2.c"
#include "features/arc/aux-v2.c"
#include "features/arc/core-arcompact.c"
#include "features/arc/aux-arcompact.c"

/* Create target description for a target with specified parameters.
   PRINT_DEBUG defines whether to print debug messages to the stderr stream.
   IS_ARCV2 defines if this is an ARCv2 (ARC EM or ARC HS) target or ARCompact
   (ARC600 or ARC700); there is no use for more specific information about
   target processor.  */

target_desc *
arc_create_target_description (bool print_debug, bool is_arcv2)
{
  target_desc *tdesc = allocate_target_description ();

  if (print_debug)
    debug_printf ("arc: Creating target description, "
	"is_arcv2=%i\n", is_arcv2);

  long regnum = 0;

#ifndef IN_PROCESS_AGENT
  if (is_arcv2)
    {
      set_tdesc_architecture (tdesc, "arc:ARCv2");
    }
  else
    {
      set_tdesc_architecture (tdesc, "arc:ARC700");
    }
#endif

  if (is_arcv2)
    {
      regnum = create_feature_arc_core_v2 (tdesc, regnum);
      regnum = create_feature_arc_aux_v2 (tdesc, regnum);
    }
  else
    {
      regnum = create_feature_arc_core_arcompact (tdesc, regnum);
      regnum = create_feature_arc_aux_arcompact (tdesc, regnum);
    }

  return tdesc;
}

