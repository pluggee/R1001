/*
 * drv8825.c
 *
 *  Created on: Sep 8, 2016
 *      Author: sherifeid
 */

#include "drv8825.h"
#include <SI_EFM8BB1_Register_Enums.h>                  // SFR declarations
#include "compiler_defs.h"
#include <intrins.h>

// This source includes all control functions for DRV8825 chip

//-----------------------------------------------------------------------------
// DRV8825 Pin Declarations
//-----------------------------------------------------------------------------

SBIT(DRESETB, SFR_P0, 5);            					// Driver reset pin
SBIT(DSLEEPB, SFR_P0, 6);            					// Driver sleep pin
SBIT(DECAY, SFR_P1, 0);            						// Driver decay pin
SBIT(MODE0, SFR_P1, 1);            						// Driver mode0 pin
SBIT(MODE1, SFR_P1, 2);            						// Driver mode1 pin
SBIT(MODE2, SFR_P1, 3);            						// Driver mode2 pin


void SetDecayFast (void)
{
	// This function sets the decay mode to fast decay
	DECAY = 1;				// set to fast decay
}

void ResetDriver (void)
{
	unsigned i; 	// for loop variable
	// Reset pulse for the motor driver
	DRESETB = 0;			// set resetb to 0, get driver into reset
	for (i=0; i<10000; i++)
	{
		_nop_ ();			// assembly NOP
	}
	DRESETB = 1;			// set resetb to 1, get driver out of reset
	DSLEEPB = 1;			// get driver out of sleep mode
}

void SetSteppingMode (unsigned char steps)
{
	// this function assigns stepping modes
	// steps	: stepping resolution in power of 2, stepping = 2^steps
	// example, if steps = 4, stepping to 1/16
	// if the input value of 'steps' in invalid (no 1,2,4,8,16,32) then it defaults to 1/32
	switch(steps) {
	case 0:
		MODE0 = 0;
		MODE1 = 0;
		MODE2 = 0;
		break;
	case 1:
		MODE0 = 1;
		MODE1 = 0;
		MODE2 = 0;
		break;
	case 2:
		MODE0 = 0;
		MODE1 = 1;
		MODE2 = 0;
		break;
	case 3:
		MODE0 = 1;
		MODE1 = 1;
		MODE2 = 0;
		break;
	case 4:
		MODE0 = 0;
		MODE1 = 0;
		MODE2 = 1;
		break;
	default :
		// defaults to 1/32
		MODE0 = 1;
		MODE1 = 0;
		MODE2 = 1;
	}
}
