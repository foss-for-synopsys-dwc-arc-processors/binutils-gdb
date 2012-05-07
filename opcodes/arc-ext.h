/* ARC target-dependent stuff. Extension data structures.
   Copyright 1995, 1997, 2000, 2001, 2005 Free Software Foundation, Inc.
   Copyright 20007 ARC International (UK) LTD

This file is part of GDB.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.  */

#ifndef ARCEXT_H
#define ARCEXT_H


enum { INST_HASH_BITS = 6 };
enum {NUM_EXT_CORE = 59-32+1};
enum {NUM_EXT_COND = 0x1f-0x10+1};

enum { INST_HASH_SIZE = 1 << INST_HASH_BITS };
#define INST_HASH(MAJOR,MINOR) \
  ((((MAJOR) << 3) ^ (MINOR)) & ((INST_HASH_SIZE) - 1))

enum ExtOperType
  {
    EXT_INSTRUCTION = 0,
    EXT_CORE_REGISTER = 1,
    EXT_AUX_REGISTER = 2,
    EXT_COND_CODE = 3,
    EXT_INSTRUCTION32 = 4,
    EXT_AC_INSTRUCTION = 4 ,
    EXT_REMOVE_CORE_REG = 5,
    EXT_LONG_CORE_REGISTER = 6,
    EXT_AUX_REGISTER_EXTENDED = 7,
    EXT_INSTRUCTION32_EXTENDED = 8,
    EXT_CORE_REGISTER_CLASS = 9
  };

/* Define this if we do not want to encode instructions based on the
   ARCompact Programmer's Reference.  */
#define UNMANGLED

struct ExtInstruction
{
  char major;
  char minor;
  char flags;
  char *name;
  struct ExtInstruction *next;
};

struct ExtAuxRegister
{
  long address;
  char *name;
  struct ExtAuxRegister *next;
};

enum ExtReadWrite
  {
    REG_INVALID,
    REG_READ,
    REG_WRITE,
    REG_READWRITE
  };

struct ExtCoreRegister
{
  short number;
  enum ExtReadWrite rw;
  char *name;
};

struct arcExtMap
{
  struct ExtAuxRegister *auxRegisters;
  struct ExtInstruction *instructions[INST_HASH_SIZE];
  struct ExtCoreRegister coreRegisters[NUM_EXT_CORE];
  char *condCodes[NUM_EXT_COND];
};

extern int arcExtMap_add(void*, unsigned long);
extern enum ExtReadWrite arcExtMap_coreReadWrite (int);
extern const char *arcExtMap_coreRegName(int);
extern const char *arcExtMap_auxRegName(long);
extern const char *arcExtMap_condCodeName(int);
extern const char *arcExtMap_instName(int, int, int*);

/* Ravi:
   warning: implicit declaration of function `build_ARC_extmap'
*/
extern void build_ARC_extmap (bfd *);


#define IGNORE_FIRST_OPD 1

#endif /* __arcExtMap_h__ */
