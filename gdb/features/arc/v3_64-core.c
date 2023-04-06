/* THIS FILE IS GENERATED.  -*- buffer-read-only: t -*- vi:set ro:
  Original: v3_64-core.xml */

#include "gdbsupport/tdesc.h"

static int
create_feature_arc_v3_64_core (struct target_desc *result, long regnum)
{
  struct tdesc_feature *feature;

  feature = tdesc_create_feature (result, "org.gnu.gdb.arc.core");
  tdesc_create_reg (feature, "r0", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r1", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r2", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r3", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r4", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r5", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r6", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r7", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r8", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r9", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r10", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r11", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r12", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r13", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r14", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r15", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r16", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r17", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r18", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r19", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r20", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r21", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r22", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r23", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r24", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r25", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "r26", regnum++, 1, NULL, 64, "int");
  tdesc_create_reg (feature, "fp", regnum++, 1, NULL, 64, "data_ptr");
  tdesc_create_reg (feature, "sp", regnum++, 1, NULL, 64, "data_ptr");
  tdesc_create_reg (feature, "ilink", regnum++, 1, NULL, 64, "code_ptr");
  tdesc_create_reg (feature, "gp", regnum++, 1, NULL, 64, "data_ptr");
  tdesc_create_reg (feature, "blink", regnum++, 1, NULL, 64, "code_ptr");
  tdesc_create_reg (feature, "pcl", regnum++, 1, NULL, 64, "code_ptr");
  return regnum;
}
