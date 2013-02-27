/* Target dependent code for ARC processor family, for GDB, the GNU debugger.

   Copyright 2009 Free Software Foundation, Inc.
   Copyright 2009-2012 Synopsys Inc.

   Contributed by  ARC International (www.arc.com), now part of Synopsys Inc.

   Authors:
      Tim Gore
      Tom Pennello    <tom.pennello@arc.com>
      Justin Wilde    <justin.wilde@arc.com>
      Phil Barnard    <phil.barnard@arc.com>
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
/*     This module implements operations for controlling an ARC target board. */
/*                                                                            */
/*     These operations are:                                                  */
/*        1) configuring ("blasting") an FPGA target with the contents of an  */
/*           XBF file;                                                        */
/*        2) checking whether a target has been so configured;                */
/*        3) setting the clock frequency of the target;                       */
/*        4) setting the clock sources of the target.                         */
/*                                                                            */
/* Notes:                                                                     */
/*     The arc_blast_board function implements an ARC-specific command; hence */
/*     its 'args' parameter contains data entered by the debugger user, which */
/*     must be checked for validity.                                          */
/*                                                                            */
/* Target Board:                                                              */
/*     It is assumed that the target board is actually an ARCangel 4 (AA4).   */
/*                                                                            */
/*     See                                                                    */
/*                      ARCangel 4 Development System                         */
/*                             User's Guide                                   */
/*                              5801-001                                      */
/*                                                                            */
/*     for a full description of the target.                                  */
/*                                                                            */
/*     The AA4 contains a Configurable Programmable Logic Device (CPLD) which */
/*     is used to control the system services on the board; this includes the */
/*     configuration of the board's PLL (Phase Lock Loop) clock chip, and     */
/*     clock routing.                                                         */
/*                                                                            */
/*     The AA4 also has a 48 MHz crystal oscillator module, and has a number  */
/*     of DIP switches which may be set manually: these may be used to select */
/*     a divisor (1, 2, 4 or 8) which may be applied to the crystal frequency */
/*     to obtain a lower frequency.                                           */
/*                                                                            */
/*     The target FPGA has 4 global clock pins (GCLK0-3); a different clock   */
/*     source may be routed to each of these by the CPLD.  The available      */
/*     sources are:                                                           */
/*                                                                            */
/*       crystal  : the physical crystal                                      */
/*       dips     : the physical crystal divided by the DIP switch divisors   */
/*       highimp  : high impedance                                            */
/*       host     : use the STR (strobe) input of the host interface          */
/*       mclk     : use a clock provided by the PLL                           */
/*       vclk     : use a clock provided by the PLL                           */
/*                                                                            */
/*     Note that "high impedance" (also referred to as "Tri-state") means, in */
/*     effect, that the clock is switched off.                                */
/*                                                                            */
/*     It is also possible to specify that the PLL clock should be a Harvard  */
/*     clock generator.                                                       */
/*                                                                            */
/*     The main clock for the target's ARC processor is provided by GLCK3.    */
/*                                                                            */
/*     The PLL is assumed to be a Cypress Semiconductor Corporation ICD2061A  */
/*     Dual Programmable Graphics Clock Generator; the Data Sheet describing  */
/*     this device may be readily found on the Web, and should be consulted   */
/*     for an understanding of how the clock is programmed.                   */
/*                                                                            */
/*     The ICD2061A actually provides two independent clocks: MCLK (Memory or */
/*     I/O Timing Clock) and VCLK (Video Clock).  It is recommended that the  */
/*     frequency of one clock should not be an integer multiple of that of    */
/*     other, in order to avoid clock signal degradation through jitter.      */
/*                                                                            */
/******************************************************************************/

/* system header files */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

/* gdb header files */
#include "defs.h"
#include "completer.h"
#include "objfiles.h"
#include "gdbcmd.h"

/* ARC header files */
#include "arc-board.h"
#include "arc-architecture.h"
#include "arc-aux-registers.h"
#include "arc-gpio.h"
#include "arc-jtag-ops.h"


/* -------------------------------------------------------------------------- */
/*                               local types                                  */
/* -------------------------------------------------------------------------- */

typedef enum
{
  CLOCK_SOURCE_HIGH_IMPEDANCE,
  CLOCK_SOURCE_PLL_MCLK,
  CLOCK_SOURCE_PLL_VCLK,
  CLOCK_SOURCE_CRYSTAL,
  CLOCK_SOURCE_PLL_MCLK_HARVARD,
  CLOCK_SOURCE_PLL_VCLK_HARVARD,
  CLOCK_SOURCE_HOST_STROBE,
  CLOCK_SOURCE_CRYSTAL_DIVIDED
} ClockSource;

typedef enum
{
  PLL_MCLK = 0,
  PLL_VCLK = 1,
  NO_PLL_CLK = 2
} PLL_ClockId;

typedef unsigned int GlobalClockId;	// 0 .. 3

typedef double MegaHertz;

typedef struct global_clock
{
  ClockSource source;
  int set;
  PLL_ClockId PLL_clock;
} GlobalClock;

typedef struct pll_clock
{
  MegaHertz requested_frequency;
  MegaHertz actual_frequency;
  int in_use;
} PLL_Clock;

typedef struct pll_clock_info
{
  const char *name;
  unsigned int PLL_register;
  MegaHertz MIN_VCO_FREQ;
  MegaHertz MAX_VCO_FREQ;
} PLL_ClockInfo;


/* -------------------------------------------------------------------------- */
/*                               local data                                   */
/* -------------------------------------------------------------------------- */

#define ARC_SET_CLOCK_FREQUENCY_COMMAND    "arc-set-clock-frequency"
#define ARC_SET_CLOCK_SOURCE_COMMAND       "arc-set-clock-source"
#define ARC_CLOCK_SETTINGS_COMMAND         "arc-clock-settings"
#define ARC_BLAST_BOARD_COMMAND            "arc-blast-board"
#define ARC_FPGA_COMMAND                   "arc-fpga"

#define ARC_SET_CLOCK_FREQUENCY_COMMAND_USAGE   "Usage: "      ARC_SET_CLOCK_FREQUENCY_COMMAND " [ <CLOCK> = ] <FREQUENCY> |\n" \
                                                                                               "                              " \
                                                                                               " <FREQUENCY> , <FREQUENCY>\n"

#define ARC_SET_CLOCK_SOURCE_COMMAND_USAGE      "Usage: "      ARC_SET_CLOCK_SOURCE_COMMAND    " gclk[N] = <SOURCE>                |\n" \
                                                                                               "                           "            \
                                                                                               " gclks   = <SOURCE> { , <SOURCE> } |\n" \
                                                                                               "                           "            \
                                                                                               " harvard\n"
#define ARC_CLOCK_SETTINGS_COMMAND_USAGE        "Usage: info " ARC_CLOCK_SETTINGS_COMMAND "\n"
#define ARC_BLAST_BOARD_COMMAND_USAGE           "Usage: "      ARC_BLAST_BOARD_COMMAND    " <FILE>\n"
#define ARC_FPGA_COMMAND_USAGE                  "Usage: info " ARC_FPGA_COMMAND           "\n"


#define MAX_MAX_BURST     256

#define S_XOR            (Byte) 0x80	// XOR value with this to get all bits positive
#define C_XOR            (Byte) 0x0b	// with respect to the signal values.

/* control bits in the masks for the Control port */
#define STR              (Byte) 0x01	// strobe
#define CNT              (Byte) 0x02
#define SS0              (Byte) 0x04
#define SS1              (Byte) 0x08
#define BI               (Byte) 0x20	// bi-directional?

/* control bits in the masks for the Status port */
#define OP               (Byte) 0x20
#define ACK              (Byte) 0x40
#define BUSY             (Byte) 0x80

// special meanings of some of those bits
#define FPA_CFG_DONE     OP
#define CFG_FROM_ROM     BUSY
#define PAR_CFG_MODE     ACK


// constants for the PLL
#define MREG_ADDRESS                          3
#define VCLK_SETUP_REG_NO                     0	// which of Reg0 .. Reg2 is used to set the VClock freq
#define MCLK_RESET_FREQUENCY   (MegaHertz) 25.0
#define VCLK_RESET_FREQUENCY   (MegaHertz) 25.0

#define NUM_GLOBAL_CLOCKS                     4
#define NUM_PLL_CLOCKS                        2

#define UNDEFINED_FREQUENCY  (MegaHertz) (-1.0)


static const char *CLOCK_SOURCE_STRINGS[] = {
  "High Impedance",
  "PLL MCLK",
  "PLL VCLK",
  "Crystal",
  "High Impedance",
  "High Impedance",
  "Host Strobe",
  "Crystal With Division"
};

static const char *GCLOCK3_SOURCE_STRINGS[] = {
  "High Impedance",
  "PLL MCLK",
  "PLL VCLK",
  "Crystal",
  "PLL MCLK (+Harvard)",
  "PLL VCLK (+Harvard)",
  "Host Strobe",
  "Crystal With Division (+Harvard)"
};


static const ClockSource default_GCLK_sources[] = {
  CLOCK_SOURCE_HIGH_IMPEDANCE,	// GCLK0
  CLOCK_SOURCE_CRYSTAL,		// GCLK1
  CLOCK_SOURCE_HOST_STROBE,	// GCLK2
  CLOCK_SOURCE_CRYSTAL_DIVIDED	// GCLK3
};


static const MegaHertz VCO_PRESET_BOUNDARIES[] =
  { 50.0, 51.0, 53.2, 58.5, 60.7, 64.4, 66.8,
  73.5, 75.6, 80.9, 83.2, 91.5, 100.0, 120.0
};


static const PLL_ClockInfo PLL_clock_info[NUM_PLL_CLOCKS] = {
  {"MCLK", MREG_ADDRESS, 52.0, 120.0},
  {"VCLK", VCLK_SETUP_REG_NO, 65.0, 165.0}
};


static PLL_Clock PLL_clocks[NUM_PLL_CLOCKS];
static GlobalClock global_clocks[NUM_GLOBAL_CLOCKS];
static int harvard;


/* -------------------------------------------------------------------------- */
/*                               local macros                                 */
/* -------------------------------------------------------------------------- */

#define IS_SET(bit, byte)     (((bit) & (byte)) == (bit))
#define __MIN(X, Y)           ((X) < (Y) ? (X) : (Y))
#define __MAX(X, Y)           ((X) < (Y) ? (Y) : (X))


/* -------------------------------------------------------------------------- */
/*                               local functions                              */
/* -------------------------------------------------------------------------- */

static void
Sleep (unsigned int milliseconds)
{
  usleep ((unsigned long) (1000 * milliseconds));
}


static Byte
read_status_port (void)
{
  return gpio_read (STATUS_PORT) ^ S_XOR;
}


static void
write_control_port (Byte data, unsigned int delay)
{
  Byte value = data ^ C_XOR;

  gpio_write (CONTROL_PORT, value);
  Sleep (delay);
}


static void
write_data_port (Byte value)
{
  gpio_write (DATA_PORT, value);
}


static int
pair (char *args, char **value)
{
  char *equals = strchr (args, '=');

  if (equals)
    {
      char *val = equals + 1;

      /* if the key is missing from the argument string */
      if (equals == args)
	return 0;

      equals--;
      while (*equals == ' ')
	equals--;
      equals[1] = '\0';

      while (*val == ' ')
	val++;
      if (*val == '\0')
	return 0;

      *value = val;
      return 2;
    }

  return 1;
}


/* -------------------------------------------------------------------------- */
/*                        local functions for FPGA blasting                   */
/* -------------------------------------------------------------------------- */

/* Initialise the FPGA ready for blasting */
static int
initialize_FPGA (void)
{
  Byte status;
  Byte iOriginalState;
  Byte iControlState;
  unsigned int cpld_rev;

  ENTERMSG;

  // snapshot the control port
  iOriginalState = gpio_read (CONTROL_PORT);

  // initialize FPGA by taking SS0 and SS1 low (all other ctrl's low as well)
  iControlState = iOriginalState & (0xFFFFFFFF ^ (SS0 | SS1 | CNT | STR | BI));
  write_control_port (iControlState, 51);

  // tri-state port outputs so we can read CPLD revision number
  iControlState = iControlState | BI;
  write_control_port (iControlState, 1);

  // read the CPLD revision number lsb
  cpld_rev = (unsigned int) gpio_read (DATA_PORT);

  // set CNT high and read CPLD revision number msb
  iControlState = iControlState | CNT;
  write_control_port (iControlState, 1);

  cpld_rev += (unsigned int) gpio_read (DATA_PORT) << 8;

  // test the CPLD rev no. If it is 0xffff then this CPLD
  // may not support parallel blasting
  if ((cpld_rev & 0xffff) == 0xffff)
    {
      warning (_("old board type (AA2), not supported"));
      gpio_close ();
      return FALSE;
    }
  else
    {
      char rev_string[32];
      unsigned int temp = cpld_rev;
      unsigned int char_pos = 0;
      unsigned int i;

      for (i = 0; i < 16; i++)
	{
	  if (temp & 0x8000)
	    rev_string[char_pos++] = '1';
	  else
	    rev_string[char_pos++] = '0';

	  temp <<= 1;
	  if ((i % 4) == 3)
	    rev_string[char_pos++] = ' ';
	}

      rev_string[char_pos] = '\0';

      printf_filtered (_("\nCPLD Revision = %20s\n"), rev_string);
    }

  // Take CNT low
  iControlState = iControlState & (0xFFFFFFFF ^ (SS0 | SS1 | CNT | STR | BI));

  // now take STR high, CNT low and SS0 high to enter FPGA download mode
  iControlState = iControlState | STR;
  write_control_port (iControlState, 1);

  iControlState = iControlState | SS0;
  write_control_port (iControlState, 3);

  // Check that FPA_CFG_DONE=0
  status = read_status_port ();

  if (IS_SET (FPA_CFG_DONE, status))
    {
      warning (_("FPGA is not responding - status = 0x%08x"), status);
      gpio_close ();
      return FALSE;
    }

  LEAVEMSG;

  return TRUE;
}


static int
parallel_send_data (Byte * buffer, unsigned int count)
{
  GPIO_Pair arr[MAX_MAX_BURST * 3 + 1];

  // work out how many bytes we can send in one pio program
  // no. of bytes of config data that can be downloaded
  // with a single pio program
  unsigned const int bytes_per_burst = 127;

  // initialize offsets into config data buffer
  unsigned int burst_start = 0;
  unsigned int burst_end = bytes_per_burst - 1;

  // snapshot the control port
  Byte iOriginalState = gpio_read (CONTROL_PORT);
  Byte iControlState =
    (iOriginalState | SS0) & (0xFFFFFFFF ^ (SS1 | CNT | STR | BI));

  while (TRUE)
    {
      GPIO_Pair *gpio = arr;
      unsigned int i;

      /* do not try to write more data than is in the buffer */
      if (burst_end > (count - 1))
	burst_end = count - 1;

      // initialize the gpio driver instruction stream
      for (i = burst_start; i <= burst_end; i++)
	{
	  gpio->port = DATA_PORT;
	  gpio->data = buffer[i];
	  gpio++;
	  gpio->port = CONTROL_PORT;
	  gpio->data = iControlState ^ C_XOR;
	  gpio++;
	  gpio->port = CONTROL_PORT;
	  gpio->data = (iControlState | STR) ^ C_XOR;
	  gpio++;
	}

      gpio_write_array (arr, gpio - arr);

      /* last block of data written */
      if (burst_end == count - 1)
	break;

      burst_start = burst_end + 1;
      burst_end = burst_start + bytes_per_burst - 1;
    }

  return TRUE;
}


static int
serial_send_data (Byte * buff, unsigned int count)
{
  // This code is taken from the SeeCode debugger file os/arc/connect/par/arc/aa3blast.cpp
  // which is intended to work with either Win95 or WinNT.  If serial blasting is required
  // for Linux, this code would have to be re-written to use Linux O/S operations.

  /*
     #if USE_PORT_OBJECT
     printf("Sorry, serial download not supported.\n");
     return false;
     // To remedy this we just have to rewrite the code below.
     #else
     LongPioInstrStream  stream;     // local instr stream buffer.
     int bytes_per_burst; // no. of bytes of config data that can be downloaded
     // with a single pio program
     int burst_start, burst_end;    // pointers into config data buffer
     unsigned char    byte_to_send; // byte currently being sent
     bool done;

     const int txs_per_byte = 16 * _mul;

     // work out how many bytes we can send in one pio program
     bytes_per_burst = max_pio_burst / txs_per_byte;  // 8 bits per byte, 2 tx's per bit

     // ensure divisible by 2
     bytes_per_burst = (bytes_per_burst/2) * 2;
     if (bytes_per_burst <= 0)  bytes_per_burst=1;

     // initialize pointers into buff
     burst_end   = bytes_per_burst - 1;
     burst_start = 0;

     done = false;
     while (!done) {
     // initialize the pio driver instruction stream
     pioInitInstr_(stream);

     // put instructions into pio instruction stream to push the required
     // parallel port output data onto the gportio data stack.
     // Note: because a stack is LIFO, we push the data reverse order.
     for (int index = burst_end; index >= burst_start; index--) {
     byte_to_send = buff[index];
     for (int bit_index = 7; bit_index >= 0; bit_index--) {
     int j;
     // instructions to push data on the stack
     if (byte_to_send & 0x80) {
     for (j=0; j<_mul; j+=1)
     pioConst_ (stream, SEND1b);     // send a '1' bit
     for (j=0; j<_mul; j+=1)  pioConst_ (stream, SEND1a);
     }
     else {
     for (j=0; j<_mul; j+=1)
     pioConst_ (stream, SEND0b);     // send a '0' bit
     for (j=0; j<_mul; j+=1)  pioConst_ (stream, SEND0a);
     }
     byte_to_send <<= 1;
     }
     }

     // and put in the program to send it
     pioConst_ (stream, (unsigned char)bytes_per_burst*txs_per_byte);
     pioInstr_ (stream, PIO_LOOP_BEGIN);
     pioOutp_  (stream, 0);
     pioInstr_ (stream, PIO_LOOP_END);

     // now execute the whole instruction stream
     gpioEval_((PioInstrStream*)&stream,0,0);

     if (burst_end >= (count-1))
     done = true;
     else {
     burst_start  = burst_end + 1;
     burst_end    = burst_start + bytes_per_burst - 1;
     if (burst_end > (count-1))
     burst_end = count-1;
     }
     }


     return true;
     #endif
   */

  warning (_("Sorry, serial download is not supported"));
  return FALSE;
}


static int
blast_FPGA (FILE * xbf)
{
  int parallel_cfg;
  unsigned long file_size;
  unsigned long five_percent;
  unsigned long bytes_sent = 0;
  unsigned long twentieths_complete = 0;
  Byte status;

  ENTERMSG;

  // get parallel port status & see whether board is expecting
  // parallel or serial blast
  status = read_status_port ();

  if ((status & CFG_FROM_ROM) == CFG_FROM_ROM)
    {
      // oops - FPGA is configured from ROM
      if (IS_SET (FPA_CFG_DONE, status))
	printf_filtered (_("FPGA is configured from ROM"));
      else
	warning (_("FPGA should be configured from ROM - BUT IT IS NOT!"));
      return FALSE;
    }

  parallel_cfg = ((status & PAR_CFG_MODE) == PAR_CFG_MODE);

  // find the length of the file (could use fstat here)
  (void) fseek (xbf, 0, SEEK_END);
  file_size = (unsigned long) ftell (xbf);
  (void) fseek (xbf, 0, SEEK_SET);

  five_percent = file_size / 20;

  // read file and blast

  while (TRUE)
    {
      Byte data_buffer[1024];
      size_t n_bytes = fread (data_buffer, 1, sizeof (data_buffer), xbf);

      if (gpio_port_error)
	error (_("Error in accessing JTAG port (device " GPIO_DEVICE ")"));

      /* end of file reached? (fread returns 0 for both EOF and error!) */
      if (n_bytes == 0)
	{
	  if (!feof (xbf))
	    {
	      warning (_("error in reading XBF file"));
	      return FALSE;
	    }
	  break;
	}

      if (!(((parallel_cfg) ? parallel_send_data
	     : serial_send_data) (data_buffer, (unsigned int) n_bytes)))
	break;

      bytes_sent += n_bytes;
      if (bytes_sent == file_size)
	break;

      if ((bytes_sent / five_percent) > twentieths_complete)
	{
	  twentieths_complete++;
	  printf_filtered (_("*"));
	  gdb_flush (gdb_stdout);
	}
    }

  printf_filtered (_("\n"));

  // check for the ConfigDone signal
  status = read_status_port ();

  if (!IS_SET (FPA_CFG_DONE, status))
    {
      warning (_("FPGA configuration failed"));
      return FALSE;
    }

  printf_filtered (_("FPGA configured\n"));

  // set SS0 and SS1 high to take board out of reset
  {
    Byte iControlState =
      (gpio_read (CONTROL_PORT) | SS0 | SS1 | STR) & (0xFFFFFFFF ^ (CNT | BI));

    write_control_port (iControlState, 1);
  }

  LEAVEMSG;

  return TRUE;
}


/* -------------------------------------------------------------------------- */
/*                      local functions for setting clocks                    */
/* -------------------------------------------------------------------------- */

static void
reset_clock_configuration (void)
{
  unsigned int i;

  for (i = 0; i < ELEMENTS_IN_ARRAY (PLL_clocks); i++)
    {
      PLL_clocks[i].requested_frequency = MCLK_RESET_FREQUENCY;
      PLL_clocks[i].actual_frequency = VCLK_RESET_FREQUENCY;
      PLL_clocks[i].in_use = FALSE;
    }

  for (i = 0; i < ELEMENTS_IN_ARRAY (global_clocks); i++)
    {
      global_clocks[i].source = default_GCLK_sources[i];
      global_clocks[i].set = FALSE;
      global_clocks[i].PLL_clock = NO_PLL_CLK;
    }

  harvard = FALSE;
}


/**************************************************************************
* The PLL consists of a VCO and 3 counters that divide by p, q and 2^d. The
* VCO runs at 2*RefClk*p/q. This is divided by 2^d to give the PLL output.
* All frequencies are in MHz.
*
* There are several contraints on the various values:
*    4 <= p <= 130
*    3 <= q <= 129
*    0 <= d <=   7
*    0.2 <= ref_clk / q <= 1.0    (200kHz .. 1MHz)
*
* This method is a bit of a palaver - very procedural. Basically it uses
* trial and error to find the best values for d, p and q, within the given
* contraints.
***************************************************************************/

static unsigned int
calculate_ctrl_word (const MegaHertz requested_frequency,
		     const MegaHertz min_vco_frequency,
		     const MegaHertz max_vco_frequency,
		     MegaHertz * actual_frequency)
{
  const unsigned int MIN_P = 4;
  const unsigned int MAX_P = 130;
  const unsigned int MIN_Q = 3;
  const unsigned int MAX_Q = 129;
  const unsigned int MIN_D = 0;
  const unsigned int MAX_D = 7;
  const MegaHertz MIN_REF_CLK_OVER_Q = 0.2;
  const MegaHertz MAX_REF_CLK_OVER_Q = 1.0;
  const MegaHertz REF_CLK = 14.31818;	// input to PLL

#define NUM_PRESETS    ELEMENTS_IN_ARRAY(VCO_PRESET_BOUNDARIES)

  unsigned int index, p = 0, q = 0, d = MIN_D;	// PLL parameters (see ICD2061A Data Sheet)
  unsigned int trial_p, trial_q;	// temp vars for p & q values that we are trying out
  unsigned int first_q, last_q;
  unsigned int ctrl_word;
  double min_delta = 1.0;	// smallest error so far
  MegaHertz vco_frequency = requested_frequency;	// freq at which the VCO will run
  double p_over_q;

  // find a value of d which gives a VCO frequency that is within limits
  // (VCO output is divided by 2^d)
  while ((vco_frequency < min_vco_frequency) && (d < MAX_D))
    {
      vco_frequency *= 2;
      d++;
    }

  DEBUG ("request = %g, vco = %g, min = %g, max = %g, d = %d\n",
	 requested_frequency, vco_frequency, min_vco_frequency,
	 max_vco_frequency, d);

  // check that we have found a suitable value for d
  if ((vco_frequency < min_vco_frequency)
      || (vco_frequency > max_vco_frequency))
    {
      DEBUG ("frequency is out of range\n");
      return 0;
    }

  // calculate the ratio needed for p/q, to get vco_frequency from ref_clk
  p_over_q = vco_frequency / (2.0 * REF_CLK);

  // now use some brute force and ignorance to find the best values for p & q:
  // we look for p & q such that p / q is the best approximation to p_over_q

  // calculate range of values allowed for q
  first_q =
    __MAX ((unsigned int) (REF_CLK / MAX_REF_CLK_OVER_Q + 0.999999), MIN_Q);
  last_q = __MIN ((unsigned int) (REF_CLK / MIN_REF_CLK_OVER_Q), MAX_Q);

  /* look at each possible value of q */
  for (trial_q = first_q; trial_q <= last_q; trial_q++)
    {
      // calculate the value of p needed with this q value
      double raw_p = p_over_q * (double) trial_q;
      double delta;

      /* round the raw value for p to the nearest integer */
      trial_p = (unsigned int) (raw_p + 0.5);

      // range check the required p value: note that because trial_q is
      // increasing, trial_p is also increasing, so if it is less than MIN_P
      // we may find a suitable value in a later iteration, whereas if it is
      // greater than MAX_P we will never find a suitable value in a later
      // iteration
      if (trial_p < MIN_P)
	continue;
      if (trial_p > MAX_P)
	break;

      // see how much error is caused by p being an integer
      delta = fabs (1.0 - ((double) trial_p / raw_p));

      // if this is the most accurate so far, then keep track of it
      if (delta < min_delta)
	{
	  p = trial_p;
	  q = trial_q;

	  // if it is exact then quit (we won't be able to find a better approximation!)
	  if (min_delta == 0.0)
	    break;

	  min_delta = delta;
	}
    }

  /* just in case */
  if (p == 0)
    {
      DEBUG ("loop failed to find p & q!");
      return 0;
    }

  // have sorted out values for p, q & d - now form them into a control word

  // first, look up the value for Index (VCO preset)
  for (index = 0; index < NUM_PRESETS; index++)
    {
      if (VCO_PRESET_BOUNDARIES[index] > vco_frequency)
	break;
    }

  // make sure we have found a suitable value for I
  if ((index == 0) || (index == NUM_PRESETS))
    {
      DEBUG ("can not find preset for %g\n", vco_frequency);
      return 0;
    }

  /* index must now be in the range 1 .. 13; so subtract 1, to change
   * the range to 0 .. 12
   */
  index--;

  /* return the frequency calculated as best approximation to the one requested */
  *actual_frequency = (2.0 * REF_CLK * p / q) / (1 << d);

  DEBUG ("p = %d, q = %d, d = %d, I = %d\n", p, q, d, index);

  /* The ranges for p, q & d are:
   *
   *    I : 0 ..  12
   *    p : 4 .. 130
   *    d : 0 ..   7
   *    q : 3 .. 129
   *
   * Subtracting a bias of 3 from p and 2 from q converts these to:
   *
   *    I : 0 ..  12     which can be held in 4 bits
   *    p : 1 .. 127     which can be held in 7 bits
   *    d : 0 ..   7     which can be held in 3 bits
   *    q : 1 .. 126     which can be held in 7 bits
   *
   * which gives a control word with bitfields:
   *
   *          00000000000IIIIPPPPPPPDDDQQQQQQQ
   *
   * Note that 0 is not a valid value for the control word, which is why
   * it is safe to return 0 from this function in the error cases.
   */

  ctrl_word = (index & 0xf);
  ctrl_word = (ctrl_word << 7) | ((p - 3) & 0x7f);
  ctrl_word = (ctrl_word << 3) | (d & 0x7);
  ctrl_word = (ctrl_word << 7) | ((q - 2) & 0x7f);

  return ctrl_word;
}


static int
write_PLL_register (unsigned int address, unsigned int ctrl_word)
{
  const Byte S0S1_FINAL_STATE[] = { (Byte) 0x0, (Byte) 0x1, (Byte) 0x2 };
  const Byte PLL_CLK_BIT = (Byte) 0x08;
  const Byte PLL_DATA_BIT = (Byte) 0x10;
  unsigned int i;
  Byte data;
  Byte iControlState;
  Byte iOriginalState;
  int manchester_bitstream[64];

  DEBUG ("writing 0x%08X to PLL register %d\n", ctrl_word, address);

  // add the address in the msb's of the ctrl_word: this gives us a 24-bit value
  // with the fields
  //
  //     AAAIIIIPPPPPPPDDDQQQQQQQ

  ctrl_word = ((address & 0x7) << 21) | (ctrl_word & 0x1fffff);

  // create a bit stream at twice the data rate that incorporates the
  // pseudo Manchester encoding for the data and also the unlock sequence
  for (i = 0; i < 11; i++)
    manchester_bitstream[i] = 1;

  // start bit
  manchester_bitstream[11] = 0;
  manchester_bitstream[12] = 0;
  manchester_bitstream[13] = 0;

  i = 14;
  while (i < 62)
    {
      if ((ctrl_word & 0x1) == 0)
	{
	  manchester_bitstream[i++] = 1;
	  manchester_bitstream[i++] = 0;
	}
      else
	{
	  manchester_bitstream[i++] = 0;
	  manchester_bitstream[i++] = 1;
	}

      ctrl_word >>= 1;
    }

  // stop bit
  manchester_bitstream[62] = 1;
  manchester_bitstream[63] = 1;

  // snapshot the control port state
  iOriginalState = gpio_read (CONTROL_PORT);

  // set the parallel port data to 0, in preparation for sending config data
  write_data_port ((Byte) 0);
  Sleep (2);

  // Set CPLD into config mode:

  // set SS0=1, SS1=1, CNT=1, BIDir=0:
  iControlState = (iOriginalState | SS0 | SS1 | CNT | BI) ^ BI;
  write_control_port (iControlState, 2);

  // Ensure STROBE is high
  iControlState = iControlState | STR;
  write_control_port (iControlState, 2);

  // set CPLD into config mode by setting SS0=1, SS1=0, CNT=1
  iControlState = iControlState ^ SS1;
  write_control_port (iControlState, 2);

  // now send the double rate data stream
  // set clock high and data low
  data = PLL_CLK_BIT & ~PLL_DATA_BIT;
  write_data_port (data);
  //Sleep(1);

  for (i = 0; i < 64; i++)
    {
      // put the next Manchester code bit out
      if (manchester_bitstream[i] == 1)
	data = data | PLL_DATA_BIT;
      else
	data = data & ~PLL_DATA_BIT;

      write_data_port (data);
      //Sleep(1);

      // toggle the clock bit
      data = data ^ PLL_CLK_BIT;
      write_data_port (data);
      //Sleep(1);
    }

  // set data/clock (alias s1/s0) to select the programmed divisor register
  // for the video clock
  write_data_port (S0S1_FINAL_STATE[VCLK_SETUP_REG_NO]);
  //Sleep(1);

  // set CPLD into ARC-Run Host-Read mode
  iControlState = iControlState | SS1 | BI;
  write_control_port (iControlState, 2);

  return TRUE;
}


static void
configure_CPLD (void)
{
  const Byte CPLD_CLK_BIT = (Byte) 0x01;
  const Byte CPLD_DATA_BIT = (Byte) 0x02;
  const Byte CPLD_SET_BIT = (Byte) 0x04;
  const unsigned int NUM_OF_CPLD_CFG_BITS = 16;
  unsigned int cpldConfigData = 0;
  Byte iControlState;
  unsigned int i;

  // snapshot the control port:
  Byte iOriginalState = gpio_read (CONTROL_PORT);

  // set the parallel port data to 0, in preparation for sending config data
  write_data_port ((Byte) 0);
  Sleep (1);

  // Set CPLD into configuration mode:

  // set SS0=1, SS1=1, CNT=1, BIDir=0
  iControlState = (iOriginalState | SS0 | SS1 | CNT | BI) ^ BI;
  write_control_port (iControlState, 2);

  // Ensure STROBE is high
  iControlState = iControlState | STR;
  write_control_port (iControlState, 2);

  // set CPLD into config mode by setting SS0=1, SS1=0, CNT=1
  iControlState = iControlState ^ SS1;
  write_control_port (iControlState, 2);

  // now send the config data stream with set low
  // set clock high and data low

  for (i = 0; i < ELEMENTS_IN_ARRAY (global_clocks); i++)
    cpldConfigData += (unsigned int) global_clocks[i].source << (3 * i);

  for (i = 0; i < NUM_OF_CPLD_CFG_BITS; i++)
    {
      Byte value;

      // see if the next cfg bit is 0 or 1
      if ((cpldConfigData & 0x1) == 0x1)
	value = CPLD_DATA_BIT;
      else
	value = (Byte) 0;

      // put data bit out to parallel port
      write_data_port (value);

      // and toggle the clock line
      value |= CPLD_CLK_BIT;
      write_data_port (value);

      value &= ~CPLD_CLK_BIT;
      write_data_port (value);

      cpldConfigData >>= 1;
    }

  // now take the clock and set bits high
  write_data_port (CPLD_CLK_BIT | CPLD_SET_BIT);

  // finally take clock low
  write_data_port (CPLD_SET_BIT);

  // and put the CPLD into ARC run mode, SS0=1, SS1= 1, CNT=x
  iControlState = iControlState | SS1 | BI;
  write_control_port (iControlState, 2);
}


static int
set_PLL_clock_frequency (PLL_ClockId clock,
			 MegaHertz requested_frequency,
			 int inform, int emit_warning)
{
  // first need to work out the control words for the frequencies set
  MegaHertz actual_frequency = UNDEFINED_FREQUENCY;
  unsigned int ctrl_word = calculate_ctrl_word (requested_frequency,
						PLL_clock_info
						[clock].MIN_VCO_FREQ,
						PLL_clock_info
						[clock].MAX_VCO_FREQ,
						&actual_frequency);
  int set;

  DEBUG ("set_PLL_clock_frequency: %s ctrl_word = %08X, freq = %.2lf MHz\n",
	 PLL_clock_info[clock].name, ctrl_word, requested_frequency);

  if (ctrl_word == 0)
    {
      if (emit_warning)
	warning (_("it is not possible to set %s to %.2lf"),
		 PLL_clock_info[clock].name, requested_frequency);
      return FALSE;
    }

  DEBUG ("set_PLL_clock_frequency: %s %.2lf, %.2lf, %.2lf\n",
	 PLL_clock_info[clock].name, requested_frequency, actual_frequency,
	 PLL_clocks[clock].actual_frequency);

  if (actual_frequency != PLL_clocks[clock].actual_frequency)
    {
      // set up the PLL chip. We program the MREG, the REG0/1/2 - whichever
      // is selected to control VCLK
      set = write_PLL_register (PLL_clock_info[clock].PLL_register, ctrl_word);

      if (set)
	{
	  PLL_clocks[clock].requested_frequency = requested_frequency;
	  PLL_clocks[clock].actual_frequency = actual_frequency;
	}
      else if (emit_warning)
	warning ("PLL programming failed");
    }
  else
    set = TRUE;

  if (set && inform)
    printf_filtered (_("PLL clock %s set to %.2lf MHz.\n"),
		     PLL_clock_info[clock].name, actual_frequency);

  return set;
}


/* the ICD2061A Data Sheet recommends that the two clocks should not be set to
 * frequencies such that one is an integer multiple of the other, in order to
 * avoid jitter.
 */
static void
check_PLL_clock_frequencies (void)
{
  DEBUG ("check_PLL_clock_frequencies\n");

  // if both clocks are in use
  if (PLL_clocks[PLL_MCLK].in_use && PLL_clocks[PLL_VCLK].in_use)
    {
      // check whether the two chosen clocks are divisible by one another, in
      // which case print a warning.
      double multiplier = PLL_clocks[PLL_VCLK].actual_frequency /
	PLL_clocks[PLL_MCLK].actual_frequency;
      double modulus;

      if (multiplier < 1.00)
	multiplier = 1 / multiplier;

      modulus = multiplier - ((int) multiplier);

      // check also for near multiples
      if ((modulus < 0.02) || (modulus > 0.98))
	warning (_
		 ("PLL MCLK and PLL VCLK frequencies are (near) multiples of each other.\n"
		  "This may lead to clock degradation."));
    }
  else if (PLL_clocks[PLL_MCLK].in_use || PLL_clocks[PLL_VCLK].in_use)
    {
      MegaHertz requested_frequency;
      MegaHertz actual_frequency;
      PLL_ClockId clock;

      // if we now are only using one PLL clock then ensure that the second
      // clock's frequency is not a multiple of the first's (M == V is OK).

      if (PLL_clocks[PLL_MCLK].in_use)
	{
	  clock = PLL_VCLK;
	  actual_frequency = PLL_clocks[PLL_MCLK].actual_frequency;
	}
      else
	{
	  clock = PLL_MCLK;
	  actual_frequency = PLL_clocks[PLL_VCLK].actual_frequency;
	}

      if (actual_frequency < VCO_PRESET_BOUNDARIES[0])
	requested_frequency = actual_frequency * 1.43;
      else
	{
	  // frequency = actual_frequency * 0.70;
	  requested_frequency = actual_frequency;
	}

      if (!set_PLL_clock_frequency (clock, requested_frequency, TRUE, FALSE))
	(void) set_PLL_clock_frequency (clock, actual_frequency, TRUE, TRUE);
    }
}


static void
use_PLL_clock (GlobalClockId clockId, MegaHertz clockValue)
{
  PLL_ClockId PLL_clock_id = NO_PLL_CLK;
  PLL_ClockId free_PLL_clock_id = NO_PLL_CLK;
  unsigned int i;

  /* is this global clock not already using a PLL clock? */
  if (global_clocks[clockId].PLL_clock == NO_PLL_CLK)
    {
      // has this frequency already been assigned to a PLL clock?
      for (i = 0; i < ELEMENTS_IN_ARRAY (PLL_clocks); i++)
	{
	  PLL_Clock *clock = &PLL_clocks[i];

	  if (clock->in_use)
	    {
	      /* the actual frequency to which the clock is set may differ
	       * slightly from the frequency that was requested - so check
	       * both
	       */
	      if (clockValue == clock->requested_frequency ||
		  clockValue == clock->actual_frequency)
		{
		  PLL_clock_id = (PLL_ClockId) i;
		  break;
		}
	    }
	  else
	    {
	      /* use MCLK (first in array) in preference to VCLK */
	      if (free_PLL_clock_id == NO_PLL_CLK)
		free_PLL_clock_id = (PLL_ClockId) i;
	    }
	}
    }
  else
    {
      PLL_ClockId this_clock = global_clocks[clockId].PLL_clock;
      int users = 0;

      /* how many global clocks are using this PLL clock? */
      for (i = 0; i < ELEMENTS_IN_ARRAY (global_clocks); i++)
	{
	  if (global_clocks[i].PLL_clock == this_clock)
	    users++;
	}

      if (users == 1)
	{
	  /* just this one - so we can change its frequency without affecting
	   * any other global clocks
	   */
	  free_PLL_clock_id = this_clock;
	}
      else
	{
	  /* look at the other clock - if it is not already in use, we can use it */
	  PLL_ClockId other_clock =
	    (this_clock == PLL_MCLK) ? PLL_VCLK : PLL_MCLK;

	  if (!PLL_clocks[other_clock].in_use)
	    free_PLL_clock_id = other_clock;
	}
    }

  // do we need another PLL clock?
  if (PLL_clock_id == NO_PLL_CLK)
    {
      // if so, and there aren't any which are not in use
      if (free_PLL_clock_id == NO_PLL_CLK)
	{
	  MegaHertz M_delta =
	    fabs (PLL_clocks[PLL_MCLK].actual_frequency - clockValue);
	  MegaHertz V_delta =
	    fabs (PLL_clocks[PLL_VCLK].actual_frequency - clockValue);

	  /* which clock has the closet frequency to what we want? */
	  PLL_clock_id = (M_delta <= V_delta) ? PLL_MCLK : PLL_VCLK;

	  warning (_("Can not set GCLK%d to %.2lf MHz: "
		     "there are no more PLL clocks available.\n"
		     "Using closest match instead (%s @ %.2lf MHz)."),
		   clockId, clockValue,
		   PLL_clock_info[PLL_clock_id].name,
		   PLL_clocks[PLL_clock_id].actual_frequency);
	}
      else
	{
	  // otherwise, use a free PLL clock
	  PLL_clock_id = free_PLL_clock_id;

	  if (set_PLL_clock_frequency (PLL_clock_id, clockValue, TRUE, TRUE))
	    {
	      PLL_clocks[PLL_clock_id].in_use = TRUE;
	      check_PLL_clock_frequencies ();
	    }
	}
    }

  global_clocks[clockId].PLL_clock = PLL_clock_id;
  global_clocks[clockId].source =
    (PLL_clock_id == PLL_MCLK) ? CLOCK_SOURCE_PLL_MCLK : CLOCK_SOURCE_PLL_VCLK;
  global_clocks[clockId].set = TRUE;
}


static void
set_global_clock (GlobalClockId clockId, const char *clockData)
{
  static const struct table_entry
  {
    ClockSource source;
    PLL_ClockId clock;
    const char *name;
    int harvard;
  } table[] =
  {
    {
    CLOCK_SOURCE_CRYSTAL, NO_PLL_CLK, "crystal", FALSE},
    {
    CLOCK_SOURCE_CRYSTAL_DIVIDED, NO_PLL_CLK, "dips", FALSE},
    {
    CLOCK_SOURCE_HIGH_IMPEDANCE, NO_PLL_CLK, "highimp", FALSE},
    {
    CLOCK_SOURCE_HOST_STROBE, NO_PLL_CLK, "host", FALSE},
    {
    CLOCK_SOURCE_PLL_MCLK_HARVARD, PLL_MCLK, "mclk", TRUE},
    {
    CLOCK_SOURCE_PLL_VCLK_HARVARD, PLL_MCLK, "vclk", TRUE},
    {
    CLOCK_SOURCE_PLL_MCLK, PLL_MCLK, "mclk", FALSE},
    {
  CLOCK_SOURCE_PLL_VCLK, PLL_VCLK, "vclk", FALSE}};

  MegaHertz clockValue;
  unsigned int i;

  for (i = 0; i < ELEMENTS_IN_ARRAY (table); i++)
    {
      const struct table_entry *entry = &table[i];

      if (strcasecmp (clockData, entry->name) == 0)
	{
	  /* N.B. the order of the entries in the table is important! */
	  if (entry->harvard && !harvard)
	    continue;

	  global_clocks[clockId].source = entry->source;
	  global_clocks[clockId].PLL_clock = entry->clock;
	  global_clocks[clockId].set = TRUE;

	  if ((clockId == 3) && (entry->source == CLOCK_SOURCE_HIGH_IMPEDANCE))
	    warning (_
		     ("GCLK3 must be valid in order for the ARC processor's debug interface to interact with the processor."));
	  else if ((clockId == 2)
		   && (entry->source != CLOCK_SOURCE_HOST_STROBE))
	    warning (_
		     ("GCLK2 must be %s for JTAG clock to be connected to the ARC processor's debug interface."),
		     CLOCK_SOURCE_STRINGS[CLOCK_SOURCE_HOST_STROBE]);
	  return;
	}
    }

  if (clockId == 2)
    warning (_
	     ("GCLK2 must be %s for JTAG clock to be connected to the ARC processor's debug interface."),
	     CLOCK_SOURCE_STRINGS[CLOCK_SOURCE_HOST_STROBE]);

  if (sscanf (clockData, "%lf", &clockValue) == 1)
    {
      use_PLL_clock (clockId, clockValue);
      return;
    }

  warning (_("'%s' is not a valid source for clock %d\n"), clockData, clockId);
}


static void
enable_Harvard_clock (void)
{
  // Does GCLK3 come from the PLL?
  if (global_clocks[3].PLL_clock != NO_PLL_CLK)
    {
      // save existing settings
      const PLL_ClockId saved_clock[] = { global_clocks[0].PLL_clock,
	global_clocks[1].PLL_clock,
	global_clocks[2].PLL_clock,
	global_clocks[3].PLL_clock
      };
      const MegaHertz saved_value[] = { PLL_clocks[PLL_MCLK].actual_frequency,
	PLL_clocks[PLL_VCLK].actual_frequency
      };
      GlobalClockId clockId;

      printf_filtered ("Configuring clocks to drive Harvard Ctl_Clk.\n");

      reset_clock_configuration ();
      harvard = TRUE;

      // Now re-assign the Harvard inputs and double the requested frequency
      use_PLL_clock (3, 2 * saved_value[saved_clock[3]]);

      // Now ensure GCLK3 is configured as a Harvard generator
      if (saved_clock[3] == PLL_MCLK)
	global_clocks[3].source = CLOCK_SOURCE_PLL_MCLK_HARVARD;
      else
	global_clocks[3].source = CLOCK_SOURCE_PLL_VCLK_HARVARD;

      // re-assign any existing PLL clocks
      for (clockId = 0; clockId < 3; clockId++)
	{
	  if (saved_clock[clockId] != NO_PLL_CLK)
	    use_PLL_clock (saved_clock[clockId],
			   saved_value[saved_clock[clockId]]);
	}
    }
}


static void
print_clock_settings (int with_PLL_clocks,
		      int with_global_only_if_using_PLL)
{
  int with_global_clocks = TRUE;
  unsigned int i;

  if (with_global_only_if_using_PLL)
    {
      with_global_clocks = FALSE;

      for (i = 0; i < ELEMENTS_IN_ARRAY (global_clocks); i++)
	{
	  if (global_clocks[i].PLL_clock != NO_PLL_CLK)
	    {
	      with_global_clocks = TRUE;
	      break;
	    }
	}
    }

  if (with_PLL_clocks)
    {
      printf_filtered (_("PLL clock %s : %.2lf MHz.\n"),
		       PLL_clock_info[PLL_MCLK].name,
		       PLL_clocks[PLL_MCLK].actual_frequency);
      printf_filtered (_("PLL clock %s : %.2lf MHz.\n"),
		       PLL_clock_info[PLL_VCLK].name,
		       PLL_clocks[PLL_VCLK].actual_frequency);
    }

  if (with_global_clocks)
    {
      for (i = 0; i < ELEMENTS_IN_ARRAY (global_clocks); i++)
	{
	  GlobalClock clock = global_clocks[i];
	  const char *format = "GCLK%d   <<   %s @ %.2lf MHz\n";
	  const char *source;
	  MegaHertz value;

	  switch (clock.source)
	    {
	    case CLOCK_SOURCE_PLL_MCLK:
	      source = CLOCK_SOURCE_STRINGS[clock.source];
	      value = PLL_clocks[PLL_MCLK].actual_frequency;
	      break;

	    case CLOCK_SOURCE_PLL_VCLK:
	      source = CLOCK_SOURCE_STRINGS[clock.source];
	      value = PLL_clocks[PLL_VCLK].actual_frequency;
	      break;

	    case CLOCK_SOURCE_PLL_MCLK_HARVARD:
	      source = GCLOCK3_SOURCE_STRINGS[clock.source];
	      value = PLL_clocks[PLL_MCLK].actual_frequency / 2.0;
	      break;

	    case CLOCK_SOURCE_PLL_VCLK_HARVARD:
	      source = GCLOCK3_SOURCE_STRINGS[clock.source];
	      value = PLL_clocks[PLL_VCLK].actual_frequency / 2.0;
	      break;

	    default:
	      format = "GCLK%d   <<   %s\n";
	      source =
		((i ==
		  3) ? GCLOCK3_SOURCE_STRINGS :
		 CLOCK_SOURCE_STRINGS)[clock.source];
	      value = 0.0;
	      break;
	    }

	  printf_filtered (format, i, source, value);
	}
    }
}


static void
set_PLL_clocks (MegaHertz requested_MCLK_frequency,
		MegaHertz requested_VCLK_frequency)
{
  DEBUG ("set_PLL_clocks: MCLK = %.2lf MHz, VCLK = %.2lf MHz\n",
	 requested_MCLK_frequency, requested_VCLK_frequency);

  // configure PLL clocks

  if (requested_MCLK_frequency != UNDEFINED_FREQUENCY)
    {
      if (set_PLL_clock_frequency
	  (PLL_MCLK, requested_MCLK_frequency, TRUE, TRUE))
	PLL_clocks[PLL_MCLK].in_use = TRUE;
    }

  if (requested_VCLK_frequency != UNDEFINED_FREQUENCY)
    {
      if (set_PLL_clock_frequency
	  (PLL_VCLK, requested_VCLK_frequency, TRUE, TRUE))
	PLL_clocks[PLL_VCLK].in_use = TRUE;
    }
}


#define FREQUENCY(clock)    ((PLL_clocks[clock].in_use) ? PLL_clocks[clock].requested_frequency : UNDEFINED_FREQUENCY)

static void
program_clock_settings (const char *message, int after_blast)
{
  unsigned int i;

  /* if the FPG has been blasted, configure the PLL clocks */
  if (after_blast)
    set_PLL_clocks (FREQUENCY (PLL_MCLK), FREQUENCY (PLL_VCLK));

  /* do any of the clocks need to be set? */
  for (i = 0; i < ELEMENTS_IN_ARRAY (global_clocks); i++)
    {
      if (global_clocks[i].set)
	{
	  // print status message only if there is something to be done
	  printf_filtered ("%s\n", message);

	  if (harvard)
	    enable_Harvard_clock ();

	  configure_CPLD ();

	  print_clock_settings (after_blast, FALSE);
	  break;
	}
    }

  /* reset the JTAG Test Access Port Controller */
  arc_jtag_ops.reset ();
}


/* -------------------------------------------------------------------------- */
/*                      local functions implementing commands                 */
/* -------------------------------------------------------------------------- */

/* Command: <command> [ <clock> = ] <frequency> [ , <frequency> ]
 *
 * Set the frequency of one or both PLL clocks.
 */
static void
arc_set_clock_frequency (char *args, int from_tty)
{
  MegaHertz MCLK_frequency = UNDEFINED_FREQUENCY;
  MegaHertz VCLK_frequency = UNDEFINED_FREQUENCY;
  int result;
  char *value;

  if (args == NULL)
    {
      printf_filtered (_(ARC_SET_CLOCK_FREQUENCY_COMMAND_USAGE));
      return;
    }

  result = pair (args, &value);

  if (result == 0)
    {
      printf_filtered (_(ARC_SET_CLOCK_FREQUENCY_COMMAND_USAGE));
      return;
    }

  /* check that the JTAG interface (which opens the GPIO driver) is open */
  arc_jtag_ops.check_open ();

  if (result == 1)
    {
      char *comma = strchr (args, ',');

      if (comma)
	{
	  *comma = '\0';
	  MCLK_frequency = strtod (args, NULL);
	  VCLK_frequency = strtod (comma + 1, NULL);
	}
      else
	MCLK_frequency = strtod (args, NULL);

    }
  else if (result == 2)
    {
      char *comma = strchr (value, ',');

      if (comma)
	{
	  printf_filtered (_(ARC_SET_CLOCK_FREQUENCY_COMMAND_USAGE));
	  return;
	}

      if (strcasecmp (args, "mclk") == 0)
	MCLK_frequency = strtod (value, NULL);
      else if (strcasecmp (args, "vclk") == 0)
	VCLK_frequency = strtod (value, NULL);
      else
	{
	  warning (_("invalid PLL clock '%s'"), args);
	  return;
	}
    }

  /* strtod returns 0 for an invalid argument - and 0 is not a valid clock
   * frequency anyway!
   */
  if (MCLK_frequency == 0.0 || VCLK_frequency == 0.0)
    warning (_("invalid clock frequency"));
  else
    {
      DEBUG (_("MCLK : %.2lf MHz.\n"), MCLK_frequency);
      DEBUG (_("VCLK : %.2lf MHz.\n"), VCLK_frequency);

      set_PLL_clocks (MCLK_frequency, VCLK_frequency);
      check_PLL_clock_frequencies ();
      print_clock_settings (FALSE, TRUE);

      /* reset the JTAG Test Access Port Controller */
      arc_jtag_ops.reset ();
    }
}


/* Command: <command> gclk<N> = <source>
 *                    gclk    = <source>
 *                    gclks   = <source> , { <source> }
 *                    harvard
 *
 * Set the source of one or more global clocks.
 */
static void
arc_set_clock_source (char *args, int from_tty)
{
  int invalid = FALSE;

  if (args)
    {
      int result;
      char *value;

      /* check that the JTAG interface (which opens the GPIO driver) is open */
      arc_jtag_ops.check_open ();

      result = pair (args, &value);

      if (result == 1)
	{
	  if (strcasecmp (args, "harvard") == 0)
	    harvard = TRUE;
	  else
	    invalid = TRUE;
	}
      else if (result == 2)
	{
	  char *key = args;

	  DEBUG ("key = %s, value = %s\n", key, value);

	  if (strncasecmp (key, "gclk", 4) == 0)
	    {
	      size_t keylength = strlen (key);

	      if (keylength == 4)
		set_global_clock (3, value);
	      else if (keylength == 5)
		{
		  if (key[4] == 's' || key[4] == 'S')
		    {
		      GlobalClockId clockId = 0;
		      char *clockData = strtok (value, " ,");

		      do
			{
			  if (clockId == NUM_GLOBAL_CLOCKS)
			    {
			      warning (_("too many clock sources specified"));
			      return;
			    }

			  set_global_clock (clockId++, clockData);
			  clockData = strtok (NULL, " ,");
			}
		      while (clockData != NULL);
		    }
		  else if ('0' <= key[4]
			   && key[4] < '0' + (char) NUM_GLOBAL_CLOCKS)
		    {
		      DEBUG ("gclkN found\n");
		      set_global_clock ((GlobalClockId) (key[4] - (char) '0'),
					value);
		    }
		  else
		    {
		      warning (_("'%c' is not a valid clock number"), key[4]);
		      return;
		    }
		}
	      else
		invalid = TRUE;
	    }
	  else
	    invalid = TRUE;
	}
      else
	invalid = TRUE;
    }
  else
    invalid = TRUE;

  if (invalid)
    printf_filtered (_(ARC_SET_CLOCK_SOURCE_COMMAND_USAGE));
  else
    program_clock_settings ("Attempting to set clocks.", FALSE);
}


static void
arc_print_clock_settings (char *args, int from_tty)
{
  if (args)
    {
      printf_filtered (_(ARC_CLOCK_SETTINGS_COMMAND_USAGE));
      return;
    }

  /* check that the JTAG interface (which opens the GPIO driver) is open */
  arc_jtag_ops.check_open ();

  print_clock_settings (TRUE, FALSE);
}


static void
arc_check_FPGA_configuration (char *args, int from_tty)
{
  if (args)
    {
      printf_filtered (_(ARC_FPGA_COMMAND_USAGE));
      return;
    }

  switch (arc_is_FPGA_configured ())
    {
    case INACCESSIBLE:
      break;
    case CONFIGURED:
      printf_filtered (_("FPGA is configured.\n"));
      break;
    case UNCONFIGURED:
      printf_filtered (_("FPGA is not configured.\n"));
      break;
    }
}


/* -------------------------------------------------------------------------- */
/*                               externally visible functions                 */
/* -------------------------------------------------------------------------- */

void
arc_blast_board (char *args, int from_tty)
{
  char *suffix;

  // check the file name is valid

  if (args == NULL)
    {
      printf_filtered (_(ARC_BLAST_BOARD_COMMAND_USAGE));
      return;
    }

  /* check that the JTAG interface (which opens the GPIO driver) is open */
  arc_jtag_ops.check_open ();

  suffix = strrchr (args, '.');

  // check the file is an .xbf

  if ((suffix != NULL) && (strcasecmp (suffix, ".xbf") == 0))
    {
      FILE *fp = fopen (args, "rb");

      if (fp)
	{
	  char *message = NULL;

	  if (initialize_FPGA ())
	    {
	      if (blast_FPGA (fp))
		{
		  unsigned int identity_regnum =
		    arc_aux_find_register_number ("IDENTITY",
						  ARC_HW_IDENTITY_REGNUM);

		  /* reset the JTAG Test Access Port Controller */
		  arc_jtag_ops.reset ();

		  /* we no longer know what the target processor is */
		  ARC_processor = NO_ARCHITECTURE;

		  /* so find it out again */
		  arc_update_architecture (identity_regnum);

		  /* and check that it matches the aux registers definition */
		  arc_check_architecture (current_gdbarch,
					  (current_objfile) ?
					  current_objfile->obfd : NULL);

		  program_clock_settings
		    ("Reconfiguring clock settings after FPGA blast.", TRUE);
		}
	      else
		message = _("can not blast FPGA");
	    }
	  else
	    message = _("can not initialize FPGA for blasting");

	  (void) fclose (fp);

	  if (message)
	    error ("%s", message);
	}
      else
	error ("Can not open file '%s': %s", args, strerror (errno));
    }
  else
    error
      ("Filename does not have suffix .xbf, so is presumably not an XBF file");
}


void
arc_reset_board (void)
{
  /* toggle the SS1 line - this should do a soft reset */

  write_control_port (SS1 | SS0 | CNT, 0);
  write_control_port (SS0 | CNT, 200);	// TBH 18 JUN 2003 delay needed by slower simulations
  write_control_port (SS1 | SS0 | CNT, 0);

  /* reset the PLL clocks and the global clock sources - this should be done
   * by the soft reset, but that does not appear to happen! 
   */
  reset_clock_configuration ();
  (void) set_PLL_clock_frequency (PLL_MCLK, MCLK_RESET_FREQUENCY, FALSE, FALSE);
  (void) set_PLL_clock_frequency (PLL_VCLK, VCLK_RESET_FREQUENCY, FALSE, FALSE);
  configure_CPLD ();
}


/* Check whether the FPGA has been configured (i.e. blasted with an XBF) */
FPGA_Status
arc_is_FPGA_configured (void)
{
  FPGA_Status result;

  ENTERMSG;

  /* try to open the JTAG interface (which opens the GPIO driver) */
  if (arc_jtag_ops.open ())
    {
      // get the current state of the control register
      Byte origCTRL = gpio_read (CONTROL_PORT) ^ C_XOR;
      Byte newCTRL;
      Byte status;

      // If SS0 is low, bring this high first (to protect against reset)
      if (SS0 != (origCTRL & SS0))
	{
	  // Output new control state
	  newCTRL = (origCTRL | SS0);
	  write_control_port (newCTRL, 1);
	}

      // Ensure that SS0 is high, and SS1 and CNT are low
      newCTRL = (origCTRL | SS0) & 0xF5;	// 11110101
      newCTRL = newCTRL | BI;
      write_control_port (newCTRL, 1);

      // Read the OP input
      status = read_status_port ();

      // If SS1 was originally high then bring high now (to protect against reset)
      if (SS1 == (origCTRL & SS1))
	{
	  // Output new control state (Gray code transition)
	  newCTRL = (origCTRL | SS1);
	  write_control_port (newCTRL, 1);
	}

      // restore the control register
      write_control_port (origCTRL, 1);

      /* reset the JTAG Test Access Port Controller */
      arc_jtag_ops.reset ();

      result = IS_SET (FPA_CFG_DONE, status) ? CONFIGURED : UNCONFIGURED;
    }
  else
    result = INACCESSIBLE;

  LEAVEMSG;
  return result;
}


void
_initialize_arc_board (void)
{
  struct cmd_list_element *c;

  reset_clock_configuration ();

  // add support for blasting an FPGA board (ARCangel)
  c = add_cmd (ARC_BLAST_BOARD_COMMAND,
	       class_obscure,
	       arc_blast_board,
	       _("Blast the ARC board FPGA.\n"
		 ARC_BLAST_BOARD_COMMAND_USAGE
		 "<FILE> is the filepath of an XBF (eXtended Binary Format) file.\n"),
	       &cmdlist);
  set_cmd_completer (c, filename_completer);

  // add support for setting the CPU clock frequency
  (void) add_cmd (ARC_SET_CLOCK_FREQUENCY_COMMAND,
		  class_obscure,
		  arc_set_clock_frequency,
		  _("Set the PLL frequency on the ARC board.\n"
		    ARC_SET_CLOCK_FREQUENCY_COMMAND_USAGE
		    "<CLOCK> is 'mclk' or 'vclk'; if omitted, and only one frequency is given, it defaults to 'mclk'.\n"
		    "<FREQUENCY> is a number (interpreted as MegaHertz).\n"),
		  &cmdlist);

  // add support for setting the CPU clock sources
  (void) add_cmd (ARC_SET_CLOCK_SOURCE_COMMAND,
		  class_obscure,
		  arc_set_clock_source,
		  _("Set the clock sources on the ARC board.\n"
		    ARC_SET_CLOCK_SOURCE_COMMAND_USAGE
		    "N is in the range 0 .. 3; if omitted, it defaults to 3.\n"
		    "<SOURCE> is 'crystal', 'dips', 'highimp', 'host', 'mclk', 'vclk' or a number (interpreted as MegaHertz). \n"),
		  &cmdlist);

  (void) add_cmd (ARC_CLOCK_SETTINGS_COMMAND,
		  class_info,
		  arc_print_clock_settings,
		  _("Show the clock settings on the ARC board.\n"
		    ARC_CLOCK_SETTINGS_COMMAND_USAGE), &infolist);

  // add support for checking whether the FPGA board has been configured
  (void) add_cmd (ARC_FPGA_COMMAND,
		  class_info,
		  arc_check_FPGA_configuration,
		  _("Check ARC board FPGA configuration.\n"
		    ARC_FPGA_COMMAND_USAGE), &infolist);
}

/******************************************************************************/
