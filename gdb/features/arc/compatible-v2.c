/* THIS FILE IS GENERATED.  Original: compatible-v2.xml */

#include "defs.h"
#include "osabi.h"
#include "target-descriptions.h"

struct target_desc *tdesc_compatible_v2;
static void
initialize_tdesc_compatible_v2 (void)
{
  struct target_desc *result = allocate_target_description ();
  struct tdesc_feature *feature;
  struct tdesc_type *field_type;

  set_tdesc_architecture (result, bfd_scan_arch ("ARCv2"));

  feature = tdesc_create_feature (result, "org.gnu.gdb.arc.core.v2");
  tdesc_create_reg (feature, "r0", 0, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r1", 1, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r2", 2, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r3", 3, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r4", 4, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r5", 5, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r6", 6, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r7", 7, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r8", 8, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r9", 9, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r10", 10, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r11", 11, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r12", 12, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r13", 13, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r14", 14, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r15", 15, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r16", 16, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r17", 17, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r18", 18, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r19", 19, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r20", 20, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r21", 21, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r22", 22, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r23", 23, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r24", 24, 1, "general", 32, "int");
  tdesc_create_reg (feature, "r25", 25, 1, "general", 32, "int");
  tdesc_create_reg (feature, "gp", 26, 1, "general", 32, "data_ptr");
  tdesc_create_reg (feature, "fp", 27, 1, "general", 32, "data_ptr");
  tdesc_create_reg (feature, "sp", 28, 1, "general", 32, "data_ptr");
  tdesc_create_reg (feature, "ilink", 29, 1, "general", 32, "code_ptr");
  tdesc_create_reg (feature, "r30", 30, 1, "", 32, "int");
  tdesc_create_reg (feature, "blink", 31, 1, "general", 32, "code_ptr");
  tdesc_create_reg (feature, "r32", 32, 1, "", 32, "int");
  tdesc_create_reg (feature, "r33", 33, 1, "", 32, "int");
  tdesc_create_reg (feature, "r34", 34, 1, "", 32, "int");
  tdesc_create_reg (feature, "r35", 35, 1, "", 32, "int");
  tdesc_create_reg (feature, "r36", 36, 1, "", 32, "int");
  tdesc_create_reg (feature, "r37", 37, 1, "", 32, "int");
  tdesc_create_reg (feature, "r38", 38, 1, "", 32, "int");
  tdesc_create_reg (feature, "r39", 39, 1, "", 32, "int");
  tdesc_create_reg (feature, "r40", 40, 1, "", 32, "int");
  tdesc_create_reg (feature, "r41", 41, 1, "", 32, "int");
  tdesc_create_reg (feature, "r42", 42, 1, "", 32, "int");
  tdesc_create_reg (feature, "r43", 43, 1, "", 32, "int");
  tdesc_create_reg (feature, "r44", 44, 1, "", 32, "int");
  tdesc_create_reg (feature, "r45", 45, 1, "", 32, "int");
  tdesc_create_reg (feature, "r46", 46, 1, "", 32, "int");
  tdesc_create_reg (feature, "r47", 47, 1, "", 32, "int");
  tdesc_create_reg (feature, "r48", 48, 1, "", 32, "int");
  tdesc_create_reg (feature, "r49", 49, 1, "", 32, "int");
  tdesc_create_reg (feature, "r50", 50, 1, "", 32, "int");
  tdesc_create_reg (feature, "r51", 51, 1, "", 32, "int");
  tdesc_create_reg (feature, "r52", 52, 1, "", 32, "int");
  tdesc_create_reg (feature, "r53", 53, 1, "", 32, "int");
  tdesc_create_reg (feature, "r54", 54, 1, "", 32, "int");
  tdesc_create_reg (feature, "r55", 55, 1, "", 32, "int");
  tdesc_create_reg (feature, "r56", 56, 1, "", 32, "int");
  tdesc_create_reg (feature, "r57", 57, 1, "", 32, "int");
  tdesc_create_reg (feature, "accl", 58, 1, "", 32, "int");
  tdesc_create_reg (feature, "acch", 59, 1, "", 32, "int");
  tdesc_create_reg (feature, "lp_count", 60, 1, "general", 32, "uint32");
  tdesc_create_reg (feature, "reserved", 61, 1, "", 32, "int");
  tdesc_create_reg (feature, "limm", 62, 1, "", 32, "int");
  tdesc_create_reg (feature, "pcl", 63, 1, "", 32, "code_ptr");

  feature = tdesc_create_feature (result, "org.gnu.gdb.arc.aux-minimal");
  field_type = tdesc_create_flags (feature, "status32_type", 4);
  tdesc_add_flag (field_type, 0, "H");
  tdesc_add_flag (field_type, 1, "E0");
  tdesc_add_flag (field_type, 2, "E1");
  tdesc_add_flag (field_type, 3, "E2");
  tdesc_add_flag (field_type, 4, "E3");
  tdesc_add_flag (field_type, 5, "AE");
  tdesc_add_flag (field_type, 6, "DE");
  tdesc_add_flag (field_type, 7, "U");
  tdesc_add_flag (field_type, 8, "V");
  tdesc_add_flag (field_type, 9, "C");
  tdesc_add_flag (field_type, 10, "N");
  tdesc_add_flag (field_type, 11, "Z");
  tdesc_add_flag (field_type, 12, "L");
  tdesc_add_flag (field_type, 13, "DZ");
  tdesc_add_flag (field_type, 14, "SC");
  tdesc_add_flag (field_type, 15, "ES");
  tdesc_add_flag (field_type, 16, "RB0");
  tdesc_add_flag (field_type, 17, "RB1");
  tdesc_add_flag (field_type, 18, "RB2");
  tdesc_add_flag (field_type, 19, "AD");
  tdesc_add_flag (field_type, 20, "US");
  tdesc_add_flag (field_type, 31, "IE");

  tdesc_create_reg (feature, "pc", 64, 1, "general", 32, "code_ptr");
  tdesc_create_reg (feature, "lp_start", 65, 1, "general", 32, "code_ptr");
  tdesc_create_reg (feature, "lp_end", 66, 1, "general", 32, "code_ptr");
  tdesc_create_reg (feature, "status32", 67, 1, "general", 32, "status32_type");

  feature = tdesc_create_feature (result, "org.gnu.gdb.arc.aux-compatible");
  tdesc_create_reg (feature, "status32_l1", 68, 1, "", 32, "int");
  tdesc_create_reg (feature, "status32_l2", 69, 1, "", 32, "int");
  tdesc_create_reg (feature, "aux_irq_lv12", 70, 1, "", 32, "int");
  tdesc_create_reg (feature, "aux_irq_lev", 71, 1, "", 32, "int");
  tdesc_create_reg (feature, "aux_irq_hint", 72, 1, "", 32, "int");
  tdesc_create_reg (feature, "eret", 73, 1, "", 32, "code_ptr");
  tdesc_create_reg (feature, "erbta", 74, 1, "", 32, "code_ptr");
  tdesc_create_reg (feature, "erstatus", 75, 1, "", 32, "int");
  tdesc_create_reg (feature, "ecr", 76, 1, "", 32, "int");
  tdesc_create_reg (feature, "efa", 77, 1, "", 32, "int");
  tdesc_create_reg (feature, "icause1", 78, 1, "", 32, "int");
  tdesc_create_reg (feature, "icause2", 79, 1, "", 32, "int");
  tdesc_create_reg (feature, "aux_ienable", 80, 1, "", 32, "int");
  tdesc_create_reg (feature, "aux_itrigger", 81, 1, "", 32, "int");
  tdesc_create_reg (feature, "bta", 82, 1, "", 32, "code_ptr");
  tdesc_create_reg (feature, "bta_l1", 83, 1, "", 32, "code_ptr");
  tdesc_create_reg (feature, "bta_l2", 84, 1, "", 32, "code_ptr");
  tdesc_create_reg (feature, "aux_irq_pulse_cancel", 85, 1, "", 32, "int");
  tdesc_create_reg (feature, "aux_irq_pending", 86, 1, "", 32, "int");

  tdesc_compatible_v2 = result;
}
