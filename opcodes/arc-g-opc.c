#include "sysdep.h"
#include <stdio.h>
#include <stdbool.h>
//#include "bfd.h"
#include "opcode/arc.h"
#include "opintl.h"
#include "libiberty.h"

/* Include the generic extract/insert functions.  Order is important
   as some of the functions present in the .h may be disabled via
   defines.  */
//#include "arc-fxi.h"

//#include "arcxx-opc.inc"

int
arc_opcode_len (const struct arc_opcode *opcode)
{
  if (opcode->mask < 0x10000ull)
    return 2;

  if (opcode->mask < 0x100000000ull)
    return 4;

  if (opcode->mask < 0x1000000000000ull)
    return 6;

  return 8;
}

