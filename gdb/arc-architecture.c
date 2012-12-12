/* Target dependent code for ARC processor family, for GDB, the GNU debugger.

   Copyright 2009 Free Software Foundation, Inc.
   Copyright 2009-2012 Synopsys Inc.

   Contributed by ARC International (www.arc.com) on behalf of Synopsys Inc.

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
/*     This module provides support for handling the architectural version of */
/*     of the ARC target processor.                                           */
/*                                                                            */
/******************************************************************************/

/* gdb header files */
#include "defs.h"
#include "objfiles.h"
#include "arch-utils.h"
#include "gdb-events.h"

/* ARC header files */
#include "arc-architecture.h"
#include "arc-jtag.h"
#include "arc-jtag-tdep.h"
#include "arc-aux-registers.h"


/* -------------------------------------------------------------------------- */
/*                               externally visible data                      */
/* -------------------------------------------------------------------------- */

ARC_ProcessorVersion ARC_processor = NO_ARCHITECTURE;


/* -------------------------------------------------------------------------- */
/*                               local functions                              */
/* -------------------------------------------------------------------------- */

static ARC_ProcessorVersion architecture(const bfd_arch_info_type* arch)
{
    switch (arch->mach)
    {
        case bfd_mach_arc_a5    : return A5;
        case bfd_mach_arc_arc600: return ARC600;
        case bfd_mach_arc_arc700: return ARC700;
        default                 : return UNSUPPORTED_ARCHITECTURE;
    }
}


/* -------------------------------------------------------------------------- */
/*                               externally visible functions                 */
/* -------------------------------------------------------------------------- */

/* return the processor variant that is connected */
ARC_ProcessorVersion arc_get_architecture(ARC_RegisterNumber identity_regnum)
{
    if (ARC_processor == NO_ARCHITECTURE)
    {
        ARC_RegisterContents value;

        if (arc_read_jtag_aux_register(identity_regnum, &value, TRUE))
        {
            /* get the processor version number */
            value &= IDENTITY_ARCVER;

            if ((value >= 0x30) && (value <= 0x3f))
                ARC_processor = ARC700;
            else if ((value >= 0x20) && (value <= 0x2f))
                ARC_processor = ARC600;
            else if ((value >= 0x10) && (value <= 0x1f))
                ARC_processor = A5;
            else if (value <= 0x0f)
                ARC_processor = A4;
            else
                warning(_("unsupported processor version 0x%x"), value);

            DEBUG("target (from IDENTITY) is %s\n", arc_version_image(ARC_processor));
        }
    }

    return ARC_processor;
}


void arc_update_architecture(ARC_RegisterNumber identity_regnum)
{
    struct gdbarch_tdep* tdep    = gdbarch_tdep (current_gdbarch);
    ARC_ProcessorVersion version = arc_get_architecture(identity_regnum);

    tdep->processor_variant_info->processor_version = version;

    switch (version)
    {
        case NO_ARCHITECTURE:
            break;
        case ARC700:
            set_gdbarch_decr_pc_after_break (current_gdbarch, 0);
            break;
        case ARC600:
            set_gdbarch_decr_pc_after_break (current_gdbarch, 2);
            break;
        case A5:
            warning(_("A5 debugging is unsupported and may be unreliable."));
            break;
        case A4:
            /* N.B. this will not return */
            error(_("A4 debugging is unsupported."));
            break;
        case UNSUPPORTED_ARCHITECTURE:
            break;
    }
}


/* This function checks for architectural consistency; there are three possible
 * architectures to be considered:
 *
 *  1) the architecture for which the program to be debugged has been built
 *  2) the architecture of the target upon which the program is to be debugged
 *  3) the architecture for which we have a description of the auxiliary registers
 *
 * The 'gdbarch' parameter to this function corresponds to 2).
 *
 * A hardware target (such as an ARCangel) has a fixed architecture (e.g. that
 * defined by the XBF file used to configure it, and which can be discovered by
 * reading the target's IDENTITY auxiliary register); however, if the target is
 * the built-in simulator, the architecture depends upon how the simulator
 * instance is created: if the instance is created by use of the commands
 *
 *     file <program_file>
 *     target sim
 *
 * then the simulator architecture is taken from the program file; if it is
 * created by the commands
 *
 *     set endian big | little
 *     set architecture <name>
 *     target sim
 *
 * then the architecture is the named one; if it is created by the commands
 *
 *     set endian big | little
 *     target sim
 *
 * the architecture is the default ARC architecture as defined in bfd/cpu-arc.c,
 * and this is indicated by the 'the_default' flag in the 'bfd_arch_info' struct
 * being TRUE.
 */

void arc_check_architecture(struct gdbarch* gdbarch, bfd* objfile_bfd)
{
    ARC_ProcessorVersion target       = gdbarch_tdep (gdbarch)->processor_variant_info->processor_version;
    ARC_ProcessorVersion auxregs      = arc_aux_architecture(gdbarch);
    ARC_ProcessorVersion program;
    bfd_boolean          is_default   = FALSE;
    Boolean              is_simulator = FALSE;

    /* this is the case for the simulator (there is no h/w target) */
    if (target == NO_ARCHITECTURE)
    {
        const char*               name = selected_architecture_name();
        const bfd_arch_info_type* arch;

        if (name)
            arch = bfd_scan_arch(name);
        else
            arch = gdbarch_bfd_arch_info(gdbarch);

        target = architecture(arch);

        is_default   = arch->the_default;
        is_simulator = TRUE;
    }

    if (auxregs == NO_ARCHITECTURE)
    {
        arc_read_default_aux_registers(gdbarch);
        auxregs = arc_aux_architecture(gdbarch);
    }

    if (objfile_bfd)
        program = architecture(objfile_bfd->arch_info);
    else
        program = NO_ARCHITECTURE;

//  printf_filtered("auxregs = %s\n", arc_version_image(auxregs));
//  printf_filtered("target  = %s\n", arc_version_image(target));
//  printf_filtered("program = %s\n", arc_version_image(program));

    {
        const char* message = NULL;
        int         params  = 0;

        /* if we do not yet have an object file (and hence we do not know the
         * program's architecture)
         */
        if (program == NO_ARCHITECTURE)
        {
            if (target != auxregs)
            {
                if (is_simulator)
                {
                    if (is_default)
                        message = _("default simulator architecture is %s but auxiliary registers are defined for %s");
                    else
                        message = _("selected simulator architecture is %s but auxiliary registers are defined for %s");
                }
                else
                    message = _("target architecture is %s but auxiliary registers are defined for %s");

                params = 2;
            }
        }
        else
        {
            if (program != target || program != auxregs)
            {
                params = 4;

                if (is_simulator)
                {
                    if (target == program)
                    {
                        message = _("executable file %s is built for %s but auxiliary registers are defined for %s");
                        params = 3;
                    }
                    else
                    {
                        if (is_default)
                            message = _("default simulator architecture is %s, executable file %s is built for %s and auxiliary registers are defined for %s");
                        else
                            message = _("selected simulator is %s, executable file %s is built for %s and auxiliary registers are defined for %s");
                    }
                }
                else
                    message = _("target architecture is %s, executable file %s is built for %s and auxiliary registers are defined for %s");
            }
        }

        if (params == 2)
            warning(message, arc_version_image(target), arc_version_image(auxregs));
        else if (params == 3)
            warning(message, objfile_bfd->filename, arc_version_image(program), arc_version_image(auxregs));
        else if (params == 4)
            warning(message, arc_version_image(target), objfile_bfd->filename, arc_version_image(program), arc_version_image(auxregs));
    }


    /* unfortunately, this event can not be sent at the point that it is known
     * that the register architecture has changed, as at that point the global
     * variable current_gdbarch may have the value NULL, and that could cause
     * an error elsewhere where gdbarch_num_regs or gdbarch_num_pseudo_regs is
     * used (e.g. in setup_architecture_data in gdbtk/generic/gdbtk-register.c)
     */
    if (arc_pending_register_architecture_change_event)
    {
        DEBUG("sending register architecture changed event\n");
        reg_architecture_changed_event();
        arc_pending_register_architecture_change_event = FALSE;
    }
}


ARC_ProcessorVersion arc_version(const char* arch)
{
    ARC_ProcessorVersion version;

#define ARCH_IS(ident)    (strcmp(arch, ident) == 0)

    if (ARCH_IS("ARC700"))
        version = ARC700;
    else if (ARCH_IS("ARC600"))
        version = ARC600;
    else if (ARCH_IS("A5"))
        version = A5;
    else if (ARCH_IS("A4"))
        version = A4;
    else
        version = UNSUPPORTED_ARCHITECTURE;

    return version;
}


const char* arc_version_image(ARC_ProcessorVersion version)
{
    switch (version)
    {
        case NO_ARCHITECTURE         : return _("NONE");
        case ARC700                  : return _("ARC700");
        case ARC600                  : return _("ARC600");
        case A5                      : return _("A5");
        case A4                      : return _("A4");
        case UNSUPPORTED_ARCHITECTURE: return _("UNSUPPORTED");
        default                      : return _("???");
    }
}

/******************************************************************************/
