/* Instruction printing code for the ARC.
   Copyright (C) 1994-2016 Free Software Foundation, Inc.

   Contributed by Claudiu Zissulescu (claziss@synopsys.com)

   This file is part of libopcodes.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include <stdio.h>
#include <assert.h>
#include "dis-asm.h"
#include "opcode/arc.h"
#include "elf/arc.h"
#include "arc-dis.h"
#include "arc-ext.h"
#include "elf-bfd.h"
#include "libiberty.h"
#include "opintl.h"

/* Structure used to iterate over, and extract the values for, operands of
   an opcode.  */

struct arc_operand_iterator
{
  enum
    {
      OPERAND_ITERATOR_STANDARD,
      OPERAND_ITERATOR_LONG
    } mode;

  /* The array of 32-bit values that make up this instruction.  All
     required values have been pre-loaded into this array during the
     find_format call.  */
  unsigned *insn;

  union
  {
    struct
    {
      /* The opcode this iterator is operating on.  */
      const struct arc_opcode *opcode;

      /* The index into the opcodes operand index list.  */
      const unsigned char *opidx;
    } standard;

    struct
    {
      /* The long instruction opcode this iterator is operating on.  */
      const struct arc_long_opcode *long_opcode;

      /* Two indexes into the opcodes operand index lists.  */
      const unsigned char *opidx_base, *opidx_limm;
    } long_insn;
  } state;
};

/* Globals variables.  */

static const char * const regnames[64] =
{
  "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
  "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
  "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
  "r24", "r25", "gp", "fp", "sp", "ilink", "r30", "blink",

  "r32", "r33", "r34", "r35", "r36", "r37", "r38", "r39",
  "r40", "r41", "r42", "r43", "r44", "r45", "r46", "r47",
  "r48", "r49", "r50", "r51", "r52", "r53", "r54", "r55",
  "r56", "r57", "ACCL", "ACCH", "lp_count", "rezerved", "LIMM", "pcl"
};

static const char * const addrtypenames[ARC_NUM_ADDRTYPES] =
{
  "bd", "jid", "lbd", "mbd", "sd", "sm", "xa", "xd",
  "cd", "cbd", "cjid", "clbd", "cm", "csd", "cxa", "cxd"
};

static int addrtypenames_max = ARC_NUM_ADDRTYPES - 1;

static const char * const addrtypeunknown = "unknown";

/* This structure keeps track which instruction class(es)
   should be ignored durring disassembling.  */

typedef struct skipclass
{
  insn_class_t     insn_class;
  insn_subclass_t  subclass;
  struct skipclass *nxt;
} skipclass_t, *linkclass;

/* Intial classes of instructions to be consider first when
   disassembling.  */
static linkclass decodelist = NULL;

/* Macros section.  */

#ifdef DEBUG
# define pr_debug(fmt, args...) fprintf (stderr, fmt, ##args)
#else
# define pr_debug(fmt, args...)
#endif

#define ARRANGE_ENDIAN(info, buf)					\
  (info->endian == BFD_ENDIAN_LITTLE ? bfd_getm32 (bfd_getl32 (buf))	\
   : bfd_getb32 (buf))

#define BITS(word,s,e)  (((word) << (sizeof (word) * 8 - 1 - e)) >>	\
			 (s + (sizeof (word) * 8 - 1 - e)))
#define OPCODE(word)	(BITS ((word), 27, 31))

#define OPCODE_AC(word)   (BITS ((word), 11, 15))

/* Functions implementation.  */

/* Add a new element to the decode list.  */

static void
add_to_decodelist (insn_class_t     insn_class,
		   insn_subclass_t  subclass)
{
  linkclass t = (linkclass) xmalloc (sizeof (skipclass_t));

  t->insn_class = insn_class;
  t->subclass = subclass;
  t->nxt = decodelist;
  decodelist = t;
}

/* Return TRUE if we need to skip the opcode from being
   disassembled.  */

static bfd_boolean
skip_this_opcode (const struct arc_opcode *  opcode)
{
  linkclass t = decodelist;

  /* Check opcode for major 0x06, return if it is not.  */
  if (OPCODE (opcode->opcode) != 0x06)
    return FALSE;

  /* or not a known truble class.  */
  switch (opcode->insn_class)
    {
    case FLOAT:
    case DSP:
      break;
    default:
      return FALSE;
    }

  while (t != NULL)
    {
      if ((t->insn_class == opcode->insn_class)
	  && (t->subclass == opcode->subclass))
	return FALSE;
      t = t->nxt;
    }

  return TRUE;
}

static bfd_vma
bfd_getm32 (unsigned int data)
{
  bfd_vma value = 0;

  value = ((data & 0xff00) | (data & 0xff)) << 16;
  value |= ((data & 0xff0000) | (data & 0xff000000)) >> 16;
  return value;
}

static bfd_boolean
special_flag_p (const char *opname,
		const char *flgname)
{
  const struct arc_flag_special *flg_spec;
  unsigned i, j, flgidx;

  for (i = 0; i < arc_num_flag_special; i++)
    {
      flg_spec = &arc_flag_special_cases[i];

      if (strcmp (opname, flg_spec->name))
	continue;

      /* Found potential special case instruction.  */
      for (j=0;; ++j)
	{
	  flgidx = flg_spec->flags[j];
	  if (flgidx == 0)
	    break; /* End of the array.  */

	  if (strcmp (flgname, arc_flag_operands[flgidx].name) == 0)
	    return TRUE;
	}
    }
  return FALSE;
}

/* Find opcode from ARC_TABLE given the instruction described by INSN and
   INSNLEN.  The ISA_MASK restricts the possible matches in ARC_TABLE.  */

static const struct arc_opcode *
find_format_from_table (struct disassemble_info *info,
			const struct arc_opcode *arc_table,
                        unsigned *insn,
			unsigned int insn_len,
                        unsigned isa_mask,
			bfd_boolean *has_limm,
			bfd_boolean overlaps)
{
  unsigned int i = 0;
  const struct arc_opcode *opcode = NULL;
  const struct arc_opcode *t_op = NULL;
  const unsigned char *opidx;
  const unsigned char *flgidx;
  bfd_boolean warn_p = FALSE;

  do
    {
      bfd_boolean invalid = FALSE;

      opcode = &arc_table[i++];

      if (ARC_SHORT (opcode->mask) && (insn_len == 2))
	{
	  if (OPCODE_AC (opcode->opcode) != OPCODE_AC (insn[0]))
	    continue;
	}
      else if (!ARC_SHORT (opcode->mask) && (insn_len == 4))
	{
	  if (OPCODE (opcode->opcode) != OPCODE (insn[0]))
	    continue;
	}
      else
	continue;

      if ((insn[0] ^ opcode->opcode) & opcode->mask)
	continue;

      if (!(opcode->cpu & isa_mask))
	continue;

      *has_limm = FALSE;

      /* Possible candidate, check the operands.  */
      for (opidx = opcode->operands; *opidx; opidx++)
	{
	  int value, limmind;
	  const struct arc_operand *operand = &arc_operands[*opidx];

	  if (operand->flags & ARC_OPERAND_FAKE)
	    continue;

	  if (operand->extract)
	    value = (*operand->extract) (insn[0], &invalid);
	  else
	    value = (insn[0] >> operand->shift) & ((1 << operand->bits) - 1);

	  /* Check for LIMM indicator.  If it is there, then make sure
	     we pick the right format.  */
	  limmind = (isa_mask & ARC_OPCODE_ARCV2) ? 0x1E : 0x3E;
	  if (operand->flags & ARC_OPERAND_IR
	      && !(operand->flags & ARC_OPERAND_LIMM))
	    {
	      if ((value == 0x3E && insn_len == 4)
		  || (value == limmind && insn_len == 2))
		{
		  invalid = TRUE;
		  break;
		}
	    }

	  if (operand->flags & ARC_OPERAND_LIMM
	      && !(operand->flags & ARC_OPERAND_DUPLICATE))
	    *has_limm = TRUE;
	}

      /* Check the flags.  */
      for (flgidx = opcode->flags; *flgidx; flgidx++)
	{
	  /* Get a valid flag class.  */
	  const struct arc_flag_class *cl_flags = &arc_flag_classes[*flgidx];
	  const unsigned *flgopridx;
	  int foundA = 0, foundB = 0;
	  unsigned int value;

	  /* Check first the extensions.  */
	  if (cl_flags->flag_class & F_CLASS_EXTEND)
	    {
	      value = (insn[0] & 0x1F);
	      if (arcExtMap_condCodeName (value))
		continue;
	    }

	  for (flgopridx = cl_flags->flags; *flgopridx; ++flgopridx)
	    {
	      const struct arc_flag_operand *flg_operand =
		&arc_flag_operands[*flgopridx];

	      value = (insn[0] >> flg_operand->shift)
		& ((1 << flg_operand->bits) - 1);
	      if (value == flg_operand->code)
		foundA = 1;
	      if (value)
		foundB = 1;
	    }

	  if (!foundA && foundB)
	    {
	      invalid = TRUE;
	      break;
	    }
	}

      if (invalid)
	continue;

      if (insn_len == 4
	  && overlaps)
	{
	  warn_p = TRUE;
	  t_op = opcode;
	  if (skip_this_opcode (opcode))
	    continue;
	}

      /* The instruction is valid.  */
      return opcode;
    }
  while (opcode->mask);

  if (warn_p)
    {
      info->fprintf_func (info->stream,
			  _("\nWarning: disassembly may be wrong due to "
			    "guessed opcode class choice.\n"
			    "Use -M<class[,class]> to select the correct "
			    "opcode class(es).\n\t\t\t\t"));
      return t_op;
    }

  return NULL;
}

/* Find long instructions matching values in INSN array.  */

static const struct arc_long_opcode *
find_format_long_instructions (unsigned *insn,
                               unsigned int *insn_len,
                               unsigned isa_mask,
                               bfd_vma memaddr,
                               struct disassemble_info *info)
{
  unsigned int i;
  unsigned limm = 0;
  bfd_boolean limm_loaded = FALSE;

  for (i = 0; i < arc_num_long_opcodes; ++i)
    {
      bfd_byte buffer[4];
      int status;
      const struct arc_opcode *opcode;

      opcode = &arc_long_opcodes[i].base_opcode;

      if (ARC_SHORT (opcode->mask) && (*insn_len == 2))
        {
          if (OPCODE_AC (opcode->opcode) != OPCODE_AC (insn[0]))
            continue;
        }
      else if (!ARC_SHORT (opcode->mask) && (*insn_len == 4))
        {
          if (OPCODE (opcode->opcode) != OPCODE (insn[0]))
            continue;
        }
      else
        continue;

      if ((insn[0] ^ opcode->opcode) & opcode->mask)
        continue;

      if (!(opcode->cpu & isa_mask))
        continue;

      if (!limm_loaded)
        {
          status = (*info->read_memory_func) (memaddr + *insn_len, buffer,
                                              4, info);
          if (status != 0)
            return NULL;

          limm = ARRANGE_ENDIAN (info, buffer);
          limm_loaded = TRUE;
        }

      /* Check the second word using the mask and template.  */
      if ((limm & arc_long_opcodes[i].limm_mask)
          != arc_long_opcodes[i].limm_template)
        continue;

      (*insn_len) += 4;
      insn[1] = limm;
      return &arc_long_opcodes[i];
    }

  return NULL;
}

/* Find opcode for INSN, trying various different sources.  The instruction
   length in INSN_LEN will be updated if the instruction requires a LIMM
   extension, and the additional values loaded into the INSN array (which
   must be big enough).

   A pointer to the opcode is placed into OPCODE_RESULT, and ITER is
   initialised, ready to iterate over the operands of the found opcode.

   This function returns TRUE in almost all cases, FALSE is reserved to
   indicate an error (failing to find an opcode is not an error) a
   returned result of FALSE would indicate that the disassembler can't
   continue.

   If no matching opcode is found then the returned result will be TRUE,
   the value placed into OPCODE_RESULT will be NULL, ITER will be
   undefined, and INSN_LEN will be unchanged.

   If a matching opcode is found, then the returned result will be TRUE,
   the opcode pointer is placed into OPCODE_RESULT, INSN_LEN will be
   increased by 4 if the instruction requires a LIMM, and the LIMM value
   will have been loaded into the INSN[1].  Finally, ITER will have been
   initialised so that calls to OPERAND_ITERATOR_NEXT will iterate over
   the opcode's operands.  */

static bfd_boolean
find_format (bfd_vma                       memaddr,
	     unsigned *                    insn,
	     unsigned int *                insn_len,
             unsigned                      isa_mask,
	     struct disassemble_info *     info,
             const struct arc_opcode **    opcode_result,
             struct arc_operand_iterator * iter)
{
  const struct arc_opcode *opcode = NULL;
  bfd_boolean needs_limm;
  const extInstruction_t *einsn, *i;

  /* First, try the extension instructions.  */
  einsn = arcExtMap_insn (OPCODE (insn[0]), insn[0]);
  for (i = einsn; (i != NULL) && (opcode == NULL); i = i->next)
    {
      const char *errmsg = NULL;

      opcode = arcExtMap_genOpcode (i, isa_mask, &errmsg);
      if (opcode == NULL)
	{
	  (*info->fprintf_func) (info->stream, "\
An error occured while generating the extension instruction operations");
	  *opcode_result = NULL;
	  return FALSE;
	}

      opcode = find_format_from_table (info, opcode, insn, *insn_len,
				       isa_mask, &needs_limm, FALSE);
    }

  /* Then, try finding the first match in the opcode table.  */
  if (opcode == NULL)
    opcode = find_format_from_table (info, arc_opcodes, insn, *insn_len,
				     isa_mask, &needs_limm, TRUE);

  if (needs_limm && opcode != NULL)
    {
      bfd_byte buffer[4];
      int status;

      status = (*info->read_memory_func) (memaddr + *insn_len, buffer,
                                          4, info);
      if (status != 0)
        {
          opcode = NULL;
        }
      else
        {
          insn[1] = ARRANGE_ENDIAN (info, buffer);
          *insn_len += 4;
        }
    }

  if (opcode == NULL)
    {
      const struct arc_long_opcode *long_opcode;

      /* No instruction found yet, try the long instructions.  */
      long_opcode =
        find_format_long_instructions (insn, insn_len, isa_mask,
                                       memaddr, info);

      if (long_opcode != NULL)
        {
          iter->mode = OPERAND_ITERATOR_LONG;
          iter->insn = insn;
          iter->state.long_insn.long_opcode = long_opcode;
          iter->state.long_insn.opidx_base =
            long_opcode->base_opcode.operands;
          iter->state.long_insn.opidx_limm =
            long_opcode->operands;
          opcode = &long_opcode->base_opcode;
        }
    }
  else
    {
      iter->mode = OPERAND_ITERATOR_STANDARD;
      iter->insn = insn;
      iter->state.standard.opcode = opcode;
      iter->state.standard.opidx = opcode->operands;
    }

  *opcode_result = opcode;
  return TRUE;
}

static void
print_flags (const struct arc_opcode *opcode,
	     unsigned *insn,
	     struct disassemble_info *info)
{
  const unsigned char *flgidx;
  unsigned int value;

  /* Now extract and print the flags.  */
  for (flgidx = opcode->flags; *flgidx; flgidx++)
    {
      /* Get a valid flag class.  */
      const struct arc_flag_class *cl_flags = &arc_flag_classes[*flgidx];
      const unsigned *flgopridx;

      /* Check first the extensions.  */
      if (cl_flags->flag_class & F_CLASS_EXTEND)
	{
	  const char *name;
	  value = (insn[0] & 0x1F);

	  name = arcExtMap_condCodeName (value);
	  if (name)
	    {
	      (*info->fprintf_func) (info->stream, ".%s", name);
	      continue;
	    }
	}

      for (flgopridx = cl_flags->flags; *flgopridx; ++flgopridx)
	{
	  const struct arc_flag_operand *flg_operand =
	    &arc_flag_operands[*flgopridx];

	  if (!flg_operand->favail)
	    continue;

	  value = (insn[0] >> flg_operand->shift)
	    & ((1 << flg_operand->bits) - 1);
	  if (value == flg_operand->code)
	    {
	       /* FIXME!: print correctly nt/t flag.  */
	      if (!special_flag_p (opcode->name, flg_operand->name))
		(*info->fprintf_func) (info->stream, ".");
	      else if (info->insn_type == dis_dref)
		{
		  switch (flg_operand->name[0])
		    {
		    case 'b':
		      info->data_size = 1;
		      break;
		    case 'h':
		    case 'w':
		      info->data_size = 2;
		      break;
		    default:
		      info->data_size = 4;
		      break;
		    }
		}
	      if (flg_operand->name[0] == 'd'
		  && flg_operand->name[1] == 0)
		info->branch_delay_insns = 1;

	      /* Check if it is a conditional flag.  */
	      if (cl_flags->flag_class & F_CLASS_COND)
		{
		  if (info->insn_type == dis_jsr)
		    info->insn_type = dis_condjsr;
		  else if (info->insn_type == dis_branch)
		    info->insn_type = dis_condbranch;
		}

	      (*info->fprintf_func) (info->stream, "%s", flg_operand->name);
	    }
	}
    }
}

static const char *
get_auxreg (const struct arc_opcode *opcode,
	    int value,
	    unsigned isa_mask)
{
  const char *name;
  unsigned int i;
  const struct arc_aux_reg *auxr = &arc_aux_regs[0];

  if (opcode->insn_class != AUXREG)
    return NULL;

  name = arcExtMap_auxRegName (value);
  if (name)
    return name;

  for (i = 0; i < arc_num_aux_regs; i++, auxr++)
    {
      if (!(auxr->cpu & isa_mask))
	continue;

      if (auxr->subclass != NONE)
	return NULL;

      if (auxr->address == value)
	return auxr->name;
    }
  return NULL;
}

/* Convert a value representing an address type to a string used to refer to
   the address type in assembly code.  */

static const char *
get_addrtype (int value)
{
  if (value < 0 || value > addrtypenames_max)
    return addrtypeunknown;

  return addrtypenames[value];
}

/* Calculate the instruction length for an instruction starting with MSB
   and LSB, the most and least significant byte.  The ISA_MASK is used to
   filter the instructions considered to only those that are part of the
   current architecture.

   The instruction lengths are calculated from the ARC_OPCODE table, and
   cached for later use.  */

static unsigned int
arc_insn_length (bfd_byte msb, bfd_byte lsb, struct disassemble_info *info)
{
  bfd_byte major_opcode = msb >> 3;

  switch (info->mach)
    {
    case bfd_mach_arc_arc700:
      /* The nps400 extension set requires this special casing of the
	 instruction length calculation.  Right now this is not causing any
	 problems as none of the known extensions overlap in opcode space,
	 but, if they ever do then we might need to start carrying
	 information around in the elf about which extensions are in use.  */
      if (major_opcode == 0xb)
        {
          bfd_byte minor_opcode = lsb & 0x1f;

          if (minor_opcode < 4)
            return 2;
        }
      /* Fall through.  */
    case bfd_mach_arc_arc600:
      return (major_opcode > 0xb) ? 2 : 4;
      break;

    case bfd_mach_arc_arcv2:
      return (major_opcode > 0x7) ? 2 : 4;
      break;

    default:
      abort ();
    }
}

/* Extract and return the value of OPERAND from the instruction whose value
   is held in the array INSN.  */

static int
extract_operand_value (const struct arc_operand *operand, unsigned *insn)
{
  int value;

  /* Read the limm operand, if required.  */
  if (operand->flags & ARC_OPERAND_LIMM)
    /* The second part of the instruction value will have been loaded as
       part of the find_format call made earlier.  */
    value = insn[1];
  else
    {
      if (operand->extract)
        value = (*operand->extract) (insn[0], (int *) NULL);
      else
        {
          if (operand->flags & ARC_OPERAND_ALIGNED32)
            {
              value = (insn[0] >> operand->shift)
                & ((1 << (operand->bits - 2)) - 1);
              value = value << 2;
            }
          else
            {
              value = (insn[0] >> operand->shift) & ((1 << operand->bits) - 1);
            }
          if (operand->flags & ARC_OPERAND_SIGNED)
            {
              int signbit = 1 << (operand->bits - 1);
              value = (value ^ signbit) - signbit;
            }
        }
    }

  return value;
}

/* Find the next operand, and the operands value from ITER.  Return TRUE if
   there is another operand, otherwise return FALSE.  If there is an
   operand returned then the operand is placed into OPERAND, and the value
   into VALUE.  If there is no operand returned then OPERAND and VALUE are
   unchanged.  */

static bfd_boolean
operand_iterator_next (struct arc_operand_iterator *iter,
                       const struct arc_operand **operand,
                       int *value)
{
  if (iter->mode == OPERAND_ITERATOR_STANDARD)
    {
      if (*iter->state.standard.opidx == 0)
        {
          *operand = NULL;
          return FALSE;
        }

      *operand = &arc_operands[*iter->state.standard.opidx];
      *value = extract_operand_value (*operand, iter->insn);
      iter->state.standard.opidx++;
    }
  else
    {
      const struct arc_operand *operand_base, *operand_limm;
      int value_base, value_limm;

      if (*iter->state.long_insn.opidx_limm == 0)
        {
          *operand = NULL;
          return FALSE;
        }

      operand_base = &arc_operands[*iter->state.long_insn.opidx_base];
      operand_limm = &arc_operands[*iter->state.long_insn.opidx_limm];

      if (operand_base->flags & ARC_OPERAND_LIMM)
        {
          /* We've reached the end of the operand list.  */
          *operand = NULL;
          return FALSE;
        }

      value_base = value_limm = 0;
      if (!(operand_limm->flags & ARC_OPERAND_IGNORE))
        {
          /* This should never happen.  If it does then the use of
             extract_operand_value below will access memory beyond
             the insn array.  */
          assert ((operand_limm->flags & ARC_OPERAND_LIMM) == 0);

          *operand = operand_limm;
          value_limm = extract_operand_value (*operand, &iter->insn[1]);
        }

      if (!(operand_base->flags & ARC_OPERAND_IGNORE))
        {
          *operand = operand_base;
          value_base = extract_operand_value (*operand, iter->insn);
        }

      /* This is a bit of a fudge.  There's no reason why simply ORing
         together the two values is the right thing to do, however, for all
         the cases we currently have, it is the right thing, so, for now,
         I've put off solving the more complex problem.  */
      *value = value_base | value_limm;

      iter->state.long_insn.opidx_base++;
      iter->state.long_insn.opidx_limm++;
    }
  return TRUE;
}

/* Helper for parsing the options.  */

static void
parse_option (char *option)
{
  if (CONST_STRNEQ (option, "dsp"))
    add_to_decodelist (DSP, NONE);

  else if (CONST_STRNEQ (option, "spfp"))
    add_to_decodelist (FLOAT, SPX);

  else if (CONST_STRNEQ (option, "dpfp"))
    add_to_decodelist (FLOAT, DPX);

  else if (CONST_STRNEQ (option, "quarkse_em"))
    {
      add_to_decodelist (FLOAT, DPX);
      add_to_decodelist (FLOAT, SPX);
      add_to_decodelist (FLOAT, QUARKSE);
    }

  else if (CONST_STRNEQ (option, "quarkse2_em"))
    {
      add_to_decodelist (DSP, NONE);
      add_to_decodelist (FLOAT, DPA);
      add_to_decodelist (FLOAT, SP);
      add_to_decodelist (FLOAT, CVT);
      add_to_decodelist (FLOAT, QUARKSE);
    }

  else if (CONST_STRNEQ (option, "fpuda"))
    add_to_decodelist (FLOAT, DPA);

  else if (CONST_STRNEQ (option, "fpus"))
    {
      add_to_decodelist (FLOAT, SP);
      add_to_decodelist (FLOAT, CVT);
    }

  else if (CONST_STRNEQ (option, "fpud"))
    {
      add_to_decodelist (FLOAT, DP);
      add_to_decodelist (FLOAT, CVT);
    }
  else
    fprintf (stderr, _("Unrecognised disassembler option: %s\n"), option);
}

/* Go over the options list and parse it.  */

static void
parse_disassembler_options (char *options)
{
  if (options == NULL)
    return;

  while (*options)
    {
      /* Skip empty options.  */
      if (*options == ',')
	{
	  ++ options;
	  continue;
	}

      parse_option (options);

      while (*options != ',' && *options != '\0')
	++ options;
    }
}

/* Disassemble ARC instructions.  */

static int
print_insn_arc (bfd_vma memaddr,
		struct disassemble_info *info)
{
  bfd_byte buffer[4];
  unsigned int lowbyte, highbyte;
  int status;
  unsigned int insn_len;
  unsigned insn[2] = { 0, 0 };
  unsigned isa_mask;
  const struct arc_opcode *opcode;
  bfd_boolean need_comma;
  bfd_boolean open_braket;
  int size;
  const struct arc_operand *operand;
  int value;
  struct arc_operand_iterator iter;
  Elf_Internal_Ehdr *header = NULL;

  if (info->disassembler_options)
    {
      parse_disassembler_options (info->disassembler_options);

      /* Avoid repeated parsing of the options.  */
      info->disassembler_options = NULL;
    }

  memset (&iter, 0, sizeof (iter));
  lowbyte  = ((info->endian == BFD_ENDIAN_LITTLE) ? 1 : 0);
  highbyte = ((info->endian == BFD_ENDIAN_LITTLE) ? 0 : 1);

  if (info->section && info->section->owner)
    header = elf_elfheader (info->section->owner);

  switch (info->mach)
    {
    case bfd_mach_arc_arc700:
      isa_mask = ARC_OPCODE_ARC700;
      break;

    case bfd_mach_arc_arc600:
      isa_mask = ARC_OPCODE_ARC600;
      break;

    case bfd_mach_arc_arcv2:
    default:
      isa_mask = ARC_OPCODE_ARCv2EM;
      /* TODO: Perhaps remove defitinion of header since it is only used at
         this location.  */
      if (header != NULL
	  && (header->e_flags & EF_ARC_MACH_MSK) == EF_ARC_CPU_ARCV2HS)
	{
	  isa_mask = ARC_OPCODE_ARCv2HS;
	  /* FPU instructions are not extensions for HS.  */
	  add_to_decodelist (FLOAT, SP);
	  add_to_decodelist (FLOAT, DP);
	  add_to_decodelist (FLOAT, CVT);
	}
      break;
    }

  /* This variable may be set by the instruction decoder.  It suggests
     the number of bytes objdump should display on a single line.  If
     the instruction decoder sets this, it should always set it to
     the same value in order to get reasonable looking output.  */

  info->bytes_per_line  = 8;

  /* In the next lines, we set two info variables control the way
     objdump displays the raw data.  For example, if bytes_per_line is
     8 and bytes_per_chunk is 4, the output will look like this:
     00:   00000000 00000000
     with the chunks displayed according to "display_endian".  */

  if (info->section
      && !(info->section->flags & SEC_CODE))
    {
      /* This is not a CODE section.  */
      switch (info->section->size)
	{
	case 1:
	case 2:
	case 4:
	  size = info->section->size;
	  break;
	default:
	  size = (info->section->size & 0x01) ? 1 : 4;
	  break;
	}
      info->bytes_per_chunk = 1;
      info->display_endian = info->endian;
    }
  else
    {
      size = 2;
      info->bytes_per_chunk = 2;
      info->display_endian = info->endian;
    }

  /* Read the insn into a host word.  */
  status = (*info->read_memory_func) (memaddr, buffer, size, info);
  if (status != 0)
    {
      (*info->memory_error_func) (status, memaddr, info);
      return -1;
    }

  if (info->section
      && !(info->section->flags & SEC_CODE))
    {
      /* Data section.  */
      unsigned long data;

      data = bfd_get_bits (buffer, size * 8,
			   info->display_endian == BFD_ENDIAN_BIG);
      switch (size)
	{
	case 1:
	  (*info->fprintf_func) (info->stream, ".byte\t0x%02lx", data);
	  break;
	case 2:
	  (*info->fprintf_func) (info->stream, ".short\t0x%04lx", data);
	  break;
	case 4:
	  (*info->fprintf_func) (info->stream, ".word\t0x%08lx", data);
	  break;
	default:
	  abort ();
	}
      return size;
    }

  insn_len = arc_insn_length (buffer[lowbyte], buffer[highbyte], info);
  pr_debug ("instruction length = %d bytes\n", insn_len);

  switch (insn_len)
    {
    case 2:
      insn[0] = (buffer[lowbyte] << 8) | buffer[highbyte];
      break;

    default:
      /* An unknown instruction is treated as being length 4.  This is
         possibly not the best solution, but matches the behaviour that was
         in place before the table based instruction length look-up was
         introduced.  */
    case 4:
      /* This is a long instruction: Read the remaning 2 bytes.  */
      status = (*info->read_memory_func) (memaddr + 2, &buffer[2], 2, info);
      if (status != 0)
	{
	  (*info->memory_error_func) (status, memaddr + 2, info);
	  return -1;
	}
      insn[0] = ARRANGE_ENDIAN (info, buffer);
      break;
    }

  /* Set some defaults for the insn info.  */
  info->insn_info_valid    = 1;
  info->branch_delay_insns = 0;
  info->data_size	   = 0;
  info->insn_type	   = dis_nonbranch;
  info->target		   = 0;
  info->target2		   = 0;

  /* FIXME to be moved in dissasemble_init_for_target.  */
  info->disassembler_needs_relocs = TRUE;

  /* Find the first match in the opcode table.  */
  if (!find_format (memaddr, insn, &insn_len, isa_mask, info, &opcode, &iter))
    return -1;

  if (!opcode)
    {
      if (insn_len == 2)
        (*info->fprintf_func) (info->stream, ".long %#04x", insn[0]);
      else
        (*info->fprintf_func) (info->stream, ".long %#08x", insn[0]);

      info->insn_type = dis_noninsn;
      return insn_len;
    }

  /* Print the mnemonic.  */
  (*info->fprintf_func) (info->stream, "%s", opcode->name);

  /* Preselect the insn class.  */
  switch (opcode->insn_class)
    {
    case BRANCH:
    case JUMP:
      if (!strncmp (opcode->name, "bl", 2)
	  || !strncmp (opcode->name, "jl", 2))
	{
	  if (opcode->subclass == COND)
	    info->insn_type = dis_condjsr;
	  else
	    info->insn_type = dis_jsr;
	}
      else
	{
	  if (opcode->subclass == COND)
	    info->insn_type = dis_condbranch;
	  else
	    info->insn_type = dis_branch;
	}
      break;
    case LOAD:
    case STORE:
    case MEMORY:
      info->insn_type = dis_dref;
      break;
    default:
      info->insn_type = dis_nonbranch;
      break;
    }

  pr_debug ("%s: 0x%08x\n", opcode->name, opcode->opcode);

  print_flags (opcode, insn, info);

  if (opcode->operands[0] != 0)
    (*info->fprintf_func) (info->stream, "\t");

  need_comma = FALSE;
  open_braket = FALSE;

  /* Now extract and print the operands.  */
  operand = NULL;
  while (operand_iterator_next (&iter, &operand, &value))
    {
      if (open_braket && (operand->flags & ARC_OPERAND_BRAKET))
	{
	  (*info->fprintf_func) (info->stream, "]");
	  open_braket = FALSE;
	  continue;
	}

      /* Only take input from real operands.  */
      if (ARC_OPERAND_IS_FAKE (operand))
	continue;

      if ((operand->flags & ARC_OPERAND_IGNORE)
	  && (operand->flags & ARC_OPERAND_IR)
          && value == -1)
	continue;

      if (operand->flags & ARC_OPERAND_COLON)
        {
          (*info->fprintf_func) (info->stream, ":");
          continue;
        }

      if (need_comma)
	(*info->fprintf_func) (info->stream, ",");

      if (!open_braket && (operand->flags & ARC_OPERAND_BRAKET))
	{
	  (*info->fprintf_func) (info->stream, "[");
	  open_braket = TRUE;
	  need_comma = FALSE;
	  continue;
	}

      need_comma = TRUE;

      /* Print the operand as directed by the flags.  */
      if (operand->flags & ARC_OPERAND_IR)
	{
	  const char *rname;

	  assert (value >=0 && value < 64);
	  rname = arcExtMap_coreRegName (value);
	  if (!rname)
	    rname = regnames[value];
	  (*info->fprintf_func) (info->stream, "%s", rname);
	  if (operand->flags & ARC_OPERAND_TRUNCATE)
	    {
	      rname = arcExtMap_coreRegName (value + 1);
	      if (!rname)
		rname = regnames[value + 1];
	      (*info->fprintf_func) (info->stream, "%s", rname);
	    }
	}
      else if (operand->flags & ARC_OPERAND_LIMM)
	{
	  const char *rname = get_auxreg (opcode, value, isa_mask);

	  if (rname && open_braket)
	    (*info->fprintf_func) (info->stream, "%s", rname);
	  else
	    {
	      (*info->fprintf_func) (info->stream, "%#x", value);
	      if (info->insn_type == dis_branch
		  || info->insn_type == dis_jsr)
		info->target = (bfd_vma) value;
	    }
	}
      else if (operand->flags & ARC_OPERAND_PCREL)
	{
	   /* PCL relative.  */
	  if (info->flags & INSN_HAS_RELOC)
	    memaddr = 0;
	  (*info->print_address_func) ((memaddr & ~3) + value, info);

	  info->target = (bfd_vma) (memaddr & ~3) + value;
	}
      else if (operand->flags & ARC_OPERAND_SIGNED)
	{
	  const char *rname = get_auxreg (opcode, value, isa_mask);
	  if (rname && open_braket)
	    (*info->fprintf_func) (info->stream, "%s", rname);
	  else
	    (*info->fprintf_func) (info->stream, "%d", value);
	}
      else if (operand->flags & ARC_OPERAND_ADDRTYPE)
        {
          const char *addrtype = get_addrtype (value);
          (*info->fprintf_func) (info->stream, "%s", addrtype);
          /* A colon follow an address type.  */
          need_comma = FALSE;
        }
      else
	{
	  if (operand->flags & ARC_OPERAND_TRUNCATE
	      && !(operand->flags & ARC_OPERAND_ALIGNED32)
	      && !(operand->flags & ARC_OPERAND_ALIGNED16)
	      && value > 0 && value <= 14)
	    (*info->fprintf_func) (info->stream, "r13-%s",
				   regnames[13 + value - 1]);
	  else
	    {
	      const char *rname = get_auxreg (opcode, value, isa_mask);
	      if (rname && open_braket)
		(*info->fprintf_func) (info->stream, "%s", rname);
	      else
		(*info->fprintf_func) (info->stream, "%#x", value);
	    }
	}
    }

  /* Assign arc_opcode as a private data of disassemble_info to be used by
     arc_insn_decode().  */
  info->private_data = (void *) opcode;

  return insn_len;
}


disassembler_ftype
arc_get_disassembler (bfd *abfd)
{
  /* BFD my be absent, if opcodes is invoked from the debugger that
     has connected to remote target and doesn't have an ELF file.  */
  if (abfd != NULL)
    {
      /* Read the extension insns and registers, if any.  */
      build_ARC_extmap (abfd);
#ifdef DEBUG
      dump_ARC_extmap ();
#endif
    }

  return print_insn_arc;
}

/* Disassemble ARC instructions.  Used by debugger.  */

struct arcDisState
arcAnalyzeInstr (bfd_vma memaddr,
		 struct disassemble_info *info)
{
  struct arcDisState ret;
  memset (&ret, 0, sizeof (struct arcDisState));

  ret.instructionLen = print_insn_arc (memaddr, info);

#if 0
  ret.words[0] = insn[0];
  ret.words[1] = insn[1];
  ret._this = &ret;
  ret.coreRegName = _coreRegName;
  ret.auxRegName = _auxRegName;
  ret.condCodeName = _condCodeName;
  ret.instName = _instName;
#endif

  return ret;
}

void
print_arc_disassembler_options (FILE *stream)
{
  fprintf (stream, _("\n\
The following ARC specific disassembler options are supported for use \n\
with -M switch (multiple options should be separated by commas):\n"));

  fprintf (stream, _("\
  dsp             Recognize DSP instructions.\n"));
  fprintf (stream, _("\
  spfp            Recognize FPX SP instructions.\n"));
  fprintf (stream, _("\
  dpfp            Recognize FPX DP instructions.\n"));
  fprintf (stream, _("\
  quarkse_em      Recognize FPU QuarkSE-EM instructions.\n"));
  fprintf (stream, _("\
  quarkse2_em     Recognize FPU QuarkSE2-EM instructions.\n"));
  fprintf (stream, _("\
  fpuda           Recognize double assist FPU instructions.\n"));
  fprintf (stream, _("\
  fpus            Recognize single precision FPU instructions.\n"));
  fprintf (stream, _("\
  fpud            Recognize double precision FPU instructions.\n"));
}

/* Read instruction as-is from memory.  This reads only instruction, without
   LIMM.  Returned value will be in converted encoding.  */

static unsigned long
read_instruction (bfd_vma addr, unsigned int length,
		  struct disassemble_info *info)
{
  bfd_byte buffer[4];

  /* This function, as used by the arc_insn_decode is always called after same
     memory has been already read by print_insn_arc, so it seems unlikely that
     we can land here when it is not possible to read memory from this address,
     so return value of read_memory_func is ignored.  */
  info->read_memory_func (addr, buffer, length, info);

  if (length == 2)
    {
      unsigned int lowbyte = (info->endian == BFD_ENDIAN_LITTLE) ? 1 : 0;
      unsigned int highbyte = (info->endian == BFD_ENDIAN_LITTLE) ? 0 : 1;
      return (buffer[lowbyte] << 8) | buffer[highbyte];
    }

  return ARRANGE_ENDIAN (info, buffer);
}

/* Identify instruction subopcodes.  In ARC ISA opcodes are always 5 most
   significant bits: 27-31 for 32-bit instructions, 11-15 for 16-bit
   instructions.  Subopcodes, however are not very unified - there lots of
   various formats; depending on opcode, subopcode may appear at different
   locations in instruction or may not be present at all.  On top of that many
   subopcodes have subopcodes of their own.  Subopcode hierarhy is not always
   symmetric, for example for [opcode=0x01 subopcode1=0x0] there is also
   subopcode2, but for [opcode=0x01 subopcode1=0x1] there is subopcode2 and
   subopcode3.  Perhaps, the most complex example are 16-bite stack based
   operations with opcode 0x18.  Bits 5-7 contain subopcode1.  Subopcodes 0x0,
   0x1, 0x2, 0x3 and 0x4 don't have any further subopcodes.  Subopcode1=0x5 has
   an additional subopcode2 at the bit 8 (bits 9 and 10 are always zero).  And
   subopcodes1 0x6 and 0x7 contain their subopcode2 at the bit 0.  And if and
   only if subopcode2 is 0x1, then bits 1-4 are also a subopcode3.  */

static void
set_insn_subopcodes (struct arc_instruction *insn)
{
  /* Find subopcode.  */
  switch (insn->opcode)
    {
    case 0x00:
      insn->subopcode1 = BITS (insn->raw_word, 16, 16);
      break;
    case 0x01:
      insn->subopcode1 = BITS (insn->raw_word, 16, 16);
      if (insn->subopcode1 == 0x1)
	{
	  insn->subopcode2 = BITS (insn->raw_word, 4, 4);
	  insn->subopcode3 = BITS (insn->raw_word, 0, 3);
	}
      else
	{
	  insn->subopcode2 = BITS (insn->raw_word, 17, 17);
	}
      break;
    /* No subopcodes for 0x02 - 0x03.  */
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x07:
      insn->subopcode1 = BITS (insn->raw_word, 16, 21);
      if (insn->subopcode1 == 0x2F)
	{
	  insn->subopcode2 = BITS (insn->raw_word, 0, 5);
	  if (insn->subopcode2 == 0x3F)
	    insn->subopcode3 = BITS (insn->raw_word, 12, 14) << 3
	      | BITS (insn->raw_word, 24, 26);
	}
      break;
    case 0x08:
      insn->subopcode1 = BITS (insn->raw_word, 2, 2);
      break;
    case 0x09:
    case 0x0A:
      insn->subopcode1 = BITS (insn->raw_word, 3, 3);
      if (insn->subopcode1 == 0x0)
	insn->subopcode1 = BITS (insn->raw_word, 3, 4);
      break;
    case 0x0B:
      insn->subopcode1 = BITS (insn->raw_word, 10, 10);
      break;
    case 0x0C:
    case 0x0D:
      insn->subopcode1 = BITS (insn->raw_word, 3, 4);
      break;
    case 0x0E:
      insn->subopcode1 = BITS (insn->raw_word, 2, 4);
      break;
    case 0x0F:
      insn->subopcode1 = BITS (insn->raw_word, 0, 4);
      if (insn->subopcode1 == 0x0)
	{
	  insn->subopcode2 = BITS (insn->raw_word, 5, 7);
	  if (insn->subopcode2 == 0x7)
	    {
	      insn->subopcode3 = BITS (insn->raw_word, 8, 10);
	      if (insn->subopcode3 == 0x4)
		insn->condition_code = ARC_CC_EQ;
	      else if (insn->subopcode3 == 0x5)
		insn->condition_code = ARC_CC_NE;
	    }
	}
      break;
    /* No subopcodes for 0x10 - 0x16.  */
    case 0x17:
    case 0x18:
      insn->subopcode1 = BITS (insn->raw_word, 5, 7);
      /* PRM doesn't put this clearly, but 0x18 has subopcode2.  */
      switch (insn->subopcode1)
	{
	case 0x5:
	  /* ADD_S SP,SP,u7 and SUB_S SP,SP,u7.  */
	  insn->subopcode2 = BITS (insn->raw_word, 8, 8);
	  break;
	case 0x6:
	case 0x7:
	  /* PUSH_S, POP_S, LEAVE_S, ENTER_S.  */
	  insn->subopcode2 = BITS (insn->raw_word, 0, 0);
	  /* If bit 0 is 0, then it is LEAVE_S, ENTER_S.  Otherwise subopcode
	     should be expanded further.  */
	  if (insn->subopcode2 != 0x0)
	    insn->subopcode2 = BITS (insn->raw_word, 0, 4);
	  break;
	}
      break;
    case 0x19:
      insn->subopcode1 = BITS (insn->raw_word, 9, 10);
      break;
    /* No subopcodes for 0x1A - 0x1B.  */
    case 0x1C:
      insn->subopcode1 = BITS (insn->raw_word, 7, 7);
      break;
    case 0x1D:
      insn->subopcode1 = BITS (insn->raw_word, 7, 7);
      insn->condition_code = (insn->subopcode1 == 0x0 ? ARC_CC_EQ : ARC_CC_NE);
      break;
    case 0x1E:
      /* B_S, BEQ_S, BNE_S, Bcc_S.  */
      insn->subopcode1 = BITS (insn->raw_word, 9, 10);
      switch (insn->subopcode1)
	{
	case 0x1:
	  insn->condition_code = ARC_CC_EQ;
	  break;
	case 0x2:
	  insn->condition_code = ARC_CC_NE;
	  break;
	case 0x3:
	  /* Bcc_S  */
	  insn->subopcode2 = BITS (insn->raw_word, 6, 8);
	  /* In this case subopcode2 is the condition code.  */
	  switch (insn->subopcode2)
	    {
	    case 0x0:
	      insn->condition_code = ARC_CC_GT;
	      break;
	    case 0x1:
	      insn->condition_code = ARC_CC_GE;
	      break;
	    case 0x2:
	      insn->condition_code = ARC_CC_LT;
	      break;
	    case 0x3:
	      insn->condition_code = ARC_CC_LE;
	      break;
	    case 0x4:
	      insn->condition_code = ARC_CC_HI;
	      break;
	    case 0x5:
	      insn->condition_code = ARC_CC_HS;
	      break;
	    case 0x6:
	      insn->condition_code = ARC_CC_LO;
	      break;
	    case 0x7:
	      insn->condition_code = ARC_CC_LS;
	      break;
	    }
	  break;
	}
      break;
    /* No subopcodes for 0x1F.  */
    }
}

/* Parse various instruction flags that are not part of the opcode/subopcode.
   This is mainly memory ops parameters - data size and register writeback.
   Another instruction flag is a condition code.  Note, however, that in case
   of BRcc instructions disassembler doesn't set respective flags, so instead
   insn->condition_code is set based on subopcode and that is done in
   set_insn_subopcodes.  */

static void
set_insn_flags (struct arc_instruction *insn, const struct arc_opcode *opcode)
{
  const unsigned char *flag_index;

  for (flag_index = opcode->flags; *flag_index; flag_index++)
    {
      const struct arc_flag_class *flag_class
	= &arc_flag_classes[*flag_index];
      const unsigned int *flag_operand_index;

      for (flag_operand_index = flag_class->flags; *flag_operand_index;
	   flag_operand_index++)
	{
	  const struct arc_flag_operand *flag_operand
	    = &arc_flag_operands[*flag_operand_index];
	  unsigned int value;

	  if (!flag_operand->favail)
	    continue;

	  value = ((insn->raw_word >> flag_operand->shift)
		   & ((1 << flag_operand->bits) - 1));
	  if (flag_operand->code == value)
	    {
	      switch (flag_operand->name[0])
		{
		case 'a':
		  /* Address writeback mode.  */
		  insn->writeback_mode = (enum arc_ldst_writeback_mode) value;
		  break;
		case 'b':
		case 'h':
		case 'w':
		  /* Data size mode.  */
		  insn->data_size_mode = (enum arc_ldst_data_size) value;
		  break;
		}

	      /* Condition codes, which are mostly several characters.  */
	      if (0 == strcmp (flag_operand->name, "eq")
		  || 0 == strcmp (flag_operand->name, "z"))
		insn->condition_code = ARC_CC_EQ;
	      else if (0 == strcmp (flag_operand->name, "ne")
		       || 0 == strcmp (flag_operand->name, "nz"))
		insn->condition_code = ARC_CC_NE;
	      else if (0 == strcmp (flag_operand->name, "p")
		       || 0 == strcmp (flag_operand->name, "pl"))
		insn->condition_code = ARC_CC_PL;
	      else if (0 == strcmp (flag_operand->name, "n")
		       || 0 == strcmp (flag_operand->name, "mi"))
		insn->condition_code = ARC_CC_MI;
	      else if (0 == strcmp (flag_operand->name, "c")
		       || 0 == strcmp (flag_operand->name, "cs")
		       || 0 == strcmp (flag_operand->name, "lo"))
		insn->condition_code = ARC_CC_CS;
	      else if (0 == strcmp (flag_operand->name, "cc")
		       || 0 == strcmp (flag_operand->name, "nc")
		       || 0 == strcmp (flag_operand->name, "hs"))
		insn->condition_code = ARC_CC_CC;
	      else if (0 == strcmp (flag_operand->name, "vs")
		       || 0 == strcmp (flag_operand->name, "v"))
		insn->condition_code = ARC_CC_VS;
	      else if (0 == strcmp (flag_operand->name, "nv")
		       || 0 == strcmp (flag_operand->name, "vc"))
		insn->condition_code = ARC_CC_NV;
	      else if (0 == strcmp (flag_operand->name, "gt"))
		insn->condition_code = ARC_CC_GT;
	      else if (0 == strcmp (flag_operand->name, "ge"))
		insn->condition_code = ARC_CC_GE;
	      else if (0 == strcmp (flag_operand->name, "lt"))
		insn->condition_code = ARC_CC_LT;
	      else if (0 == strcmp (flag_operand->name, "le"))
		insn->condition_code = ARC_CC_LE;
	      else if (0 == strcmp (flag_operand->name, "hi"))
		insn->condition_code = ARC_CC_HI;
	      else if (0 == strcmp (flag_operand->name, "ls"))
		insn->condition_code = ARC_CC_LS;
	      else if (0 == strcmp (flag_operand->name, "pnz"))
		insn->condition_code = ARC_CC_PNZ;
	    }
	}
    }

  /* Disassembler doesn't set data size flags for some instructions - instead
     each "data size" variation is a separate instruction.  */
  if (arc_insn_match_op (insn, 0x03))
    insn->data_size_mode
      = (enum arc_ldst_data_size) BITS (insn->raw_word, 1, 2);
  else if (arc_insn_match_op (insn, 0x15))
    insn->data_size_mode = ARC_SCALING_B;
  else if (arc_insn_match_op (insn, 0x16))
    insn->data_size_mode = ARC_SCALING_H;
  else if (arc_insn_match_subop1 (insn, 0x18, 3))
    insn->data_size_mode = ARC_SCALING_B;

  /* Opcodes disassembler doesn't set writeback flags for POP_S and PUSH_S.  */
  if (arc_insn_is_push_s (insn))
    insn->writeback_mode = ARC_WRITEBACK_AW;
  else if (arc_insn_is_pop_s (insn))
    insn->writeback_mode = ARC_WRITEBACK_AB;
}

static void
set_insn_operands (struct arc_instruction *insn,
		   const struct arc_opcode *opcode)
{
  unsigned int cur_operand_index;
  const unsigned char *opindex;
  for (opindex = opcode->operands, cur_operand_index = 0; *opindex; opindex++)
    {
      const struct arc_operand *operand = &arc_operands[*opindex];

      if (operand->flags & ARC_OPERAND_FAKE)
	continue;

      if (operand->flags & ARC_OPERAND_LIMM)
	{
	  assert (insn->limm_p);
	  insn->operands[cur_operand_index].kind = ARC_OPERAND_KIND_LIMM;
	  insn->operands[cur_operand_index].value = 63;
	}
      else
	{
	  insn->operands[cur_operand_index].value
	    = extract_operand_value (operand, (unsigned *)&(insn->raw_word));
	  insn->operands[cur_operand_index].kind
	    = (operand->flags & ARC_OPERAND_IR
	       ? ARC_OPERAND_KIND_REG
	       : ARC_OPERAND_KIND_SHIMM);
	}

      cur_operand_index += 1;
      assert (cur_operand_index <= ARC_MAX_OPERAND_COUNT);
    }
  insn->operands_count = cur_operand_index;
}

void arc_insn_decode (bfd_vma addr,
		      struct disassemble_info *info,
		      disassembler_ftype disasm_func,
		      struct arc_instruction *insn)
{
  int length_with_limm;
  const struct arc_opcode *opcode;

  /* Ensure that insn would be in the reset state.  */
  memset (insn, 0, sizeof (struct arc_instruction));

  length_with_limm = disasm_func (addr, info);

  /* There was an error when disassembling, for example memory read error.  */
  if (length_with_limm < 0)
    {
      insn->valid = FALSE;
      return;
    }

  if (length_with_limm == 2 || length_with_limm == 6)
    insn->length = 2;
  else
    insn->length = 4;

  insn->address = addr;

  /* Quick exit if memory at this address is not an instruction.  */
  if (info->insn_type == dis_noninsn)
    {
      insn->valid = FALSE;
      return;
    }

  insn->valid = TRUE;

  /* arc_opcode must be set if this is not a dis_noninsn.  */
  assert (info->private_data != NULL);

  opcode = (const struct arc_opcode *) info->private_data;
  insn->insn_class = opcode->insn_class;

  insn->raw_word = read_instruction (addr, insn->length, info);

  if (insn->length == 2)
    insn->opcode = BITS (insn->raw_word, 11, 15);
  else
    insn->opcode = BITS (insn->raw_word, 27, 31);
  set_insn_subopcodes (insn);

  /* Read LIMM if there is one.  */
  if (length_with_limm > 4)
    {
      insn->limm_value = read_instruction (addr + insn->length, 4, info);
      insn->limm_p = TRUE;
    }

  insn->is_control_flow = (info->insn_type == dis_branch
			   || info->insn_type == dis_condbranch
			   || info->insn_type == dis_jsr
			   || info->insn_type == dis_condjsr);
  /* LEAVE_S has insn type dref and MEMORY opcode class, so has to be handled
     separately.  */
  if (arc_insn_is_leave_s (insn))
    insn->is_control_flow = TRUE;

  /* ARC can have only one instruction in delay slot.  */
  assert (info->branch_delay_insns <= 1);
  insn->has_delay_slot = info->branch_delay_insns;

  set_insn_flags (insn, opcode);
  set_insn_operands (insn, opcode);
}

int
arc_insn_get_memory_base_reg (const struct arc_instruction *insn)
{
  assert (insn->insn_class == MEMORY);

  /* POP_S and PUSH_S have SP as an implicit argument in a disassembler.  */
  if (arc_insn_is_pop_s (insn) || arc_insn_is_push_s (insn))
    return 28;

  /* Other instructions all have at least two operands: operand 0 is data,
     operand 1 is address.  Operand 2 is offset from address.  However, see
     comment to operands_count - in some cases, third operand may be missing,
     if it is 0.  */
  assert (insn->operands_count >= 2);
  return insn->operands[1].value;
}

bfd_vma
arc_insn_get_memory_offset (const struct arc_instruction *insn)
{
  bfd_vma value;
  assert (insn->insn_class == MEMORY);

  /* POP_S and PUSH_S have offset as an implicit argument in a
     disassembler.  */
  if (arc_insn_is_pop_s (insn))
    return 4;
  else if (arc_insn_is_push_s (insn))
    return -4;

  /* Other instructions all have at least two operands: operand 0 is data,
     operand 1 is address.  Operand 2 is offset from address.  However, see
     comment to operands_count - in some cases, third operand may be missing,
     if it is 0.  */
  if (insn->operands_count < 3)
    return 0;

  assert (insn->operands[2].kind != ARC_OPERAND_KIND_REG);
  value = (insn->operands[2].kind == ARC_OPERAND_KIND_LIMM
	   ? insn->limm_value
	   : insn->operands[2].value);

  /* Handle scaling.  */
  if (insn->writeback_mode == ARC_WRITEBACK_AS)
    {
      /* Byte data size is not valid for AS.  Halfword means shift by 1 bit.
	 Word and double word means shift by 2 bits.  */
      assert (insn->data_size_mode != ARC_SCALING_B);
      if (insn->data_size_mode == ARC_SCALING_H)
	value <<= 1;
      else
	value <<= 2;
    }
  return value;
}


/* Local variables:
   eval: (c-set-style "gnu")
   indent-tabs-mode: t
   End:  */
