/* THIS FILE IS GENERATED.  -*- buffer-read-only: t -*- vi:set ro:
  Original: aux-v2.xml */

#include "arch/tdesc.h"

static int
create_feature_arc_aux_v2 (struct target_desc *result, long regnum)
{
  struct tdesc_feature *feature;

  feature = tdesc_create_feature (result, "org.gnu.gdb.arc.aux-minimal", "aux-v2.xml");
  struct tdesc_type *field_type;
  struct tdesc_type *type;
  type = tdesc_create_flags (feature, "status32_type", 4);
  tdesc_add_flag (type, 0, "H");
  tdesc_add_bitfield (type, "E", 1, 4);
  tdesc_add_flag (type, 5, "AE");
  tdesc_add_flag (type, 6, "DE");
  tdesc_add_flag (type, 7, "U");
  tdesc_add_flag (type, 8, "V");
  tdesc_add_flag (type, 9, "C");
  tdesc_add_flag (type, 10, "N");
  tdesc_add_flag (type, 11, "Z");
  tdesc_add_flag (type, 12, "L");
  tdesc_add_flag (type, 13, "DZ");
  tdesc_add_flag (type, 14, "SC");
  tdesc_add_flag (type, 15, "ES");
  tdesc_add_bitfield (type, "RB", 16, 18);
  tdesc_add_flag (type, 19, "AD");
  tdesc_add_flag (type, 20, "US");
  tdesc_add_flag (type, 31, "IE");

  tdesc_create_reg (feature, "pc", regnum++, 1, NULL, 32, "code_ptr");
  tdesc_create_reg (feature, "status32", regnum++, 1, NULL, 32, "status32_type");
  return regnum;
}
