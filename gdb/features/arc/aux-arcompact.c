/* THIS FILE IS GENERATED.  -*- buffer-read-only: t -*- vi:set ro:
  Original: aux-arcompact.xml */

#include "arch/tdesc.h"

static int
create_feature_arc_aux_arcompact (struct target_desc *result, long regnum)
{
  struct tdesc_feature *feature;

  feature = tdesc_create_feature (result, "org.gnu.gdb.arc.aux-minimal", "aux-arcompact.xml");
  struct tdesc_type *field_type;
  struct tdesc_type *type;
  type = tdesc_create_flags (feature, "status32_type", 4);
  tdesc_add_flag (type, 0, "H");
  tdesc_add_bitfield (type, "E", 1, 2);
  tdesc_add_bitfield (type, "A", 3, 4);
  tdesc_add_flag (type, 5, "AE");
  tdesc_add_flag (type, 6, "DE");
  tdesc_add_flag (type, 7, "U");
  tdesc_add_flag (type, 8, "V");
  tdesc_add_flag (type, 9, "C");
  tdesc_add_flag (type, 10, "N");
  tdesc_add_flag (type, 11, "Z");
  tdesc_add_flag (type, 12, "L");
  tdesc_add_flag (type, 13, "R");
  tdesc_add_flag (type, 14, "SE");

  tdesc_create_reg (feature, "pc", regnum++, 1, NULL, 32, "code_ptr");
  tdesc_create_reg (feature, "status32", regnum++, 1, NULL, 32, "status32_type");
  return regnum;
}
