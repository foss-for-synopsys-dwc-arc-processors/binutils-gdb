/* Target dependent code for ARC processor family, for GDB, the GNU debugger.

   Copyright 2009 Free Software Foundation, Inc.
   Copyright 2009-2012 Synopsys Inc.

   Contributed by ARC International (www.arc.com), now part of Synopsys Inc.

   Author:
      Richard Stuckey <richard.stuckey@arc.com>

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
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  
*/

/******************************************************************************/
/*                                                                            */
/* Outline:                                                                   */
/*     This module implements facilities for intercepting I/O (and other)     */
/*     operations attempted on a JTAG target and performing them on the host, */
/*     using a RPC (Remote Procedure Call) mechanism.                         */
/*                                                                            */
/* Mechanism:                                                                 */
/*     When interception is enabled, this module sets a breakpoint at the     */
/*     entry point of each operation which is to be intercepted; it finds the */
/*     entry points of named routines in the C runtime library code by using  */
/*     gdb's symbol lookup facilities.                                        */
/*                                                                            */
/*     When a breakpoint is triggered on the target, the target monitoring    */
/*     loop calls the function 'arc_check_interception_breakpoint' to check   */
/*     whether the breakpoint triggered is an interception breakpoint; this   */
/*     function will return a code indicating either                          */
/*                                                                            */
/*       a) the breakpoint is an interception breakpoint, the interception    */
/*          has been performed and execution of the target program should be  */
/*          resumed; or                                                       */
/*                                                                            */
/*       b) the breakpoint is an interception breakpoint, but the intercepted */
/*          routine is 'exit' and execution should not be resumed; or         */
/*                                                                            */
/*       c) the breakpoint is not an interception breakpoint, so execution    */
/*          should not be resumed and the trigger should be reported to gdb.  */
/*                                                                            */
/*     In case a), this module then reads the routine's parameters from the   */
/*     target's registers, performs whatever conversions are required, and    */
/*     constructs a gdb RSP File I/O extension 'F' message which it passes to */
/*     the gdb target_fileio module, which performs the requested operation   */
/*     on the host machine.                                                   */
/*                                                                            */
/*     The target_fileio module is passed a set of operations which allow it  */
/*     to read data from target memory, write data to target memory, and      */
/*     return a result value (and possibly a error code) to the intercepted   */
/*     routine.  The result value is written into the target's R0 register;   */
/*     the error code (if any) is written into the location of the 'errno'    */
/*     variable.                                                              */
/*                                                                            */
/*     Finally, this module copies the routine return address from the BLINK  */
/*     register to the PC register - this ensures that when execution of the  */
/*     target is resumed, control returns to the code after the call to the   */
/*     intercepted routine.                                                   */
/*                                                                            */
/* Notes:                                                                     */
/*     1) the set of routines to be intercepted, and the parameters to these  */
/*        routines, is defined by a table (see below) - so it is simple to    */
/*        add more routines to the set;                                       */
/*                                                                            */
/*     2) the 'open' syscall (see man open(2)) has a 'flags' parameter which  */
/*        is a bit mask; unfortunately, the bits differ in meaning between    */
/*        the host and the elf-32 target program, so the parameter must be    */
/*        converted before it can be passed to the target_fileio module;      */
/*                                                                            */
/*     3) the 'fstat' syscall (see man fstat(2)) has an out parameter which   */
/*        is a 'struct stat' structure (i.e. the address of such a structure  */
/*        is a parameter to the syscall): the target_fileio module writes the */
/*        data of the structure to that location in target memory; however,   */
/*        the structure does not have the same layout on host and target, so  */
/*        the structure must be converted before it can be written to the     */
/*        target;                                                             */
/*                                                                            */
/*     4) the interception breakpoints are not handled by the core gdb        */
/*        breakpoint mechanism; hence, they are not listed by the 'info break'*/
/*        command, and can not be (accidentally) deleted by the user; though  */
/*        they could be handled by gdb, that would require the introduction   */
/*        of a new "invisible" breakpoint type, and hence more changes to     */
/*        supposedly generic code;                                            */
/*                                                                            */
/*     5) it would be more elegant (from one perspective) to intecept these   */
/*        operations by placing a breakpoint at the interrupt vector location */
/*        of the 'swi' (SoftWare Interrupt) handler: only one breakpoint      */
/*        would then be required, and all syscalls would be intercepted;      */
/*        however, this module would then have to simulate a "return from     */
/*        exception" in order to resume target execution, which would be more */
/*        complex than the "restart at return address" method currently used. */
/*                                                                            */
/* Restrictions:                                                              */
/*     1) this module places s/w breakpoints at the entry points; therefore,  */
/*        the mechanism will not work with programs that are loaded into read */
/*        -only memory;                                                       */
/*                                                                            */
/*     2) this mechanism will probably not work if the user sets breakpoints  */
/*        on the entry points of the intercepted routines - there will be a   */
/*        conflict!                                                           */
/*                                                                            */
/******************************************************************************/

/* system header files */
#include <stdio.h>
#include <string.h>

/* gdb header files */
#include "defs.h"
#include "symtab.h"
#include "frame.h"
#include "block.h"
#include "target-fileio.h"
#include "gdb/fileio.h"

/* ARC header files */
#include "arc-jtag-fileio.h"
#include "arc-jtag-ops.h"
#include "arc-tdep.h"
#include "arc-jtag.h"
#include "config/arc/tm-embed.h"


/* -------------------------------------------------------------------------- */
/*                               local types                                  */
/* -------------------------------------------------------------------------- */

#define MAX_SYSCALL_PARAMS    4

/* these are the intercepted routines */
typedef enum
{
    READ_CALL,
    WRITE_CALL,
    OPEN_CALL,
    CLOSE_CALL,
    LSEEK_CALL,
    FSTAT_CALL,
    GETTIMEOFDAY_CALL,
    EXIT_CALL
} SystemCall;


struct lib_function
{
    SystemCall         call;
    const char*        name;
    const char*        format;
    CORE_ADDR          entrypoint;
    Boolean            bp_is_set;
    unsigned int       param_count;
    ARC_RegisterNumber param_register[MAX_SYSCALL_PARAMS];
    gdb_byte           saved_code[BYTES_IN_WORD];
};


/* this structure defines a memory image of the 'stat' structure as it is
 * represented on the ARC target
 */
struct arc_stat
{
    ARC_Byte fst_dev    [4];
    ARC_Byte fst_ino    [4];
    ARC_Byte fst_mode   [2];
    ARC_Byte fst_nlink  [2];
    ARC_Byte fst_uid    [2];
    ARC_Byte fst_gid    [2];
    ARC_Byte fst_rdev   [4];
    ARC_Byte fst_size   [4];
    ARC_Byte fst_blksize[4];
    ARC_Byte fst_blocks [4];
    ARC_Byte fst_atime  [8];
    ARC_Byte fst_mtime  [8];
    ARC_Byte fst_ctime  [8];
};


/* -------------------------------------------------------------------------- */
/*                               local data                                   */
/* -------------------------------------------------------------------------- */

#define ZERO_WORD    { (gdb_byte) 0, (gdb_byte) 0, (gdb_byte) 0, (gdb_byte) 0 }


/* The %x specifiers in the format strings in this table correspond to the
 * parameters to the intercepted functions; the register number of the target
 * register in which the parameter is passed is given by the corresponding
 * entry in the param_register array.
 *
 * N.B. the special value of SL as the number of the register in which a
 *      parameter is passed indicates that the preceding parameter was the
 *      address of a string, and the length of that string (including the
 *      terminating NUL) is required here.
 *
 *      F<n> indicates that the parameter in register <n> is a word of flag
 *      bits which must be handled specially!
 *
 *      X indicates that the array element is not used.
 */

#define SL   1000
#define F2   1002
#define X    9999

static struct lib_function functions[] =
{
    { READ_CALL,         "_read_r",         "Fread,%x,%x,%x",       0, FALSE, 3, {1, 2,   3, X}, ZERO_WORD },
    { WRITE_CALL,        "_write_r",        "Fwrite,%x,%x,%x",      0, FALSE, 3, {1, 2,   3, X}, ZERO_WORD },
    { OPEN_CALL,         "_open_r",         "Fopen,%x/%x,%x,%x",    0, FALSE, 4, {1, SL, F2, 3}, ZERO_WORD },
    { CLOSE_CALL,        "_close_r",        "Fclose,%x",            0, FALSE, 1, {1, X,   X, X}, ZERO_WORD },
    { LSEEK_CALL,        "_lseek_r",        "Flseek,%x,%x,%x",      0, FALSE, 3, {1, 2,   3, X}, ZERO_WORD },
    { FSTAT_CALL,        "_fstat_r",        "Ffstat,%x,%x",         0, FALSE, 2, {1, 2,   X, X}, ZERO_WORD },
    { GETTIMEOFDAY_CALL, "_gettimeofday_r", "Fgettimeofday,%x,%x",  0, FALSE, 2, {1, 2,   X, X}, ZERO_WORD },
    { EXIT_CALL,         "_exit_r",         NULL,                   0, FALSE, 1, {1, X,   X, X}, ZERO_WORD }
};


/* -------------------------------------------------------------------------- */
/*                               local functions                              */
/* -------------------------------------------------------------------------- */

static int read_bytes (CORE_ADDR memaddr, gdb_byte *myaddr, int len)
{
    DEBUG("reading %d bytes from %x\n", len, (unsigned int) memaddr);
    return (int) arc_jtag_ops.memory_read_chunk((ARC_Address)  memaddr,
                                                (ARC_Byte*)    myaddr,
                                                (unsigned int) len);
}


static int write_bytes (CORE_ADDR memaddr, gdb_byte *myaddr, int len)
{
    DEBUG("writing %d bytes to %x\n", len, (unsigned int) memaddr);
    return (int) arc_jtag_ops.memory_write_chunk((ARC_Address)  memaddr,
                                                 (ARC_Byte*)    myaddr,
                                                 (unsigned int) len);
}


static void reply(int retcode, int error)
{
    DEBUG("reply: retcode = %d, error = %d\n", retcode, error);

    /* if an error has occurred */
    if (retcode == -1)
    {
        ARC_RegisterContents errno_address;

        /* read the address of the 'errno' variable from R0 */
        if (arc_read_jtag_core_register(0, &errno_address, TRUE))
            /* write the error number into the 'errno' variable */
            (void) arc_jtag_ops.memory_write_word((ARC_Address) errno_address,
                                                  (ARC_Word)    error);
    }

    /* write the return code into the function result register R0 */
    (void) arc_write_jtag_core_register(0, (ARC_RegisterContents) retcode, TRUE);
}


static void copy_bytes(char*     from, size_t fromsize,
                       ARC_Byte* to,   size_t tosize,
                       Boolean   target_is_big_endian)
{
    unsigned int bytes = (unsigned int) ((fromsize > tosize) ? tosize : fromsize);
    unsigned int i;

    /* N.B. 1) the fio_stat structure created by target-fileio.c has the values
     *         in big-endian byte order; so if the ARC target is little-endian
     *         we must reverse the order;
     *
     *      2) the fields in the fio_stat structure may be smaller (or larger!)
     *         than the corresponding fields in the ARC target structure - so we
     *         copy the *least* significant bytes of the fields, on the grounds
     *         that the most significant bytes are probably just sign-extensions!
     */
    for (i = 0; i < bytes; i++)
        to[i] = (ARC_Byte) ((target_is_big_endian) ? from[i]
                                                   : from[fromsize - 1 - i]);
}


/* 'myaddr' points to a fio_stat structure created by the target-fileio module;
 * this structure is meant for use in the RSP protocol, and is designed for 
 * independence of host/target systems - therefore, we must create an equivalent
 * structure which is ARC-specific, and write that structure to the target at
 * address 'memaddr'
 */
static int write_fstat(CORE_ADDR memaddr, gdb_byte *myaddr, int len)
{
    Boolean          target_is_big_endian = (gdbarch_byte_order (current_gdbarch) == BFD_ENDIAN_BIG);
    struct fio_stat* fst                  = (struct fio_stat*) myaddr;
    struct arc_stat  ast;

    memset(&ast, 0, sizeof(ast));

#define COPY(from, to)   copy_bytes(from, sizeof(from), to, sizeof(to), target_is_big_endian)

    COPY(fst->fst_dev,     ast.fst_dev);
    COPY(fst->fst_ino,     ast.fst_ino);
    COPY(fst->fst_mode,    ast.fst_mode);
    COPY(fst->fst_nlink,   ast.fst_nlink);
    COPY(fst->fst_uid,     ast.fst_uid);
    COPY(fst->fst_gid,     ast.fst_gid);
    COPY(fst->fst_rdev,    ast.fst_rdev);
    COPY(fst->fst_size,    ast.fst_size);
    COPY(fst->fst_blksize, ast.fst_blksize);
    COPY(fst->fst_blocks,  ast.fst_blocks);
    COPY(fst->fst_atime,   ast.fst_atime);
    COPY(fst->fst_mtime,   ast.fst_mtime);
    COPY(fst->fst_ctime,   ast.fst_ctime);

    return write_bytes(memaddr, (gdb_byte*) &ast, (int) sizeof(ast));
}


static CORE_ADDR findEntryPoint(const char* routine)
{
    CORE_ADDR      entry = 0;
    int            is_a_field_of_this;
    struct symbol *sym = lookup_symbol (routine,
                                        get_selected_block (0),
                                        VAR_DOMAIN,
                                        &is_a_field_of_this,
                                        (struct symtab **) NULL);
    if (sym)
    {
        if (SYMBOL_CLASS (sym) == LOC_BLOCK)
            entry = BLOCK_START (SYMBOL_BLOCK_VALUE (sym));
        else
            warning(_("%s is not a function"), routine);
    }
    else
        warning(_("can not find entry point of function %s"), routine);

    return entry;
}


static void insert_breakpoint(struct lib_function* f)
{
    if (!f->bp_is_set)
    {
        struct gdbarch_tdep* tdep = gdbarch_tdep (current_gdbarch);

        int bytes = read_bytes(f->entrypoint, f->saved_code, (int) tdep->breakpoint_size);

        if (bytes == (int) tdep->breakpoint_size)
        {
            bytes = write_bytes(f->entrypoint, (gdb_byte*) tdep->breakpoint_instruction,
                                                     (int) tdep->breakpoint_size);

            if (bytes == (int) tdep->breakpoint_size)
            {
                f->bp_is_set = TRUE;
                return;
            }
        }

        warning(_("can not set breakpoint at entrypoint of %s"), f->name);
    }
}


static void remove_breakpoint(struct lib_function* f)
{
    if (f->bp_is_set)
    {
        struct gdbarch_tdep* tdep = gdbarch_tdep (current_gdbarch);

        int bytes = write_bytes(f->entrypoint, f->saved_code, (int) tdep->breakpoint_size);

        if (bytes == (int) tdep->breakpoint_size)
            f->bp_is_set = FALSE;
        else
            warning(_("can not unset breakpoint at entrypoint of %s"), f->name);
    }
}


static unsigned int find_string_length(ARC_Address address)
{
    unsigned int length = 0;

    while (TRUE)
    {
        ARC_Byte     buf[65];
        unsigned int bytes = arc_jtag_ops.memory_read_chunk
                                 (address,
                                  buf,
                                  (unsigned int) sizeof(buf) - 1);
        unsigned int i;

        for (i = 0; i < bytes; i++)
            if (buf[i] == (ARC_Byte) '\0')
                return length + i + 1;

        address += bytes;
        length  += bytes;
    }
}


/* convert flags to target syscall to what they "should" be! */
static ARC_RegisterContents convert_flags(ARC_RegisterContents flags)
{
    ARC_RegisterContents result = flags;

/* See gcc/src/newlib/libc/sys/arc/sys/fcntl.h */

/* The following values have been changed for uclibc compatibility.  */
#define _FAPPEND        0x0400  /* append (writes guaranteed at the end) */
#define _FASYNC         0x2000  /* signal pgrp when data ready */
#define _FCREAT         0x0040  /* open with file create */
#define _FTRUNC         0x0200  /* open with truncation */
#define _FEXCL          0x0080  /* error on open if file exists */
#define _FSYNC          0x1000  /* do all writes synchronously */
#define _FNONBLOCK      0x0800  /* non blocking I/O (POSIX style) */

#define REMOVE(flag)    if (flags & _F ## flag) result &= ~ _F        ## flag
#define ADD(flag)       if (flags & _F ## flag) result |=   FILEIO_O_ ## flag

    /* N.B. all "old" bits most be removed from the result word before all
     *      "new" bits are added, in case the old and new sets intersect!
     */
    REMOVE(APPEND);
//  REMOVE(ASYNC);     // no equivalent flag in gdb/fileio.h
    REMOVE(CREAT);
    REMOVE(TRUNC);
    REMOVE(EXCL);
//  REMOVE(SYNC);      // no equivalent flag in gdb/fileio.h
//  REMOVE(NONBLOCK);  // no equivalent flag in gdb/fileio.h
    ADD(APPEND);
//  ADD(ASYNC);        // no equivalent flag in gdb/fileio.h
    ADD(CREAT);
    ADD(TRUNC);
    ADD(EXCL);
//  ADD(SYNC);         // no equivalent flag in gdb/fileio.h
//  ADD(NONBLOCK);     // no equivalent flag in gdb/fileio.h

    return result;
}


static void perform_interception(struct lib_function* f, ARC_RegisterNumber pc_regnum)
{
    ARC_RegisterContents params [MAX_SYSCALL_PARAMS];
    char                 request[MAX_SYSCALL_PARAMS * 9 + 40];
    unsigned int         i;

    /* these operations allow the target_fileio module to read data from target
     * memory, write data to target memory, and return a result value (and
     * possibly a error code) to the intercepted routine
     *
     * N.B. if the syscsall is 'fstat', we pass a special write function
     *      which converts the 'struct stat' structure to target layout before
     *      writing it to target memory.
     */
    struct memory_operations operations =
    {
        read_bytes,
        (f->call == FSTAT_CALL) ? write_fstat : write_bytes,
        reply,
        NULL
    };

    /* evaluate the parameters to be passed to the RPC request */
    for (i = 0; i < f->param_count; i++)
    {
        ARC_RegisterNumber reg = f->param_register[i];

        if (reg == SL)
            params[i] = find_string_length((ARC_Address) params[i - 1]);
        else if (reg == F2)
        {
            ARC_RegisterContents flags;

            (void) arc_read_jtag_core_register(2, &flags, TRUE);
            params[i] = convert_flags(flags);
        }
        else
            (void) arc_read_jtag_core_register(reg, &params[i], TRUE);
    }

    /* do not close the target program's stdin, stdout or stderr streams on the
     * host: it is possible that the program may be re-loaded and re-run on the
     * target in the same debugging session (so re-initializing its I/O system)
     * so it may try to read/write those streams again - instead, just tell the
     * target that the close succeeded
     */
    if (f->call == CLOSE_CALL)
    {
        int fd = (int) params[0];

        if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO)
        {
            reply(0, 0);
            DEBUG("*** RPC close of stream %d ignored\n", fd);
            return;
        }
    }

    /* parameters which are extra to those required by the format will simply be
     * ignored
     */
    (void) snprintf(request, sizeof(request), f->format,
                    params[0], params[1], params[2], params[3]);

    DEBUG("RPC request: %s\n", request);

    /* make the RPC request */
    target_fileio_request(request, &operations);
}


/* -------------------------------------------------------------------------- */
/*                               externally visible functions                 */
/* -------------------------------------------------------------------------- */

void arc_set_jtag_interception(Interception state)
{
    unsigned int i;

    DEBUG("*** interception: %s\n", (state == INTERCEPTION_RESET) ? "RESET" :
                                    (state == INTERCEPTION_ON)    ? "ON"    :
                                                                    "OFF");

    for (i = 0; i < ELEMENTS_IN_ARRAY(functions); i++)
    {
        struct lib_function* f = &functions[i];

        switch (state)
        {
            case INTERCEPTION_RESET:
                f->bp_is_set = FALSE;
                break;

            case INTERCEPTION_ON:
                /* set a breakpoint on the entry point of the function */
                f->entrypoint = findEntryPoint(f->name);
                if (f->entrypoint != 0)
                {
                    DEBUG("0x%08X  :  %s\n", (unsigned int) f->entrypoint, f->name);
                    insert_breakpoint(f);
                }
                break;

            case INTERCEPTION_OFF:
                if (f->entrypoint != 0)
                {
                    remove_breakpoint(f);
                    f->entrypoint = 0;
                }
                break;
        }
    }
}


Action arc_check_interception_breakpoint(ARC_RegisterNumber pc_regnum,
                                         int*               exitcode)
{
    ARC_RegisterContents pc;

    *exitcode = 0;


    /* get the current execution point from the TCP, rather than the PC - this
     * gives the same result on both ARC700 and ARC600 targets
     */
    if (arc_read_jtag_core_register(ARC_PCL_REGNUM, &pc, TRUE))
    {
        unsigned int i;

        DEBUG("checking for interception at 0x%08X\n", pc);

        for (i = 0; i < ELEMENTS_IN_ARRAY(functions); i++)
        {
            struct lib_function* f = &functions[i];

            if (f->entrypoint == (CORE_ADDR) pc)
            {
                DEBUG("intercepted function %s\n", f->name);

                if (f->call == EXIT_CALL)
                {
                    ARC_RegisterContents code;

                    /* the exit code is in parameter register R1 */
                    if (arc_read_jtag_core_register(1, &code, TRUE))
                        *exitcode = (int) code;

                    return INTERCEPTION_EXIT;
                }
                else
                {
                    ARC_RegisterContents blink;

                    perform_interception(f, pc_regnum);

                    /* copy BLINK to PC, so that when execution is re-started,
                     * control will return to the point after the call of the
                     * intercepted function
                     */
                    if (arc_read_jtag_core_register(ARC_BLINK_REGNUM, &blink, TRUE) &&
                        arc_write_jtag_aux_register(pc_regnum,         blink, TRUE))
                    {
                        DEBUG("copied BLINK (%x) to PC (was %x)\n", blink, pc);
                        return INTERCEPTION_RESUME;
                    }

                    /* if we couldn't set PC, fall through */
                }
            }
        }
    }

    return INTERCEPTION_HALT;
}

/******************************************************************************/
